#include <qttasks.h>
#include "ui_nGanttTriggers.h"

#pragma message("GanttTriggers requires a group re-organize")

N::GanttTriggers:: GanttTriggers (QWidget * parent,Plan * p)
                 : Widget        (          parent,       p)
                 , ui            (new Ui::nGanttTriggers   )
                 , Gantt         (NULL                     )
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

N::GanttTriggers::~GanttTriggers (void)
{
  delete ui ;
}

void N::GanttTriggers::Prepare (void)
{
  ui -> Start  -> clear   (        )           ;
  ui -> Finish -> clear   (        )           ;
  ui -> Start  -> addItem ( "" , 0 )           ;
  ui -> Finish -> addItem ( "" , 0 )           ;
  SqlConnection SC ( plan->sql )               ;
  if (SC.open("nGanttTriggers::Prepare"))      {
    SUID    uuid                               ;
    UUIDs   Uuids                              ;
    SUID    strig = 0                          ;
    SUID    ftrig = 0                          ;
    QString Q                                  ;
    Uuids = SC.Uuids                           (
      PlanTable(Triggers)                      ,
      "uuid","order by id asc"               ) ;
    foreach (uuid,Uuids)                       {
      QString name                             ;
      name = SC.getName                        (
         PlanTable(Names)                      ,
         "uuid",vLanguageId,uuid             ) ;
      ui -> Start  -> addItem ( name , uuid  ) ;
      ui -> Finish -> addItem ( name , uuid  ) ;
    }                                          ;
    Q = SC.sql.SelectFrom("second"             ,
        PlanTable(Groups)                      ,
          QString("where first = %1"
                  " and t1 = %2"
                  " and t2 = %3"
                  " and relation = %4"         )
            .arg(Gantt->Uuid                   )
            .arg(Types::Schedule     )
            .arg(Types::Trigger      )
            .arg(Groups::StartTrigger)
        )                                      ;
    if (SC.Fetch(Q)) strig = SC.Uuid(0)        ;
    Q = SC.sql.SelectFrom("second"             ,
        PlanTable(Groups)                      ,
          QString("where first = %1"
                  " and t1 = %2"
                  " and t2 = %3"
                  " and relation = %4"         )
            .arg(Gantt->Uuid                   )
            .arg(Types::Schedule     )
            .arg(Types::Trigger      )
            .arg(Groups::FinalTrigger)
        )                                      ;
    if (SC.Fetch(Q)) ftrig = SC.Uuid(0)        ;
    if (strig>0) (*ui->Start ) <= strig        ;
    if (ftrig>0) (*ui->Finish) <= ftrig        ;
    SC.close()                                 ;
  }                                            ;
  SC.remove()                                  ;
}

void N::GanttTriggers::Done (void)
{
  SUID strig = N::GetUuid(ui->Start )                    ;
  SUID ftrig = N::GetUuid(ui->Finish)                    ;
  SqlConnection SC(plan->sql)                            ;
  if (SC.open("nGanttTriggers::Done"))                   {
    QString Q                                            ;
    Q = SC.sql.DeleteFrom                                (
          PlanTable(Groups)                              ,
            QString("where first = %1 "
                    "and t1 = %2 "
                    "and t2 = %3 "
                    "and relation = %4"                  )
            .arg(Gantt->Uuid                             )
            .arg(Types::Schedule                         )
            .arg(Types::Trigger                          )
            .arg(Groups::StartTrigger                    )
        )                                                ;
    SC . Query ( Q )                                     ;
    Q = SC.sql.DeleteFrom                                (
          PlanTable(Groups)                              ,
            QString("where first = %1 "
                    "and t1 = %2 "
                    "and t2 = %3 "
                    "and relation = %4"                  )
            .arg(Gantt->Uuid                             )
            .arg(Types::Schedule                         )
            .arg(Types::Trigger                          )
            .arg(Groups::FinalTrigger                    )
        )                                                ;
    SC.Query(Q)                                          ;
    if (strig>0)                                         {
      Q = SC.sql.InsertInto                              (
            PlanTable(Groups)                            ,
            5,"first","second","t1","t2","relation")     ;
      SC.Prepare(Q                                     ) ;
      SC.Bind   ("first",Gantt->Uuid                   ) ;
      SC.Bind   ("second",strig                        ) ;
      SC.Bind   ("t1",Types::Schedule                  ) ;
      SC.Bind   ("t2",Types::Trigger                   ) ;
      SC.Bind   ("relation",Groups::StartTrigger       ) ;
      SC.Exec   (                                      ) ;
    }                                                    ;
    if (ftrig>0) {
      Q = SC.sql.InsertInto                              (
                  PlanTable(Groups)                      ,
                5,"first","second","t1","t2","relation") ;
      SC.Prepare(Q                                     ) ;
      SC.Bind   ("first",Gantt->Uuid                   ) ;
      SC.Bind   ("second",ftrig                        ) ;
      SC.Bind   ("t1",Types::Schedule                  ) ;
      SC.Bind   ("t2",Types::Trigger                   ) ;
      SC.Bind   ("relation",Groups::FinalTrigger       ) ;
      SC.Exec   (                                      ) ;
    }                                                    ;
  }                                                      ;
  SC   . remove ( )                                      ;
  emit GanttChanged ( Gantt )                            ;
  emit Finish       (       )                            ;
}

void N::GanttTriggers::Cancel (void)
{
  emit Finish ( ) ;
}

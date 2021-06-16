#include <qttasks.h>
#include "ui_NotifierTrigger.h"

#pragma message("NotifierTrigger is incompleted")

N::NotifierTrigger:: NotifierTrigger ( QWidget * parent , Plan * p )
                   : Widget          (           parent ,        p )
                   , TaskManager     (                           p )
                   , ui              ( new Ui::NotifierTrigger     )
                   , Uuid            ( 0                           )
{
  ui -> setupUi ( this ) ;
}

N::NotifierTrigger::~NotifierTrigger (void)
{
  delete ui ;
}

typedef struct {
  SUID Music   ;
} NtPacket     ;

void N::NotifierTrigger::load(SUID uuid)
{
  ui->MusicBox->clear()                           ;
  EnterSQL ( SC , plan->sql )                     ;
    QString Q                                     ;
    SUID    auid                                  ;
    UUIDs   Uuids = SC.Uuids                      (
           PlanTable(Audios)                      ,
            "uuid","order by id asc"            ) ;
    foreach (auid,Uuids)                          {
      QString name = SC.getName                   (
        PlanTable(Names)                          ,
        "uuid"                                    ,
        vLanguageId                               ,
        auid                                    ) ;
      ui->MusicBox->addItem(name,auid)            ;
    }                                             ;
    Q = SC.sql.SelectFrom( "identifier,paraments" ,
         PlanTable(Triggers)                      ,
         SC.WhereUuid(uuid)                     ) ;
    if (SC.Fetch(Q))                              {
      QString    name                             ;
      QString    identifier = SC . String    (0)  ;
      QByteArray MID        = SC . ByteArray (1)  ;
      ui->IdEdit  ->setText ( identifier        ) ;
      name = SC.getName                           (
        PlanTable(Names)                          ,
        "uuid",vLanguageId,uuid                 ) ;
      ui->NameEdit->setText ( name              ) ;
      if (MID.size()==sizeof(SUID))               {
        NtPacket * np = (NtPacket *)MID.data()    ;
        *(ui->MusicBox) <= np->Music              ;
      }                                           ;
    }                                             ;
    Uuid = uuid                                   ;
  LeaveSQL ( SC , plan->sql )                     ;
}

void N::NotifierTrigger::Done (void)
{
  EnterSQL ( SC , plan->sql )                              ;
    QString    Q                                           ;
    QString    Name     = ui->NameEdit->text()             ;
    QString    ID       = ui->IdEdit  ->text()             ;
    QString    Style    = "Notifier"                       ;
    QString    Executor = "Panel"                          ;
    QByteArray BA                                          ;
    NtPacket   NP                                          ;
    int        index = ui->MusicBox->currentIndex()        ;
    NP.Music = ui->MusicBox->itemData(index).toULongLong() ;
    BA.resize(sizeof(NtPacket))                            ;
    memcpy(BA.data(),&NP,sizeof(NtPacket))                 ;
    Q = SC.sql.Update                                      (
          PlanTable(Triggers)                              ,
          "where uuid = :UUID"                             ,
          4,"identifier","style","executor","paraments"  ) ;
    SC . Prepare ( Q                                     ) ;
    SC . Bind    ( "uuid"       , Uuid                   ) ;
    SC . Bind    ( "identifier" , ID.toUtf8()            ) ;
    SC . Bind    ( "style"      , Style.toUtf8()         ) ;
    SC . Bind    ( "executor"   , Executor.toUtf8()      ) ;
    SC . Bind    ( "paraments"  , BA                     ) ;
    SC . Exec    (                                       ) ;
  LeaveSQL ( SC , plan->sql )                              ;
  emit Finish()                                            ;
}

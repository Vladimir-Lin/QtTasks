#include <qttasks.h>

N::ExecutionView:: ExecutionView (QWidget * parent,Plan * p)
                 : IconDock      (          parent,       p)
{
  Configure ( ) ;
}

N::ExecutionView::~ExecutionView (void)
{
}

QSize N::ExecutionView::sizeHint (void) const
{
  if (plan->Booleans["Phone"]) {
    return QSize ( 320 , 320 ) ;
  }                            ;
  return   QSize ( 640 , 640 ) ;
}

void N::ExecutionView::Configure(void)
{
  setWindowTitle               ( tr("Execution lists") ) ;
  setViewMode                  ( IconMode              ) ;
  setIconSize                  ( QSize(128,128)        ) ;
  setGridSize                  ( QSize(140,192)        ) ;
  setDragDropMode              ( NoDragDrop            ) ;
  setResizeMode                ( QListView::Adjust     ) ;
  setWordWrap                  ( true                  ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded ) ;
  setMinimumSize               ( QSize(172,192)        ) ;
  MountCommands                (                       ) ;
  plan->setFont                ( this                  ) ;
}

bool N::ExecutionView::FocusIn(void)
{
  nKickOut     ( IsNull(plan) , false    ) ;
  AssignAction ( Label   , windowTitle() ) ;
  LinkAction   ( Refresh , startup    () ) ;
  LinkAction   ( Insert  , New        () ) ;
  return true                              ;
}

bool N::ExecutionView::startup(void)
{
  nKickOut ( IsNull(plan) , false ) ;
  clear    (                      ) ;
  List     (                      ) ;
  return true                       ;
}

void N::ExecutionView::List(void)
{
  setToolTip  ( tr("Reading executions...") )                      ;
  setEnabled  ( false                       )                      ;
  emit OnBusy (                             )                      ;
  Bustle      (                             )                      ;
  SqlConnection SC(plan->sql)                                      ;
  PictureManager PM ( plan )                                       ;
  if ( SC . open ( "ExecutionView::List" ) )                       {
    UUIDs   Uuids = SC.Uuids                                       (
                      PlanTable(Executions)                        ,
                      "uuid"                                       ,
                      SC . OrderByAsc ( "id" )                   ) ;
    SUID    u                                                      ;
    QString Q                                                      ;
    foreach (u,Uuids)                                              {
      QListWidgetItem * lwi                                        ;
      SUID              puid                                       ;
      QString name = SC.getName                                    (
                       PlanTable(Names)                            ,
                       "uuid"                                      ,
                       vLanguageId                                 ,
                       u                                         ) ;
      Q = SC.sql.SelectFrom                                        (
            "icon"                                                 ,
            PlanTable(Executions)                                  ,
            SC.WhereUuid(u)                                      ) ;
      if (SC.Fetch(Q)) puid = SC.Uuid(0)                           ;
      lwi = addItem ( u , name , QIcon(":/images/execution.png") ) ;
      if (puid>0)                                                  {
        QImage        * Thumb = NULL                               ;
        Thumb = PM.Thumb( SC , puid )                              ;
        if (NotNull(Thumb))                                        {
          QSize is = iconSize()                                    ;
          QIcon ic = PM . Icon ( Thumb , is )                      ;
          delete Thumb                                             ;
          lwi->setIcon(ic)                                         ;
        }                                                          ;
      }                                                            ;
    }                                                              ;
    SC . close   (       )                                         ;
  } else                                                           {
    plan->showMessage(tr("Database can not be connected"))         ;
    SC . close   (       )                                         ;
  }                                                                ;
  SC . remove    (       )                                         ;
  emit GoRelax   (       )                                         ;
  Vacancy        (       )                                         ;
  reportItems    (       )                                         ;
  setEnabled     ( true  )                                         ;
}

void N::ExecutionView::New(void)
{
  emit Append ( ) ;
}

bool N::ExecutionView::Menu(QPoint pos)
{
  nScopedMenu ( mm , this )                                        ;
  //////////////////////////////////////////////////////////////////
  QListWidgetItem * item = itemAt(pos)                             ;
  SUID              uuid = 0                                       ;
  QString           name = ""                                      ;
  QAction         * a    = NULL                                    ;
  QMenu           * me   = NULL                                    ;
  QMenu           * mi   = NULL                                    ;
  QMenu           * mn   = NULL                                    ;
  QMenu           * ms   = NULL                                    ;
  //////////////////////////////////////////////////////////////////
  mm.add(101,tr("Refresh"      ))                                  ;
  mm.addSeparator()                                                ;
  mm.add(102,tr("New execution"))                                  ;
  if (NotNull(item))                                               {
    uuid = nListUuid ( item )                                      ;
    mm.add(103,tr("Edit"))                                         ;
  }                                                                ;
      mm . setFont ( plan )                                        ;
  a = mm . exec    (      )                                        ;
  nKickOut ( IsNull(a) , false )                                   ;
  //////////////////////////////////////////////////////////////////
  switch (mm[a])                                                   {
    case 101                                                       :
      startup       (                    )                         ;
    break                                                          ;
    case 102                                                       :
      emit Append   (                    )                         ;
    break                                                          ;
    case 103                                                       :
      emit Command  ( this , name , uuid )                         ;
    break                                                          ;
  }                                                                ;
  return true                                                      ;
}

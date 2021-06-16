#include <qttasks.h>

#define TABLES(ID) plan->Tables[Tables::ID]

N::ExecutionLists:: ExecutionLists (QWidget * parent,Plan * p)
                  : TreeDock       (          parent,       p)
{
  Configure ( ) ;
}

N::ExecutionLists::~ExecutionLists(void)
{
}

QMimeData * N::ExecutionLists::dragMime (void)
{
  QTreeWidgetItem * IT = currentItem()        ;
  if (IsNull(IT)) return NULL                 ;
  SUID  uuid  = nTreeUuid(IT,0)               ;
  QMimeData * mime = new QMimeData()          ;
  setMime ( mime , "execution/uuid"  , uuid ) ;
  mime -> setText ( IT -> text ( 0 )        ) ;
  return mime                                 ;
}

bool N::ExecutionLists::hasItem(void)
{
  QTreeWidgetItem * item = currentItem () ;
  return NotNull ( item )                 ;
}

bool N::ExecutionLists::startDrag(QMouseEvent * event)
{
  QTreeWidgetItem * atItem = itemAt(event->pos())            ;
  if (IsNull(atItem)) return false                           ;
  if (!IsMask(event->buttons(),Qt::LeftButton)) return false ;
  dragPoint = event->pos()                                   ;
  if (!atItem->isSelected()) return false                    ;
  if (!PassDragDrop) return true                             ;
  return true                                                ;
}

bool N::ExecutionLists::fetchDrag(QMouseEvent * event)
{
  if (!IsMask(event->buttons(),Qt::LeftButton)) return false   ;
  QPoint pos = event->pos()                                    ;
  pos -= dragPoint                                             ;
  return ( pos.manhattanLength() > qApp->startDragDistance() ) ;
}

void N::ExecutionLists::dragDone(Qt::DropAction dropIt,QMimeData * mime)
{
}

bool N::ExecutionLists::finishDrag(QMouseEvent * event)
{
  return true   ;
}

void N::ExecutionLists::Configure(void)
{
  NewTreeWidgetItem            ( head                  ) ;
  head -> setText              ( 0 , tr("Execution")   ) ;
  setWindowTitle               ( tr("Execution lists") ) ;
  setDragDropMode              ( DragOnly              ) ;
  setRootIsDecorated           ( false                 ) ;
  setAlternatingRowColors      ( true                  ) ;
  setSelectionMode             ( SingleSelection       ) ;
  setColumnCount               ( 1                     ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded ) ;
  assignHeaderItems            ( head                  ) ;
  plan -> setFont              ( this                  ) ;
  MountClicked                 ( 2                     ) ;
  PassDragDrop = false                                   ;
}

bool N::ExecutionLists::FocusIn(void)
{
  nKickOut          ( IsNull(plan) , false           ) ;
  DisableAllActions (                                ) ;
  AssignAction      ( Label        , windowTitle ( ) ) ;
  LinkAction        ( Rename       , Rename      ( ) ) ;
  LinkAction        ( Copy         , Copy        ( ) ) ;
  LinkAction        ( Font         , setFont     ( ) ) ;
  LinkAction        ( Refresh      , startup     ( ) ) ;
  LinkAction        ( Start        , Execution   ( ) ) ;
  return true                                          ;
}

bool N::ExecutionLists::Menu(QPoint pos)
{
  nScopedMenu ( mm , this )                                        ;
  QTreeWidgetItem * IT = currentItem()                             ;
  QAction         * aa                                             ;
  nIfSafe(IT) mm . add ( 201 , tr("Execution")                   ) ;
  nIfSafe(IT) mm . add ( 101 , tr("Edit"     )                   ) ;
  mm . add ( 102 , tr("Refresh") )                                 ;
  DockingMenu ( mm )                                               ;
  mm . setFont ( plan )                                            ;
  aa = mm . exec ( )                                               ;
  if ( IsNull     (      aa ) ) return true                        ;
  if ( RunDocking ( mm , aa ) ) return true                        ;
  switch ( mm [ aa ] )                                             {
    case     101                                                   :
      if (NotNull(IT))                                             {
        SUID uuid = nTreeUuid ( IT , 0 )                           ;
        if (uuid>0)                                                {
          emit Edit ( this , IT -> text ( 0 ) , uuid )             ;
        }                                                          ;
      }                                                            ;
    break                                                          ;
    case 102                                                       :
      startup   ( )                                                ;
    break                                                          ;
    case 201                                                       :
      Execution ( )                                                ;
    break                                                          ;
    default                                                        :
    break                                                          ;
  }                                                                ;
  return true                                                      ;
}

bool N::ExecutionLists::startup(void)
{
  clear (       ) ;
  start ( 10001 ) ;
  return true     ;
}

void N::ExecutionLists::run(int Type,ThreadData * data)
{
  switch ( Type ) {
    case 10001    :
      List ( )    ;
    break         ;
  }               ;
}

void N::ExecutionLists::List(void)
{
  TreeWidgetItems Items                           ;
  emit OnBusy ( )                                 ;
  EnterSQL ( SC , plan->sql )                     ;
    QString name                                  ;
    SUID    uuid                                  ;
    UUIDs   Uuids = SC . Uuids                    (
                      TABLES(Executions)          ,
                      "uuid"                      ,
                      "order by id asc"         ) ;
    foreach (uuid,Uuids)                          {
      NewTreeWidgetItem ( IT )                    ;
      name = SC . getName                         (
               TABLES(Names)                      ,
               "uuid"                             ,
               vLanguageId                        ,
               uuid                             ) ;
      IT -> setData   ( 0 , Qt::UserRole , uuid ) ;
      IT -> setText   ( 0 , name                ) ;
      Items << IT                                 ;
    }                                             ;
  LeaveSQL ( SC , plan->sql )                     ;
  addTopLevelItems ( Items )                      ;
  emit GoRelax     (       )                      ;
  Alert            ( Done  )                      ;
}

void N::ExecutionLists::Copy(void)
{
  QMimeData * mime = dragMime    (      ) ;
  if (IsNull(mime)) return                ;
  qApp->clipboard()->setMimeData ( mime ) ;
}

void N::ExecutionLists::Insert(void)
{
  removeOldItem     (  )                  ;
  NewTreeWidgetItem (IT)                  ;
  IT->setData(0,Qt::UserRole,0)           ;
  addTopLevelItem   (IT)                  ;
  scrollToItem      (IT)                  ;
  QLineEdit * name = new QLineEdit(this)  ;
  ItemEditing = IT                        ;
  ItemColumn  = 0                         ;
  ItemWidget  = (QWidget *)name           ;
  IT->setData(0,Qt::UserRole  ,0        ) ;
  setItemWidget(IT,0,name)                ;
  connect(name,SIGNAL(editingFinished())  ,
          this,SLOT  (NameFinished   ())) ;
  name->setFocus(Qt::TabFocusReason)      ;
}

void N::ExecutionLists::Rename(void)
{
  QTreeWidgetItem * IT = currentItem() ;
  if (NotNull(IT)) return              ;
  doubleClicked ( IT , 0 )             ;
}

void N::ExecutionLists::Execution(void)
{
  QTreeWidgetItem * IT = currentItem() ;
  if (IsNull(IT)) return               ;
  SUID uuid    = nTreeUuid ( IT , 0 )  ;
  bool success = false                 ;
  N::Execution ne                      ;
  EnterSQL ( SC , plan->sql )          ;
    ne.clear()                         ;
    success = ne.Load ( plan,SC,uuid ) ;
  LeaveSQL ( SC , plan->sql )          ;
  if (!success) return                 ;
  plan->Talk(ne.Name)                  ;
  ne.Run()                             ;
}

void N::ExecutionLists::doubleClicked(QTreeWidgetItem *item, int column)
{
  if (column!=0) return                   ;
  QLineEdit * name = new QLineEdit(this)  ;
  SUID uuid = nTreeUuid(item,column)      ;
  ItemEditing = item                      ;
  ItemColumn  = 0                         ;
  ItemWidget  = (QWidget *)name           ;
  name -> setText (item->text(0))         ;
  setItemWidget(item,0,name)              ;
  connect(name,SIGNAL(editingFinished())  ,
          this,SLOT  (NameFinished   ())) ;
  name->setFocus(Qt::TabFocusReason)      ;
}

void N::ExecutionLists::removeOldItem(void)
{
  if (IsNull(ItemEditing)) return                ;
  SUID uuid = nTreeUuid(ItemEditing,ItemColumn)  ;
  removeItemWidget (ItemEditing,ItemColumn)      ;
  if (uuid<=0)                                   {
    int index = indexOfTopLevelItem(ItemEditing) ;
    takeTopLevelItem(index)                      ;
  }                                              ;
  ItemEditing = NULL                             ;
  ItemWidget  = NULL                             ;
  ItemColumn  = -1                               ;
}

void N::ExecutionLists::NameFinished(void)
{
  SUID uuid = nTreeUuid(ItemEditing,ItemColumn)            ;
  QLineEdit * name = qobject_cast<QLineEdit *>(ItemWidget) ;
  if (IsNull(name))                                        {
    removeOldItem ( )                                      ;
    return                                                 ;
  }                                                        ;
  QString action = name->text()                            ;
  if (action.length()<=0)                                  {
    removeOldItem ( )                                      ;
    return                                                 ;
  }                                                        ;
  CodeManager CM ( plan )                                  ;
  EnterSQL ( SC , plan->sql )                              ;
    if (uuid>0)                                            {
      CM . assureName(SC,uuid,vLanguageId,action         ) ;
      ItemEditing->setData(0,Qt::UserRole,uuid)            ;
      ItemEditing->setText(0,action)                       ;
      emit Update ( this , uuid )                          ;
    }                                                      ;
  LeaveSQL ( SC , plan->sql )                              ;
  removeOldItem ( )                                        ;
  Alert ( Done )                                           ;
}

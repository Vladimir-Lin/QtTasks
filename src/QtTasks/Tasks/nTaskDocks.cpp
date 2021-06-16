#include <qttasks.h>

N::TaskDocks:: TaskDocks   ( QWidget * parent , Plan * p )
             : TreeDock    (           parent ,        p )
             , TaskManager (                           p )
{
  Configure ( ) ;
}

N::TaskDocks::~TaskDocks(void)
{
}

QMimeData * N::TaskDocks::dragMime(void)
{
  TreeWidgetItems Items = selectedItems() ;
  if (Items.count()<=0) return NULL ;
  QMimeData * mime = new QMimeData() ;
  if (Items.count()==1) {
    SUID        type = Items[0]->data(0,Qt::UserRole).toULongLong();
    QByteArray  data((const char *)&type,sizeof(SUID));
    mime->setData("task/uuid",data);
  } else {
    QByteArray  data;
    data.resize(sizeof(SUID)*(Items.count()+1)) ;
    SUID * suid = (SUID *)data.data();
    suid[0] = Items.count() ;
    for (int i=0;i<Items.count();i++) suid[i+1] = Items[i]->data(0,Qt::UserRole).toULongLong();
    mime->setData("task/uuids",data);
  };
  return mime ;
}

QString N::TaskDocks::MimeType(const QMimeData * mime)
{
  return AbstractGui::MimeType(mime,"task/uuid;task/uuids");
}

UUIDs N::TaskDocks::MimeUuids(const QMimeData * mime,QString mimetype)
{
  UUIDs      Uuids                       ;
  QByteArray data = mime->data(mimetype) ;
  if (data.size()<=0) return Uuids       ;
  if (mimetype=="task/uuid")             {
    SUID * suid = (SUID *)data.data()    ;
    Uuids << (*suid)                     ;
  } else
  if (mimetype=="task/uuids")            {
    SUID * suid  = (SUID *)data.data()   ;
    int    total = (int)suid[0]          ;
    for (int i=0;i<total;i++)            {
      Uuids << suid[i+1]                 ;
      DoProcessEvents                    ;
    }                                    ;
  }                                      ;
  return Uuids                           ;
}

bool N::TaskDocks::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{
  QString    mtype                     ;
  UUIDs      Uuids                     ;
  if (source==this)                    {
    return false                       ;
  } else                               {
    if (mime->hasUrls())               {
      return false                     ;
    } else                             {
      mtype = MimeType  (mime      )   ;
      Uuids = MimeUuids (mime,mtype)   ;
    }                                  ;
  }                                    ;
  return true                          ;
}

bool N::TaskDocks::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{
  if (source==this)                   {
    return false                      ;
  } else                              {
    if (mime->hasUrls()) return false ;
  }                                   ;
  return true                         ;
}

bool N::TaskDocks::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  QString mtype                            ;
  UUIDs   Uuids                            ;
  if (source==this)                        {
    return false                           ;
  } else                                   {
    QTreeWidgetItem * atItem = itemAt(pos) ;
    SUID before = 0                        ;
    if (NotNull(atItem))                   {
      before = nTreeUuid(atItem,0)         ;
    }                                      ;
    if (mime->hasUrls())                   {
    } else                                 {
      mtype = MimeType  (mime      )       ;
      Uuids = MimeUuids (mime,mtype)       ;
    }                                      ;
  }                                        ;
  return true                              ;
}

bool N::TaskDocks::FocusIn(void)
{
  nKickOut          ( IsNull(plan) , true            ) ;
  DisableAllActions (                                ) ;
  AssignAction      ( Label        , windowTitle ( ) ) ;
  LinkAction        ( Font         , setFont     ( ) ) ;
  LinkAction        ( Delete       , Obsolete    ( ) ) ;
  LinkAction        ( Insert       , New         ( ) ) ;
  return true                                          ;
}

bool N::TaskDocks::Shutdown(void)
{
  if (IsNull(plan)) return false            ;
  QAction * a = plan->Action(Menus::Delete) ;
  if (IsNull(a)) return false               ;
  a->setEnabled(false)                      ;
  return true                               ;
}

void N::TaskDocks::Store(QMainWindow * Main)
{
  N::AttachDock::Store    ( Main                            ) ;
  plan -> site.beginGroup ( Scope                           ) ;
  plan -> site.setValue   ( "Behavior" , !isColumnHidden(1) ) ;
  plan -> site.setValue   ( "Status"   , !isColumnHidden(2) ) ;
  plan -> site.endGroup   (                                 ) ;
}

void N::TaskDocks::Docking       (
       QMainWindow       * Main  ,
       QString             title ,
       Qt::DockWidgetArea  area  ,
       Qt::DockWidgetAreas areas )
{
  bool behavior = false                              ;
  bool status   = false                              ;
  N::AttachDock::Docking(Main,this,title,area,areas) ;
  plan->site.beginGroup (Scope                     ) ;
  if (plan->site.contains("Behavior"))               {
    behavior = plan->site.value("Behavior").toBool() ;
  }                                                  ;
  if (plan->site.contains("Status"  ))               {
    status   = plan->site.value("Status"  ).toBool() ;
  }                                                  ;
  plan->site.endGroup   (                          ) ;
  setColumnHidden       (1,!behavior               ) ;
  setColumnHidden       (2,!status                 ) ;
  emit AutoFit          (                          ) ;
}

void N::TaskDocks::Configure(void)
{
  NewTreeWidgetItem       ( header             )    ;
  header -> setText       ( 0 , tr("Task"    ) )    ;
  header -> setText       ( 1 , tr("Behavior") )    ;
  header -> setText       ( 2 , tr("Status"  ) )    ;
  setSuggestion           ( QSize(400,120)     )    ;
  setFocusPolicy          ( Qt::WheelFocus     )    ;
  setDragDropMode         ( DragDrop           )    ;
  setAlternatingRowColors ( true               )    ;
  setRootIsDecorated      ( false              )    ;
  setSelectionMode        ( ExtendedSelection  )    ;
  setColumnCount          ( 3                  )    ;
  setColumnHidden         ( 1 , true           )    ;
  setColumnHidden         ( 2 , true           )    ;
  assignHeaderItems       ( header             )    ;
  MountClicked            ( 2                  )    ;
  ///////////////////////////////////////////////////
  behaviors[Tasks::Undecided  ] = tr("Undecided"  ) ;
  behaviors[Tasks::Standalone ] = tr("Standalone" ) ;
  behaviors[Tasks::Framework  ] = tr("Framework"  ) ;
  behaviors[Tasks::Root       ] = tr("Root"       ) ;
  behaviors[Tasks::Child      ] = tr("Child"      ) ;
  behaviors[Tasks::Heir       ] = tr("Heir"       ) ;
  behaviors[Tasks::Decision   ] = tr("Decision"   ) ;
  behaviors[Tasks::Prerequiste] = tr("Prerequiste") ;
  behaviors[Tasks::Obsolete   ] = tr("Obsolete"   ) ;
  states   [0                 ] = tr("Unknown"    ) ;
  states   [Tasks::Template   ] = tr("Template"   ) ;
  states   [Tasks::Proposed   ] = tr("Proposed"   ) ;
  states   [Tasks::Analysis   ] = tr("Analysis"   ) ;
  states   [Tasks::Preparation] = tr("Preparation") ;
  states   [Tasks::Ready      ] = tr("Ready"      ) ;
  states   [Tasks::Dispatching] = tr("Dispatching") ;
  states   [Tasks::Assigned   ] = tr("Assigned"   ) ;
  states   [Tasks::Execution  ] = tr("Execution"  ) ;
  states   [Tasks::Feedback   ] = tr("Feedback"   ) ;
  states   [Tasks::Completed  ] = tr("Completed"  ) ;
  states   [Tasks::Terminated ] = tr("Terminated" ) ;
  states   [Tasks::Expired    ] = tr("Expired"    ) ;
  states   [Tasks::Forwarded  ] = tr("Forwarded"  ) ;
  states   [Tasks::Finished   ] = tr("Finished"   ) ;
  states   [Tasks::Failed     ] = tr("Failed"     ) ;
  states   [Tasks::Delegated  ] = tr("Delegated"  ) ;
  states   [Tasks::Rejected   ] = tr("Rejected"   ) ;
  states   [Tasks::Review     ] = tr("Review"     ) ;
  states   [Tasks::End        ] = tr("End"        ) ;
  ///////////////////////////////////////////////////
  plan -> setFont ( this )                          ;
}

bool N::TaskDocks::Menu(QPoint pos)
{
  nScopedMenu ( mm , this )                         ;
  TreeWidgetItems   items = selectedItems()         ;
  QTreeWidgetItem * it    = itemAt(pos)             ;
  SUID              uuid  = 0                       ;
  QAction         * a                               ;
  removeOldItem()                                   ;
  mm.add(101,tr("New"))                             ;
  if (NotNull(it))                                  {
    uuid = nTreeUuid(it,0)                          ;
    if (it->isSelected()) mm.add(102,tr("Edit"   )) ;
    if (it->isSelected()) mm.add(103,tr("Rename" )) ;
    if (items.count()>0 ) mm.add(104,tr("Details")) ;
    mm.add(105,tr("Obsolete"))                      ;
  }                                                 ;
  mm. addSeparator (                  )             ;
  a = mm.add       (201,tr("Behavior"))             ;
  a-> setCheckable (true              )             ;
  a-> setChecked   (!isColumnHidden(1))             ;
  a = mm.add       (202,tr("Status"  ))             ;
  a-> setCheckable (true              )             ;
  a-> setChecked   (!isColumnHidden(2))             ;
  if (plan->fonts.contains(Fonts::Menu))            {
    mm.setFont(plan->fonts[Fonts::Menu])            ;
  }                                                 ;
  a = mm.exec      (mapToGlobal(pos)  )             ;
  switch (mm[a])                                    {
    case 101                                        :
      New()                                         ;
    break                                           ;
    case 102                                        :
      emit Clicked(uuid)                            ;
    break                                           ;
    case 103                                      : {
      QLineEdit * name = new QLineEdit(this)        ;
      ItemEditing = it                              ;
      ItemColumn  = 0                               ;
      ItemWidget  = (QWidget *)name                 ;
      name -> setText (it->text(0))                 ;
      setItemWidget(it,0,name)                      ;
      nConnect ( name , SIGNAL(editingFinished())   ,
                 this , SLOT  (editingFinished()) ) ;
      name->setFocus(Qt::TabFocusReason)            ;
    }                                               ;
    break                                           ;
    case 104                                        :
      if (items.count()>0)                          {
        UUIDs Uuids                                 ;
        for (int i=0;i<items.count();i++)           {
          Uuids << nTreeUuid(items[i],0)            ;
        }                                           ;
        emit Details(Uuids)                         ;
      }                                             ;
    break                                           ;
    case 105                                        :
      Obsolete()                                    ;
    break                                           ;
    case 201                                        :
      setColumnHidden (1,!a->isChecked())           ;
      emit AutoFit        (                 )       ;
    break                                           ;
    case 202                                        :
      setColumnHidden (2,!a->isChecked())           ;
      emit AutoFit        (                 )       ;
    break                                           ;
  }                                                 ;
  return true                                       ;
}

void N::TaskDocks::run(int Type,ThreadData * data)
{ Q_UNUSED ( data ) ;
  switch   ( Type ) {
    case 10001      :
      List ( )      ;
    break           ;
  }                 ;
}

bool N::TaskDocks::startup(void)
{
  clear (       ) ;
  start ( 10001 ) ;
  return true     ;
}

bool N::TaskDocks::List(void)
{
  AbstractGui::Mutex.lock  ()                       ;
  setEnabled (false)                                ;
  Sql sql = plan->sql                               ;
  SqlConnection SC(sql)                             ;
  if (SC.open("nTaskDocks","List"))                 {
    UUIDs Uuids                                     ;
    SUID  uuid                                      ;
    int   index = 0                                 ;
    Uuids = SC.Uuids                                (
              PlanTable(Tasks)                      ,
              "uuid"                                ,
              SC . OrderByDesc ( "id" )           ) ;
    foreach (uuid,Uuids)                            {
      QString Q                                     ;
      QTreeWidgetItem * IT                          ;
      QString name                                  ;
      name = SC.getName                             (
               PlanTable(Names)                     ,
               "uuid",vLanguageId,uuid            ) ;
      IT = addItem(name,uuid,0)                     ;
      Q = sql.SelectFrom                            (
            "behavior,status,flags"                 ,
            PlanTable(Tasks)                        ,
            SC . WhereUuid ( uuid )               ) ;
      if (SC.Fetch(Q))                              {
        int  Behavior = SC.Value(0) . toInt()       ;
        int  State    = SC.Value(1) . toInt()       ;
        SUID Flags    = SC.Uuid (2)                 ;
        IT->setData(0,Qt::UserRole+1,Flags  )       ;
        IT->setData(1,Qt::UserRole,Behavior )       ;
        IT->setText(1,behaviors[Behavior]   )       ;
        IT->setData(2,Qt::UserRole,State    )       ;
        IT->setText(2,states   [State   ]   )       ;
      }                                             ;
      index++                                       ;
      if ((index%100)==0)                           {
        emit AutoFit ()                             ;
        DoProcessEvents                             ;
      }                                             ;
    }                                               ;
    SC.close()                                      ;
  }                                                 ;
  SC.remove()                                       ;
  setEnabled (true)                                 ;
  AbstractGui::Mutex.unlock()                       ;
  return true                                       ;
}

void N::TaskDocks::Obsolete(void)
{
  TreeWidgetItems items = selectedItems()                 ;
  if (items.count()<=0) return                            ;
  UUIDs Uuids                                             ;
  for (int i=0;i<items.count();i++)                       {
    Uuids << items[i]->data(0,Qt::UserRole).toULongLong() ;
  }                                                       ;
  AbstractGui::Mutex.lock  ()                             ;
  clear       ()                                          ;
  Sql sql = plan->sql                                     ;
  SqlConnection SC(sql)                                   ;
  if (SC.open("nTaskDocks","Obsolete"))                   {
    SUID    uuid                                          ;
    QString Q                                             ;
    foreach (uuid,Uuids)                                  {
      UpdateBehavior ( SC , uuid , Tasks::Obsolete )      ;
    }                                                     ;
    SC.close()                                            ;
  }                                                       ;
  SC.remove()                                             ;
  AbstractGui::Mutex.unlock()                             ;
  List ()                                                 ;
}

void N::TaskDocks::doubleClicked(QTreeWidgetItem * item,int column)
{
  SUID uuid = nTreeUuid(item,column)                    ;
  switch (column)                                       {
    case 0                                              :
      emit Clicked (uuid)                               ;
    break                                               ;
    case 1 :                                            {
      removeOldItem()                                   ;
      int behavior = item->data(1,Qt::UserRole).toInt() ;
      QComboBox * CB = new QComboBox(this)              ;
      N::AddItems(*CB,behaviors)                        ;
      CB->setCurrentIndex(behavior)                     ;
      ItemEditing = item                                ;
      ItemColumn  = column                              ;
      ItemWidget  = (QWidget *)CB                       ;
      setItemWidget(item,1,CB)                          ;
      connect(CB  ,SIGNAL(activated      (int))         ,
              this,SLOT  (behaviorChanged(int))       ) ;
      CB->setMaxVisibleItems(30)                        ;
      CB->showPopup()                                   ;
    }                                                   ;
    break                                               ;
    case 2 :                                            {
      removeOldItem()                                   ;
      int state = item->data(2,Qt::UserRole).toInt()    ;
      QComboBox * CB = new QComboBox(this)              ;
      N::AddItems(*CB,states)                           ;
      CB->setCurrentIndex(state)                        ;
      ItemEditing = item                                ;
      ItemColumn  = column                              ;
      ItemWidget  = (QWidget *)CB                       ;
      setItemWidget(item,2,CB)                          ;
      connect(CB  ,SIGNAL(activated   (int))            ,
              this,SLOT  (stateChanged(int))          ) ;
      CB->setMaxVisibleItems(30)                        ;
      CB->showPopup()                                   ;
    }                                                   ;
    break                                               ;
  }                                                     ;
}

void N::TaskDocks::New(void)
{
  removeOldItem     (  )                       ;
  NewTreeWidgetItem (IT)                       ;
  IT->setData(0,Qt::UserRole,0)                ;
  insertTopLevelItem(0,IT)                     ;
  scrollToItem(IT)                             ;
  QLineEdit * name = new QLineEdit(this)       ;
  ItemEditing = IT                             ;
  ItemColumn  = 0                              ;
  ItemWidget  = (QWidget *)name                ;
  IT->setData(0,Qt::UserRole  ,0             ) ;
  IT->setData(0,Qt::UserRole+1,0             ) ;
  IT->setData(1,Qt::UserRole,Tasks::Undecided) ;
  IT->setText(1,behaviors[Tasks::Undecided]  ) ;
  IT->setData(2,Qt::UserRole,Tasks::Template ) ;
  IT->setText(2,states   [Tasks::Template ]  ) ;
  setItemWidget(IT,0,name)                     ;
  nConnect ( name , SIGNAL(editingFinished())  ,
             this , SLOT  (editingFinished())) ;
  name->setFocus(Qt::TabFocusReason)           ;
}

void N::TaskDocks::removeOldItem(void)
{
  if (IsNull(ItemEditing)) return                ;
  SUID uuid = nTreeUuid(ItemEditing,0)           ;
  removeItemWidget (ItemEditing,ItemColumn)      ;
  if (uuid<=0)                                   {
    int index = indexOfTopLevelItem(ItemEditing) ;
    takeTopLevelItem(index)                      ;
  }                                              ;
  ItemEditing = NULL                             ;
  ItemWidget  = NULL                             ;
  ItemColumn  = -1                               ;
}

void N::TaskDocks::editingFinished(void)
{
  SUID uuid = nTreeUuid(ItemEditing,0)                   ;
  QLineEdit * name = Casting(QLineEdit,ItemWidget)       ;
  if (NotNull(name))                                     {
    QString task = name->text()                          ;
    if (task.length()>0)                                 {
      LockGui  ( )                                       ;
      SqlConnection SC ( plan -> sql )                   ;
      if ( SC . open ( "nTaskDocks::editingFinished" ) ) {
        if ( uuid <= 0 )                                 {
          uuid = NewTask ( SC                            ,
                           Tasks::Undecided              ,
                           Tasks::Template               ,
                           0                           ) ;
        }                                                ;
        SC . assureName ( PlanTable(Names)               ,
                          uuid                           ,
                          vLanguageId                    ,
                          task                         ) ;
        ItemEditing->setData(0,Qt::UserRole,uuid)        ;
        ItemEditing->setText(0,task)                     ;
        SC.close()                                       ;
      }                                                  ;
      SC.remove()                                        ;
      UnlockGui ( )                                      ;
    }                                                    ;
  }                                                      ;
  removeOldItem (  )                                     ;
}

void N::TaskDocks::behaviorChanged(int behavior)
{
  SUID uuid = nTreeUuid(ItemEditing,0)        ;
  ItemEditing->setText(1,behaviors[behavior]) ;
  LockGui          (                      )   ;
  SqlConnection SC ( plan -> sql          )   ;
  if (SC.open("nTaskDocks::behaviorChanged")) {
    UpdateBehavior ( SC , uuid , behavior )   ;
    SC . close     (                      )   ;
  }                                           ;
  SC . remove      (                      )   ;
  UnlockGui        (                      )   ;
  removeOldItem    (                      )   ;
}

void N::TaskDocks::stateChanged(int state)
{
  SUID uuid = nTreeUuid(ItemEditing,0)     ;
  ItemEditing->setText(2,states[state])    ;
  LockGui          (                   )   ;
  SqlConnection SC ( plan -> sql       )   ;
  if (SC.open("nTaskDocks::stateChanged")) {
    UpdateStatus   ( SC , uuid , state )   ;
    SC . close     (                   )   ;
  }                                        ;
  SC . remove      (                   )   ;
  UnlockGui        (                   )   ;
  removeOldItem    (                   )   ;
}

#include <qttasks.h>

#pragma message("EventDocks requires some revise")

#define UuidAndLanguage "where uuid = %1 and language = %2"
#define UUIDLANGUAGE(UUID,LANGUAGE) QString(UuidAndLanguage).arg(UUID).arg(LANGUAGE)
#define LANGUAGESQL(PLAN,UUID,LANGUAGE)    \
  (PLAN).Sql.SelectFrom                  ( \
  "name"                                 , \
  (PLAN).Tables[Tables::Names] , \
  UUIDLANGUAGE(UUID,LANGUAGE)            )
#define REPLACENAME(SQL,PLAN)              \
  (SQL).ReplaceInto                      ( \
  (PLAN).Tables[Tables::Names] , \
  3                                      , \
  "uuid"                                 , \
  "language"                             , \
  "name"                                 )

#define QMessage(caption,message) QMessageBox::information(this,caption,message)
#define WhereUuidIs(uuid) QString("where uuid = %1").arg(uuid)

N::EventDocks:: EventDocks (QWidget * parent,Plan * p)
              : TreeDock   (          parent,       p)
              , Editable   (true                     )
              , EventTable (""                       )
{
  Configure () ;
}

N::EventDocks::~EventDocks(void)
{
}

QMimeData * N::EventDocks::dragMime(void)
{
  TreeWidgetItems Items = selectedItems() ;
  if (Items.count()<=0) return NULL ;
  QMimeData * mime = new QMimeData() ;
  if (Items.count()==1) {
    SUID        type = Items[0]->data(0,Qt::UserRole).toULongLong();
    QByteArray  data((const char *)&type,sizeof(SUID));
    mime->setData("event/uuid",data);
  } else {
    QByteArray  data;
    data.resize(sizeof(SUID)*(Items.count()+1)) ;
    SUID * suid = (SUID *)data.data();
    suid[0] = Items.count() ;
    for (int i=0;i<Items.count();i++) suid[i+1] = Items[i]->data(0,Qt::UserRole).toULongLong();
    mime->setData("event/uuids",data);
  };
  return mime ;
}

QString N::EventDocks::MimeType(const QMimeData * mime)
{
  return AbstractGui::MimeType(mime,"event/uuid;event/uuids");
}

UUIDs N::EventDocks::MimeUuids(const QMimeData * mime,QString mimetype)
{
  UUIDs      Uuids                       ;
  QByteArray data = mime->data(mimetype) ;
  if (data.size()<=0) return Uuids       ;
  if (mimetype=="event/uuid")            {
    SUID * suid = (SUID *)data.data()    ;
    Uuids << (*suid)                     ;
  } else
  if (mimetype=="event/uuids")           {
    SUID * suid  = (SUID *)data.data()   ;
    int    total = (int)suid[0]          ;
    for (int i=0;i<total;i++)            {
      Uuids << suid[i+1]                 ;
      DoProcessEvents                    ;
    }                                    ;
  }                                      ;
  return Uuids                           ;
}

bool N::EventDocks::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
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

bool N::EventDocks::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{
  if (source==this)                   {
    return false                      ;
  } else                              {
    if (mime->hasUrls()) return false ;
  }                                   ;
  return true                         ;
}

bool N::EventDocks::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  QString mtype                                              ;
  UUIDs   Uuids                                              ;
  if (source==this)                                          {
    return false                                             ;
  } else                                                     {
    QTreeWidgetItem * atItem = itemAt(pos)                   ;
    SUID before = 0                                          ;
    if (NotNull(atItem))                                     {
      before = atItem->data(0,Qt::UserRole).toULongLong()    ;
    }                                                        ;
    if (mime->hasUrls())                                     {
      return false                                           ;
    } else                                                   {
      mtype = MimeType  (mime      )                         ;
      Uuids = MimeUuids (mime,mtype)                         ;
    }                                                        ;
  }                                                          ;
  return true                                                ;
}

bool N::EventDocks::FocusIn(void)
{
  nKickOut          ( IsNull(plan) , false           ) ;
  DisableAllActions (                                ) ;
  AssignAction      ( Label        , windowTitle ( ) ) ;
  LinkAction        ( Insert       , New         ( ) ) ;
  LinkAction        ( Refresh      , List        ( ) ) ;
  LinkAction        ( Delete       , Obsolete    ( ) ) ;
  LinkAction        ( Font         , setFont     ( ) ) ;
  return true                                          ;
}

bool N::EventDocks::Shutdown(void)
{
  if (IsNull(plan)) return false ;
  return true                    ;
}

void N::EventDocks::Store(QMainWindow * Main)
{
  AttachDock::Store     (Main                           ) ;
  plan->site.beginGroup (Scope                          ) ;
  plan->site.setValue   ("EventType" ,!isColumnHidden(1)) ;
  plan->site.setValue   ("StartTime" ,!isColumnHidden(2)) ;
  plan->site.setValue   ("Notify"    ,!isColumnHidden(3)) ;
  plan->site.setValue   ("FinishTime",!isColumnHidden(4)) ;
  plan->site.endGroup   (                               ) ;
}

void N::EventDocks::Docking(QMainWindow * Main,QString title,Qt::DockWidgetArea area,Qt::DockWidgetAreas areas)
{
  bool eventtype  = false                                ;
  bool notify     = false                                ;
  bool starttime  = false                                ;
  bool finishtime = false                                ;
  N::AttachDock::Docking(Main,this,title,area,areas)     ;
  plan->site.beginGroup (Scope                         ) ;
  if (plan->site.contains("EventType"   ))               {
    eventtype  = plan->site.value("EventType" ).toBool() ;
  }                                                  ;
  if (plan->site.contains("Notify"      ))               {
    notify     = plan->site.value("Notify"    ).toBool() ;
  }                                                  ;
  if (plan->site.contains("StartTime"   ))               {
    starttime  = plan->site.value("StartTime" ).toBool() ;
  }                                                  ;
  if (plan->site.contains("FinishTime"  ))               {
    finishtime = plan->site.value("FinishTime").toBool() ;
  }                                                      ;
  plan->site.endGroup   (                              ) ;
  setColumnHidden       ( 1 , !eventtype               ) ;
  setColumnHidden       ( 2 , !starttime               ) ;
  setColumnHidden       ( 3 , !notify                  ) ;
  setColumnHidden       ( 4 , !finishtime              ) ;
  setColumnHidden       ( 5 , !notify                  ) ;
  emit AutoFit          (                              ) ;
}

void N::EventDocks::Configure(void)
{
  setAccessibleName       ( "EventDocks"       ) ;
  setSuggestion           ( QSize(720,120)     ) ;
  NewTreeWidgetItem       ( header             ) ;
  header -> setText       ( 0 , tr("Event"   ) ) ;
  header -> setText       ( 1 , tr("Type"    ) ) ;
  header -> setText       ( 2 , tr("Start"   ) ) ;
  header -> setText       ( 3 , tr("Trigger" ) ) ;
  header -> setText       ( 4 , tr("Finish"  ) ) ;
  header -> setText       ( 5 , tr("Trigger" ) ) ;
  setFocusPolicy          ( Qt::WheelFocus     ) ;
  setDragDropMode         ( DragDrop           ) ;
  setAlternatingRowColors ( true               ) ;
  setRootIsDecorated      ( false              ) ;
  setSelectionMode        ( ExtendedSelection  ) ;
  setColumnCount          ( 6                  ) ;
  setColumnHidden         ( 1 , false          ) ;
  setColumnHidden         ( 2 , false          ) ;
  setColumnHidden         ( 3 , false          ) ;
  setColumnHidden         ( 4 , false          ) ;
  setColumnHidden         ( 5 , false          ) ;
  assignHeaderItems       ( header             ) ;
  ////////////////////////////////////////////////
  MountClicked            ( 1                  ) ;
  MountClicked            ( 2                  ) ;
  plan -> setFont         ( this               ) ;
  ////////////////////////////////////////////////
  // Load Action Types
  AbstractGui::Mutex.lock  ()                    ;
  Sql sql = plan->sql                            ;
  SqlConnection SC ( sql  )                      ;
  EventManager  EM ( plan )                      ;
  if (SC.open("nEventDocks","Configure"))        {
    SUID    uuid                                 ;
    QString Q = EM.ActionQuery(SC)               ;
    SqlLoopNow(SC,Q)                             ;
      int Type = SC.Value(0).toInt()             ;
          uuid = SC.Uuid (1)                     ;
      TypeUuids [Type] = uuid                    ;
      UuidTypes [uuid] = Type                    ;
      NameUuids       << uuid                    ;
    SqlLoopErr(SC,Q)                             ;
    SqlLoopEnd(SC,Q)                             ;
    foreach (uuid,NameUuids)                     {
      TypeNames [uuid] = EM.Name(SC,uuid)        ;
    }                                            ;
    SC.close()                                   ;
  }                                              ;
  SC.remove()                                    ;
  AbstractGui::Mutex.unlock()                    ;
}

bool N::EventDocks::Menu(QPoint pos)
{
  nScopedMenu ( mm , this )                                     ;
  TreeWidgetItems   items = selectedItems()                     ;
  QTreeWidgetItem * it    = itemAt(pos)                         ;
  SUID              uuid  = 0                                   ;
  QAction         * a                                           ;
  removeOldItem()                                               ;
  if (Editable) mm.add(101,tr("New"))                           ;
  if (NotNull(it))                                              {
    uuid = it->data(0,Qt::UserRole).toULongLong()               ;
    if (it->isSelected() && Editable) mm.add(102,tr("Edit"))    ;
    if (it->isSelected() && Editable) mm.add(103,tr("Rename"))  ;
    if (items.count()>0 ) mm.add(104,tr("Details"))             ;
    if (Editable) mm.add(105,tr("Obsolete"))                    ;
    mm.add(106,tr("Clone"))                                     ;
    if (!Editable) mm.add(107,tr("Reinstate"))                  ;
  }                                                             ;
  mm. addSeparator (                  )                         ;
  a = mm.add       (201,tr("Type"    ))                         ;
  a-> setCheckable (true              )                         ;
  a-> setChecked   (!isColumnHidden(1))                         ;
  a = mm.add       (202,tr("Trigger" ))                         ;
  a-> setCheckable (true              )                         ;
  a-> setChecked   (!isColumnHidden(3))                         ;
  a = mm.add       (203,tr("Start"   ))                         ;
  a-> setCheckable (true              )                         ;
  a-> setChecked   (!isColumnHidden(2))                         ;
  a = mm.add       (204,tr("Finish"  ))                         ;
  a-> setCheckable (true              )                         ;
  a-> setChecked   (!isColumnHidden(4))                         ;
  if (plan->fonts.contains(Fonts::Menu))                        {
    mm.setFont(plan->fonts[Fonts::Menu])                        ;
  }                                                             ;
  Alert ( Menu )                                                ;
  a = mm.exec ( mapToGlobal(pos) )                              ;
  switch (mm[a])                                                {
    case 101                                                    :
      New()                                                     ;
    break                                                       ;
    case 102                                                    :
      emit Clicked(uuid)                                        ;
    break                                                       ;
    case 103                                                  : {
      QLineEdit * name = new QLineEdit(this)                    ;
      ItemEditing = it                                          ;
      ItemColumn  = 0                                           ;
      ItemWidget  = (QWidget *)name                             ;
      name -> setText (it->text(0))                             ;
      setItemWidget(it,0,name)                                  ;
      connect(name,SIGNAL(editingFinished())                    ,
              this,SLOT  (editingFinished()))                   ;
      name->setFocus(Qt::TabFocusReason)                        ;
    }                                                           ;
    break                                                       ;
    case 104                                                    :
      if (items.count()>0)                                      {
        UUIDs Uuids                                             ;
        for (int i=0;i<items.count();i++)                       {
          Uuids << items[i]->data(0,Qt::UserRole).toULongLong() ;
        }                                                       ;
        emit Details(Uuids)                                     ;
      }                                                         ;
    break                                                       ;
    case 105                                                    :
      Obsolete()                                                ;
    break                                                       ;
    case 106 /* clone */                                        :
      // emit Clicked(uuid)                                        ;
    break                                                       ;
    case 107 /* reinstate */                                    :
      //emit Clicked(uuid)                                        ;
    break                                                       ;
    case 201                                                    :
      setColumnHidden (1,!a->isChecked())                       ;
      emit AutoFit    (                 )                       ;
    break                                                       ;
    case 202                                                    :
      setColumnHidden (3,!a->isChecked())                       ;
      setColumnHidden (5,!a->isChecked())                       ;
      emit AutoFit    (                 )                       ;
    break                                                       ;
    case 203                                                    :
      setColumnHidden (2,!a->isChecked())                       ;
      emit AutoFit    (                 )                       ;
    break                                                       ;
    case 204                                                    :
      setColumnHidden (4,!a->isChecked())                       ;
      emit AutoFit    (                 )                       ;
    break                                                       ;
  }                                                             ;
  return true                                                   ;
}

bool N::EventDocks::Load(SqlConnection & SC,SUID uuid,QTreeWidgetItem * IT)
{
  QString Q                                                  ;
  Sql sql = SC.sql                                           ;
  EventManager EM(plan)                                      ;
  Q = sql.SelectFrom                                         (
        "type,status,adjust",EventTable,WhereUuidIs(uuid)  ) ;
  if (SC.Fetch(Q))                                           {
    int  Type   = SC.Value(0) . toInt()                      ;
    int  State  = SC.Value(1) . toInt()                      ;
    int  Adjust = SC.Value(2) . toInt()                      ;
    SUID nuid   = TypeUuids[Type]                            ;
    SUID tspot  = 0                                          ;
    IT->setData(1,Qt::UserRole,Type)                         ;
    IT->setData(2,Qt::UserRole,State)                        ;
    IT->setData(3,Qt::UserRole,0)                            ;
    IT->setData(4,Qt::UserRole,Adjust)                       ;
    IT->setData(5,Qt::UserRole,0)                            ;
    IT->setText(1,TypeNames[nuid])                           ;
    tspot = EM.Chronology(SC,uuid)                           ;
    if (tspot>0)                                             {
      int tstyle = EM.UuidType(SC,tspot)                     ;
      if (tstyle==Types::History)                            {
        TUID tuid = EM.TimeSpot(SC,tspot)                    ;
        if (tuid>0)                                          {
          QDateTime D = EM.toDateTime(tuid)                  ;
          IT->setText(2,D.toString("yyyy/MM/dd hh:mm:ss"))   ;
        }                                                    ;
      } else
      if (tstyle==Types::Period)                             {
        Q = EM.TimePeriod(SC,tspot)                          ;
        if (SC.Fetch(Q))                                     {
          SUID first  = SC.Uuid(0)                           ;
          SUID second = SC.Uuid(1)                           ;
          TUID tuid   = 0                                    ;
          tuid = EM.TimeSpot(SC,first)                       ;
          if (tuid>0)                                        {
            QDateTime D = EM.toDateTime(tuid)                ;
            IT->setText(2,D.toString("yyyy/MM/dd hh:mm:ss")) ;
          }                                                  ;
          tuid   = EM.TimeSpot(SC,second)                    ;
          if (tuid>0)                                        {
            QDateTime D = EM.toDateTime(tuid)                ;
            IT->setText(4,D.toString("yyyy/MM/dd hh:mm:ss")) ;
          }                                                  ;
        }                                                    ;
      }                                                      ;
    }                                                        ;
    Q = SC.sql.SelectFrom("second"                           ,
          PlanTable(Groups)                                  ,
          QString("where first = %1 and t1 = %2 and t2 = %3 and relation = %4")
            .arg(uuid                                        )
            .arg(Types::Schedule                             )
            .arg(Types::Trigger                              )
            .arg(Groups::StartTrigger                        )
        )                                                    ;
    if (SC.Fetch(Q))                                         {
      SUID    First = SC.Uuid(0)                             ;
      QString Name  = SC.getName                             (
        PlanTable(Names)                                     ,
        "uuid",vLanguageId,First                           ) ;
      IT -> setData ( 3 , Qt::UserRole , First  )            ;
      IT -> setText ( 3 , Name                  )            ;
    }                                                        ;
    Q = SC.sql.SelectFrom("second"                           ,
          PlanTable(Groups)                                  ,
          QString("where first = %1 and t1 = %2 and t2 = %3 and relation = %4")
            .arg(uuid                                        )
            .arg(Types::Schedule                             )
            .arg(Types::Trigger                              )
            .arg(Groups::FinalTrigger                        )
        )                                                    ;
    if (SC.Fetch(Q))                                         {
      SUID    Second = SC.Uuid(0)                            ;
      QString Name   = SC.getName                            (
        PlanTable(Names)                                     ,
        "uuid",vLanguageId,Second                          ) ;
      IT -> setData ( 5 , Qt::UserRole , Second )            ;
      IT -> setText ( 5 , Name                  )            ;
    }                                                        ;
  }                                                          ;
  return true                                                ;
}

void N::EventDocks::run(int Type,ThreadData * data)
{ Q_UNUSED ( data ) ;
  switch   ( Type ) {
    case 10001      :
      List ( )      ;
    break           ;
  }                 ;
}

bool N::EventDocks::startup(void)
{
  clear (       ) ;
  start ( 10001 ) ;
  return true     ;
}

bool N::EventDocks::List(void)
{
  setEnabled      ( false          )       ;
  EventManager EM ( plan           )       ;
  EnterSQL        ( SC , plan->sql )       ;
    UUIDs   Uuids                          ;
    SUID    uuid                           ;
    int     index = 0                      ;
    QString T                              ;
    Uuids = EM . Uuids ( SC , EventTable ) ;
    foreach (uuid,Uuids)                   {
      QTreeWidgetItem * IT                 ;
      QString name = EM.Name(SC,uuid)      ;
      IT = addItem(name,uuid,0)            ;
      Load ( SC , uuid , IT )              ;
      index++                              ;
      if ((index%100)==0)                  {
        emit AutoFit ()                    ;
        DoProcessEvents                    ;
      }                                    ;
    }                                      ;
    T = tr("%1 events").arg(Uuids.count()) ;
    setToolTip ( T )                       ;
  LeaveSQL ( SC , plan->sql )              ;
  setEnabled (true)                        ;
  emit AutoFit ( )                         ;
  Alert ( Done )                           ;
  return true                              ;
}

void N::EventDocks::Obsolete(void)
{
  if (!Editable) return                   ;
  TreeWidgetItems items = selectedItems() ;
  if (items.count()<=0) return            ;
  UUIDs Uuids                             ;
  for (int i=0;i<items.count();i++)       {
    Uuids << nTreeUuid(items[i],0)        ;
  }                                       ;
  AbstractGui::Mutex.lock  ()             ;
  clear       ()                          ;
  Sql sql = plan->sql                     ;
  SqlConnection SC(sql)                   ;
  if (SC.open("nTaskDocks","Obsolete"))   {
    SUID    uuid                          ;
    QString Q                             ;
    foreach (uuid,Uuids)                  {
    }                                     ;
    SC.close()                            ;
  }                                       ;
  SC.remove()                             ;
  AbstractGui::Mutex.unlock()             ;
  List ()                                 ;
}

void N::EventDocks::singleClicked(QTreeWidgetItem * item,int column)
{
  Alert ( Click )                                     ;
  if (ItemEditing==item && column==ItemColumn) return ;
  removeOldItem (  )                                  ;
}

void N::EventDocks::doubleClicked(QTreeWidgetItem * item,int column)
{
  SUID uuid = nTreeUuid(item,0)                  ;
  int  Type = nTreeUuid(item,1)                  ;
  switch (column)                                {
    case 0                                       :
      emit Clicked (uuid)                        ;
    break                                        ;
    case 1                                       :
    if (Editable)                                {
      removeOldItem()                            ;
      int         behavior = Type                ;
      QComboBox * CB       = new QComboBox(this) ;
      N::AddItems(*CB,NameUuids,TypeNames)       ;
      CB->setCurrentIndex(behavior)              ;
      ItemEditing = item                         ;
      ItemColumn  = column                       ;
      ItemWidget  = (QWidget *)CB                ;
      setItemWidget(item,1,CB)                   ;
      connect(CB  ,SIGNAL( activated  (int))     ,
              this,SLOT  ( TypeChanged(int)) )   ;
      CB->setMaxVisibleItems(30)                 ;
      CB->showPopup()                            ;
    }                                            ;
    break                                        ;
    case 2 /* Start  */                          :
      setDateTime ( item , column )              ;
    break                                        ;
    case 3 /* Start Trigger */                   :
      setTrigger  ( item , column )              ;
    break                                        ;
    case 4 /* Finish */                          :
      setDateTime ( item , column )              ;
    break                                        ;
    case 5 /* Final Trigger */                   :
      setTrigger  ( item , column )              ;
    break                                        ;
  }                                              ;
}

void N::EventDocks::New(void)
{
  removeOldItem     (  )                  ;
  NewTreeWidgetItem (IT)                  ;
  IT->setData(0,Qt::UserRole,0)           ;
  insertTopLevelItem(0,IT)                ;
  scrollToItem(IT)                        ;
  QLineEdit * name = new QLineEdit(this)  ;
  ItemEditing = IT                        ;
  ItemColumn  = 0                         ;
  ItemWidget  = (QWidget *)name           ;
  IT -> setData (0,Qt::UserRole,0)        ;
  setItemWidget(IT,0,name)                ;
  connect(name,SIGNAL(editingFinished())  ,
          this,SLOT  (editingFinished())) ;
  name->setFocus(Qt::TabFocusReason)      ;
}

void N::EventDocks::removeOldItem(void)
{
  if (IsNull(ItemEditing)) return                             ;
  SUID uuid = ItemEditing->data(0,Qt::UserRole).toULongLong() ;
  removeItemWidget (ItemEditing,ItemColumn)                   ;
  if (uuid<=0)                                                {
    int index = indexOfTopLevelItem(ItemEditing)              ;
    takeTopLevelItem(index)                                   ;
  }                                                           ;
  ItemEditing = NULL                                          ;
  ItemWidget  = NULL                                          ;
  ItemColumn  = -1                                            ;
}

void N::EventDocks::editingFinished(void)
{
  SUID uuid = nTreeUuid(ItemEditing,0)                       ;
  QLineEdit * name = Casting(QLineEdit,ItemWidget)           ;
  if (NotNull(name))                                         {
    QString task = name->text()                              ;
    if (task.length()>0)                                     {
      AbstractGui::Mutex.lock  ()                            ;
      Sql sql = plan->sql                                    ;
      SqlConnection SC ( sql  )                              ;
      EventManager  EM ( plan )                              ;
      if (SC.open("EventDocks","editingFinished"))           {
        QString Q                                            ;
        QString oldName = ItemEditing->text(0)               ;
        if (uuid<=0)                                         {
          uuid = EM.AssureUuid(SC)                           ;
          oldName = ""                                       ;
          ItemEditing->setText(1,TypeNames[TypeUuids[None]]) ;
          ItemEditing->setData(1,Qt::UserRole,None)          ;
        }                                                    ;
        EM.UpdateName(SC,uuid,task,oldName)                  ;
        ItemEditing->setText(0,task             )            ;
        ItemEditing->setData(0,Qt::UserRole,uuid)            ;
        SC.close()                                           ;
      }                                                      ;
      SC.remove()                                            ;
      AbstractGui::Mutex.unlock()                            ;
    }                                                        ;
  }                                                          ;
  removeOldItem (  )                                         ;
  emit Update ( this , uuid )                                ;
}

void N::EventDocks::TypeChanged(int index)
{
  if (IsNull(ItemEditing)) return                               ;
  QComboBox * combo = qobject_cast<QComboBox *>(ItemWidget)     ;
  if (IsNull(combo)) return                                     ;
  SUID uuid = ItemEditing->data  (0,Qt::UserRole).toULongLong() ;
  SUID type = combo->itemData(index,Qt::UserRole).toULongLong() ;
  int  tid  = UuidTypes[type]                                   ;
  ItemEditing->setText(1,TypeNames[type] )                      ;
  ItemEditing->setData(1,Qt::UserRole,tid)                      ;
  removeOldItem (  )                                            ;
  AbstractGui::Mutex.lock  ()                                   ;
  Sql sql = plan->sql                                           ;
  SqlConnection SC(sql)                                         ;
  EventManager EM(plan)                                         ;
  if (SC.open("nTaskDocks","TypeChanged"))                      {
    QString T = PlanTable(EventHistory)                         ;
    QString Q                                                   ;
    EM.UpdateType(SC,T,uuid,tid)                                ;
    if (EventTable!=T) EM.UpdateType(SC,EventTable,uuid,tid)    ;
    SC.close()                                                  ;
  }                                                             ;
  SC.remove()                                                   ;
  AbstractGui::Mutex.unlock()                                   ;
  emit Update ( this , uuid )                                   ;
}

void N::EventDocks::NotifyChanged(int index)
{
  QComboBox * combo  = qobject_cast<QComboBox*>(ItemWidget)  ;
  SUID        uuid   = 0                                     ;
  SUID        event  = 0                                     ;
  int         column = ItemColumn                            ;
  event = nTreeUuid(ItemEditing,0)                           ;
  if (NotNull(combo))                                        {
    int index = combo->currentIndex ( )                      ;
    uuid = combo->itemData(index,Qt::UserRole).toULongLong() ;
    ItemEditing->setText(column,combo->currentText())        ;
  }                                                          ;
  removeOldItem ( )                                          ;
  if (uuid<=0) return                                        ;
  int Relation = 0                                           ;
  if (column==3) Relation = Groups::StartTrigger             ;
  if (column==5) Relation = Groups::FinalTrigger             ;
  EnterSQL ( SC , plan->sql )                                ;
    QString Q                                                ;
    Q = SC.sql.DeleteFrom                                    (
          PlanTable(Groups)                                  ,
            QString("where first = %1 and t1 = %2 and t2 = %3 and relation = %4")
            .arg(event                                       )
            .arg(Types::Schedule                             )
            .arg(Types::Trigger                              )
            .arg(Relation                                ) ) ;
    SC.Query(Q)                                              ;
    Q = SC.sql.InsertInto                                    (
          PlanTable(Groups)                                  ,
          5                                                  ,
          "first"                                            ,
          "second"                                           ,
          "t1"                                               ,
          "t2"                                               ,
          "relation"                                       ) ;
    SC . Prepare ( Q                                       ) ;
    SC . Bind    ( "first"    , event                      ) ;
    SC . Bind    ( "second"   , uuid                       ) ;
    SC . Bind    ( "t1"       , Types::Schedule            ) ;
    SC . Bind    ( "t2"       , Types::Trigger             ) ;
    SC . Bind    ( "relation" , Relation                   ) ;
    SC . Exec    (                                         ) ;
  LeaveSQL       ( SC , plan->sql                          ) ;
}

void N::EventDocks::TimeFinished(void)
{
  QDateTimeEdit * DTE = Casting(QDateTimeEdit,ItemWidget)  ;
  QDateTime       DS                                       ;
  if (NotNull(DTE))                                        {
    DS = DTE->dateTime()                                   ;
    QString DR = DS.toString("yyyy/MM/dd hh:mm:ss")        ;
    ItemEditing -> setText  ( ItemColumn , DR     )        ;
  }                                                        ;
  if (IsNull(DTE)) return                                  ;
  //////////////////////////////////////////////////////////
  StarDate  ST                                             ;
  StarDate  FT                                             ;
  SUID      UU  = 0                                        ;
  ST . Stardate = 0                                        ;
  FT . Stardate = 0                                        ;
  UU = nTreeUuid ( ItemEditing , 0 )                       ;
  if (UU>0)                                                {
    QDateTime DD                                           ;
    QString   SS                                           ;
    SS = ItemEditing->text(2)                              ;
    if (SS.length()>0)                                     {
      DD = QDateTime::fromString(SS,"yyyy/MM/dd hh:mm:ss") ;
      ST = DD                                              ;
    }                                                      ;
    SS = ItemEditing->text(4)                              ;
    if (SS.length()>0)                                     {
      DD = QDateTime::fromString(SS,"yyyy/MM/dd hh:mm:ss") ;
      FT = DD                                              ;
    }                                                      ;
  }                                                        ;
  removeOldItem ( )                                        ;
  if (ST.Stardate<=0) return                               ;
  if (FT.Stardate<=0) return                               ;
  if (UU         <=0) return                               ;
  //////////////////////////////////////////////////////////
  EventManager EM ( plan )                                 ;
  EnterSQL ( SC , plan->sql )                              ;
    EM.UpdateEvent                                         (
      SC                                                   ,
      UU                                                   ,
      Calendars::Duration                                  ,
      ST.Stardate                                          ,
      FT.Stardate                                        ) ;
    EM.attachSpot                                          (
      SC                                                   ,
      UU                                                   ,
      History::WorkingPeriod                               ,
      ST.Stardate                                          ,
      FT.Stardate                                        ) ;
  LeaveSQL ( SC , plan->sql )                              ;
  Alert    ( Done           )                              ;
}

void N::EventDocks::setTrigger(QTreeWidgetItem * item,int column)
{
  removeOldItem()                              ;
  QComboBox * CB = new QComboBox(this)         ;
  ItemEditing    = item                        ;
  ItemColumn     = column                      ;
  ItemWidget     = (QWidget *)CB               ;
  setItemWidget ( item , column , CB )         ;
  //////////////////////////////////////////////
  EventManager EM(plan)                        ;
  EnterSQL ( SC , plan->sql )                  ;
    QString Name                               ;
    SUID    uuid                               ;
    UUIDs   Uuids                              ;
    Uuids = SC.Uuids                           (
      PlanTable(Triggers)                      ,
      "uuid","order by id asc"               ) ;
    foreach (uuid,Uuids)                       {
      Name  = SC.getName                       (
         PlanTable(Names)                      ,
        "uuid",vLanguageId,uuid              ) ;
      CB->addItem(Name,uuid)                   ;
    }                                          ;
  LeaveSQL ( SC , plan->sql )                  ;
  //////////////////////////////////////////////
  connect(CB  ,SIGNAL(activated    (int))      ,
          this,SLOT  (NotifyChanged(int)) )    ;
  CB->setMaxVisibleItems(30)                   ;
  CB->showPopup()                              ;
}

void N::EventDocks::setDateTime(QTreeWidgetItem * item,int column)
{
  removeOldItem()                                                       ;
  QString         DS  = item -> text ( column )                         ;
  if (DS.length()<=0) DS = nTimeNow.toString("yyyy/MM/dd hh:mm:00")     ;
  QDateTimeEdit * DTE = new QDateTimeEdit(this)                         ;
  QDateTime       DT  = QDateTime::fromString(DS,"yyyy/MM/dd hh:mm:ss") ;
  DTE         -> setDateTime ( DT )                                     ;
  ItemEditing  = item                                                   ;
  ItemColumn   = column                                                 ;
  ItemWidget   = (QWidget *)DTE                                         ;
  setItemWidget(item,column,DTE)                                        ;
  connect( DTE , SIGNAL(editingFinished()), this,SLOT(TimeFinished()) ) ;
}

void N::EventDocks::Update(SUID uuid)
{
  QTreeWidgetItem * item = NULL ;
  for (int i=0;IsNull(item) && i<topLevelItemCount();i++) {
    QTreeWidgetItem * it = topLevelItem(i)                ;
    if (RetrieveUuid(it,0)==uuid) item = it               ;
  }                                                       ;
  EventManager EM(plan)                                   ;
  EnterSQL(SC,plan->sql)                                  ;
    QString name = EM.Name(SC,uuid)                       ;
    if (item==NULL) item = addItem(name,uuid,0) ; else    {
      for (int i=0;i<columnCount();i++)                   {
        item->setText(i,"")                               ;
      }                                                   ;
      item-> setText(0,name)                              ;
    }                                                     ;
    Load(SC,uuid,item)                                    ;
  LeaveSQL(SC,plan->sql)                                  ;
  emit AutoFit ()                                             ;
}

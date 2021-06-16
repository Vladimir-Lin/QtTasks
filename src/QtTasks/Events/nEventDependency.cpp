#include <qttasks.h>
#include "ui_nEventDependency.h"

N::EventDependency:: EventDependency ( QWidget * parent , Plan * p )
                   : Widget          (           parent ,        p )
                   , ui              ( new Ui::nEventDependency    )
                   , TimeDepend      ( NULL                        )
                   , EditingItem     ( NULL                        )
{
  Configure ( ) ;
}

N::EventDependency::~EventDependency(void)
{
  delete ui ;
}

void N::EventDependency::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
  Relocation           (   ) ;
}

void N::EventDependency::showEvent(QShowEvent * e)
{
  QWidget::showEvent ( e ) ;
  Relocation         (   ) ;
}

void N::EventDependency::closeEvent(QCloseEvent * e)
{
  if ( isLoading ( ) )      {
    stopForcely  ( )        ;
  }                         ;
  QWidget::closeEvent ( e ) ;
}

void N::EventDependency::SendActivity(int state)
{
  emit Activity ( state ) ;
}

void N::EventDependency::Configure(void)
{
  NewTreeWidgetItem                   ( head                       ) ;
  ui   -> setupUi                     ( this                       ) ;
  head -> setText                     ( 0 , tr("Event")            ) ;
  head -> setText                     ( 1 , tr("Relation")         ) ;
  head -> setText                     ( 2 , tr("Time")             ) ;
  head -> setTextAlignment            ( 0 , Qt::AlignCenter        ) ;
  head -> setTextAlignment            ( 1 , Qt::AlignCenter        ) ;
  head -> setTextAlignment            ( 2 , Qt::AlignCenter        ) ;
  ui   -> Dependency -> setHeaderItem ( head                       ) ;
  ui   -> Relation   -> addItem       ( tr("After"                 ) ,
                                        RelationUUID(After)        ) ;
  ui   -> Relation   -> addItem       ( tr("Before"  )               ,
                                        RelationUUID(Before)       ) ;
  ui   -> Relation   -> addItem       ( tr("Subordination")          ,
                                        RelationUUID(Subordination)) ;
  ui   -> Relation   -> addItem       ( tr("Contains")               ,
                                        RelationUUID(Contains)     ) ;
  plan -> setFont                     ( this                       ) ;
  nConnect ( this , SIGNAL ( PrivateActivity(int)      )   ,
             this , SLOT   ( SendActivity   (int)      ) ) ;
  start                               ( 11001                      ) ;
}

void N::EventDependency::run(int type,ThreadData * data)
{
  switch ( type )                                                        {
    case 10001                                                           :
      emit PrivateActivity ( 0                                         ) ;
      Load                 ( data -> Arguments [ 0 ] . toULongLong ( ) ) ;
      emit PrivateActivity ( 1                                         ) ;
    break                                                                ;
    case 11001                                                           :
      if ( isLoading ( ) ) return                                        ;
      emit PrivateActivity ( 0                                         ) ;
      startLoading         (                                           ) ;
      pushCanStop          (                                           ) ;
      List                 (                                           ) ;
      popCanStop           (                                           ) ;
      stopLoading          (                                           ) ;
      emit PrivateActivity ( 1                                         ) ;
    break                                                                ;
  }                                                                      ;
}

bool N::EventDependency::Relocation(void)
{
  QRect g                                            ;
  ////////////////////////////////////////////////////
  g = ui -> Events     -> geometry    (            ) ;
  g . setRight                        ( width  ( ) ) ;
  ui     -> Events     -> setGeometry ( g          ) ;
  ////////////////////////////////////////////////////
  g = ui -> Dependency -> geometry    (            ) ;
  g . setRight                        ( width  ( ) ) ;
  g . setBottom                       ( height ( ) ) ;
  ui     -> Dependency -> setGeometry ( g          ) ;
  ////////////////////////////////////////////////////
  return true                                        ;
}

bool N::EventDependency::startup(SUID uuid)
{
  VarArgs args                  ;
  ui -> Dependency -> clear ( ) ;
  args << uuid                  ;
  start ( 10001 , args )        ;
  return true                   ;
}

void N::EventDependency::List(void)
{
  ui -> Add    -> setEnabled                 ( false )          ;
  ui -> Events -> blockSignals               ( true  )          ;
  ui -> Events -> clear                      (       )          ;
  ui -> Events -> setEnabled                 ( false )          ;
  ui -> Events -> lineEdit ( ) -> setEnabled ( false )          ;
  ///////////////////////////////////////////////////////////////
  EventManager  EM ( plan        )                              ;
  SqlConnection SC ( plan -> sql )                              ;
  if ( SC . open ( FunctionString ) )                           {
    UUIDs     U                                                 ;
    SUID      u                                                 ;
    QDateTime Now = nTimeNow                                    ;
    QDateTime ST                                                ;
    QDateTime ET                                                ;
    QTime     ZT ( 0 , 0 , 0 , 0 )                              ;
    QDate     NT  = Now . date ( )                              ;
    ST = QDateTime ( QDate ( NT.year()-1,NT.month(),1 ) , ZT  ) ;
    ET = QDateTime ( QDate ( NT.year()+1,NT.month(),1 ) , ZT  ) ;
    U  = EM . Events ( SC , ST , ET )                           ;
    foreach ( u , U )                                           {
      QString n = EM . Name ( SC , u )                          ;
      ui -> Events -> insertItem ( 0 , n , u )                  ;
    }                                                           ;
    SC . close  ( )                                             ;
  }                                                             ;
  SC   . remove ( )                                             ;
  ///////////////////////////////////////////////////////////////
  ui -> Events -> setEnabled                 ( true  )          ;
  ui -> Events -> lineEdit ( ) -> setEnabled ( true  )          ;
  ui -> Events -> blockSignals               ( false )          ;
  ui -> Add    -> setEnabled                 ( true  )          ;
}

void N::EventDependency::Load(SUID uuid)
{
  ui -> Dependency -> clear ( )                                 ;
  if ( 0 == uuid ) return                                       ;
  ///////////////////////////////////////////////////////////////
  EventManager  EM ( plan        )                              ;
  SqlConnection SC ( plan -> sql )                              ;
  if ( SC . open ( FunctionString ) )                           {
    QString Q                                                   ;
    UUIDs   U                                                   ;
    SUID    u                                                   ;
    Q = SC . sql . SelectFrom                                   (
          "second"                                              ,
          PlanTable(Triples)                                    ,
          QString("where `first` = %1 and `type` = %2"          )
          . arg ( uuid                                          )
          . arg ( Types::Schedule                             ) ,
          SC . OrderByAsc ( "id" )                            ) ;
    SqlLoopNow ( SC , Q )                                       ;
      U << SC . Uuid ( 0 )                                      ;
    SqlLoopErr ( SC , Q )                                       ;
    SqlLoopEnd ( SC , Q )                                       ;
    foreach ( u , U )                                           {
      Q = SC . sql . SelectFrom                                 (
            "third,flags"                                       ,
            PlanTable(Triples)                                  ,
            QString("where `first` = %1"
                     " and `second` = %2"
                     " and `type` = %3"                         )
            . arg ( uuid                                        )
            . arg ( u                                           )
            . arg ( Types::Schedule                         ) ) ;
      if ( SC . Fetch ( Q ) )                                   {
        SUID    t = SC . Uuid ( 0      )                        ;
        SUID    f = SC . Uuid ( 1      )                        ;
        QString n = EM . Name ( SC , u )                        ;
        bool    c = false                                       ;
        QString r = ""                                          ;
        QString g = QString::number ( f )                       ;
        /////////////////////////////////////////////////////////
        switch ( ToGroupID ( t ) )                              {
          case Groups::After                                    :
            c = true                                            ;
            r = tr("After")                                     ;
          break                                                 ;
          case Groups::Before                                   :
            c = true                                            ;
            r = tr("Before")                                    ;
          break                                                 ;
          case Groups::Subordination                            :
            c = true                                            ;
            r = tr("Subordination")                             ;
          break                                                 ;
          case Groups::Contains                                 :
            c = true                                            ;
            r = tr("Contains")                                  ;
          break                                                 ;
        }                                                       ;
        /////////////////////////////////////////////////////////
        if ( c )                                                {
          NewTreeWidgetItem ( IT                   )            ;
          IT -> setData     ( 0 , Qt::UserRole , u )            ;
          IT -> setData     ( 1 , Qt::UserRole , t )            ;
          IT -> setText     ( 0 , n                )            ;
          IT -> setText     ( 1 , r                )            ;
          IT -> setText     ( 2 , g                )            ;
          ui -> Dependency -> addTopLevelItem ( IT )            ;
        }                                                       ;
      }                                                         ;
    }                                                           ;
    SC . close  ( )                                             ;
  }                                                             ;
  SC   . remove ( )                                             ;
  ///////////////////////////////////////////////////////////////
}

bool N::EventDependency::store(SqlConnection & SC,SUID uuid)
{
  if ( uuid <= 0 ) return false                                          ;
  ////////////////////////////////////////////////////////////////////////
  QString Q                                                              ;
  ////////////////////////////////////////////////////////////////////////
  Q = QString ( "delete from `%1`"
                " where `first` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(After)                                      )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  Q = QString ( "delete from `%1`"
                " where `first` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(Before)                                     )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  Q = QString ( "delete from `%1`"
                " where `first` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(Subordination)                              )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  Q = QString ( "delete from `%1`"
                " where `first` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(Contains)                                   )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  ////////////////////////////////////////////////////////////////////////
  Q = QString ( "delete from `%1`"
                " where `second` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(After)                                      )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  Q = QString ( "delete from `%1`"
                " where `second` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(Before)                                     )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  Q = QString ( "delete from `%1`"
                " where `second` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(Subordination)                              )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  Q = QString ( "delete from `%1`"
                " where `second` = %2"
                  " and `third` = %3"
                  " and `type` = %4 ;"                                   )
      . arg   ( PlanTable(Triples)                                       )
      . arg   ( uuid                                                     )
      . arg   ( RelationUUID(Contains)                                   )
      . arg   ( Types::Schedule                                          )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  ////////////////////////////////////////////////////////////////////////
  for (int i = 0 ; i < ui -> Dependency -> topLevelItemCount ( ) ; i++ ) {
    QTreeWidgetItem * it = ui -> Dependency -> topLevelItem ( i )        ;
    SUID              v  = nTreeUuid  ( it , 0 )                         ;
    SUID              z  = nTreeUuid  ( it , 1 )                         ;
    int               d  = it -> text ( 2      ) . toInt ( )             ;
    //////////////////////////////////////////////////////////////////////
    Q = QString ( "insert into `%1`"
                  " (`first`,`second`,`third`,`type`,`flags`)"
                  " values (%2,%3,%4,%5,%6) ;"                           )
        . arg   ( PlanTable(Triples)                                     )
        . arg   ( uuid                                                   )
        . arg   ( v                                                      )
        . arg   ( z                                                      )
        . arg   ( Types::Schedule                                        )
        . arg   ( d                                                    ) ;
    SC . Query  ( Q                                                    ) ;
    //////////////////////////////////////////////////////////////////////
    switch ( ToGroupID(z) )                                              {
      case Groups::After                                                 :
        z = RelationUUID ( Before        )                               ;
      break                                                              ;
      case Groups::Before                                                :
        z = RelationUUID ( After         )                               ;
      break                                                              ;
      case Groups::Subordination                                         :
        z = RelationUUID ( Contains      )                               ;
      break                                                              ;
      case Groups::Contains                                              :
        z = RelationUUID ( Subordination )                               ;
      break                                                              ;
    }                                                                    ;
    //////////////////////////////////////////////////////////////////////
    Q = QString ( "insert into `%1`"
                  " (`first`,`second`,`third`,`type`,`flags`)"
                  " values (%2,%3,%4,%5,%6) ;"                           )
        . arg   ( PlanTable(Triples)                                     )
        . arg   ( v                                                      )
        . arg   ( uuid                                                   )
        . arg   ( z                                                      )
        . arg   ( Types::Schedule                                        )
        . arg   ( d                                                    ) ;
    SC . Query  ( Q                                                    ) ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  return true                                                            ;
}

void N::EventDependency::Add(void)
{
  int index = ui -> Events   -> currentIndex ( )                       ;
  if ( index < 0 ) return                                              ;
  int type  = ui -> Relation -> currentIndex ( )                       ;
  if ( type  < 0 ) return                                              ;
  //////////////////////////////////////////////////////////////////////
  SUID    u   = ui -> Events   -> itemData ( index ) . toULongLong ( ) ;
  SUID    v   = ui -> Relation -> itemData ( type  ) . toULongLong ( ) ;
  QString ons = ui -> Events   -> currentText                      ( ) ;
  QString rns = ui -> Relation -> currentText                      ( ) ;
  int     rts = 0                                                      ;
  int     rtt = ToGroupID ( v )                                        ;
  //////////////////////////////////////////////////////////////////////
  switch ( rtt )                                                       {
    case Groups::After                                                 :
    case Groups::Before                                                :
      rts = 300                                                        ;
    break                                                              ;
    case Groups::Subordination                                         :
    case Groups::Contains                                              :
    break                                                              ;
  }                                                                    ;
  //////////////////////////////////////////////////////////////////////
  NewTreeWidgetItem                   ( IT                       )     ;
  IT -> setData                       ( 0 , Qt::UserRole , u     )     ;
  IT -> setData                       ( 1 , Qt::UserRole , v     )     ;
  IT -> setText                       ( 0 , ons                  )     ;
  IT -> setText                       ( 1 , rns                  )     ;
  IT -> setText                       ( 2 , QString::number(rts) )     ;
  ui -> Dependency -> addTopLevelItem ( IT                       )     ;
  //////////////////////////////////////////////////////////////////////
  Alert                               ( Click                    )     ;
}

void N::EventDependency::Remove(void)
{
  QList<QTreeWidgetItem *> items                           ;
  items = ui -> Dependency -> selectedItems ( )            ;
  if ( items . count ( ) <= 0 )                            {
    Alert ( Error )                                        ;
    return                                                 ;
  }                                                        ;
  for (int i = 0 ; i < items . count ( ) ; i++ )           {
    QTreeWidgetItem * it = items [ i ]                     ;
    int               index                                ;
    index = ui -> Dependency -> indexOfTopLevelItem ( it ) ;
    if ( index >= 0 )                                      {
      ui -> Dependency -> takeTopLevelItem ( index )       ;
    }                                                      ;
  }                                                        ;
  ui -> Remove -> setEnabled ( false )                     ;
  Alert                      ( Done  )                     ;
}

void N::EventDependency::itemClicked(QTreeWidgetItem * item,int column)
{
  if ( NULL != item )                   {
    ui -> Remove -> setEnabled ( true ) ;
  }                                     ;
  Alert ( Click )                       ;
}

void N::EventDependency::itemDoubleClicked(QTreeWidgetItem * item,int column)
{
  switch ( column )                                            {
    case 0                                                     :
    return                                                     ;
    case 1                                                     :
    return                                                     ;
    case 2                                                     :
    break                                                      ;
  }                                                            ;
  //////////////////////////////////////////////////////////////
  if ( NotNull(EditingItem) && NotNull(TimeDepend) )           {
    ui -> Dependency -> removeItemWidget ( EditingItem , 2 )   ;
    EditingItem = NULL                                         ;
    TimeDepend  = NULL                                         ;
  }                                                            ;
  //////////////////////////////////////////////////////////////
  EditingItem = item                                           ;
  TimeDepend  = new SpinBox ( NULL , plan                    ) ;
  TimeDepend -> setRange    ( 0    , INT_MAX                 ) ;
  TimeDepend -> setValue    ( item -> text ( 2 ) . toInt ( ) ) ;
  ui -> Dependency -> setItemWidget ( item , 2 , TimeDepend  ) ;
  //////////////////////////////////////////////////////////////
  nConnect ( TimeDepend , SIGNAL ( editingFinished ( ) )       ,
             this       , SLOT   ( timeChanged     ( ) )     ) ;
}

void N::EventDependency::timeChanged(void)
{
  if ( IsNull ( TimeDepend  ) ) return                     ;
  if ( IsNull ( EditingItem ) ) return                     ;
  int v = TimeDepend -> value ( )                          ;
  EditingItem -> setText ( 2 , QString::number(v) )        ;
  ui -> Dependency -> removeItemWidget ( EditingItem , 2 ) ;
  EditingItem = NULL                                       ;
  TimeDepend  = NULL                                       ;
}

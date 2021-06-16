#include <qttasks.h>
#include "ui_nEventOwners.h"

N::EventOwners:: EventOwners  ( QWidget * parent , Plan * p )
               : Widget       (           parent ,        p )
               , ui           ( new Ui::nEventOwners        )
               , uuid         ( 0                           )
               , crowd        ( 0                           )
               , organization ( 0                           )
{
  Configure ( ) ;
}

N::EventOwners::~EventOwners(void)
{
  delete ui ;
}

void N::EventOwners::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
  Relocation           (   ) ;
}

void N::EventOwners::showEvent(QShowEvent * e)
{
  QWidget::showEvent ( e ) ;
  Relocation         (   ) ;
}

void N::EventOwners::closeEvent(QCloseEvent * e)
{
  if ( isLoading ( ) )      {
    stopForcely  ( )        ;
  }                         ;
  QWidget::closeEvent ( e ) ;
}

void N::EventOwners::SendActivity(int state)
{
  emit Activity ( state ) ;
}

void N::EventOwners::Configure(void)
{
  NewTreeWidgetItem               ( head                ) ;
  ui   -> setupUi                 ( this                ) ;
  head -> setText                 ( 0 , tr("Type")      ) ;
  head -> setText                 ( 1 , tr("Owner")     ) ;
  head -> setTextAlignment        ( 0 , Qt::AlignCenter ) ;
  head -> setTextAlignment        ( 1 , Qt::AlignCenter ) ;
  ui   -> Owners -> setHeaderItem ( head                ) ;
  ui   -> Type   -> addItem       ( tr("Equipment")     ) ;
  ui   -> Type   -> addItem       ( tr("People")        ) ;
  ui   -> Type   -> addItem       ( tr("Organization")  ) ;
  ui   -> Type   -> addItem       ( tr("Application")   ) ;
  plan -> setFont                 ( this                ) ;
  nConnect ( this , SIGNAL ( PrivateActivity(int)     )   ,
             this , SLOT   ( SendActivity   (int)     ) ) ;
  start                           ( 11001               ) ;
}

void N::EventOwners::run(int type,ThreadData * data)
{
  switch ( type )                 {
    case 10001                    :
      emit PrivateActivity ( 0 )  ;
      Load                 (   )  ;
      emit PrivateActivity ( 1 )  ;
    break                         ;
    case 11001                    :
      if ( isLoading ( ) ) return ;
      emit PrivateActivity ( 0 )  ;
      startLoading         (   )  ;
      pushCanStop          (   )  ;
      LoadEquipments       (   )  ;
      popCanStop           (   )  ;
      stopLoading          (   )  ;
      emit PrivateActivity ( 1 )  ;
    break                         ;
    case 11002                    :
      if ( isLoading ( ) ) return ;
      emit PrivateActivity ( 0 )  ;
      startLoading         (   )  ;
      pushCanStop          (   )  ;
      LoadPeople           (   )  ;
      popCanStop           (   )  ;
      stopLoading          (   )  ;
      emit PrivateActivity ( 1 )  ;
    break                         ;
    case 11003                    :
      if ( isLoading ( ) ) return ;
      emit PrivateActivity ( 0 )  ;
      startLoading         (   )  ;
      pushCanStop          (   )  ;
      LoadOrganizations    (   )  ;
      popCanStop           (   )  ;
      stopLoading          (   )  ;
      emit PrivateActivity ( 1 )  ;
    break                         ;
    case 11004                    :
      if ( isLoading ( ) ) return ;
      emit PrivateActivity ( 0 )  ;
      startLoading         (   )  ;
      pushCanStop          (   )  ;
      LoadApplications     (   )  ;
      popCanStop           (   )  ;
      stopLoading          (   )  ;
      emit PrivateActivity ( 1 )  ;
    break                         ;
  }                               ;
}

bool N::EventOwners::Relocation(void)
{
  QRect g                                        ;
  ////////////////////////////////////////////////
  g = ui -> Type   -> geometry    (            ) ;
  g . setRight                    ( width  ( ) ) ;
  ui     -> Type   -> setGeometry ( g          ) ;
  ////////////////////////////////////////////////
  g = ui -> Items  -> geometry    (            ) ;
  g . setRight                    ( width  ( ) ) ;
  ui     -> Items  -> setGeometry ( g          ) ;
  ////////////////////////////////////////////////
  g = ui -> Owners -> geometry    (            ) ;
  g . setRight                    ( width  ( ) ) ;
  g . setBottom                   ( height ( ) ) ;
  ui     -> Owners -> setGeometry ( g          ) ;
  ////////////////////////////////////////////////
  return true                                    ;
}

bool N::EventOwners::startup(SUID u)
{
  uuid = u                  ;
  ui -> Owners -> clear ( ) ;
  start ( 10001 )           ;
  return true               ;
}

bool N::EventOwners::store(SqlConnection & SC,SUID u)
{
  if ( u <= 0 ) return false                                            ;
  ///////////////////////////////////////////////////////////////////////
  QString      Q                                                        ;
  EventManager EM ( plan )                                              ;
  ///////////////////////////////////////////////////////////////////////
  Q = QString ( "delete from `%1`"
                " where `t2` = %2"
                " and ( ( `t1` = %3 ) or"
                      " ( `t1` = %4 ) or"
                      " ( `t1` = %5 ) )"
                " and `relation` = %6"
                " and `second` = %7 ;"                                  )
      . arg   ( PlanTable(Groups)                                       )
      . arg   ( Types::Schedule                                         )
      . arg   ( Types::Equipment                                        )
      . arg   ( Types::People                                           )
      . arg   ( Types::Organization                                     )
      . arg   ( Groups::Subordination                                   )
      . arg   ( u                                                     ) ;
  SC . Query ( Q )                                                      ;
  ///////////////////////////////////////////////////////////////////////
  EM . DeleteVariable ( SC , u , "Application" )                        ;
  ///////////////////////////////////////////////////////////////////////
  for (int i = 0 ; i < ui -> Owners -> topLevelItemCount ( ) ; i++ )    {
    QTreeWidgetItem * it = ui -> Owners -> topLevelItem ( i )           ;
    int               t  = nTreeInt   ( it , 0 )                        ;
    SUID              v  = nTreeUuid  ( it , 1 )                        ;
    QString           n  = it -> text ( 1      )                        ;
    int               p  = i + 1                                        ;
    if ( N::Types::Execution == t )                                     {
      QVariant Z = n                                                    ;
      EM . SaveVariable ( SC , u , "Application" , Z )                  ;
    } else                                                              {
      Q = QString ( "insert into `%1`"
                    " (`first`,`second`,`t1`,`t2`,`relation`,`position`)"
                    " values (%2,%3,%4,%5,%6,%7) ;"                     )
          . arg   ( PlanTable(Groups)                                   )
          . arg   ( v                                                   )
          . arg   ( u                                                   )
          . arg   ( t                                                   )
          . arg   ( Types::Schedule                                     )
          . arg   ( Groups::Subordination                               )
          . arg   ( p                                                 ) ;
      SC . Query  ( Q                                                 ) ;
    }                                                                   ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  return true                                                           ;
}

void N::EventOwners::Load(void)
{
  ui -> Owners -> clear ( )                                      ;
  if ( 0 == uuid ) return                                        ;
  ////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                               ;
  EventManager  EM ( plan        )                               ;
  if ( SC . open ( FunctionString ) )                            {
    QString  Q                                                   ;
    UUIDs    U                                                   ;
    RMAPs    R                                                   ;
    SUID     u                                                   ;
    QVariant Z                                                   ;
    //////////////////////////////////////////////////////////////
    Q = SC . sql . SelectFrom                                    (
          "first,t1"                                             ,
          PlanTable(Groups)                                      ,
          QString("where `t2` = %1"
                  " and ( ( `t1` = %2 ) or"
                        " ( `t1` = %3 ) or"
                        " ( `t1` = %4 ) )"
                  " and `relation` = %5"
                  " and `second` = %6"                           )
          . arg ( Types::Schedule                                )
          . arg ( Types::Equipment                               )
          . arg ( Types::People                                  )
          . arg ( Types::Organization                            )
          . arg ( Groups::Subordination                          )
          . arg ( uuid                                         ) ,
          SC . OrderByAsc ( "id" )                             ) ;
    SqlLoopNow ( SC , Q )                                        ;
      int t                                                      ;
      t = SC . Int  ( 1 )                                        ;
      u = SC . Uuid ( 0 )                                        ;
      U << u                                                     ;
      R  [ u ] = t                                               ;
    SqlLoopErr ( SC , Q )                                        ;
    SqlLoopEnd ( SC , Q )                                        ;
    //////////////////////////////////////////////////////////////
    foreach ( u , U )                                            {
      QStringList S                                              ;
      int         t = R [ u ]                                    ;
      NewTreeWidgetItem ( IT )                                   ;
      S . clear ( )                                              ;
      IT -> setData ( 0 , Qt::UserRole , t )                     ;
      IT -> setData ( 1 , Qt::UserRole , u )                     ;
      switch ( t )                                               {
        case Types::Equipment                                    :
          IT -> setText ( 0 , tr("Equipment")    )               ;
          Q = SC . sql . SelectFrom                              (
                "identifier"                                     ,
                PlanTable(Equipments)                            ,
                SC . WhereUuid ( u )                           ) ;
          if (SC . Fetch ( Q ) )                                 {
            QString n = SC . String ( 0 )                        ;
            IT -> setText ( 1 , n )                              ;
          }                                                      ;
        break                                                    ;
        case Types::People                                       :
          IT -> setText ( 0 , tr("People")       )               ;
          N::Manager::UuidNames ( *plan , SC , u , S )           ;
          if ( S . count ( ) > 0 )                               {
            IT -> setText ( 1 , S [ 0 ] )                        ;
          }                                                      ;
        break                                                    ;
        case Types::Organization                                 :
          IT -> setText ( 0 , tr("Organization") )               ;
          N::Manager::UuidNames ( *plan , SC , u , S )           ;
          if ( S . count ( ) > 0 )                               {
            IT -> setText ( 1 , S [ 0 ] )                        ;
          }                                                      ;
        break                                                    ;
      }                                                          ;
      ui -> Owners -> addTopLevelItem ( IT )                     ;
    }                                                            ;
    //////////////////////////////////////////////////////////////
    if ( EM . LoadVariable ( SC , uuid , "Application" , Z ) )   {
      QString zs = Z . toString ( )                              ;
      if ( zs . length ( ) > 0 )                                 {
        NewTreeWidgetItem ( IT )                                 ;
        IT -> setData ( 0 , Qt::UserRole , N::Types::Execution ) ;
        IT -> setData ( 1 , Qt::UserRole , 0                   ) ;
        IT -> setText ( 0 , tr("Application")                  ) ;
        IT -> setText ( 1 , zs                                 ) ;
        ui -> Owners -> addTopLevelItem ( IT )                   ;
      }                                                          ;
    }                                                            ;
    //////////////////////////////////////////////////////////////
    SC . close  ( )                                              ;
  }                                                              ;
  SC   . remove ( )                                              ;
}

void N::EventOwners::LoadEquipments(void)
{
  ui -> Add   -> setEnabled                 ( false )           ;
  ui -> Type  -> blockSignals               ( true  )           ;
  ui -> Type  -> setEnabled                 ( false )           ;
  ui -> Type  -> lineEdit ( ) -> setEnabled ( false )           ;
  ui -> Items -> blockSignals               ( true  )           ;
  ui -> Items -> clear                      (       )           ;
  ui -> Items -> setEnabled                 ( false )           ;
  ui -> Items -> lineEdit ( ) -> setEnabled ( false )           ;
  ///////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                              ;
  if ( SC . open ( FunctionString ) )                           {
    QString Q                                                   ;
    Q = SC . sql . SelectFrom                                   (
          "uuid,identifier"                                     ,
          PlanTable(Equipments)                                 ,
          SC . OrderByAsc ( "id" )                            ) ;
    SqlLoopNow ( SC , Q         )                               ;
      SUID    u = SC . Uuid   (0)                               ;
      QString s = SC . String (1)                               ;
      ui -> Items -> addItem ( s , u )                          ;
    SqlLoopErr ( SC , Q         )                               ;
    SqlLoopEnd ( SC , Q         )                               ;
    SC . close  ( )                                             ;
  }                                                             ;
  SC   . remove ( )                                             ;
  ///////////////////////////////////////////////////////////////
  ui -> Items -> lineEdit ( ) -> setText      ( ""    )         ;
  if ( plan -> Machine > 0 )                                    {
    ( * ( ui -> Items ) ) <= plan -> Machine                    ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  ui -> Type  -> setEnabled                   ( true  )         ;
  ui -> Type  -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Type  -> blockSignals                 ( false )         ;
  ui -> Items -> lineEdit ( ) -> blockSignals ( false )         ;
  ui -> Items -> blockSignals                 ( false )         ;
  ui -> Items -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Items -> setEnabled                   ( true  )         ;
  ui -> Add   -> setEnabled                   ( true  )         ;
}

void N::EventOwners::LoadPeople(void)
{
  ui -> Add   -> setEnabled                 ( false )           ;
  ui -> Type  -> blockSignals               ( true  )           ;
  ui -> Type  -> setEnabled                 ( false )           ;
  ui -> Type  -> lineEdit ( ) -> setEnabled ( false )           ;
  ui -> Items -> blockSignals               ( true  )           ;
  ui -> Items -> clear                      (       )           ;
  ui -> Items -> setEnabled                 ( false )           ;
  ui -> Items -> lineEdit ( ) -> setEnabled ( false )           ;
  ///////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                              ;
  if ( SC . open ( FunctionString ) )                           {
    QString Q                                                   ;
    UUIDs   U                                                   ;
    if ( crowd <= 0 )                                           {
      U = SC . Uuids                                            (
            PlanTable(PeopleUuid)                               ,
            "uuid"                                              ,
            SC . OrderByAsc ( "id" )                          ) ;
    } else                                                      {
      Q = QString("select `second` from %1"
                  " where `t1` = %2"
                    " and `t2` = %3"
                    " and `relation` = %4"
                    " and `first` = %5"
                    " order by `position` asc ;"                )
          . arg ( PlanTable(Groups)                             )
          . arg ( Types::Division                               )
          . arg ( Types::People                                 )
          . arg ( Groups::Subordination                         )
          . arg ( crowd                                       ) ;
      SqlLoopNow ( SC , Q )                                     ;
        U << SC . Uuid ( 0 )                                    ;
      SqlLoopErr ( SC , Q )                                     ;
      SqlLoopEnd ( SC , Q )                                     ;
    }                                                           ;
    /////////////////////////////////////////////////////////////
    for (int i = 0 ; isLoading ( ) && i < U . count ( ) ; i++ ) {
      SUID        u = U [ i ]                                   ;
      QStringList S                                             ;
      QString     s                                             ;
      S . clear ( )                                             ;
      N::Manager::UuidNames ( *plan , SC , u , S )              ;
      foreach ( s , S )                                         {
        ui -> Items -> addItem ( s , u )                        ;
      }                                                         ;
    }                                                           ;
    /////////////////////////////////////////////////////////////
    SC . close  ( )                                             ;
  }                                                             ;
  SC   . remove ( )                                             ;
  ///////////////////////////////////////////////////////////////
  ui -> Items -> lineEdit ( ) -> setText      ( ""    )         ;
  if ( plan -> UserUuid > 0 )                                   {
    ( * ( ui -> Items ) ) <= plan -> UserUuid                   ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  ui -> Type  -> setEnabled                   ( true  )         ;
  ui -> Type  -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Items -> lineEdit ( ) -> blockSignals ( false )         ;
  ui -> Items -> blockSignals                 ( false )         ;
  ui -> Items -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Items -> setEnabled                   ( true  )         ;
  ui -> Type  -> blockSignals                 ( false )         ;
  ui -> Add   -> setEnabled                   ( true  )         ;
}

void N::EventOwners::LoadOrganizations(void)
{
  ui -> Add   -> setEnabled                 ( false )           ;
  ui -> Type  -> blockSignals               ( true  )           ;
  ui -> Type  -> setEnabled                 ( false )           ;
  ui -> Type  -> lineEdit ( ) -> setEnabled ( false )           ;
  ui -> Items -> blockSignals               ( true  )           ;
  ui -> Items -> clear                      (       )           ;
  ui -> Items -> setEnabled                 ( false )           ;
  ui -> Items -> lineEdit ( ) -> setEnabled ( false )           ;
  ///////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                              ;
  if ( SC . open ( FunctionString ) )                           {
    QString Q                                                   ;
    UUIDs   U                                                   ;
    if ( organization <= 0 )                                    {
      U = SC . Uuids                                            (
            PlanTable(Organizations)                            ,
            "uuid"                                              ,
            SC . OrderByAsc ( "id" )                          ) ;
    } else                                                      {
      Q = QString("select `second` from %1"
                  " where `t1` = %2"
                    " and `t2` = %3"
                    " and `relation` = %4"
                    " and `first` = %5"
                    " order by `position` asc ;"                )
          . arg ( PlanTable(Groups)                             )
          . arg ( Types::Division                               )
          . arg ( Types::Organization                           )
          . arg ( Groups::Subordination                         )
          . arg ( organization                                ) ;
      SqlLoopNow ( SC , Q )                                     ;
        U << SC . Uuid ( 0 )                                    ;
      SqlLoopErr ( SC , Q )                                     ;
      SqlLoopEnd ( SC , Q )                                     ;
    }                                                           ;
    /////////////////////////////////////////////////////////////
    for (int i = 0 ; isLoading ( ) && i < U . count ( ) ; i++ ) {
      SUID        u = U [ i ]                                   ;
      QStringList S                                             ;
      QString     s                                             ;
      S . clear ( )                                             ;
      N::Manager::UuidNames ( *plan , SC , u , S )              ;
      foreach ( s , S )                                         {
        ui -> Items -> addItem ( s , u )                        ;
      }                                                         ;
    }                                                           ;
    /////////////////////////////////////////////////////////////
    SC . close  ( )                                             ;
  }                                                             ;
  SC   . remove ( )                                             ;
  ///////////////////////////////////////////////////////////////
  ui -> Items -> lineEdit ( ) -> setText      ( ""    )         ;
  ui -> Type  -> setEnabled                   ( true  )         ;
  ui -> Type  -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Items -> lineEdit ( ) -> blockSignals ( false )         ;
  ui -> Items -> blockSignals                 ( false )         ;
  ui -> Items -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Items -> setEnabled                   ( true  )         ;
  ui -> Type  -> blockSignals                 ( false )         ;
  ui -> Add   -> setEnabled                   ( true  )         ;
}

void N::EventOwners::LoadApplications(void)
{
  ui -> Add   -> setEnabled                 ( false )           ;
  ui -> Type  -> blockSignals               ( true  )           ;
  ui -> Type  -> setEnabled                 ( false )           ;
  ui -> Type  -> lineEdit ( ) -> setEnabled ( false )           ;
  ui -> Items -> blockSignals               ( true  )           ;
  ui -> Items -> clear                      (       )           ;
  ui -> Items -> setEnabled                 ( false )           ;
  ui -> Items -> lineEdit ( ) -> setEnabled ( false )           ;
  ///////////////////////////////////////////////////////////////
  ui -> Items -> addItem ( "CIOS"        ,  1 )                 ;
  ui -> Items -> addItem ( "Player"      ,  2 )                 ;
  ui -> Items -> addItem ( "MtJsGUI"     ,  4 )                 ;
  ui -> Items -> addItem ( "KrcForex"    ,  5 )                 ;
  ui -> Items -> addItem ( "KrcCore"     ,  6 )                 ;
  ui -> Items -> addItem ( "Videos"      ,  7 )                 ;
  ui -> Items -> addItem ( "People"      ,  8 )                 ;
  ui -> Items -> addItem ( "Pictures"    ,  9 )                 ;
  ui -> Items -> addItem ( "Audios"      , 10 )                 ;
  ui -> Items -> addItem ( "Graphics"    , 11 )                 ;
  ui -> Items -> addItem ( "Database"    , 12 )                 ;
  ui -> Items -> addItem ( "Designer"    , 13 )                 ;
  ui -> Items -> addItem ( "Tasks"       , 14 )                 ;
  ui -> Items -> addItem ( "Documents"   , 15 )                 ;
  ui -> Items -> addItem ( "Science"     , 16 )                 ;
  ui -> Items -> addItem ( "Knowledge"   , 17 )                 ;
  ui -> Items -> addItem ( "History"     , 18 )                 ;
  ui -> Items -> addItem ( "Linguistics" , 19 )                 ;
  ui -> Items -> addItem ( "Network"     , 20 )                 ;
  ui -> Items -> addItem ( "Business"    , 21 )                 ;
  ui -> Items -> addItem ( "Backup"      , 22 )                 ;
  ui -> Items -> addItem ( "Update"      , 23 )                 ;
  ui -> Items -> addItem ( "Cashing"     , 24 )                 ;
  ui -> Items -> addItem ( "Finance"     , 25 )                 ;
  ui -> Items -> addItem ( "Geography"   , 26 )                 ;
  ui -> Items -> addItem ( "Note"        , 27 )                 ;
  ui -> Items -> addItem ( "ICPT"        , 28 )                 ;
  ui -> Items -> addItem ( "ISO639"      , 29 )                 ;
  ui -> Items -> addItem ( "CLF"         , 30 )                 ;
  ui -> Items -> addItem ( "Personal"    , 31 )                 ;
  ui -> Items -> addItem ( "Slider"      , 32 )                 ;
  ui -> Items -> addItem ( "Testbed"     , 33 )                 ;
  ///////////////////////////////////////////////////////////////
  ui -> Items -> lineEdit ( ) -> setText      ( ""    )         ;
  ui -> Type  -> setEnabled                   ( true  )         ;
  ui -> Type  -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Items -> lineEdit ( ) -> blockSignals ( false )         ;
  ui -> Items -> blockSignals                 ( false )         ;
  ui -> Items -> lineEdit ( ) -> setEnabled   ( true  )         ;
  ui -> Items -> setEnabled                   ( true  )         ;
  ui -> Type  -> blockSignals                 ( false )         ;
  ui -> Add   -> setEnabled                   ( true  )         ;
}

void N::EventOwners::setCrowd(SUID u)
{
  crowd = u ;
}

void N::EventOwners::setOrganization(SUID u)
{
  organization = u ;
}

void N::EventOwners::Add(void)
{
  int type  = ui -> Type  -> currentIndex ( )                       ;
  int index = ui -> Items -> currentIndex ( )                       ;
  if ( type  < 0 ) return                                           ;
  if ( index < 0 ) return                                           ;
  ///////////////////////////////////////////////////////////////////
  QList<QTreeWidgetItem *> EITs                                     ;
  switch ( type )                                                   {
    case 0                                                          :
      type = N::Types::Equipment                                    ;
    break                                                           ;
    case 1                                                          :
      type = N::Types::People                                       ;
    break                                                           ;
    case 2                                                          :
      type = N::Types::Organization                                 ;
    break                                                           ;
    case 3                                                          :
      type = N::Types::Execution                                    ;
      for (int i = 0 ; i < ui->Owners->topLevelItemCount() ; i++ )  {
        QTreeWidgetItem * eit                                       ;
        eit = ui -> Owners -> topLevelItem ( i )                    ;
        if ( NULL != eit )                                          {
          int ett = nTreeUuid ( eit , 0 )                           ;
          if ( N::Types::Execution == ett ) EITs << eit             ;
        }                                                           ;
      }                                                             ;
      if ( EITs . count ( ) > 0 )                                   {
        QTreeWidgetItem * ext                                       ;
        for (int i = 0 ; i < EITs . count ( ) ; i++ )               {
          int xid                                                   ;
          ext = EITs [ i ]                                          ;
          xid = ui -> Owners -> indexOfTopLevelItem ( ext )         ;
          if ( xid >= 0 ) ui->Owners->takeTopLevelItem ( xid )      ;
        }                                                           ;
      }                                                             ;
    break                                                           ;
    default                                                         :
      Alert ( Error )                                               ;
    return                                                          ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  SUID    u   = ui -> Items -> itemData ( index ) . toULongLong ( ) ;
  QString tns = ui -> Type  -> currentText                      ( ) ;
  QString ons = ui -> Items -> currentText                      ( ) ;
  NewTreeWidgetItem               ( IT                      )       ;
  IT -> setData                   ( 0 , Qt::UserRole , type )       ;
  IT -> setData                   ( 1 , Qt::UserRole , u    )       ;
  IT -> setText                   ( 0 , tns                 )       ;
  IT -> setText                   ( 1 , ons                 )       ;
  ui -> Owners -> addTopLevelItem ( IT                      )       ;
  Alert                           ( Action                  )       ;
}

void N::EventOwners::Remove(void)
{
  QList<QTreeWidgetItem *> items                       ;
  items = ui -> Owners -> selectedItems ( )            ;
  if ( items . count ( ) <= 0 )                        {
    Alert ( Error )                                    ;
    return                                             ;
  }                                                    ;
  for (int i = 0 ; i < items . count ( ) ; i++ )       {
    QTreeWidgetItem * it = items [ i ]                 ;
    int               index                            ;
    index = ui -> Owners -> indexOfTopLevelItem ( it ) ;
    if ( index >= 0 )                                  {
      ui -> Owners -> takeTopLevelItem ( index )       ;
    }                                                  ;
  }                                                    ;
  ui -> Remove -> setEnabled ( false )                 ;
  Alert                      ( Done  )                 ;
}

void N::EventOwners::Type(int index)
{
  if ( index < 0     ) return ;
  if ( isLoading ( ) ) return ;
  start ( 11001 + index )     ;
}

void N::EventOwners::Items(int index)
{
}

void N::EventOwners::itemClicked(QTreeWidgetItem * item,int column)
{
  if ( NULL != item )                   {
    ui -> Remove -> setEnabled ( true ) ;
  }                                     ;
  Alert ( Click )                       ;
}

#include <qttasks.h>
#include "ui_nBriefEvent.h"

N::BriefEvent:: BriefEvent ( QWidget * parent , Plan * p )
              : Widget     (           parent ,        p )
              , ui         ( new Ui::nBriefEvent         )
              , vif        ( NULL                        )
              , period     ( NULL                        )
              , editor     ( NULL                        )
              , trigger    ( NULL                        )
              , owners     ( NULL                        )
              , tasks      ( NULL                        )
              , dependency ( NULL                        )
              , repeated   ( NULL                        )
              , uuid       ( 0                           )
              , RunThreads ( 0                           )
{
  Configure ( ) ;
}

N::BriefEvent::~BriefEvent(void)
{
  delete ui ;
}

void N::BriefEvent::Configure(void)
{
  QRect g                                                   ;
  ui     -> setupUi                  ( this               ) ;
  g       = ui -> Cancel -> geometry (                    ) ;
  period  = new PeriodEditor         ( ui -> Tab , plan   ) ;
  period -> move                     ( g . bottomLeft ( ) ) ;
  period -> setStyleSheet            ( styleSheet ( )     ) ;
  ///////////////////////////////////////////////////////////
  TypeNames [ N::None          ] = tr("None"         )      ;
  TypeNames [ N::Notify        ] = tr("Notify"       )      ;
  TypeNames [ N::Period        ] = tr("Period"       )      ;
  TypeNames [ N::Record        ] = tr("Record"       )      ;
  TypeNames [ N::Meeting       ] = tr("Meeting"      )      ;
  TypeNames [ N::Automation    ] = tr("Automation"   )      ;
  TypeNames [ N::Operation     ] = tr("Operation"    )      ;
  TypeNames [ N::Sync          ] = tr("Sync"         )      ;
  TypeNames [ N::Download      ] = tr("Download"     )      ;
  TypeNames [ N::Upload        ] = tr("Upload"       )      ;
  TypeNames [ N::Audio         ] = tr("Audio"        )      ;
  TypeNames [ N::Video         ] = tr("Video"        )      ;
  TypeNames [ N::TV            ] = tr("TV"           )      ;
  TypeNames [ N::Programming   ] = tr("Programming"  )      ;
  TypeNames [ N::Backup        ] = tr("Backup"       )      ;
  TypeNames [ N::FileUpdate    ] = tr("FileUpdate"   )      ;
  TypeNames [ N::Cooking       ] = tr("Cooking"      )      ;
  TypeNames [ N::Sleep         ] = tr("Sleep"        )      ;
  TypeNames [ N::Housework     ] = tr("Housework"    )      ;
  TypeNames [ N::Shopping      ] = tr("Shopping"     )      ;
  TypeNames [ N::Communication ] = tr("Communication")      ;
  TypeNames [ N::Finish        ] = tr("Finish"       )      ;
  TypeNames [ N::Obsolete      ] = tr("Obsolete"     )      ;
  TypeNames [ N::Others        ] = tr("Others"       )      ;
  TypeNames [ N::ForexTrade    ] = tr("FOREX"        )      ;
  ///////////////////////////////////////////////////////////
  ui   -> Type -> blockSignals    ( true                )   ;
  for (int i = N::None ; i < N::MaxEventTypeNumber ; i++ )  {
    ui -> Type -> addItem         ( TypeNames [ i ] , i )   ;
  }                                                         ;
  ui   -> Type -> setCurrentIndex ( N::Period           )   ;
  ui   -> Type -> blockSignals    ( false               )   ;
  ///////////////////////////////////////////////////////////
  period -> hide                  ( 1                   )   ;
  ui     -> Tab -> addTab  ( period , tr("Time period") )   ;
  ///////////////////////////////////////////////////////////
  nConnect ( this , SIGNAL ( AssignNote (QString)       )   ,
             this , SLOT   ( WriteNote  (QString)       ) ) ;
  nConnect ( this , SIGNAL ( LoadingType (int)          )   ,
             this , SLOT   ( AssignType  (int)          ) ) ;
  nConnect ( this , SIGNAL ( EnableWidget(int,bool)     )   ,
             this , SLOT   ( Enabling    (int,bool)     ) ) ;
  nConnect ( this , SIGNAL ( AssignTimeType ( int )     )   ,
             this , SLOT   ( EventType      ( int )     ) ) ;
  nConnect ( this , SIGNAL ( PrivateComplete ( ) )          ,
             this , SLOT   ( SendComplete    ( ) )        ) ;
  plan -> setFont ( this )                                  ;
}

void N::BriefEvent::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
  Relocation           (   ) ;
}

void N::BriefEvent::showEvent(QShowEvent * e)
{
  QWidget::showEvent ( e ) ;
  Relocation         (   ) ;
}

bool N::BriefEvent::Relocation(void)
{
  QRect g                                             ;
  /////////////////////////////////////////////////////
  g = ui -> Description -> geometry    (            ) ;
  g . setRight                         ( width  ( ) ) ;
  ui     -> Description -> setGeometry ( g          ) ;
  /////////////////////////////////////////////////////
  g = ui -> Type        -> geometry    (            ) ;
  g . setRight                         ( width  ( ) ) ;
  ui     -> Type        -> setGeometry ( g          ) ;
  /////////////////////////////////////////////////////
  g = ui -> Tab         -> geometry    (            ) ;
  g . setRight                         ( width  ( ) ) ;
  g . setBottom                        ( height ( ) ) ;
  ui     -> Tab         -> setGeometry ( g          ) ;
  /////////////////////////////////////////////////////
  return true                                         ;
}

void N::BriefEvent::run(int type,ThreadData * data)
{
  switch ( type )      {
    case 10001         :
      startLoading ( ) ;
      Load         ( ) ;
      stopLoading  ( ) ;
    break              ;
    case 10002         :
      startLoading ( ) ;
      Append       ( ) ;
      stopLoading  ( ) ;
    break              ;
    case 10003         :
      startLoading ( ) ;
      Modify       ( ) ;
      stopLoading  ( ) ;
    break              ;
    case 10004         :
      startLoading ( ) ;
      FetchNote    ( ) ;
      stopLoading  ( ) ;
    break              ;
    case 10005         :
      startLoading ( ) ;
      FetchTrigger ( ) ;
      stopLoading  ( ) ;
    break              ;
  }                    ;
}

bool N::BriefEvent::StoreNote(SqlConnection & SC)
{
  if ( IsNull ( editor ) ) return false            ;
  if ( uuid <= 0         ) return false            ;
  //////////////////////////////////////////////////
  QString Q                                        ;
  QString note = editor -> toPlainText ( )         ;
  Q = SC . sql . SelectFrom                        (
        "name"                                     ,
        PlanTable ( EventNotes )                   ,
        QString("where uuid = %1 and language = %2")
        .arg(uuid).arg(vLanguageId)              ) ;
  if ( SC . Fetch ( Q ) )                          {
    Q = SC . NameUpdate ( PlanTable(EventNotes)  ) ;
  } else                                           {
    Q = SC . NameSyntax ( PlanTable(EventNotes)  ) ;
  }                                                ;
  return SC . insertName ( Q                       ,
                           uuid                    ,
                           vLanguageId             ,
                           note                  ) ;
}

bool N::BriefEvent::FetchNote(SqlConnection & SC)
{
  if ( uuid <= 0 ) return false                             ;
  EventManager EM ( plan )                                  ;
  QString note = EM . EventNote ( SC , uuid , vLanguageId ) ;
  ///////////////////////////////////////////////////////////
  if ( IsNull  ( editor ) && ( note . length ( ) > 0 ) )    {
    editor = new PlainEditor ( ui -> Tab , plan )           ;
    ui -> Tab -> addTab ( editor , tr("Note") )             ;
  }                                                         ;
  emit AssignNote ( note )                                  ;
  ///////////////////////////////////////////////////////////
  return true                                               ;
}

void N::BriefEvent::WriteNote(QString note)
{
  if ( NotNull ( editor ) )         {
    editor -> setPlainText ( note ) ;
  }                                 ;
}

bool N::BriefEvent::StoreTrigger(SqlConnection & SC)
{
  if ( IsNull ( trigger ) ) return false               ;
  if ( uuid <= 0          ) return false               ;
  //////////////////////////////////////////////////////
  QString Q                                            ;
  SUID    S = trigger -> StartTrigger  ( )             ;
  SUID    F = trigger -> FinishTrigger ( )             ;
  //////////////////////////////////////////////////////
  Q = SC . sql . DeleteFrom                            (
        PlanTable(OtherGroups)                         ,
        QString("where `first` = %1"
                 " and `t1` = %2"
                 " and `t2` = %3"
                 " and `relation` = %4"                )
        . arg ( uuid                                   )
        . arg ( Types::Schedule                        )
        . arg ( Types::Trigger                         )
        . arg ( Groups::StartTrigger               ) ) ;
  SC . Query ( Q )                                     ;
  //////////////////////////////////////////////////////
  Q = SC . sql . DeleteFrom                            (
        PlanTable(OtherGroups)                         ,
        QString("where `first` = %1"
                 " and `t1` = %2"
                 " and `t2` = %3"
                 " and `relation` = %4"                )
        . arg ( uuid                                   )
        . arg ( Types::Schedule                        )
        . arg ( Types::Trigger                         )
        . arg ( Groups::FinalTrigger               ) ) ;
  SC . Query ( Q )                                     ;
  //////////////////////////////////////////////////////
  if ( S > 0 )                                         {
    Q = SC . sql . InsertInto                          (
          PlanTable(OtherGroups)                       ,
          5                                            ,
          "first"                                      ,
          "second"                                     ,
          "t1"                                         ,
          "t2"                                         ,
          "relation"                                 ) ;
    SC . Prepare ( Q                                 ) ;
    SC . Bind    ( "first"    , uuid                 ) ;
    SC . Bind    ( "second"   , S                    ) ;
    SC . Bind    ( "t1"       , Types::Schedule      ) ;
    SC . Bind    ( "t2"       , Types::Trigger       ) ;
    SC . Bind    ( "relation" , Groups::StartTrigger ) ;
    SC . Exec    (                                   ) ;
  }                                                    ;
  //////////////////////////////////////////////////////
  if ( F > 0 )                                         {
    Q = SC . sql . InsertInto                          (
          PlanTable(OtherGroups)                       ,
          5                                            ,
          "first"                                      ,
          "second"                                     ,
          "t1"                                         ,
          "t2"                                         ,
          "relation"                                 ) ;
    SC . Prepare ( Q                                 ) ;
    SC . Bind    ( "first"    , uuid                 ) ;
    SC . Bind    ( "second"   , F                    ) ;
    SC . Bind    ( "t1"       , Types::Schedule      ) ;
    SC . Bind    ( "t2"       , Types::Trigger       ) ;
    SC . Bind    ( "relation" , Groups::FinalTrigger ) ;
    SC . Exec    (                                   ) ;
  }                                                    ;
  //////////////////////////////////////////////////////
  return true                                          ;
}

bool N::BriefEvent::FetchTrigger(SqlConnection & SC)
{
  if ( uuid <= 0 ) return false                                 ;
  ///////////////////////////////////////////////////////////////
  EventManager EM ( plan )                                      ;
  SUID S = EM . GetTrigger ( SC , Groups::StartTrigger , uuid ) ;
  SUID F = EM . GetTrigger ( SC , Groups::FinalTrigger , uuid ) ;
  ///////////////////////////////////////////////////////////////
  if ( IsNull  ( trigger ) && ( ( S > 0 ) || ( F > 0 ) ) )      {
    trigger = new EventTriggers ( ui -> Tab , plan )            ;
    nConnect ( trigger , SIGNAL ( Activity(int) )               ,
               this    , SLOT   ( Activity(int) )             ) ;
    ui -> Tab -> addTab ( trigger , tr("Event trigger") )       ;
  }                                                             ;
  if ( NotNull ( trigger ) ) trigger -> startup ( S , F )       ;
  ///////////////////////////////////////////////////////////////
  return true                                                   ;
}

bool N::BriefEvent::StoreOwners(SqlConnection & SC)
{
  if ( uuid <= 0         ) return false ;
  if ( IsNull ( owners ) ) return false ;
  return owners -> store ( SC , uuid )  ;
}

bool N::BriefEvent::StoreTasks(SqlConnection & SC)
{
  if ( uuid <= 0        ) return false ;
  if ( IsNull ( tasks ) ) return false ;
  return tasks -> store ( SC , uuid )  ;
}

bool N::BriefEvent::StoreDepends(SqlConnection & SC)
{
  if ( uuid <= 0             ) return false ;
  if ( IsNull ( dependency ) ) return false ;
  return dependency -> store ( SC , uuid )  ;
}

bool N::BriefEvent::StoreRepeated(SqlConnection & SC)
{
  if ( uuid <= 0           ) return false ;
  if ( IsNull ( repeated ) ) return false ;
  return repeated -> store ( SC , uuid )  ;
}

bool N::BriefEvent::UpdateEvent(SqlConnection & SC,SUID uu,int tt,QString n,TUID ST,TUID ET)
{
  N::EventManager EM ( plan )                                   ;
  ///////////////////////////////////////////////////////////////
  EM . UpdateType  ( SC                                         ,
                     plan -> Tables [ N::Tables::EventHistory ] ,
                     uu                                         ,
                     tt                                       ) ;
  EM . AssureEvent ( SC , uu ,tt                              ) ;
  EM . UpdateType  ( SC                                         ,
                     plan -> Tables [ N::Tables::Events ]       ,
                     uu                                         ,
                     tt                                       ) ;
  SC . assureName  ( plan -> Tables [ N::Tables::Names ]        ,
                     uu                                         ,
                     plan -> LanguageId                         ,
                     n                                        ) ;
  EM . UpdateEvent ( SC                                         ,
                     uu                                         ,
                     N::Calendars::Duration                     ,
                     ST                                         ,
                     ET                                       ) ;
  EM . attachSpot  ( SC                                         ,
                     uu                                         ,
                     N::History::WorkingPeriod                  ,
                     ST                                         ,
                     ET                                       ) ;
  return true                                                   ;
}

SUID N::BriefEvent::AppendEvent(SqlConnection & SC,int type,QString name)
{
  if ( IsNull ( period )      ) return 0          ;
  if ( name . length ( ) <= 0 ) return 0          ;
  /////////////////////////////////////////////////
  TUID ST = period -> Start  ( )                  ;
  TUID ET = period -> Finish ( )                  ;
  if ( ST > ET                ) return 0          ;
  /////////////////////////////////////////////////
  N::EventManager EM ( plan )                     ;
  SUID            uu                              ;
  /////////////////////////////////////////////////
  uu = EM . AssureUuid ( SC                     ) ;
  if ( uu <= 0 ) return 0                         ;
  UpdateEvent ( SC , uu , type , name , ST , ET ) ;
  /////////////////////////////////////////////////
  return uu                                       ;
}

void N::BriefEvent::Load(void)
{
  if ( 0 == uuid )                                                           {
    setEnabled ( true  )                                                     ;
    Alert      ( Error )                                                     ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  EventManager  EM ( plan        )                                           ;
  SqlConnection SC ( plan -> sql )                                           ;
  if ( SC . open ( FunctionString ) )                                        {
    QString Q                                                                ;
    //////////////////////////////////////////////////////////////////////////
    Q = SC . sql . SelectFrom                                                (
      "owner,type,status,adjust,start,final"                                 ,
      PlanTable(EventHistory)                                                ,
      SC . WhereUuid ( uuid )                                              ) ;
    if ( SC . Fetch ( Q ) )                                                  {
      SUID    owner  = SC . Uuid       ( 0                       )           ;
      int     etype  = SC . Int        ( 1                       )           ;
      int     status = SC . Int        ( 2                       )           ;
      int     adjust = SC . Int        ( 3                       )           ;
      TUID    ST     = SC . Tuid       ( 4                       )           ;
      TUID    FT     = SC . Tuid       ( 5                       )           ;
      QString name   = EM . Name       ( SC , uuid               )           ;
      QString note   = EM . EventNote  ( SC , uuid , vLanguageId )           ;
      ////////////////////////////////////////////////////////////////////////
      ui -> Description -> blockSignals ( true                             ) ;
      ui -> Add         -> blockSignals ( true                             ) ;
      ui -> Description -> setText      ( name                             ) ;
      ui -> Add         -> setChecked   ( name . length ( ) > 0            ) ;
      ui -> Add         -> blockSignals ( false                            ) ;
      ui -> Description -> blockSignals ( false                            ) ;
      ui -> Description -> setFocus     ( Qt::TabFocusReason               ) ;
      emit LoadingType                  ( etype                            ) ;
      ////////////////////////////////////////////////////////////////////////
      period -> setStart                ( ST                               ) ;
      period -> setFinish               ( FT                               ) ;
      emit AssignTimeType               ( etype                            ) ;
      ////////////////////////////////////////////////////////////////////////
      if ( EM . hasOwners                ( SC , uuid ) )                     {
        ui -> Owner      -> blockSignals ( true      )                       ;
        ui -> Owner      -> setChecked   ( true      )                       ;
        ui -> Owner      -> blockSignals ( false     )                       ;
        emit EnableWidget                ( 0 , true  )                       ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      if ( EM . hasTriggers              ( SC , uuid ) )                     {
        ui -> Trigger    -> blockSignals ( true      )                       ;
        ui -> Trigger    -> setChecked   ( true      )                       ;
        ui -> Trigger    -> blockSignals ( false     )                       ;
        emit EnableWidget                ( 1 , true  )                       ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      if ( EM . hasDependency            ( SC , uuid ) )                     {
        ui -> Dependency -> blockSignals ( true      )                       ;
        ui -> Dependency -> setChecked   ( true      )                       ;
        ui -> Dependency -> blockSignals ( false     )                       ;
        emit EnableWidget                ( 2 , true  )                       ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      if ( EM . isRepeated               ( SC , uuid ) )                     {
        ui -> Repeat     -> blockSignals ( true      )                       ;
        ui -> Repeat     -> setChecked   ( true      )                       ;
        ui -> Repeat     -> blockSignals ( false     )                       ;
        emit EnableWidget                ( 3 , true  )                       ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      if ( EM . hasTasks                 ( SC , uuid ) )                     {
        ui -> Tasks      -> blockSignals ( true      )                       ;
        ui -> Tasks      -> setChecked   ( true      )                       ;
        ui -> Tasks      -> blockSignals ( false     )                       ;
        emit EnableWidget                ( 4 , true  )                       ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      if ( note . length ( ) > 0 )                                           {
        ui -> Note       -> blockSignals ( true      )                       ;
        ui -> Note       -> setChecked   ( true      )                       ;
        ui -> Note       -> blockSignals ( false     )                       ;
        emit EnableWidget                ( 5 , true  )                       ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  setEnabled ( true  )                                                       ;
}

void N::BriefEvent::Append(void)
{
  if ( 0 != uuid )                                                           {
    setEnabled ( true  )                                                     ;
    Alert      ( Error )                                                     ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QString description = ui -> Description -> text         ( )                ;
  int     type        = ui -> Type        -> currentIndex ( )                ;
  bool    correct     = false                                                ;
  correct = ( description . length ( ) > 0 )                                 ;
  type    = ui -> Type -> itemData ( type ) . toInt ( )                      ;
  if ( correct ) correct = ( type > N::None )                                ;
  if ( correct )                                                             {
    SqlConnection SC ( plan -> sql )                                         ;
    if ( SC . open ( FunctionString , QtUUID::createUuidString ( ) ) )       {
      ////////////////////////////////////////////////////////////////////////
      switch ( type )                                                        {
        case N::Notify                                                       :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Period                                                       :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Record                                                       :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Meeting                                                      :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Automation                                                   :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Operation                                                    :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Sync                                                         :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Download                                                     :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Upload                                                       :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Audio                                                        :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Video                                                        :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::TV                                                           :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Programming                                                  :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Backup                                                       :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::FileUpdate                                                   :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Cooking                                                      :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Sleep                                                        :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Housework                                                    :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Shopping                                                     :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Communication                                                :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::Finish                                                       :
          correct = false                                                    ;
        break                                                                ;
        case N::Obsolete                                                     :
          correct = false                                                    ;
        break                                                                ;
        case N::Others                                                       :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        case N::ForexTrade                                                   :
          uuid    = AppendEvent ( SC , type , description )                  ;
          correct = ( uuid > 0 )                                             ;
        break                                                                ;
        default                                                              :
          correct = false                                                    ;
        break                                                                ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      if ( correct ) StoreNote     ( SC )                                    ;
      if ( correct ) StoreTrigger  ( SC )                                    ;
      if ( correct ) StoreOwners   ( SC )                                    ;
      if ( correct ) StoreTasks    ( SC )                                    ;
      if ( correct ) StoreDepends  ( SC )                                    ;
      if ( correct ) StoreRepeated ( SC )                                    ;
      ////////////////////////////////////////////////////////////////////////
      SC . close  ( )                                                        ;
    }                                                                        ;
    SC   . remove ( )                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  setEnabled             ( true  )                                           ;
  if ( correct )                                                             {
    Alert                ( Done  )                                           ;
    emit PrivateComplete (       )                                           ;
  } else                                                                     {
    Alert                ( Error )                                           ;
  }                                                                          ;
}

void N::BriefEvent::Modify(void)
{
  if ( 0 == uuid )                                                           {
    setEnabled ( true  )                                                     ;
    Alert      ( Error )                                                     ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QString description = ui -> Description -> text         ( )                ;
  int     type        = ui -> Type        -> currentIndex ( )                ;
  bool    correct     = false                                                ;
  TUID    ST          = period -> Start  ( )                                 ;
  TUID    ET          = period -> Finish ( )                                 ;
  correct = ( description . length ( ) > 0 )                                 ;
  type    = ui -> Type -> itemData ( type ) . toInt ( )                      ;
  if ( correct ) correct = ( type > N::None )                                ;
  if ( correct ) correct = ( ST < ET        )                                ;
  if ( correct )                                                             {
    SqlConnection SC ( plan -> sql )                                         ;
    if ( SC . open ( FunctionString , QtUUID::createUuidString ( ) ) )       {
      ////////////////////////////////////////////////////////////////////////
      switch ( type )                                                        {
        case N::Notify                                                       :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Period                                                       :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Record                                                       :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Meeting                                                      :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Automation                                                   :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Operation                                                    :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Sync                                                         :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Download                                                     :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Upload                                                       :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Audio                                                        :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Video                                                        :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::TV                                                           :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Programming                                                  :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Backup                                                       :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::FileUpdate                                                   :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Cooking                                                      :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Sleep                                                        :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Housework                                                    :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Shopping                                                     :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Communication                                                :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::Finish                                                       :
          correct = false                                                    ;
        break                                                                ;
        case N::Obsolete                                                     :
          correct = false                                                    ;
        break                                                                ;
        case N::Others                                                       :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        case N::ForexTrade                                                   :
          UpdateEvent ( SC , uuid , type , description , ST , ET )           ;
        break                                                                ;
        default                                                              :
          correct = false                                                    ;
        break                                                                ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      if ( correct ) StoreNote     ( SC )                                    ;
      if ( correct ) StoreTrigger  ( SC )                                    ;
      if ( correct ) StoreOwners   ( SC )                                    ;
      if ( correct ) StoreTasks    ( SC )                                    ;
      if ( correct ) StoreDepends  ( SC )                                    ;
      if ( correct ) StoreRepeated ( SC )                                    ;
      ////////////////////////////////////////////////////////////////////////
      SC . close  ( )                                                        ;
    }                                                                        ;
    SC   . remove ( )                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  setEnabled             ( true  )                                           ;
  if ( correct )                                                             {
    Alert                ( Done  )                                           ;
    emit PrivateComplete (       )                                           ;
  } else                                                                     {
    Alert                ( Error )                                           ;
  }                                                                          ;
}

void N::BriefEvent::FetchNote(void)
{
  if ( 0 == uuid ) return                                            ;
  SqlConnection SC ( plan -> sql )                                   ;
  if ( SC . open ( FunctionString , QtUUID::createUuidString ( ) ) ) {
    FetchNote ( SC )                                                 ;
    SC . close  ( )                                                  ;
  }                                                                  ;
  SC   . remove ( )                                                  ;
}

void N::BriefEvent::FetchTrigger(void)
{
  if ( 0 == uuid ) return               ;
  SqlConnection SC ( plan -> sql      ) ;
  if ( SC . open   ( FunctionString ) ) {
    FetchTrigger   ( SC               ) ;
    SC . close     (                  ) ;
  }                                     ;
  SC   . remove    (                  ) ;
}

bool N::BriefEvent::startup(SUID u,QDateTime s,QDateTime e)
{
  StarDate sdt                                                         ;
  StarDate edt                                                         ;
  sdt  = s                                                             ;
  edt  = e                                                             ;
  uuid = u                                                             ;
  if ( 0 == u )                                                        {
    period -> setStart                ( sdt . Stardate               ) ;
    period -> setFinish               ( edt . Stardate               ) ;
    EventType                         ( N::Period                    ) ;
    ui     -> Description -> setFocus ( Qt::TabFocusReason           ) ;
  } else                                                               {
    ui     -> Add         -> setIcon  ( QIcon(":/images/update.png") ) ;
    start ( 10001 )                                                    ;
  }                                                                    ;
  return true                                                          ;
}

void N::BriefEvent::Enabling(int type,bool enable)
{
  switch ( type )           {
    case 0                  :
      Owner      ( enable ) ;
    break                   ;
    case 1                  :
      Trigger    ( enable ) ;
    break                   ;
    case 2                  :
      Dependency ( enable ) ;
    break                   ;
    case 3                  :
      Repeat     ( enable ) ;
    break                   ;
    case 4                  :
      Tasks      ( enable ) ;
    break                   ;
    case 5                  :
      Note       ( enable ) ;
    break                   ;
  }                         ;
}

void N::BriefEvent::Owner(bool enabled)
{
  if ( enabled )                                                     {
    if ( IsNull  ( owners ) )                                        {
      owners = new EventOwners ( ui -> Tab , plan )                  ;
      nConnect ( owners , SIGNAL ( Activity(int) )                   ,
                 this   , SLOT   ( Activity(int) )                 ) ;
      ui -> Tab -> addTab ( owners , tr("Event owners") )            ;
      owners -> setOrganization ( plan -> Uuids [ "Organization" ] ) ;
      owners -> setCrowd        ( plan -> Uuids [ "Crowd"        ] ) ;
      owners -> startup         ( uuid                             ) ;
    }                                                                ;
  } else                                                             {
    if ( NotNull ( owners ) )                                        {
      owners -> deleteLater ( )                                      ;
      owners  = NULL                                                 ;
    }                                                                ;
  }                                                                  ;
}

void N::BriefEvent::Trigger(bool enabled)
{
  if ( enabled )                                             {
    if ( IsNull  ( trigger ) )                               {
      trigger = new EventTriggers ( ui -> Tab , plan )       ;
      nConnect ( trigger , SIGNAL ( Activity(int) )          ,
                 this    , SLOT   ( Activity(int) )        ) ;
      ui -> Tab -> addTab ( trigger , tr("Event triggers") ) ;
      if ( uuid > 0 )                                        {
        start              ( 10005 )                         ;
      } else                                                 {
        trigger -> startup ( 0 , 0 )                         ;
      }                                                      ;
    }                                                        ;
  } else                                                     {
    if ( NotNull ( trigger ) )                               {
      trigger -> deleteLater ( )                             ;
      trigger  = NULL                                        ;
    }                                                        ;
  }                                                          ;
}

void N::BriefEvent::Dependency(bool enabled)
{
  if ( enabled )                                            {
    if ( IsNull  ( dependency ) )                           {
      dependency = new EventDependency ( ui -> Tab , plan ) ;
      nConnect ( dependency , SIGNAL ( Activity(int) )      ,
                 this       , SLOT   ( Activity(int) )    ) ;
      ui -> Tab -> addTab ( dependency , tr("Dependency") ) ;
      dependency -> startup ( uuid )                        ;
    }                                                       ;
  } else                                                    {
    if ( NotNull ( dependency ) )                           {
      dependency -> deleteLater ( )                         ;
      dependency  = NULL                                    ;
    }                                                       ;
  }                                                         ;
}

void N::BriefEvent::Repeat(bool enabled)
{
  if ( enabled )                                              {
    if ( IsNull  ( repeated ) )                               {
      repeated = new RepeatedEvent ( ui -> Tab , plan )       ;
      nConnect ( repeated , SIGNAL ( Activity(int) )          ,
                 this     , SLOT   ( Activity(int) )        ) ;
      ui -> Tab -> addTab ( repeated , tr("Repeated event") ) ;
      repeated -> startup ( uuid )                            ;
    }                                                         ;
  } else                                                      {
    if ( NotNull ( repeated ) )                               {
      repeated -> deleteLater ( )                             ;
      repeated  = NULL                                        ;
    }                                                         ;
  }                                                           ;
}

void N::BriefEvent::Tasks(bool enabled)
{
  if ( enabled )                                    {
    if ( IsNull  ( tasks ) )                        {
      tasks = new EventTasks ( ui -> Tab , plan )   ;
      nConnect ( tasks , SIGNAL ( Activity(int) )   ,
                 this  , SLOT   ( Activity(int) ) ) ;
      ui -> Tab -> addTab ( tasks , tr("Tasks") )   ;
      tasks -> startup ( uuid )                     ;
    }                                               ;
  } else                                            {
    if ( NotNull ( tasks ) )                        {
      tasks -> deleteLater ( )                      ;
      tasks  = NULL                                 ;
    }                                               ;
  }                                                 ;
}

void N::BriefEvent::Note(bool enabled)
{
  if ( enabled )                                    {
    if ( IsNull  ( editor ) )                       {
      editor = new PlainEditor ( ui -> Tab , plan ) ;
      ui -> Tab -> addTab ( editor , tr("Note") )   ;
      if ( uuid > 0 ) start ( 10004 )               ;
    }                                               ;
  } else                                            {
    if ( NotNull ( editor ) )                       {
      editor -> deleteLater ( )                     ;
      editor  = NULL                                ;
    }                                               ;
  }                                                 ;
}

void N::BriefEvent::Description(QString text)
{
  Validate ( ) ;
}

void N::BriefEvent::RemoveEditor(void)
{
  if ( NotNull ( editor ) )              {
    editor     -> deleteLater  (       ) ;
    ui -> Note -> blockSignals ( true  ) ;
    ui -> Note -> setChecked   ( false ) ;
    ui -> Note -> blockSignals ( false ) ;
    editor  = NULL                       ;
  }                                      ;
}

void N::BriefEvent::RemoveTrigger(void)
{
  if ( NotNull ( trigger ) )                {
    trigger       -> deleteLater  (       ) ;
    ui -> Trigger -> blockSignals ( true  ) ;
    ui -> Trigger -> setChecked   ( false ) ;
    ui -> Trigger -> blockSignals ( false ) ;
    trigger = NULL                          ;
  }                                         ;
}

void N::BriefEvent::RemoveOwners(void)
{
  if ( NotNull ( owners ) )               {
    owners      -> deleteLater  (       ) ;
    ui -> Owner -> blockSignals ( true  ) ;
    ui -> Owner -> setChecked   ( false ) ;
    ui -> Owner -> blockSignals ( false ) ;
    owners = NULL                         ;
  }                                       ;
}

void N::BriefEvent::RemoveTasks(void)
{
  if ( NotNull ( tasks ) )                {
    tasks       -> deleteLater  (       ) ;
    ui -> Tasks -> blockSignals ( true  ) ;
    ui -> Tasks -> setChecked   ( false ) ;
    ui -> Tasks -> blockSignals ( false ) ;
    tasks = NULL                          ;
  }                                       ;
}

void N::BriefEvent::RemoveDepends(void)
{
  if ( NotNull ( dependency ) )                {
    dependency       -> deleteLater  (       ) ;
    ui -> Dependency -> blockSignals ( true  ) ;
    ui -> Dependency -> setChecked   ( false ) ;
    ui -> Dependency -> blockSignals ( false ) ;
    dependency = NULL                          ;
  }                                            ;
}

void N::BriefEvent::RemoveRepeat(void)
{
  if ( NotNull ( repeated ) )              {
    repeated     -> deleteLater  (       ) ;
    ui -> Repeat -> blockSignals ( true  ) ;
    ui -> Repeat -> setChecked   ( false ) ;
    ui -> Repeat -> blockSignals ( false ) ;
    repeated = NULL                        ;
  }                                        ;
}

void N::BriefEvent::EventType(int type)
{
  type = ui -> Type -> itemData ( type ) . toInt ( ) ;
  switch ( type )                                    {
    case N::None                                     :
      RemoveEditor  ( )                              ;
      RemoveTrigger ( )                              ;
      RemoveOwners  ( )                              ;
    break                                            ;
    case N::Notify                                   :
    break                                            ;
    case N::Period                                   :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Record                                   :
      RemoveTrigger ( )                              ;
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Meeting                                  :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Automation                               :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Operation                                :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Sync                                     :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Download                                 :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Upload                                   :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Audio                                    :
      RemoveTrigger ( )                              ;
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Video                                    :
      RemoveTrigger ( )                              ;
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::TV                                       :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Programming                              :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Backup                                   :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::FileUpdate                               :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Cooking                                  :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Sleep                                    :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Housework                                :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Shopping                                 :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Communication                            :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Finish                                   :
      RemoveEditor  ( )                              ;
      RemoveTrigger ( )                              ;
      RemoveOwners  ( )                              ;
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Obsolete                                 :
      RemoveEditor  ( )                              ;
      RemoveTrigger ( )                              ;
      RemoveOwners  ( )                              ;
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::Others                                   :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
    case N::ForexTrade                               :
      period -> setType ( 0 )                        ;
      period -> hide    ( 1 )                        ;
    break                                            ;
  }                                                  ;
  Validate ( )                                       ;
}

void N::BriefEvent::Validate(void)
{
  int     type        = ui -> Type -> currentIndex ( )   ;
  QString description = ui -> Description -> text ( )    ;
  bool    des         = ( description . length ( ) > 0 ) ;
  type = ui -> Type -> itemData ( type ) . toInt ( )     ;
  ////////////////////////////////////////////////////////
  switch ( type )                                        {
    case N::None                                         :
      ui -> Add        -> setEnabled ( false )           ;
      ui -> Owner      -> setEnabled ( false )           ;
      ui -> Trigger    -> setEnabled ( false )           ;
      ui -> Dependency -> setEnabled ( false )           ;
      ui -> Repeat     -> setEnabled ( false )           ;
      ui -> Tasks      -> setEnabled ( false )           ;
      ui -> Note       -> setEnabled ( false )           ;
    break                                                ;
    case N::Notify                                       :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Period                                       :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Record                                       :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( false )           ;
      ui -> Dependency -> setEnabled ( false )           ;
      ui -> Repeat     -> setEnabled ( false )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Meeting                                      :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Automation                                   :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Operation                                    :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Sync                                         :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Download                                     :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Upload                                       :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Audio                                        :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( false )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Video                                        :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( false )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::TV                                           :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Programming                                  :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Backup                                       :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::FileUpdate                                   :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Cooking                                      :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Sleep                                        :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Housework                                    :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Shopping                                     :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Communication                                :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::Finish                                       :
      ui -> Add        -> setEnabled ( false )           ;
      ui -> Owner      -> setEnabled ( false )           ;
      ui -> Trigger    -> setEnabled ( false )           ;
      ui -> Dependency -> setEnabled ( false )           ;
      ui -> Repeat     -> setEnabled ( false )           ;
      ui -> Tasks      -> setEnabled ( false )           ;
      ui -> Note       -> setEnabled ( false )           ;
    break                                                ;
    case N::Obsolete                                     :
      ui -> Add        -> setEnabled ( false )           ;
      ui -> Owner      -> setEnabled ( false )           ;
      ui -> Trigger    -> setEnabled ( false )           ;
      ui -> Dependency -> setEnabled ( false )           ;
      ui -> Repeat     -> setEnabled ( false )           ;
      ui -> Tasks      -> setEnabled ( false )           ;
      ui -> Note       -> setEnabled ( false )           ;
    break                                                ;
    case N::Others                                       :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
    case N::ForexTrade                                   :
      ui -> Add        -> setEnabled ( des   )           ;
      ui -> Owner      -> setEnabled ( des   )           ;
      ui -> Trigger    -> setEnabled ( des   )           ;
      ui -> Dependency -> setEnabled ( des   )           ;
      ui -> Repeat     -> setEnabled ( des   )           ;
      ui -> Note       -> setEnabled ( true  )           ;
      ui -> Tasks      -> setEnabled ( true  )           ;
    break                                                ;
  }                                                      ;
}

void N::BriefEvent::AssignType(int typeId)
{
  ui -> Type -> blockSignals ( true  ) ;
  (*(ui->Type)) <= typeId              ;
  ui -> Type -> blockSignals ( false ) ;
}

void N::BriefEvent::Activity(int state)
{
  switch ( state )               {
    case 0                       :
      RunThreads++               ;
    break                        ;
    case 1                       :
      RunThreads--               ;
    break                        ;
  }                              ;
  setEnabled ( RunThreads <= 0 ) ;
}

void N::BriefEvent::Add(void)
{
  setEnabled                 ( false ) ;
  ui -> Add    -> setEnabled ( false ) ;
  ui -> Cancel -> setEnabled ( false ) ;
  if ( 0 == uuid )                     {
    start ( 10002 )                    ;
  } else                               {
    start ( 10003 )                    ;
  }                                    ;
}

void N::BriefEvent::WaitComplete(void)
{
  while ( isLoading ( ) ) Time::skip(10)                   ;
  if ( NotNull(trigger))                                   {
      while ( trigger    -> isLoading ( ) ) Time::skip(10) ;
  }                                                        ;
  if ( NotNull(owners))                                    {
      while ( owners     -> isLoading ( ) ) Time::skip(10) ;
  }                                                        ;
  if ( NotNull(tasks))                                     {
      while ( tasks      -> isLoading ( ) ) Time::skip(10) ;
  }                                                        ;
  if ( NotNull(dependency))                                {
      while ( dependency -> isLoading ( ) ) Time::skip(10) ;
  }                                                        ;
  if ( NotNull(repeated))                                  {
      while ( repeated   -> isLoading ( ) ) Time::skip(10) ;
  }                                                        ;
}

void N::BriefEvent::SendComplete(void)
{
  WaitComplete  (      )  ;
  emit Complete (      )  ;
  emit Leave    ( this )  ;
  if ( NotNull ( vif ) )  {
    emit EraseVIF ( vif ) ;
  }                       ;
}

void N::BriefEvent::Cancel(void)
{
  setEnabled                 ( false ) ;
  ui -> Add    -> setEnabled ( false ) ;
  ui -> Cancel -> setEnabled ( false ) ;
  WaitComplete               (       ) ;
  emit Leave                 ( this  ) ;
  if ( NotNull ( vif ) )               {
    emit EraseVIF ( vif )              ;
  }                                    ;
}

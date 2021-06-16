#include <qttasks.h>

N::CalendarObject:: CalendarObject ( QObject * parent , Plan * p )
                  : SceneWidget    (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CalendarObject:: CalendarObject ( QObject * parent , Plan * p , SceneDestructor * des )
                  : SceneWidget    (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CalendarObject::~CalendarObject (void)
{
}

void N::CalendarObject::Configure(void)
{
  int          flag = Qt::AlignCenter                     ;
  ControlPoint color                                      ;
  QColor       blue     (   0 ,    0 , 192 , 224        ) ;
  QColor       black    (   0 ,    0 ,   0 , 192        ) ;
  QColor       year     ( 224 ,  224 , 224 , 192        ) ;
  color  = QColor       ( 192 ,  192 , 192 , 192        ) ;
  addColor              (    0 , color                  ) ;
  color  = ControlPoint (    0 ,    0 ,   1 , 0.01      ) ;
  addColor              (    1 , color                  ) ;
  color  = ControlPoint (    1 ,    0 ,   0 , 0.01      ) ;
  addColor              (    2 , color                  ) ;
  color  = ControlPoint (    0 ,  0.6 ,   0 , 0.01      ) ;
  addColor              (    3 , color                  ) ;
  color  = ControlPoint (    0 ,    0 ,   0 , 0.25      ) ;
  addColor              (    4 , color                  ) ;
  color  = ControlPoint ( 0.10 , 0.70 ,   1 , 0.03      ) ;
  addColor              (    5 , color                  ) ;
  color  = ControlPoint ( 0.20 , 0.75 , 0.2 , 0.10      ) ;
  addColor              (    6 , color                  ) ;
  color  = ControlPoint ( 1.00 , 1.00 , 0.9 , 0.15      ) ;
  addColor              (    7 , color                  ) ;
  color  = ControlPoint ( 1.00 , 1.00 , 0.9 , 0.15      ) ;
  addColor              (    8 , color                  ) ;
  color  = ControlPoint ( 0.70 , 0.25 , 0.5 , 0.25      ) ;
  addColor              (    9 , color                  ) ;
  color  = ControlPoint ( 0.80 , 0.75 , 0.6 , 0.10      ) ;
  addColor              (   10 , color                  ) ;
  color  = ControlPoint ( 0.60 , 0.80 , 0.9 , 0.10      ) ;
  addColor              (   11 , color                  ) ;
  color  = ControlPoint ( 0.50 , 0.70 , 0.3 , 0.25      ) ;
  addColor              (   12 , color                  ) ;
  /////////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"     , "CalendarObject" ) ;
  setVariable           ( "Type"           , "Calendar" ) ;
  setVariable           ( "Focus"          , false      ) ;
  setVariable           ( "Mouse"          , true       ) ;
  /////////////////////////////////////////////////////////
  setVariable           ( "GridColor"      ,  0         ) ;
  setVariable           ( "BackColor"      ,  1         ) ;
  setVariable           ( "FrontColor"     ,  2         ) ;
  setVariable           ( "SideColor"      ,  3         ) ;
  setVariable           ( "BorderColor"    ,  4         ) ;
  setVariable           ( "SeparatorColor" ,  5         ) ;
  setVariable           ( "MetricColor"    ,  6         ) ;
  setVariable           ( "DayBack"        ,  7         ) ;
  setVariable           ( "DayFront"       ,  8         ) ;
  setVariable           ( "DayLine"        ,  9         ) ;
  setVariable           ( "MarkBack"       , 10         ) ;
  setVariable           ( "MarkFront"      , 11         ) ;
  setVariable           ( "MarkLine"       , 12         ) ;
  /////////////////////////////////////////////////////////
  setVariable           ( "Front"          , true       ) ;
  setVariable           ( "Back"           , true       ) ;
  setVariable           ( "Side"           , true       ) ;
  setVariable           ( "Dayline"        , true       ) ;
  setVariable           ( "Weekdays"       , true       ) ;
  setVariable           ( "Tick"           , true       ) ;
  setVariable           ( "AutoTicks"      , true       ) ;
  setVariable           ( "Happened"       , true       ) ;
  setVariable           ( "CurrentTime"    , true       ) ;
  setVariable           ( "TimeLabels"     , true       ) ;
  setVariable           ( "Daylight"       , false      ) ;
  setVariable           ( "Weather"        , false      ) ;
  /////////////////////////////////////////////////////////
  setVariable           ( "Metric"         , 32         ) ;
  setVariable           ( "BarMetric"      , 32         ) ;
  setVariable           ( "TextGap"        ,  8         ) ;
  setVariable           ( "DayLineWidth"   , 0.750      ) ;
  setVariable           ( "TickLineWidth"  , 0.500      ) ;
  setVariable           ( "TopMetric"      , true       ) ;
  setVariable           ( "BottomMetric"   , true       ) ;
  /////////////////////////////////////////////////////////
  setVariable           ( "BriefAdd"       , false      ) ;
  setVariable           ( "AddEvent"       , false      ) ;
  setVariable           ( "AddPeriod"      , false      ) ;
  setVariable           ( "ZoomIn"         , false      ) ;
  setVariable           ( "Selection"      , true       ) ;
  setVariable           ( "Actions"        , false      ) ;
  setVariable           ( "Selected"       , false      ) ;
  setVariable           ( "Tracking"       , false      ) ;
  setVariable           ( "T1"             , nTimeNow   ) ;
  setVariable           ( "T2"             , nTimeNow   ) ;
  setVariable           ( "T3"             , nTimeNow   ) ;
  setVariable           ( "T4"             , nTimeNow   ) ;
  /////////////////////////////////////////////////////////
  setVariable           ( "Hold"           , false      ) ;
  setVariable           ( "Menu"           , true       ) ;
  setVariable           ( "FollowWindow"   , true       ) ;
  setVariable           ( "ControlPanel"   , false      ) ;
  setVariable           ( "Hover"          , false      ) ;
  setVariable           ( "Timebar"        , false      ) ;
  setVariable           ( "Marking"        , false      ) ;
  setVariable           ( "Hit"            , false      ) ;
  setVariable           ( "HitEvent"       , false      ) ;
  setVariable           ( "MinuteOnly"     , true       ) ;
  setVariable           ( "Gantt"          , true       ) ;
  setVariable           ( "CanClose"       , false      ) ;
  setVariable           ( "LocalOnly"      , true       ) ;
  setVariable           ( "MomentTime"     , 25         ) ;
  setVariable           ( "Baseline"       , 60.0       ) ;
  setVariable           ( "TimeMargin"     , 0.25       ) ;
  setVariable           ( "TextColor"      , blue       ) ;
  setVariable           ( "LabelColor"     , black      ) ;
  setVariable           ( "YearColor"      , year       ) ;
  setVariable           ( "TextFlags"      , flag       ) ;
  setVariable           ( "DisplayTime"    , nTimeNow   ) ;
  /////////////////////////////////////////////////////////
  addType               ( CiosMenuId ( 93 , 44 , 23 )   ) ;
  /////////////////////////////////////////////////////////
  TypeNames [ N::None          ] = tr("None"         )    ;
  TypeNames [ N::Notify        ] = tr("Notify"       )    ;
  TypeNames [ N::Period        ] = tr("Period"       )    ;
  TypeNames [ N::Record        ] = tr("Record"       )    ;
  TypeNames [ N::Meeting       ] = tr("Meeting"      )    ;
  TypeNames [ N::Automation    ] = tr("Automation"   )    ;
  TypeNames [ N::Operation     ] = tr("Operation"    )    ;
  TypeNames [ N::Sync          ] = tr("Sync"         )    ;
  TypeNames [ N::Download      ] = tr("Download"     )    ;
  TypeNames [ N::Upload        ] = tr("Upload"       )    ;
  TypeNames [ N::Audio         ] = tr("Audio"        )    ;
  TypeNames [ N::Video         ] = tr("Video"        )    ;
  TypeNames [ N::TV            ] = tr("TV"           )    ;
  TypeNames [ N::Programming   ] = tr("Programming"  )    ;
  TypeNames [ N::Backup        ] = tr("Backup"       )    ;
  TypeNames [ N::FileUpdate    ] = tr("FileUpdate"   )    ;
  TypeNames [ N::Cooking       ] = tr("Cooking"      )    ;
  TypeNames [ N::Sleep         ] = tr("Sleep"        )    ;
  TypeNames [ N::Housework     ] = tr("Housework"    )    ;
  TypeNames [ N::Shopping      ] = tr("Shopping"     )    ;
  TypeNames [ N::Communication ] = tr("Communication")    ;
  TypeNames [ N::Finish        ] = tr("Finish"       )    ;
  TypeNames [ N::Obsolete      ] = tr("Obsolete"     )    ;
  TypeNames [ N::Others        ] = tr("Others"       )    ;
  TypeNames [ N::ForexTrade    ] = tr("FOREX"        )    ;
  /////////////////////////////////////////////////////////
  for (int i=0;i<=60;i++)                                 {
    int     id = 1000000 + i                              ;
    QString tx                                            ;
    tx . append ( QString::number ( i / 10 ) )            ;
    tx . append ( QString::number ( i % 10 ) )            ;
    drawLabel ( id , tx )                                 ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  nConnect ( this , SIGNAL ( EmitSection ( ) )            ,
             this , SLOT   ( SendSection ( ) )          ) ;
}

bool N::CalendarObject::FocusIn(void)
{
  nKickOut          ( IsNull(plan) , false       ) ;
  LinkAction        ( ZoomIn       , ZoomIn  ( ) ) ;
  LinkAction        ( ZoomOut      , ZoomOut ( ) ) ;
  emit assignCursor ( Qt::ArrowCursor            ) ;
  Alert             ( Action                     ) ;
  return false                                     ;
}

bool N::CalendarObject::FocusOut(void)
{
  return false ;
}

void N::CalendarObject::SendSection(void)
{
  emit SectionChanged ( this ) ;
}

void N::CalendarObject::MoveRange(QDateTime s,QDateTime f)
{
  qint64 gap = Value ( "Gap" ) . toLongLong ( ) ;
  setRange ( s , f , gap )                      ;
  start    ( 10001       )                      ;
}

void N::CalendarObject::setRange(QDateTime s,QDateTime e,qint64 gap)
{
  LockAt ( "Operate" )                                  ;
  QDateTime ST = Value ( "Separator" ) . toDateTime ( ) ;
  qint64    ds = s . msecsTo ( ST )                     ;
  qint64    dm = ds                                     ;
  if ( s > e )                                          {
    ds = e  . msecsTo ( ST )                            ;
    setVariable ( "Start" , e   )                       ;
    setVariable ( "End"   , s   )                       ;
  } else                                                {
    setVariable ( "Start" , s   )                       ;
    setVariable ( "End"   , e   )                       ;
  }                                                     ;
  setVariable ( "Gap"   , gap )                         ;
  ///////////////////////////////////////////////////////
  if ( ds > 0 )                                         {
    dm /= gap                                           ;
    dm *= gap                                           ;
    ds -= dm                                            ;
  } else                                                {
    dm  = -dm                                           ;
    dm /= gap                                           ;
    dm += 1                                             ;
    dm *= gap                                           ;
    ds  += dm                                           ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  if ( s > e )                                          {
    ST = e                                              ;
  } else                                                {
    ST = s                                              ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  ST = ST . addMSecs ( ds )                             ;
  setVariable ( "Separator" , ST )                      ;
  UnlockAt    ( "Operate"        )                      ;
}

void N::CalendarObject::setRange(QDateTime s,QDateTime e)
{
  LockAt        ( "Operate"   ) ;
  if            ( s > e       ) {
    setVariable ( "Start" , e ) ;
    setVariable ( "End"   , s ) ;
  } else                        {
    setVariable ( "Start" , s ) ;
    setVariable ( "End"   , e ) ;
  }                             ;
  UnlockAt      ( "Operate"   ) ;
}

void N::CalendarObject::setGap(QDateTime separator,qint64 gap)
{
  LockAt      ( "Operate"               ) ;
  setVariable ( "Separator" , separator ) ;
  setVariable ( "Gap"       , gap       ) ;
  UnlockAt    ( "Operate"               ) ;
}

bool N::CalendarObject::Animation(void)
{
  SceneObject::Animation ( ) ;
  MakeTime               ( ) ;
  TrackingTime           ( ) ;
  return true                ;
}

bool N::CalendarObject::Spot (
       ControlPoint & From   ,
       ControlPoint & To     ,
       ControlPoint & At     )
{
  if ( ! Value ( "Mouse" ) . toBool ( ) ) return false ;
  if ( isLoading ( ) ) return false                    ;
  return xymSpot ( From , To , At )                    ;
}

bool N::CalendarObject::MouseVector (
       ControlPoint & From          ,
       ControlPoint & To            ,
       BMAPs        & buttons       )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false        ;
  if ( isLoading ( )                     ) return false        ;
  if ( ! matrices . contains ( 2 )       ) return false        ;
  if ( buttons [ Universe::MouseMiddle ] ) return false        ;
  if ( buttons [ Universe::MouseRight  ] ) return false        ;
  //////////////////////////////////////////////////////////////
  ControlPoint At                                              ;
  if ( ! Collide ( From , To , At )      ) return false        ;
  //////////////////////////////////////////////////////////////
  if ( buttons [ Universe::MouseLeft   ] )                     {
    if ( ! isFocus ( ) )                                       {
      Alert    ( Action )                                      ;
    }                                                          ;
    setFocus ( true   )                                        ;
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      setVariable   ( "T2" , AtFixTime ( At ) )                ;
      MovingObjects ( From , To , At          )                ;
      return true                                              ;
    } else
    if ( Value ( "Timebar" ) . toBool ( ) )                    {
      setVariable ( "ToTime" , AtOldTime ( At ) )              ;
      MoveToNew ( )                                            ;
      return true                                              ;
    } else
    if ( Value ( "Marking" ) . toBool ( ) )                    {
      setVariable  ( "T2" , AtFixTime ( At ) )                 ;
      ShowDuration (                         )                 ;
      return true                                              ;
    } else                                                     {
      int region = AtRegion ( At )                             ;
      switch ( region )                                        {
        case 1                                                 :
        case 2                                                 :
          if ( ! isLoading() )                                 {
            emit assignCursor ( Qt::ClosedHandCursor )         ;
            Variables [ "OldStart" ] = Variables [ "Start" ]   ;
            Variables [ "OldEnd"   ] = Variables [ "End"   ]   ;
            setVariable ( "BaseTime" , AtFixTime ( At ) )      ;
            setVariable ( "Timebar"  , true             )      ;
          } else                                               {
            emit assignCursor ( Qt::WaitCursor       )         ;
          }                                                    ;
        return true                                            ;
        case 3                                                 :
          if ( ! isLoading() )                                 {
            if ( HitObjects ( From , To , At ) )               {
              QDateTime ATX = AtFixTime ( At )                 ;
              setVariable  ( "T1"   , ATX  )                   ;
              setVariable  ( "T2"   , ATX  )                   ;
              setVariable  ( "Hit"  , true )                   ;
              setVariable  ( "Grab" , true )                   ;
            } else                                             {
              emit assignCursor ( Qt::SplitHCursor )           ;
              QDateTime ATX = AtFixTime ( At )                 ;
              setVariable  ( "T1"      , ATX  )                ;
              setVariable  ( "T2"      , ATX  )                ;
              setVariable  ( "Marking" , true )                ;
              ShowDuration (                  )                ;
            }                                                  ;
          }                                                    ;
        break                                                  ;
      }                                                        ;
    }                                                          ;
  } else                                                       {
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      emit assignCursor ( Qt::ArrowCursor )                    ;
      FinalObjects ( From , To , At  )                         ;
      setVariable  ( "Hit"  , false  )                         ;
      setVariable  ( "Grab" , false  )                         ;
      return true                                              ;
    } else
    if ( Value ( "Timebar" ) . toBool ( ) )                    {
      emit assignCursor ( Qt::ArrowCursor )                    ;
      setVariable ( "Timebar" , false )                        ;
      QDateTime stx = Value ( "Start" ) . toDateTime ( )       ;
      QDateTime etx = Value ( "End"   ) . toDateTime ( )       ;
      MoveTime ( stx , etx )                                   ;
      return true                                              ;
    } else
    if ( Value ( "Marking" ) . toBool ( ) )                    {
      emit assignCursor ( Qt::ArrowCursor )                    ;
      QDateTime stx = Value ( "T1" ) . toDateTime ( )          ;
      QDateTime etx = Value ( "T2" ) . toDateTime ( )          ;
      setVariable ( "Marking" , false )                        ;
      if ( stx > etx )                                         {
        AddSection ( etx , stx )                               ;
      } else                                                   {
        AddSection ( stx , etx )                               ;
      }                                                        ;
      return true                                              ;
    } else                                                     {
      emit assignCursor ( Qt::ArrowCursor )                    ;
    }                                                          ;
  }                                                            ;
  return true                                                  ;
}

bool N::CalendarObject::MouseHover (
       ControlPoint & From         ,
       ControlPoint & To           ,
       BMAPs        & buttons      )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false             ;
  if ( isLoading ( )                     ) return false             ;
  if ( ! isFocus             (  )        ) return false             ;
  if ( ! matrices . contains ( 2 )       ) return false             ;
  ///////////////////////////////////////////////////////////////////
  ControlPoint At                                                   ;
  if ( ! Collide ( From , To , At )      ) return false             ;
  ///////////////////////////////////////////////////////////////////
  if ( Value ( "Timebar" ) . toBool ( ) )                           {
    Variables [ "ToTime" ] = AtOldTime ( At )                       ;
    MoveToNew ( )                                                   ;
    return true                                                     ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  if ( Value ( "Marking" ) . toBool ( ) )                           {
    Variables [ "T2" ] = AtFixTime ( At )                           ;
    ShowDuration ( )                                                ;
    return true                                                     ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  if ( Value ( "Hit" ) . toBool ( ) )                               {
    setVariable   ( "T2" , AtFixTime ( At ) )                       ;
    MovingObjects ( From , To , At          )                       ;
    return true                                                     ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  int region = AtRegion ( At )                                      ;
  if ( region <= 0 )                                                {
    emit assignCursor ( Qt::ArrowCursor )                           ;
    return false                                                    ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  bool onlyMoving = true                                            ;
  if ( buttons [ Universe::MouseLeft   ] ) onlyMoving = false       ;
  if ( buttons [ Universe::MouseMiddle ] ) onlyMoving = false       ;
  if ( buttons [ Universe::MouseRight  ] ) onlyMoving = false       ;
  if ( ! onlyMoving ) return true                                   ;
  ///////////////////////////////////////////////////////////////////
  switch ( region )                                                 {
    case 1                                                          :
    case 2                                                          :
      emit assignCursor ( Qt::OpenHandCursor )                      ;
      TimeToolTip       ( At                 )                      ;
    break                                                           ;
    case 3                                                          :
      if ( HoverEvent ( From , To , At     ) ) return true          ;
      emit assignCursor ( Qt::ArrowCursor    )                      ;
      TimeToolTip       ( At                 )                      ;
    break                                                           ;
    default                                                         :
      emit assignCursor ( Qt::ArrowCursor    )                      ;
      TimeToolTip       ( At                 )                      ;
    break                                                           ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  return true                                                       ;
}

bool N::CalendarObject::MouseMove (
       ControlPoint & From1       ,
       ControlPoint & To1         ,
       ControlPoint & From2       ,
       ControlPoint & To2         ,
       BMAPs        & buttons     )
{
  if ( ! Value ( "Mouse" ) . toBool ( ) ) return false ;
  if ( isLoading                    ( ) ) return false ;
  return false                                         ;
}

void N::CalendarObject::TimeToolTip(ControlPoint & At)
{
  QDateTime AT = AtFixTime ( At )                               ;
  QString   AS = AT . toString ("yyyy/MM/dd hh:mm:ss")          ;
  QRect     RX                                                  ;
  QToolTip::showText ( QCursor::pos() , AS , NULL , RX , 3000 ) ;
  if ( NULL != gui ) gui -> setToolTip ( AS )                   ;
}

void N::CalendarObject::ShowDuration(void)
{
  if ( ! LastMoment ( nTimeNow ) ) return                        ;
  ////////////////////////////////////////////////////////////////
  QDateTime T1 = Value ( "T1" ) . toDateTime ( )                 ;
  QDateTime T2 = Value ( "T2" ) . toDateTime ( )                 ;
  QString   S1 = T1 . toString ("yyyy/MM/dd hh:mm:ss")           ;
  QString   S2 = T2 . toString ("yyyy/MM/dd hh:mm:ss")           ;
  QString   S3                                                   ;
  QString   TT                                                   ;
  QRect     RX                                                   ;
  qint64    dt = 0                                               ;
  ////////////////////////////////////////////////////////////////
  if ( T1 > T2 )                                                 {
    TT  = tr("Start : %1" ) . arg ( S2 )                         ;
    TT  . append("\n")                                           ;
    TT += tr("Finish : %1") . arg ( S1 )                         ;
    dt  = T2 . secsTo             ( T1 )                         ;
  } else                                                         {
    TT  = tr("Start : %1" ) . arg ( S1 )                         ;
    TT  . append("\n")                                           ;
    TT += tr("Finish : %1") . arg ( S2 )                         ;
    dt  = T1 . secsTo             ( T2 )                         ;
  }                                                              ;
  if ( dt > 0 )                                                  {
    int days = dt / 86400                                        ;
    QTime TZ ( 0 , 0 , 0 , 0 )                                   ;
    TZ  = TZ . addSecs  ( dt         )                           ;
    S3  = TZ . toString ( "hh:mm:ss" )                           ;
    if ( days > 0 )                                              {
      S3 = tr("Period : %1 days %2") . arg ( days ) . arg ( S3 ) ;
    } else                                                       {
      S3 = tr("Period : %1") . arg ( S3 )                        ;
    }                                                            ;
    TT  . append ( "\n" )                                        ;
    TT += S3                                                     ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  QToolTip::showText ( QCursor::pos() , TT , NULL , RX , 3000 )  ;
  if ( NULL != gui ) gui -> setToolTip ( TT )                    ;
}

bool N::CalendarObject::HoverEvent(ControlPoint & From,ControlPoint & To,ControlPoint & At)
{
  EventObject * eol = LocateEvent ( From , To , At )            ;
  if ( IsNull ( eol ) ) return false                            ;
  ///////////////////////////////////////////////////////////////
  QString tt = eol -> ToolTip ( )                               ;
  QRect   RX                                                    ;
  ///////////////////////////////////////////////////////////////
  QToolTip::showText ( QCursor::pos() , tt , NULL , RX , 3000 ) ;
  if ( NULL != gui ) gui -> setToolTip ( tt )                   ;
  ///////////////////////////////////////////////////////////////
  switch ( eol -> AtRegion ( At ) )                             {
    case 1                                                      :
    case 2                                                      :
      emit assignCursor ( Qt::SplitHCursor   )                  ;
    break                                                       ;
    default                                                     :
      emit assignCursor ( Qt::OpenHandCursor )                  ;
    break                                                       ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  return true                                                   ;
}

N::EventObject * N::CalendarObject::LocateEvent (
                   ControlPoint & From          ,
                   ControlPoint & To            ,
                   ControlPoint & At            )
{
  if ( ! matrices . contains ( 2 ) ) return NULL                    ;
  UUIDs U = list ( "Event" )                                        ;
  if ( U . count ( ) <= 0          ) return NULL                    ;
  ///////////////////////////////////////////////////////////////////
  SUID         u                                                    ;
  QPointF      p ( At . x , At . y )                                ;
  ControlPoint F                                                    ;
  ControlPoint T                                                    ;
  ///////////////////////////////////////////////////////////////////
  F = matrices [ 2 ] * From                                         ;
  T = matrices [ 2 ] * To                                           ;
  foreach ( u , U ) if ( SceneObject::children . contains ( u ) )   {
    EventObject * eol = ChildOf<EventObject> ( u )                  ;
    QRectF        R   = eol -> BoxPlane ( 0 )                       ;
    if ( R . contains ( p ) ) return eol                            ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  return NULL                                                       ;
}

bool N::CalendarObject::Relocation(QRectF region)
{
  if ( isLoading ( ) ) return false                                          ;
  maximum . x = region . width  ( )                                          ;
  maximum . y = region . height ( )                                          ;
  DOFs [ 0 ] . x = - ( maximum . x / 2 )                                     ;
  DOFs [ 0 ] . y = - ( maximum . y / 2 )                                     ;
  Finish ( )                                                                 ;
  Dual   ( )                                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  UUIDs                U = list ( "Event" )                                  ;
  SUID                 u                                                     ;
  QList<EventObject *> EOLs                                                  ;
  ////////////////////////////////////////////////////////////////////////////
  foreach ( u , U ) if ( SceneObject :: children . contains ( u ) )          {
    EOLs << ChildOf<EventObject> ( u )                                       ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( EOLs . count ( ) > 0 ) ArrangeItems ( EOLs )                          ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

QRectF N::CalendarObject::BarArea(void)
{
  int    metric = Value ( "Metric"       ) . toInt ( ) ;
  int    gap    = Value ( "TextGap"      ) . toInt ( ) ;
  bool   top    = Value ( "TopMetric"    ) . toInt ( ) ;
  bool   bottom = Value ( "BottomMetric" ) . toInt ( ) ;
  double T      = minimum . y                          ;
  double B      = maximum . y                          ;
  QRectF R                                             ;
  //////////////////////////////////////////////////////
  if (   top &&   bottom )                             {
    T += metric + gap                                  ;
    B -= metric + gap                                  ;
    B -= metric + gap                                  ;
  } else
  if (   top && ! bottom )                             {
    B -= metric + gap                                  ;
    B -= metric + gap                                  ;
  } else
  if ( ! top &&   bottom )                             {
    T += metric + gap                                  ;
    T += metric + gap                                  ;
  } else                                               {
    B -= metric + gap                                  ;
  }                                                    ;
  //////////////////////////////////////////////////////
  R . setLeft   ( minimum . x )                        ;
  R . setRight  ( maximum . x )                        ;
  R . setTop    ( T           )                        ;
  R . setBottom ( B           )                        ;
  //////////////////////////////////////////////////////
  return R                                             ;
}

void N::CalendarObject::drawTicks(double y,double z,bool up)
{
  bool         autoticks = Value ( "AutoTicks"   ) . toBool     ( )          ;
  int          metric    = Value ( "Metric"      ) . toInt      ( )          ;
  QDateTime    st        = Value ( "Start"       ) . toDateTime ( )          ;
  QDateTime    et        = Value ( "End"         ) . toDateTime ( )          ;
  qint64       dts       = st . msecsTo ( et )                               ;
  int          border    = Value ( "BorderColor" ) . toInt      ( )          ;
  ControlPoint line      = colors [ border ]                                 ;
  double       maxy      = y + metric                                        ;
  double       miny      = y                                                 ;
  qint64       mts       = 0                                                 ;
  bool         m60       = true                                              ;
  bool         m30       = true                                              ;
  bool         m10       = true                                              ;
  bool         m05       = true                                              ;
  bool         m01       = true                                              ;
  bool         t01       = true                                              ;
  ControlPoint minp                                                          ;
  ControlPoint maxp                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( autoticks )                                                           {
    qint64 vvx = 86400 * 1000                                                ;
    qint64 vxm =  3600 * 1000                                                ;
    if ( dts > (       vxm ) ) t01 = false                                   ;
    if ( dts > (       vvx ) ) m01 = false                                   ;
    if ( dts > (   3 * vvx ) ) m05 = false                                   ;
    if ( dts > (   7 * vvx ) ) m10 = false                                   ;
    if ( dts > (  14 * vvx ) ) m30 = false                                   ;
    if ( dts > (  28 * vvx ) ) m60 = false                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::Disable                  ( GL_CULL_FACE                       )      ;
  QtGL::Disable                  ( GL_DEPTH_TEST                      )      ;
  QtGL::Disable                  ( GL_LINE_SMOOTH                     )      ;
  QtGL::Disable                  ( GL_POLYGON_SMOOTH                  )      ;
  ////////////////////////////////////////////////////////////////////////////
  minp     = minimum                                                         ;
  maxp     = maximum                                                         ;
  minp . y = miny                                                            ;
  maxp . y = maxy                                                            ;
  if ( isFocus () )                                                          {
    assumeColor                  ( "MetricColor"                      )      ;
  } else                                                                     {
    assumeColor                  ( "SeparatorColor"                   )      ;
  }                                                                          ;
  CubeVertex                     ( 106 , minp , maxp                  )      ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::Enable                   ( GL_LINE_SMOOTH                     )      ;
  QtGL::Enable                   ( GL_POLYGON_SMOOTH                  )      ;
  LineWidth                      ( "TickLineWidth" , 0.500f           )      ;
  assumeColor                    ( "BorderColor"                      )      ;
  CubeVertex                     ( 206 , minp , maxp                  )      ;
  if ( ! m60 ) return                                                        ;
  ////////////////////////////////////////////////////////////////////////////
  QTime     TX = st . time ( )                                               ;
  QTime     TZ                                                               ;
  QDateTime ftx                                                              ;
  ////////////////////////////////////////////////////////////////////////////
  TZ  = QTime        ( TX . hour ( ) , TX . minute ( ) , 0 , 0 )             ;
  ftx = QDateTime    ( st . date ( ) , TZ                      )             ;
  mts = st . msecsTo ( ftx                                     )             ;
  ////////////////////////////////////////////////////////////////////////////
  #define FIXY                                                               \
    if ( up )                                                              { \
      y1   = y                                                             ; \
      y2  += y1                                                            ; \
    } else                                                                 { \
      y1   = y  + (double) metric                                          ; \
      y2   = y1 - y2                                                       ; \
    }
  #define FIXZ(nn,dd)                                                        \
    p . z /= (double) nn                                                   ; \
    d      = true                                                          ; \
    y2     = ( (double) metric ) * ( (double) nn ) / ( (double) dd )
  ////////////////////////////////////////////////////////////////////////////
  while ( mts < dts )                                                        {
    QDateTime    T  = st                                                     ;
    int          m                                                           ;
    ControlPoint p  = line                                                   ;
    double       xp = mts                                                    ;
    double       y1                                                          ;
    double       y2                                                          ;
    bool         d  = false                                                  ;
    T    = T . addMSecs ( mts )                                              ;
    m    = T . time     (     ) . minute ( )                                 ;
    xp  /= dts                                                               ;
    xp  *= length  . x                                                       ;
    xp  += minimum . x                                                       ;
    if ( mts >= 0 )                                                          {
      if ( m60 && (  0 ==  m )       )                                       { // hour
        QtGL::LineWidth ( 0.750f )                                           ;
        d      = true                                                        ;
        y1     = y                                                           ;
        y2     = metric                                                      ;
        y2    += y1                                                          ;
      } else
      if ( m30 && ( 30 ==  m )       )                                       { // 30 minutes
        QtGL::LineWidth ( 0.500f )                                           ;
        FIXZ (  2 ,  3 )                                                     ;
        FIXY                                                                 ;
      } else
      if ( m10 && ( 0 == ( m % 10 ) ) )                                      { // 10 minutes
        QtGL::LineWidth ( 0.250f )                                           ;
        FIXZ (  4 ,  9 )                                                     ;
        FIXY                                                                 ;
      } else
      if ( m05 && ( 0 == ( m %  5 ) ) )                                      { //  5 minutes
        QtGL::LineWidth ( 0.125f )                                           ;
        FIXZ (  8 , 27 )                                                     ;
        FIXY                                                                 ;
      } else
      if ( m01 )                                                             { // 1 minute
        QtGL::LineWidth ( 0.100f )                                           ;
        FIXZ ( 16 , 81 )                                                     ;
        FIXY                                                                 ;
      }                                                                      ;
      if ( d )                                                               {
        p . Color4d    (             )                                       ;
        QtGL::Lines    (             )                                       ;
        QtGL::Vertex3d ( xp , y1 , z )                                       ;
        QtGL::Vertex3d ( xp , y2 , z )                                       ;
        QtGL::End      (             )                                       ;
      }                                                                      ;
    }                                                                        ;
    if ( t01 )                                                               { // 5 seconds
      for (int i=1;i<12;i++)                                                 {
        p    = line                                                          ;
        xp   = mts + ( i * 5000 )                                            ;
        if ( xp >= 0 )                                                       {
          xp  /= dts                                                         ;
          xp  *= length  . x                                                 ;
          xp  += minimum . x                                                 ;
          QtGL::LineWidth ( 0.100f )                                         ;
          FIXZ ( 20 , 120 )                                                  ;
          FIXY                                                               ;
          p . Color4d    (             )                                     ;
          QtGL::Lines    (             )                                     ;
          QtGL::Vertex3d ( xp , y1 , z )                                     ;
          QtGL::Vertex3d ( xp , y2 , z )                                     ;
          QtGL::End      (             )                                     ;
        }                                                                    ;
      }                                                                      ;
    }                                                                        ;
    mts += 60000                                                             ;
  }                                                                          ;
  #undef FIXZ
  #undef FIXY
}

void N::CalendarObject::MakeTime(void)
{
  if ( isLoading ( ) ) return                             ;
  if ( ! Value ( "Happened"    ) . toBool ( ) ) return    ;
  if ( ! Value ( "CurrentTime" ) . toBool ( ) ) return    ;
  LockAt   ( "Operate" )                                  ;
  /////////////////////////////////////////////////////////
  SceneTexture * tz = NULL                                ;
  if ( ! textures . contains ( 129 ) )                    {
    QSize    s ( 128 , 16 )                               ;
    QImage * O = new QImage ( s , QImage::Format_ARGB32 ) ;
    tz         = new SceneTexture  ( destructor         ) ;
    tz -> node      = 129                                 ;
    tz -> create ( O , true , false )                     ;
    textures [ 129 ]  = tz                                ;
  } else                                                  {
    tz = textures [ 129 ]                                 ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  if ( NotNull ( tz ) )                                   {
    QString   ts                                          ;
    QColor    c (   0 ,   0 , 0   , 255 )                 ;
    QRectF    z (   0 ,   0 , 128 ,  16 )                 ;
    int       flag = Qt::AlignVCenter | Qt::AlignHCenter  ;
    QFont     F                                           ;
    QDateTime nt                                          ;
    nt  = Value ( "DisplayTime" ) . toDateTime ( )        ;
    tz -> original -> fill ( 0 )                          ;
    ts  = nt . toString ( "yyyy/MM/dd hh:mm:ss.zzz" )     ;
    F   = plan -> fonts [ Fonts::Editor ] . toQFont ( )   ;
    F . setPixelSize ( 10   )                             ;
    if ( Variables . contains ( "TextColor" ) )           {
      c = Variables [ "TextColor" ] . value <QColor> ( )  ;
    }                                                     ;
    if ( Variables . contains ( "TextFlags" ) )           {
      flag = Variables [ "TextFlags" ] . toInt ( )        ;
    }                                                     ;
    tz -> drawText ( c , F , z , flag , ts )              ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  UnlockAt ( "Operate" )                                  ;
}

void N::CalendarObject::renderTime(void)
{
  if ( ! Value ( "CurrentTime" ) . toBool ( ) ) return    ;
  if ( ! textures . contains ( 129 )          ) return    ;
  /////////////////////////////////////////////////////////
  QDateTime st = Value ( "Start"       ) . toDateTime ( ) ;
  QDateTime et = Value ( "End"         ) . toDateTime ( ) ;
  QDateTime nt = Value ( "DisplayTime" ) . toDateTime ( ) ;
  if ( nt < st ) return                                   ;
  if ( nt > et ) return                                   ;
  /////////////////////////////////////////////////////////
  qint64 dt     = st . msecsTo ( et )                     ;
  qint64 ds     = st . msecsTo ( nt )                     ;
  int    metric = Value ( "Metric" ) . toInt ( )          ;
  double z      = ( maximum . z + minimum . z ) / 2       ;
  double xp                                               ;
  double yp     = maximum . y - metric - 20               ;
  QRectF r                                                ;
  /////////////////////////////////////////////////////////
  xp  = ds                                                ;
  xp /= dt                                                ;
  xp *= ( maximum . x - minimum . x )                     ;
  xp +=   minimum . x                                     ;
  /////////////////////////////////////////////////////////
  r . setTop    ( yp          )                           ;
  r . setLeft   ( xp - 64     )                           ;
  r . setWidth  ( 128         )                           ;
  r . setHeight ( 16          )                           ;
  renderLabel   ( 129 , r , z )                           ;
}

void N::CalendarObject::drawHappened(void)
{
  QDateTime    st    = Value ( "Start" ) . toDateTime ( )                    ;
  QDateTime    et    = Value ( "End"   ) . toDateTime ( )                    ;
  QDateTime    nt    = nTimeNow                                              ;
  double       x1    = minimum . x                                           ;
  double       x2    = maximum . x                                           ;
  int          faces = 0                                                     ;
  ControlPoint minp                                                          ;
  ControlPoint maxp                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  setVariable ( "DisplayTime" , nt )                                         ;
  if ( nt < st ) return                                                      ;
  if ( nt < et )                                                             {
    qint64 dt = st . msecsTo ( et )                                          ;
    qint64 ds = st . msecsTo ( nt )                                          ;
    x2  = ds                                                                 ;
    x2 /= dt                                                                 ;
    x2 *= ( maximum . x - minimum . x )                                      ;
    x2 +=   minimum . x                                                      ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  minp     = minimum                                                         ;
  maxp     = maximum                                                         ;
  minp . x = x1                                                              ;
  minp . z = minimum . z + 1                                                 ;
  maxp . x = x2                                                              ;
  maxp . z = maximum . z - 1                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Back" ) . toBool ( )             ) {
    faces ++                                                                 ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Disable              ( GL_LINE_SMOOTH                            ) ; // Back
    QtGL::Disable              ( GL_POLYGON_SMOOTH                         ) ;
    assumeColor                ( "DayBack"                                 ) ;
    CubeVertex                 ( 100 , minp , maxp                         ) ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Enable               ( GL_LINE_SMOOTH                            ) ; // Line
    QtGL::Enable               ( GL_POLYGON_SMOOTH                         ) ;
    LineWidth                  ( "DayLineWidth" , 0.750f                   ) ;
    assumeColor                ( "DayLine"                                 ) ;
    CubeVertex                 ( 200 , minp , maxp                         ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Front" ) . toBool ( )            ) {
    faces ++                                                                 ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Disable              ( GL_LINE_SMOOTH                            ) ; // Front
    QtGL::Disable              ( GL_POLYGON_SMOOTH                         ) ;
    assumeColor                ( "DayFront"                                ) ;
    CubeVertex                 ( 101 , minp , maxp                         ) ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Enable               ( GL_LINE_SMOOTH                            ) ; // Front
    QtGL::Enable               ( GL_POLYGON_SMOOTH                         ) ;
    LineWidth                  ( "DayLineWidth" , 0.750f                   ) ;
    assumeColor                ( "DayLine"                                 ) ;
    CubeVertex                 ( 201 , minp , maxp                         ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( faces >= 2 )                                                          {
    QtGL::Enable               ( GL_LINE_SMOOTH                            ) ; // Front
    QtGL::Enable               ( GL_POLYGON_SMOOTH                         ) ;
    LineWidth                  ( "DayLineWidth" , 0.750f                   ) ;
    assumeColor                ( "DayLine"                                 ) ;
    QtGL::Lines                (                                           ) ;
    CubeVertex                 (   6 , minp , maxp                         ) ;
    QtGL::End                  (                                           ) ;
  }                                                                          ;
}

void N::CalendarObject::drawLabels(void)
{
  drawYears   ( ) ;
  drawMonths  ( ) ;
  drawDays    ( ) ;
  drawHours   ( ) ;
  drawMinutes ( ) ;
}

N::SceneTexture * N::CalendarObject::GetLabel(int id,QSize s)
{
  if ( textures . contains ( id ) ) return textures [ id ] ;
  SceneTexture * tz = NULL                                 ;
  QImage * O = new QImage ( s , QImage::Format_ARGB32 )    ;
  tz         = new SceneTexture  ( destructor         )    ;
  tz -> node = id                                          ;
  tz -> create ( O , true , false )                        ;
  textures [ id ]  = tz                                    ;
  if ( NULL != destructor ) (*destructor) += O             ;
  return tz                                                ;
}

N::SceneTexture * N::CalendarObject::GetLabel(int id)
{
  QSize s         ( 64 , 16 ) ;
  return GetLabel ( id , s  ) ;
}

void N::CalendarObject::drawLabel(int id,QString text)
{
  QColor c = Value ( "LabelColor" ) . value < QColor > ( ) ;
  drawLabel ( id , text , c , Qt::AlignCenter )            ;
}

void N::CalendarObject::drawLabel(int id,QString text,QRectF z,QColor c,int f,int pixel)
{
  QSize          s  = z . size ( ) . toSize ( )       ;
  SceneTexture * tz = GetLabel ( id , s )             ;
  if ( IsNull ( tz ) ) return                         ;
  /////////////////////////////////////////////////////
  QFont F                                             ;
  tz -> original -> fill ( 0 )                        ;
  F   = plan -> fonts [ Fonts::Editor ] . toQFont ( ) ;
  F . setPixelSize ( pixel )                          ;
  tz -> drawText ( c , F , z , f , text )             ;
}

void N::CalendarObject::drawLabel(int id,QString text,QColor c,int f)
{
  QRectF z  ( 0 , 0 , 64 , 16       ) ;
  drawLabel ( id , text , z , c , f ) ;
}

void N::CalendarObject::renderLabel(int id,QRectF & r,double z)
{
  if ( ! textures . contains ( id ) ) return  ;
  bool texture = ( bindTexture  ( id ) >= 0 ) ;
  if ( texture ) TextureRect    ( r , z     ) ;
  if ( texture ) releaseTexture ( id        ) ;
}

void N::CalendarObject::drawOneYear(void)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( )             ;
  int       yy = st . date ( ) . year ( )                       ;
  QString   ys = QString::number ( yy )                         ;
  QColor    c  = Value ( "YearColor" ) . value < QColor > ( )   ;
  QRectF    R ( 0 , 0 , 256 , 64     )                          ;
  double    z  = minimum . z + 0.5                              ;
  QRectF    X                                                   ;
  double    xp = ( minimum . x + maximum . x ) / 2              ;
  double    yp = ( minimum . y + maximum . y ) / 2              ;
  bool      hy = false                                          ;
  ///////////////////////////////////////////////////////////////
  if ( Variables . contains ( "LastYear" ) )                    {
    int ly                                                      ;
    ly = Variables [ "LastYear" ] . toInt ( )                   ;
    if ( ly == yy ) hy = true                                   ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  yp -=  64                                                     ;
  xp -= 128                                                     ;
  X . setTop    ( yp  )                                         ;
  X . setLeft   ( xp  )                                         ;
  X . setWidth  ( 256 )                                         ;
  X . setHeight ( 64  )                                         ;
  ///////////////////////////////////////////////////////////////
  if ( ! hy )                                                   {
    setVariable ( "LastYear" , yy                             ) ;
    drawLabel   ( 1300000 , ys , R , c , Qt::AlignCenter , 60 ) ;
  }                                                             ;
  renderLabel   ( 1300000 , X  , z                            ) ;
}

void N::CalendarObject::drawYears(void)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( )           ;
  QDateTime et = Value ( "End"   ) . toDateTime ( )           ;
  if ( st . date ( ) . year ( ) == et . date ( ) . year ( ) ) {
    drawOneYear ( )                                           ;
    return                                                    ;
  }                                                           ;
}

void N::CalendarObject::drawMonths(void)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( ) ;
  QDateTime et = Value ( "End"   ) . toDateTime ( ) ;
  qint64    dt = st . secsTo ( et )                 ;
  qint64    mt = dt / 86400                         ;
  if ( mt > 730 ) return                            ;
}

void N::CalendarObject::drawDays(void)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( )  ;
  QDateTime et = Value ( "End"   ) . toDateTime ( )  ;
  qint64    dt = st . secsTo ( et )                  ;
  qint64    mt = dt / 86400                          ;
  if ( mt > 31 ) return                              ;
  ////////////////////////////////////////////////////
  int       m  = Value ( "Metric" ) . toInt      ( ) ;
  double    y  = maximum . y - 24.0 - m              ;
  double    z  = minimum . z + 0.2                   ;
  QDateTime ft = st                                  ;
  qint64    xt                                       ;
  QRectF    r                                        ;
  double    xp                                       ;
  QTime     TZ ( 0 , 0 , 0 , 0 )                     ;
  qint64    hr = 86400 * 1000                        ;
  int       ti = 0                                   ;
  ////////////////////////////////////////////////////
  bool top    = Value ( "TopMetric"    ) . toInt ( ) ;
  bool bottom = Value ( "BottomMetric" ) . toInt ( ) ;
  ////////////////////////////////////////////////////
  if ( ( ! top ) && bottom )                         {
    y = minimum . y + 8.0 + m                        ;
  }                                                  ;
  ////////////////////////////////////////////////////
  dt = st . msecsTo ( et )                           ;
  ft = QDateTime ( st . date ( ) , TZ )              ;
  ////////////////////////////////////////////////////
  while ( ft < et )                                  {
    int       id                                     ;
    QString   dx                                     ;
    QDateTime T1                                     ;
    QDateTime T2                                     ;
    qint64    dxs                                    ;
    //////////////////////////////////////////////////
    id = ti + 1100000                                ;
    dx = ft . toString ( "MM/dd" )                   ;
    drawLabel          ( id , dx )                   ;
    //////////////////////////////////////////////////
    T1  = ft                                         ;
    T2  = T1                                         ;
    T2  = T2 . addSecs ( 86400 )                     ;
    if ( T1 < st ) T1 = st                           ;
    if ( T2 > et ) T2 = et                           ;
    dxs  = T1 . secsTo  ( T2  )                      ;
    dxs /= 2                                         ;
    T1   = T1 . addSecs ( dxs )                      ;
    //////////////////////////////////////////////////
    xt  = st . msecsTo  ( T1    )                    ;
    xp  = xt                                         ;
    xp /= dt                                         ;
    xp *= ( maximum . x - minimum . x )              ;
    xp +=   minimum . x                              ;
    //////////////////////////////////////////////////
    r . setTop          ( y          )               ;
    r . setLeft         ( xp - 32    )               ;
    r . setWidth        ( 64         )               ;
    r . setHeight       ( 16         )               ;
    renderLabel         ( id , r , z )               ;
    ft  = ft . addMSecs ( hr         )               ;
    //////////////////////////////////////////////////
    ti ++                                            ;
  }                                                  ;
}

void N::CalendarObject::drawHours(void)
{
  QDateTime st = Value ( "Start"  ) . toDateTime ( ) ;
  QDateTime et = Value ( "End"    ) . toDateTime ( ) ;
  qint64    dt = st . secsTo ( et )                  ;
  qint64    mt = 86400                               ;
  if ( dt > ( mt * 4 ) ) return                      ; // 4 days
  ////////////////////////////////////////////////////
  int       m  = Value ( "Metric" ) . toInt      ( ) ;
  double    y  = maximum . y - 8.0 - m               ;
  double    z  = minimum . z + 0.2                   ;
  QDateTime ft = st                                  ;
  qint64    xt                                       ;
  QRectF    r                                        ;
  double    xp                                       ;
  QTime     TX = st . time ( )                       ;
  QTime     TZ                                       ;
  qint64    hr = 3600 * 1000                         ;
  ////////////////////////////////////////////////////
  bool top    = Value ( "TopMetric"    ) . toInt ( ) ;
  bool bottom = Value ( "BottomMetric" ) . toInt ( ) ;
  ////////////////////////////////////////////////////
  if ( ( ! top ) && bottom )                         {
    y = minimum . y - 8.0 + m                        ;
  }                                                  ;
  ////////////////////////////////////////////////////
  dt = st . msecsTo ( et )                           ;
  TZ = QTime ( TX.hour() , 0 , 0 , 0 )               ;
  ft = QDateTime ( st . date ( ) , TZ )              ;
  ////////////////////////////////////////////////////
  while ( ft < et )                                  {
    if ( ft >= st )                                  {
      int id = ft . time() . hour ( ) + 1000000      ;
      ////////////////////////////////////////////////
      xt  = st . msecsTo  ( ft    )                  ;
      xp  = xt                                       ;
      xp /= dt                                       ;
      xp *= ( maximum . x - minimum . x )            ;
      xp +=   minimum . x                            ;
      ////////////////////////////////////////////////
      r . setTop        ( y          )               ;
      r . setLeft       ( xp - 32    )               ;
      r . setWidth      ( 64         )               ;
      r . setHeight     ( 16         )               ;
      renderLabel       ( id , r , z )               ;
    }                                                ;
    ft  = ft . addMSecs ( hr         )               ;
  }                                                  ;
}

void N::CalendarObject::drawMinutes(void)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( ) ;
  QDateTime et = Value ( "End"   ) . toDateTime ( ) ;
  qint64    dt = st . secsTo ( et ) / 60            ;
  if ( dt > 150 ) return                            ; // 150 minutes => 2 hours 30 minutes
  ///////////////////////////////////////////////////
  double    y  = maximum . y - 16.0                 ;
  double    z  = minimum . z +  0.2                 ;
  QDateTime ft = st                                 ;
  qint64    xt                                      ;
  QRectF    r                                       ;
  double    xp                                      ;
  QTime     TX = st . time ( )                      ;
  QTime     TZ                                      ;
  ///////////////////////////////////////////////////
  bool top    = Value ( "TopMetric"    ) . toInt () ;
  bool bottom = Value ( "BottomMetric" ) . toInt () ;
  ///////////////////////////////////////////////////
  if ( ( ! top ) && bottom ) y = minimum . y        ;
  ///////////////////////////////////////////////////
  dt = st . msecsTo ( et )                          ;
  TZ = QTime ( TX.hour() , TX.minute() , 0 , 0 )    ;
  ft = QDateTime ( st . date ( ) , TZ )             ;
  ///////////////////////////////////////////////////
  while ( ft < et )                                 {
    if ( ft >= st )                                 {
      int id = ft . time() . minute ( ) + 1000000   ;
      ///////////////////////////////////////////////
      xt  = st . msecsTo  ( ft    )                 ;
      xp  = xt                                      ;
      xp /= dt                                      ;
      xp *= ( maximum . x - minimum . x )           ;
      xp +=   minimum . x                           ;
      ///////////////////////////////////////////////
      r . setTop        ( y          )              ;
      r . setLeft       ( xp - 32    )              ;
      r . setWidth      ( 64         )              ;
      r . setHeight     ( 16         )              ;
      renderLabel       ( id , r , z )              ;
    }                                               ;
    ft  = ft . addMSecs ( 60000      )              ;
  }                                                 ;
}

void N::CalendarObject::drawDaylight(double z)
{
  double alpha [ 24 ] =                                     {
    0.50 , 0.50 , 0.45 , 0.42 , 0.40 , 0.35 , 0.30 , 0.25   ,
    0.12 , 0.08 , 0.03 , 0.02 , 0.01 , 0.01 , 0.02 , 0.03   ,
    0.06 , 0.08 , 0.12 , 0.25 , 0.30 , 0.35 , 0.40 , 0.45 } ;
  ControlPoint dl = colors [ 0 ]                            ;
  QDateTime    st = Value ( "Start" ) . toDateTime ( )      ;
  QDateTime    et = Value ( "End"   ) . toDateTime ( )      ;
  QDateTime    ft                                           ;
  QDateTime    zt                                           ;
  QDateTime    dft                                          ;
  QDateTime    dzt                                          ;
  QTime        TT                                           ;
  qint64       dt = st . msecsTo ( et )                     ;
  double       x1                                           ;
  double       x2                                           ;
  int          hr                                           ;
  int          nr                                           ;
  ///////////////////////////////////////////////////////////
  TT = st . time (                       )                  ;
  TT = QTime     ( TT . hour ( ) , 0 , 0 )                  ;
  ft = QDateTime ( st . date ( ) , TT    )                  ;
  ///////////////////////////////////////////////////////////
  QtGL::Disable ( GL_CULL_FACE      )                       ;
  QtGL::Disable ( GL_DEPTH_TEST     )                       ;
  QtGL::Enable  ( GL_LINE_SMOOTH    )                       ;
  QtGL::Enable  ( GL_POLYGON_SMOOTH )                       ;
  while ( ft < et )                                         {
    hr  = ft . time ( ) . hour ( )                          ;
    nr  = ( hr + 1 ) % 24                                   ;
    zt  = ft                                                ;
    zt  = zt . addSecs ( 3600 )                             ;
    dft = ft                                                ;
    dzt = zt                                                ;
    if ( dft < st ) dft = st                                ;
    if ( dzt > et ) dzt = et                                ;
    /////////////////////////////////////////////////////////
    x1  = st . msecsTo ( dft )                              ;
    x1 /= dt                                                ;
    x1 *= length  . x                                       ;
    x1 += minimum . x                                       ;
    x2  = st . msecsTo ( dzt )                              ;
    x2 /= dt                                                ;
    x2 *= length  . x                                       ;
    x2 += minimum . x                                       ;
    /////////////////////////////////////////////////////////
    QtGL::Quadrilateral ( )                                 ;
    dl . t = alpha [ hr ]                                   ;
    dl . Color4d ( )                                        ;
    QtGL::Vertex3d ( x1 , minimum . y , z )                 ;
    dl . t = alpha [ nr ]                                   ;
    dl . Color4d ( )                                        ;
    QtGL::Vertex3d ( x2 , minimum . y , z )                 ;
    dl . t = alpha [ nr ]                                   ;
    dl . Color4d ( )                                        ;
    QtGL::Vertex3d ( x2 , maximum . y , z )                 ;
    dl . t = alpha [ hr ]                                   ;
    dl . Color4d ( )                                        ;
    QtGL::Vertex3d ( x1 , maximum . y , z )                 ;
    QtGL::End           ( )                                 ;
    /////////////////////////////////////////////////////////
    ft  = ft . addSecs ( 3600 )                             ;
  }                                                         ;
}

void N::CalendarObject::drawWeather(double z)
{
}

void N::CalendarObject::drawMarking(void)
{
  QDateTime    st    = Value ( "Start" ) . toDateTime ( )                    ;
  QDateTime    et    = Value ( "End"   ) . toDateTime ( )                    ;
  QDateTime    t1    = Value ( "T1"    ) . toDateTime ( )                    ;
  QDateTime    t2    = Value ( "T2"    ) . toDateTime ( )                    ;
  double       x1    = minimum . x                                           ;
  double       x2    = maximum . x                                           ;
  int          faces = 0                                                     ;
  qint64       dt    = st . msecsTo ( et )                                   ;
  qint64       xt    = 0                                                     ;
  double       z                                                             ;
  ControlPoint minp                                                          ;
  ControlPoint maxp                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( t1 > t2 )                                                             {
    t1 = Value ( "T2" ) . toDateTime ( )                                     ;
    t2 = Value ( "T1" ) . toDateTime ( )                                     ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  xt  = st . msecsTo ( t1 )                                                  ;
  x1  = xt                                                                   ;
  x1 /= dt                                                                   ;
  x1 *= ( maximum . x - minimum . x )                                        ;
  x1 +=   minimum . x                                                        ;
  ////////////////////////////////////////////////////////////////////////////
  xt  = st . msecsTo ( t2 )                                                  ;
  x2  = xt                                                                   ;
  x2 /= dt                                                                   ;
  x2 *= ( maximum . x - minimum . x )                                        ;
  x2 +=   minimum . x                                                        ;
  ////////////////////////////////////////////////////////////////////////////
  minp . x = x1                                                              ;
  minp . y = minimum . y                                                     ;
  minp . z = minimum . z                                                     ;
  maxp . x = x2                                                              ;
  maxp . y = maximum . y                                                     ;
  maxp . z = maximum . z                                                     ;
  ////////////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Back" ) . toBool ( )             ) {
    faces ++                                                                 ;
    z = minimum . z                                                          ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Disable              ( GL_LINE_SMOOTH                            ) ; // Back
    QtGL::Disable              ( GL_POLYGON_SMOOTH                         ) ;
    assumeColor                ( "MarkBack"                                ) ;
    CubeVertex                 ( 100 , minp , maxp                         ) ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Enable               ( GL_LINE_SMOOTH                            ) ; // Line
    QtGL::Enable               ( GL_POLYGON_SMOOTH                         ) ;
    LineWidth                  ( "DayLineWidth" , 0.750f                   ) ;
    assumeColor                ( "MarkLine"                                ) ;
    CubeVertex                 ( 200 , minp , maxp                         ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Front" ) . toBool ( )            ) {
    faces ++                                                                 ;
    z = maximum . z - 1                                                      ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Disable              ( GL_LINE_SMOOTH                            ) ; // Front
    QtGL::Disable              ( GL_POLYGON_SMOOTH                         ) ;
    assumeColor                ( "MarkFront"                               ) ;
    CubeVertex                 ( 101 , minp , maxp                         ) ;
    //////////////////////////////////////////////////////////////////////////
    QtGL::Enable               ( GL_LINE_SMOOTH                            ) ; // Front
    QtGL::Enable               ( GL_POLYGON_SMOOTH                         ) ;
    LineWidth                  ( "DayLineWidth" , 0.750f                   ) ;
    assumeColor                ( "MarkLine"                                ) ;
    CubeVertex                 ( 201 , minp , maxp                         ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( faces >= 2 )                                                          {
    QtGL::Enable               ( GL_LINE_SMOOTH                            ) ; // Front
    QtGL::Enable               ( GL_POLYGON_SMOOTH                         ) ;
    LineWidth                  ( "DayLineWidth" , 0.750f                   ) ;
    assumeColor                ( "MarkLine"                                ) ;
    QtGL::Lines                (                                           ) ;
    CubeVertex                 (   6 , minp , maxp                         ) ;
    QtGL::End                  (                                           ) ;
  }                                                                          ;
}

void N::CalendarObject::renderGrids(void)
{
  /////////////////////////////////////////////////////////////////////
  QtGL::PushMatrix             (                                    ) ;
  /////////////////////////////////////////////////////////////////////
  QtGL::Disable                ( GL_CULL_FACE                       ) ;
  QtGL::Disable                ( GL_DEPTH_TEST                      ) ;
  QtGL::Disable                ( GL_LINE_SMOOTH                     ) ;
  QtGL::Disable                ( GL_POLYGON_SMOOTH                  ) ;
  FeatureCube                  ( minimum , maximum                  ) ;
  /////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Dayline" ) . toBool ( )   ) {
    QDateTime st  = Value ( "Start"     ) . toDateTime ( )            ;
    QDateTime et  = Value ( "End"       ) . toDateTime ( )            ;
    QDateTime sr  = Value ( "Separator" ) . toDateTime ( )            ;
    qint64    gap = Value ( "Gap"       ) . toLongLong ( )            ;
    qint64    dts = st . msecsTo ( et )                               ;
    qint64    rts = st . msecsTo ( sr )                               ;
    while ( rts < dts )                                               {
      if ( rts >= 0 )                                                 {
        ControlPoint minp                                             ;
        ControlPoint maxp                                             ;
        double       xp = rts                                         ;
        xp      /= dts                                                ;
        xp      *= length  . x                                        ;
        xp      += minimum . x                                        ;
        minp     = minimum                                            ;
        maxp     = maximum                                            ;
        minp . x = xp                                                 ;
        maxp . x = xp                                                 ;
        assumeColor                    ( "SeparatorColor"           ) ;
        CubeVertex                     ( 103 , minp , maxp          ) ;
        assumeColor                    ( "GridColor"                ) ;
        CubeVertex                     ( 203 , minp , maxp          ) ;
      }                                                               ;
      rts += gap                                                      ;
    }                                                                 ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Tick" ) . toBool ( )      ) {
    int metric = Value ( "Metric" ) . toInt ( )                       ;
    if ( Value ( "TopMetric"    ) . toBool ( ) )                      {
      drawTicks ( maximum . y - metric , minimum.z + 0.1 , true     ) ;
    }                                                                 ;
    if ( Value ( "BottomMetric" ) . toBool ( ) )                      {
      drawTicks ( 0                    , minimum.z + 0.1 , false    ) ;
    }                                                                 ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Happened" ) . toBool ( )  ) {
    drawHappened               (                                    ) ;
    renderTime                 (                                    ) ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  if                           ( Value ( "TimeLabels"). toBool ( )  ) {
    drawLabels                 (                                    ) ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Daylight" ) . toBool ( )  ) {
    drawDaylight               ( minimum.z + 0.2                    ) ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Weather"  ) . toBool ( )  ) {
    drawWeather                ( minimum.z + 0.3                    ) ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  if                           ( Value ( "Marking"  ) . toBool ( )  ) {
    drawMarking                (                                    ) ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  QtGL::Enable                 ( GL_CULL_FACE                       ) ;
  QtGL::Enable                 ( GL_DEPTH_TEST                      ) ;
  /////////////////////////////////////////////////////////////////////
  QtGL::PopMatrix              (                                    ) ;
  /////////////////////////////////////////////////////////////////////
}

void N::CalendarObject::renderChildren(void)
{
  if ( isLoading ( ) ) return     ;
  SceneObject::renderChildren ( ) ;
}

void N::CalendarObject::run(int type,ThreadData * data)
{
  nDropOut ( ! IsContinue ( data ) )                            ;
  switch ( type )                                               {
    case 10001                                                  :
      Time::msleep    ( 200 )                                   ;
      Load            (     )                                   ;
    break                                                       ;
    case 10002                                                  :
      if ( 3 == data -> Arguments . count ( ) )                 {
        SUID      u = data -> Arguments [ 0 ] . toULongLong ( ) ;
        QDateTime s = data -> Arguments [ 1 ] . toDateTime  ( ) ;
        QDateTime f = data -> Arguments [ 2 ] . toDateTime  ( ) ;
        UpdateSpot ( u , s , f )                                ;
      }                                                         ;
    break                                                       ;
    case 10003                                                  :
      Time::msleep    ( 200 )                                   ;
      WeatherFeeder   (     )                                   ;
    break                                                       ;
    case 10004                                                  :
      Time::msleep    ( 200 )                                   ;
      OrganizeDepends (     )                                   ;
    break                                                       ;
    case 10005                                                  :
      if ( 2 == data -> Arguments . count ( ) )                 {
        QDateTime s = data -> Arguments [ 0 ] . toDateTime  ( ) ;
        QDateTime f = data -> Arguments [ 1 ] . toDateTime  ( ) ;
        BriefAdd   ( s , f     )                                ;
      }                                                         ;
    break                                                       ;
  }                                                             ;
}

void N::CalendarObject::ThreadEvent(void)
{
  qApp -> processEvents ( ) ;
}

bool N::CalendarObject::contains(QDateTime start,QDateTime final)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( )      ;
  QDateTime et = Value ( "End"   ) . toDateTime ( )      ;
  if ( ( final <  st )                    ) return false ;
  if ( ( start >  et )                    ) return false ;
  if ( ( start >= st ) && ( start <= et ) ) return true  ;
  if ( ( final >= st ) && ( final <= et ) ) return true  ;
  if ( ( start <= st ) && ( final >= et ) ) return true  ;
  return false                                           ;
}

bool N::CalendarObject::Intersects(QRectF & r,QList<QRectF> & rects)
{
  int t = rects . count ( )               ;
  if ( t <= 0 ) return false              ;
  for (int i=0;i<t;i++)                   {
    if ( rects [ i ] . intersects ( r ) ) {
      return true                         ;
    }                                     ;
  }                                       ;
  return false                            ;
}

bool N::CalendarObject::EventRectangle (
       EventObject * eol               ,
       QRectF      & r                 ,
       QRectF      & area              ,
       int           gap               ,
       int           metric            )
{
  QDateTime st = Value          ( "Start" ) . toDateTime ( )                 ;
  QDateTime et = Value          ( "End"   ) . toDateTime ( )                 ;
  QDateTime se = eol -> Value   ( "Start" ) . toDateTime ( )                 ;
  QDateTime ee = eol -> Value   ( "End"   ) . toDateTime ( )                 ;
  qint64    dt = st   . msecsTo ( et      )                                  ;
  qint64    ds = st   . msecsTo ( se      )                                  ;
  qint64    de = st   . msecsTo ( ee      )                                  ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( ds <  0 ) && ( de <  0 ) ) return false                             ;
  if ( ( ds > dt ) && ( de > dt ) ) return false                             ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ds <  0 ) ds = 0                                                      ;
  if ( de <  0 ) de = 0                                                      ;
  if ( ds > dt ) ds = dt                                                     ;
  if ( de > dt ) de = dt                                                     ;
  ////////////////////////////////////////////////////////////////////////////
  if ( gap < 0 )                                                             {
    r . setBottom ( area . bottom ( )          )                             ;
    r . setTop    ( area . bottom ( ) - metric )                             ;
  } else                                                                     {
    r . setTop    ( area . top    ( )          )                             ;
    r . setBottom ( area . top    ( ) + metric )                             ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  eol -> minimum . x  = r . top    ( )                                       ;
  eol -> maximum . y  = r . bottom ( )                                       ;
  ////////////////////////////////////////////////////////////////////////////
  eol -> minimum . x  = ds                                                   ;
  eol -> minimum . x /= dt                                                   ;
  eol -> minimum . x *= ( maximum . x - minimum . x )                        ;
  eol -> minimum . x +=   minimum . x                                        ;
  ////////////////////////////////////////////////////////////////////////////
  eol -> maximum . x  = de                                                   ;
  eol -> maximum . x /= dt                                                   ;
  eol -> maximum . x *= ( maximum . x - minimum . x )                        ;
  eol -> maximum . x +=   minimum . x                                        ;
  ////////////////////////////////////////////////////////////////////////////
  r . setLeft  ( eol -> minimum . x )                                        ;
  r . setRight ( eol -> maximum . x )                                        ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

void N::CalendarObject::Clear(void)
{
  UUIDs R = list ( "Event" )                    ;
  SUID  u                                       ;
  ///////////////////////////////////////////////
  if ( R . count ( ) <= 0 ) return              ;
  ///////////////////////////////////////////////
  foreach ( u , R )                             {
    EventObject * eox = ChildOf<EventObject>(u) ;
    if ( NULL != eox )                          {
      SceneObject::children.remove ( u )        ;
      delete eox                                ;
    }                                           ;
  }                                             ;
}

void N::CalendarObject::startup(void)
{
  start ( 10001 ) ;
}

void N::CalendarObject::TrackingTime(void)
{
  if ( ! Value ( "Tracking" ) . toBool ( ) ) return       ;
  QDateTime st  = Value ( "Start"      ) . toDateTime ( ) ;
  QDateTime et  = Value ( "End"        ) . toDateTime ( ) ;
  QDateTime nt  = nTimeNow                                ;
  double    tm  = Value ( "TimeMargin" ) . toDouble   ( ) ;
  qint64    gap = Value ( "Gap"        ) . toLongLong ( ) ;
  qint64    dt  = st . msecsTo ( et )                     ;
  qint64    ct  = st . msecsTo ( nt )                     ;
  qint64    gt  = (qint64)( ((double)dt) * tm )           ;
  /////////////////////////////////////////////////////////
  if (   ct        < 0  ) return                          ;
  if ( ( ct + gt ) < dt ) return                          ;
  /////////////////////////////////////////////////////////
  ct  = dt / 2                                            ;
  st  = nt                                                ;
  et  = nt                                                ;
  st  = st . addMSecs ( -ct )                             ;
  et  = et . addMSecs (  ct )                             ;
  /////////////////////////////////////////////////////////
  setRange   ( st , et , gap )                            ;
  MoveTime   ( st , et       )                            ;
}

bool N::CalendarObject::Filter(SqlConnection & SC,EventObject * eol)
{
  if ( ! Value ( "LocalOnly" ) . toBool ( ) ) return true ;
  SUID    u = eol -> Value ( "UUID" ) . toULongLong ( )   ;
  if ( u <= 0                               ) return true ;
  QString Q                                               ;
  bool    c = false                                       ;
  Q = SC . sql . SelectFrom                               (
        "first"                                           ,
        PlanTable(OtherGroups)                            ,
        QString ( "where `second` = %1"
                   " and `t1` = %2"
                   " and `t2` = %3"
                   " and `relation` = %4"                 )
        . arg ( u                                         )
        . arg ( Types::Equipment                          )
        . arg ( Types::Schedule                           )
        . arg ( Groups::Subordination                 ) ) ;
  SqlLoopNow ( SC , Q )                                   ;
    SUID e = SC . Uuid ( 0 )                              ;
    if ( e == plan -> Machine ) c = true                  ;
  SqlLoopErr ( SC , Q )                                   ;
  SqlLoopEnd ( SC , Q )                                   ;
  return c                                                ;
}

N::EventObject * N::CalendarObject::NewEventObject(void)
{
  EventObject * eol = new EventObject ( NULL , plan , destructor ) ;
  QVariants     v                                                  ;
  eol -> setUniverse   ( UniverseUuid ( ) )                        ;
  eol -> setParentUuid ( node             )                        ;
  eol -> calendar         = this                                   ;
  eol -> gui              = gui                                    ;
  eol -> DynamicFunctions = DynamicFunctions                       ;
  eol -> ConnectCalendar ( this )                                  ;
  BindingMenu ( eol                              )                 ;
  CallDynamic ( "EventConnector" , eol , gui , v )                 ;
  return eol                                                       ;
}

N::PeriodBlock * N::CalendarObject::NewPeriodBlock(QDateTime s,QDateTime f)
{
  PeriodBlock * pob = new PeriodBlock ( NULL , plan , destructor ) ;
  QDateTime     st  = Value ( "Start" ) . toDateTime ( )           ;
  QDateTime     et  = Value ( "End"   ) . toDateTime ( )           ;
  qint64        dt  = st . msecsTo ( et )                          ;
  qint64        ft  = st . msecsTo ( s  )                          ;
  qint64        zt  = st . msecsTo ( f  )                          ;
  QVariants     v                                                  ;
  //////////////////////////////////////////////////////////////////
  pob -> setUniverse   ( UniverseUuid ( ) )                        ;
  pob -> setParentUuid ( node             )                        ;
  pob -> gui              = gui                                    ;
  pob -> DynamicFunctions = DynamicFunctions                       ;
  //////////////////////////////////////////////////////////////////
  BindingMenu        ( pob                         )               ;
  CalculateBlock     ( pob , s , f                 )               ;
  pob -> addSequence ( 16 , SceneObject::RenderBox )               ;
  appendChild        ( 50001 , pob                 )               ;
  //////////////////////////////////////////////////////////////////
  nConnect ( pob  , SIGNAL ( Changed      (SUID) )                 ,
             this , SLOT   ( ChangePeriod (SUID) )               ) ;
  nConnect ( pob  , SIGNAL ( Close        (SUID) )                 ,
             this , SLOT   ( ClosePeriod  (SUID) )               ) ;
  CallDynamic ( "PeriodConnector" , pob , gui , v )                ;
  return pob                                                       ;
}

void N::CalendarObject::CalculateBlock(PeriodBlock * pob,QDateTime s,QDateTime f)
{
  QDateTime     st  = Value ( "Start" ) . toDateTime ( )           ;
  QDateTime     et  = Value ( "End"   ) . toDateTime ( )           ;
  qint64        dt  = st . msecsTo ( et )                          ;
  qint64        ft  = st . msecsTo ( s  )                          ;
  qint64        zt  = st . msecsTo ( f  )                          ;
  //////////////////////////////////////////////////////////////////
  pob -> minimum . x  = ft                                         ;
  pob -> minimum . x /= dt                                         ;
  pob -> minimum . x *= length  . x                                ;
  pob -> minimum . x += minimum . x                                ;
  pob -> maximum . x  = zt                                         ;
  pob -> maximum . x /= dt                                         ;
  pob -> maximum . x *= length  . x                                ;
  pob -> maximum . x += minimum . x                                ;
  //////////////////////////////////////////////////////////////////
  pob -> minimum . y  = minimum . y                                ;
  pob -> maximum . y  = maximum . y                                ;
  pob -> minimum . z  = minimum . z + 1.0                          ;
  pob -> maximum . z  = maximum . z - 1.0                          ;
  //////////////////////////////////////////////////////////////////
  pob -> setVariable ( "DrawStart" , s             )               ;
  pob -> setVariable ( "DrawEnd"   , f             )               ;
  pob -> setVariable ( "Start"     , st            )               ;
  pob -> setVariable ( "End"       , et            )               ;
  //////////////////////////////////////////////////////////////////
  pob -> Finish      (                             )               ;
  pob -> Dual        (                             )               ;
}

void N::CalendarObject::ChangePeriod(SUID u)
{
  PeriodBlock * pob = ChildOf<PeriodBlock> ( u )                    ;
  if ( IsNull ( pob ) ) return                                      ;
  ///////////////////////////////////////////////////////////////////
  QDateTime     st  = Value        ( "Start"     ) . toDateTime ( ) ;
  QDateTime     et  = Value        ( "End"       ) . toDateTime ( ) ;
  QDateTime     dst = pob -> Value ( "DrawStart" ) . toDateTime ( ) ;
  QDateTime     det = pob -> Value ( "DrawEnd"   ) . toDateTime ( ) ;
  qint64        dt  = st . msecsTo ( et  )                          ;
  qint64        ft  = st . msecsTo ( dst )                          ;
  qint64        zt  = st . msecsTo ( det )                          ;
  double        x1                                                  ;
  double        x2                                                  ;
  ///////////////////////////////////////////////////////////////////
  if ( dst > det )                                                  {
    dst  = pob -> Value ( "DrawEnd"         ) . toDateTime ( )      ;
    det  = pob -> Value ( "DrawStart"       ) . toDateTime ( )      ;
    ft   = st . msecsTo ( dst               )                       ;
    zt   = st . msecsTo ( det               )                       ;
    pob -> setVariable  ( "DrawStart" , dst )                       ;
    pob -> setVariable  ( "DrawEnd"   , det )                       ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  x1                  = ft                                          ;
  x1                 /= dt                                          ;
  x1                 *= length  . x                                 ;
  x1                 += minimum . x                                 ;
  ///////////////////////////////////////////////////////////////////
  x2                  = zt                                          ;
  x2                 /= dt                                          ;
  x2                 *= length  . x                                 ;
  x2                 += minimum . x                                 ;
  ///////////////////////////////////////////////////////////////////
  pob -> minimum . x  = x1                                          ;
  pob -> maximum . x  = x2                                          ;
}

void N::CalendarObject::ClosePeriod(SUID u)
{
  PeriodBlock * pob = ChildOf<PeriodBlock> ( u ) ;
  if ( IsNull ( pob ) ) return                   ;
  SceneObject::children.remove             ( u ) ;
  delete pob                                     ;
}

bool N::CalendarObject::isLoading(void)
{
  return Value ( "Loading" ) . toBool ( ) ;
}

void N::CalendarObject::RemoveWeekdays(void)
{
  UUIDs R = list ( "PeriodBlock" )                    ;
  SUID  u                                             ;
  /////////////////////////////////////////////////////
  if ( R . count ( ) <= 0 ) return                    ;
  /////////////////////////////////////////////////////
  foreach ( u , R )                                   {
    PeriodBlock * pob = ChildOf<PeriodBlock>(u)       ;
    if ( NULL != pob )                                {
      if ( pob -> Value ( "Generate" ) . toBool ( ) ) {
        SceneObject::children.remove ( u )            ;
        delete pob                                    ;
      }                                               ;
    }                                                 ;
  }                                                   ;
}

void N::CalendarObject::AddWeekdays(void)
{
  if ( ! Value ( "Weekdays" ) . toBool ( ) ) return         ;
  QDateTime     st = Value ( "Start" ) . toDateTime ( )     ;
  QDateTime     et = Value ( "End"   ) . toDateTime ( )     ;
  QDate         sd = st . date ( )                          ;
  QDate         ed = et . date ( )                          ;
  QDateTime     ws                                          ;
  QDateTime     we                                          ;
  QDateTime     fs                                          ;
  QDateTime     fe                                          ;
  PeriodBlock * pob                                         ;
  int           dow                                         ;
  double        baseline                                    ;
  QString       name                                        ;
  ///////////////////////////////////////////////////////////
  baseline = Value ( "Baseline" ) . toDouble ( )            ;
  baseline = maximum . y - baseline                         ;
  while ( sd <= ed )                                        {
    dow = sd . dayOfWeek ( )                                ;
    switch ( dow )                                          {
      case 6                                                :
      case 7                                                :
        ws = QDateTime   ( sd , QTime(  0 ,  0 ,  0 , 0 ) ) ;
        we = QDateTime   ( sd , QTime( 23 , 59 , 59 , 0 ) ) ;
        we = we.addMSecs ( 999                            ) ;
        fs = ws                                             ;
        fe = we                                             ;
        if ( st > fs ) fs = st                              ;
        if ( et < fe ) fe = et                              ;
        name = QDate::longDayName ( dow )                   ;
        pob  = NewPeriodBlock ( fs           , fe         ) ;
        pob -> setVariable    ( "Start"      , ws         ) ;
        pob -> setVariable    ( "End"        , we         ) ;
        pob -> setVariable    ( "Index"      , dow        ) ;
        pob -> setVariable    ( "Generate"   , true       ) ;
        pob -> setVariable    ( "BackColor"  , dow - 5    ) ;
        pob -> setVariable    ( "FrontColor" , dow - 5    ) ;
        pob -> setVariable    ( "Baseline"   , baseline   ) ;
        pob -> setText        ( name                      ) ;
      break                                                 ;
      default                                               :
      break                                                 ;
    }                                                       ;
    sd = sd . addDays ( 1 )                                 ;
  }                                                         ;
}

void N::CalendarObject::LocateWeekdays(void)
{
  UUIDs R = list ( "PeriodBlock" )                                  ;
  SUID  u                                                           ;
  ///////////////////////////////////////////////////////////////////
  if ( R . count ( ) <= 0 ) return                                  ;
  ///////////////////////////////////////////////////////////////////
  foreach ( u , R )                                                 {
    PeriodBlock * pob = ChildOf<PeriodBlock>(u)                     ;
    if ( NULL != pob )                                              {
      if ( ! pob -> Value ( "Generate" ) . toBool ( ) )             {
        QDateTime s = pob -> Value ( "DrawStart" ) . toDateTime ( ) ;
        QDateTime f = pob -> Value ( "DrawEnd"   ) . toDateTime ( ) ;
        CalculateBlock ( pob , s , f )                              ;
      }                                                             ;
    }                                                               ;
  }                                                                 ;
}

void N::CalendarObject::UpdateSpot(SUID uu,QDateTime st,QDateTime et)
{
  if ( uu <= 0 ) return                          ;
  setVariable ( "Loading" , true )               ;
  ////////////////////////////////////////////////
  EventManager  EM ( plan        )               ;
  SqlConnection SC ( plan -> sql )               ;
  StarDate      ST                               ;
  StarDate      FT                               ;
  bool          outdated = false                 ;
  int           tt                               ;
  ST = st                                        ;
  FT = et                                        ;
  if ( nTimeNow >= et ) outdated = true          ;
  ////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )            {
    EM . UpdateEvent ( SC                        ,
                       uu                        ,
                       N::Calendars::Duration    ,
                       ST . Stardate             ,
                       FT . Stardate           ) ;
    EM . attachSpot  ( SC                        ,
                       uu                        ,
                       N::History::WorkingPeriod ,
                       ST . Stardate             ,
                       FT . Stardate           ) ;
    if ( outdated )                              {
      EM . DeleteScheduling ( SC , uu      )     ;
      EM . Delete           ( SC , uu      )     ;
    } else                                       {
      tt = EM . Type        ( SC , uu      )     ;
      EM . AssureEvent      ( SC , uu , tt )     ;
      EM . DeleteScheduling ( SC , uu      )     ;
      EM . AddScheduling    ( SC , uu      )     ;
    }                                            ;
    SC . close ( )                               ;
  }                                              ;
  SC . remove ( )                                ;
  ////////////////////////////////////////////////
  setVariable  ( "Loading" , false )             ;
  Load         (                   )             ;
}

void N::CalendarObject::Load(void)
{
  if ( ! Value ( "Gantt" ) . toBool ( ) )                                    {
    if ( isLoading ( ) ) return                                              ;
    setVariable    ( "Loading" , true  )                                     ;
    Clear          (                   )                                     ;
    RemoveWeekdays (                   )                                     ;
    AddWeekdays    (                   )                                     ;
    LocateWeekdays (                   )                                     ;
    setVariable    ( "Loading" , false )                                     ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if                ( isLoading ( )    ) return                              ;
  setVariable       ( "Loading" , true )                                     ;
  emit assignCursor ( Qt::WaitCursor   )                                     ;
  ////////////////////////////////////////////////////////////////////////////
  QList<EventObject *> EOLs                                                  ;
  EventManager         EM ( plan      )                                      ;
  QDateTime            st = Value ( "Start" ) . toDateTime ( )               ;
  QDateTime            et = Value ( "End"   ) . toDateTime ( )               ;
  ////////////////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan->sql )                                             ;
  if ( SC . open ( FunctionString ) )                                        {
    QString   Q                                                              ;
    UUIDs     U                                                              ;
    SUID      u                                                              ;
    U = EM . Events ( SC , st , et )                                         ;
    foreach ( u , U )                                                        {
      Q = SC . sql . SelectFrom                                              (
        "owner,type,status,adjust,start,final"                               ,
        PlanTable(EventHistory)                                              ,
        SC . WhereUuid ( u )                                               ) ;
      if ( SC . Fetch ( Q ) )                                                {
        QDateTime S = EM . toDateTime ( SC . Tuid ( 4 ) )                    ;
        QDateTime F = EM . toDateTime ( SC . Tuid ( 5 ) )                    ;
        if ( contains ( S , F ) )                                            {
          EventObject * eol  = NewEventObject ( )                            ;
          QString       note = ""                                            ;
          QString       name = ""                                            ;
          eol -> setVariable  ( "UUID"         , u                     )     ;
          eol -> setVariable  ( "TaskUUID"     , 0                     )     ;
          eol -> setVariable  ( "Owner"        , SC . Uuid ( 0 )       )     ;
          eol -> setVariable  ( "EventType"    , SC . Int  ( 1 )       )     ;
          eol -> setVariable  ( "Status"       , SC . Int  ( 2 )       )     ;
          eol -> setVariable  ( "Adjust"       , SC . Int  ( 3 )       )     ;
          eol -> setVariable  ( "Start"        , S                     )     ;
          eol -> setVariable  ( "End"          , F                     )     ;
          eol -> setVariable  ( "ControlPanel" , Value("ControlPanel") )     ;
          ////////////////////////////////////////////////////////////////////
          name = EM . Name    ( SC          , u               )              ;
          note = SC . getName ( PlanTable(EventNotes)                        ,
                                "uuid"                                       ,
                                plan -> LanguageId                           ,
                                u                             )              ;
          ////////////////////////////////////////////////////////////////////
          eol -> setVariable  ( "Name"      , name            )              ;
          eol -> setVariable  ( "Note"      , note            )              ;
          if ( Variables . contains ( "Length" ) )                           {
            eol -> setVariable ( "Length" , Variables [ "Length" ] )         ;
          }                                                                  ;
          ////////////////////////////////////////////////////////////////////
          if ( Filter ( SC , eol ) )                                         {
            EOLs << eol                                                      ;
          } else                                                             {
            delete eol                                                       ;
          }                                                                  ;
        }                                                                    ;
      }                                                                      ;
    }                                                                        ;
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  Clear             (                       )                                ;
  RemoveWeekdays    (                       )                                ;
  AddWeekdays       (                       )                                ;
  LocateWeekdays    (                       )                                ;
  emit assignCursor ( Qt::ArrowCursor       )                                ;
  if                ( EOLs . count ( ) <= 0 )                                {
    setVariable     ( "Loading" , false     )                                ;
    Alert           ( Done                  )                                ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  ArrangeItems ( EOLs )                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0 ; i < EOLs . count ( ) ; i++ )                              {
    EventObject * eol = EOLs [ i ]                                           ;
    eol -> Finish      (                               )                     ;
    eol -> Dual        (                               )                     ;
    eol -> addSequence ( 10 , SceneObject::RenderFaces )                     ;
    eol -> addSequence ( 15 , SceneObject::AssignColor )                     ;
    eol -> addSequence ( 16 , SceneObject::RenderBox   )                     ;
    appendChild        ( 10001 , eol                   )                     ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  setVariable ( "Loading" , false )                                          ;
  Alert       ( Done              )                                          ;
}

void N::CalendarObject::ArrangeItems(QList<EventObject *> & EOLs)
{
  QRectF        Area   = BarArea (                )                          ;
  int           metric = Value   ( "BarMetric"    ) . toInt      ( )         ;
  int           tg     = Value   ( "TextGap"      ) . toInt      ( )         ;
  bool          top    = Value   ( "TopMetric"    ) . toInt      ( )         ;
  bool          bottom = Value   ( "BottomMetric" ) . toInt      ( )         ;
  int           gap    = - ( metric + 8 )                                    ;
  QList<QRectF> rects                                                        ;
  QList<QRectF> areas                                                        ;
  QRectF        eor                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( ! top ) && bottom ) gap = ( metric + tg )                           ;
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0 ; i < EOLs . count ( ) ; i++ )                              {
    EventObject * eol = EOLs [ i ]                                           ;
    eol -> minimum . z = minimum . z + 2.0                                   ;
    eol -> maximum . z = maximum . z - 2.0                                   ;
    if ( EventRectangle ( eol , eor , Area , gap , metric ) )                {
      bool    intersected                                                    ;
      QString n = eol -> Value ( "Name"      ) . toString ( )                ;
      int     e = eol -> Value ( "EventType" ) . toInt    ( )                ;
      do                                                                     {
        intersected = false                                                  ;
        areas . clear      (                        )                        ;
        eol  -> setRect    ( eor                    )                        ;
        eol  -> setText    ( n , eor , Area , false )                        ;
        eol  -> setIcon    ( e , eor , Area , false )                        ;
        eol  -> Rectangles ( areas                  )                        ;
        //////////////////////////////////////////////////////////////////////
        for (int j=0 ; ( !intersected ) && ( j < areas . count ( ) ) ; j++ ) {
          intersected = Intersects ( areas [ j ] , rects )                   ;
        }                                                                    ;
        //////////////////////////////////////////////////////////////////////
        if ( intersected )                                                   {
          QRectF EOR = eor                                                   ;
          eor . setTop    ( EOR . top    ( ) + gap )                         ;
          eor . setBottom ( EOR . bottom ( ) + gap )                         ;
        } else                                                               {
          rects << areas                                                     ;
          eol  -> setText ( n , eor , Area , true  )                         ;
          eol  -> setIcon ( e , eor , Area , true  )                         ;
        }                                                                    ;
      } while ( intersected )                                                ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
}

int N::CalendarObject::AtRegion(ControlPoint & At)
{
  if ( At . x < minimum . x ) return 0         ;
  if ( At . x > maximum . x ) return 0         ;
  if ( At . y < minimum . y ) return 0         ;
  if ( At . y > maximum . y ) return 0         ;
  //////////////////////////////////////////////
  int metric = Value ( "Metric" ) . toInt ( )  ;
  double h                                     ;
  if ( Value ( "TopMetric"    ) . toBool ( ) ) {
    h = maximum . y - metric                   ;
    if ( At . y >= h ) return 1                ;
  }                                            ;
  //////////////////////////////////////////////
  if ( Value ( "BottomMetric" ) . toBool ( ) ) {
    h = minimum . y + metric                   ;
    if ( At . y <= h ) return 2                ;
  }                                            ;
  //////////////////////////////////////////////
  return 3                                     ;
}

void N::CalendarObject::WeatherFeeder(void)
{
}

void N::CalendarObject::HandleDependency(SUID uuid,UUIDs & After,UUIDs & Current)
{
  UUIDs         U                                                            ;
  SUID          u                                                            ;
  SUID          t                                                            ;
  SUID          f                                                            ;
  SMAPs         dt                                                           ;
  EventManager  EM ( plan        )                                           ;
  SqlConnection SC ( plan -> sql )                                           ;
  ////////////////////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                                        {
    QString Q                                                                ;
    //////////////////////////////////////////////////////////////////////////
    Q = SC . sql . SelectFrom                                                (
          "second,third,flags"                                               ,
          PlanTable(Triples)                                                 ,
          QString("where `first` = %1 and `type` = %2"                       )
          . arg ( uuid                                                       )
          . arg ( Types::Schedule                                          ) ,
          SC . OrderByAsc ( "id" )                                         ) ;
    SqlLoopNow ( SC , Q )                                                    ;
      u = SC . Uuid ( 0 )                                                    ;
      t = SC . Uuid ( 1 )                                                    ;
      f = SC . Uuid ( 2 )                                                    ;
      switch ( ToGroupID ( t ) )                                             {
        case Groups::After                                                   :
        break                                                                ;
        case Groups::Before                                                  :
          U << u                                                             ;
          dt [ u ] = f                                                       ;
        break                                                                ;
        case Groups::Subordination                                           :
        break                                                                ;
        case Groups::Contains                                                :
        break                                                                ;
      }                                                                      ;
    SqlLoopErr ( SC , Q )                                                    ;
    SqlLoopEnd ( SC , Q )                                                    ;
    //////////////////////////////////////////////////////////////////////////
    if ( U . count ( ) > 0 )                                                 {
      Q = SC . sql . SelectFrom                                              (
            "start,final,type"                                               ,
            PlanTable(EventHistory)                                          ,
             SC . WhereUuid ( uuid )                                       ) ;
      if ( SC . Fetch ( Q ) )                                                {
        SUID      FT = SC . Tuid       ( 1  )                                ;
        QDateTime LT = EM . toDateTime ( FT )                                ;
        foreach ( u , U ) if ( ! Current . contains ( u ) )                  {
          SUID st                                                            ;
          SUID ft                                                            ;
          f = dt [ u ]                                                       ;
          Q = SC . sql . SelectFrom                                          (
                "start,final"                                                ,
                PlanTable(EventHistory)                                      ,
                 SC . WhereUuid ( u )                                      ) ;
          if ( SC . Fetch ( Q ) )                                            {
            //////////////////////////////////////////////////////////////////
            st = SC . Tuid ( 0 )                                             ;
            ft = SC . Tuid ( 1 )                                             ;
            t  = ft - st                                                     ;
            st = FT + f                                                      ;
            ft = st + t                                                      ;
            //////////////////////////////////////////////////////////////////
            EM . UpdateEvent ( SC                                            ,
                               u                                             ,
                               N::Calendars::Duration                        ,
                               st                                            ,
                               ft                                          ) ;
            EM . attachSpot  ( SC                                            ,
                               u                                             ,
                               N::History::WorkingPeriod                     ,
                               st                                            ,
                               ft                                          ) ;
            //////////////////////////////////////////////////////////////////
            LT = EM . toDateTime ( ft )                                      ;
            if ( nTimeNow > LT )                                             {
              EM . DeleteScheduling ( SC , u      )                          ;
              EM . Delete           ( SC , u      )                          ;
            } else                                                           {
              int tt                                                         ;
              tt = EM . Type        ( SC , u      )                          ;
              EM . AssureEvent      ( SC , u , tt )                          ;
              EM . DeleteScheduling ( SC , u      )                          ;
              EM . AddScheduling    ( SC , u      )                          ;
            }                                                                ;
          }                                                                  ;
        }                                                                    ;
        if ( ! After . contains ( u ) ) After << u                           ;
      }                                                                      ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    SC.close()                                                               ;
  }                                                                          ;
  SC.remove()                                                                ;
}

void N::CalendarObject::OrganizeDepends(void)
{
  UUIDs U = list ( "Event" )                       ;
  if ( U . count ( ) <= 0  ) return                ;
  //////////////////////////////////////////////////
  QDateTime ET                                     ;
  UUIDs     After                                  ;
  UUIDs     Current                                ;
  UUIDs     Next                                   ;
  SUID      u                                      ;
  //////////////////////////////////////////////////
  foreach ( u , U )                                {
    EventObject * eol = ChildOf<EventObject>(u)    ;
    u  = eol -> Value ( "UUID" ) . toULongLong ( ) ;
    ET = eol -> Value ( "End"  ) . toDateTime  ( ) ;
    if ( nTimeNow < ET ) Next << u                 ;
  }                                                ;
  if ( Next . count ( ) <= 0 ) return              ;
  //////////////////////////////////////////////////
  while ( Next . count ( ) > 0 )                   {
    u = Next . first ( )                           ;
    Next . takeFirst    ( )                        ;
    if ( ! Current . contains ( u ) )              {
      Current << u                                 ;
    }                                              ;
    HandleDependency ( u , After , Current )       ;
    foreach ( u , After )                          {
      if ( ! Next . contains ( u ) )               {
        Next << u                                  ;
      }                                            ;
    }                                              ;
    After . clear ( )                              ;
  }                                                ;
  //////////////////////////////////////////////////
  Load ( )                                         ;
}

bool N::CalendarObject::EventsMenu(MenuManager & mm,QMenu * menu,int region)
{
  mm . add          ( menu , 61101 , tr("List"    )      ) ;
  mm . add          ( menu , 61102 , tr("Triggers")      ) ;
  mm . addSeparator ( menu                               ) ;
  mm . add          ( menu                                 ,
                      61201                                ,
                      tr("Local equipment only")           ,
                      true                                 ,
                      Value ( "LocalOnly" ) . toBool ( ) ) ;
  return true                                              ;
}

bool N::CalendarObject::TasksMenu(MenuManager & mm,QMenu * menu,int region)
{
  mm . add ( menu , 62101 , tr("List") ) ;
  return true                            ;
}

bool N::CalendarObject::EditMenu (MenuManager & mm,QMenu * menu,int region)
{
  QMenu        * mx                                     ;
  QMenu        * ma                                     ;
  QActionGroup * ag                                     ;
  QAction      * aa                                     ;
  QDateTime      et = Value ( "End" ) . toDateTime ( )  ;
  ///////////////////////////////////////////////////////
  mx = mm . addMenu     ( menu , tr("Mouse actions") )  ;
  ma = mm . addMenu     ( menu , tr("Time accuracy") )  ;
  ///////////////////////////////////////////////////////
  mm      . add  ( menu                                 ,
                   75101                                ,
                   tr("Show gantt bars")                ,
                   true                                 ,
                   Value ( "Gantt"  ) . toBool ( )    ) ;
  ///////////////////////////////////////////////////////
  if ( nTimeNow < et )                                  {
    mm    . addSeparator ( menu )                       ;
    mm    . add  ( menu                                 ,
                   75102                                ,
                   tr("Organize dependency")          ) ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  if ( Value ( "CanClose" ) . toBool ( ) )              {
    mm    . addSeparator ( menu )                       ;
    mm    . add  ( menu                                 ,
                   75201                                ,
                   tr("Close scheduler")              ) ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  ag = new QActionGroup ( menu                        ) ;
  ///////////////////////////////////////////////////////
  aa  = mm . add ( mx                                   ,
                   73101                                ,
                   tr("Brief add event")                ,
                   true                                 ,
                   Value ( "BriefAdd"  ) . toBool ( ) ) ;
  ag -> addAction ( aa )                                ;
  aa  = mm . add ( mx                                   ,
                   73102                                ,
                   tr("Add event")                      ,
                   true                                 ,
                   Value ( "AddEvent"  ) . toBool ( ) ) ;
  ag -> addAction ( aa )                                ;
  aa  = mm . add ( mx                                   ,
                   73103                                ,
                   tr("Add time block")                 ,
                   true                                 ,
                   Value ( "AddPeriod" ) . toBool ( ) ) ;
  ag -> addAction ( aa )                                ;
  aa  = mm . add ( mx                                   ,
                   73106                                ,
                   tr("Run actions")                    ,
                   true                                 ,
                   Value ( "Actions"   ) . toBool ( ) ) ;
  ag -> addAction ( aa )                                ;
  mm . addSeparator ( mx )                              ;
  aa  = mm . add ( mx                                   ,
                   73104                                ,
                   tr("Zoom in")                        ,
                   true                                 ,
                   Value ( "ZoomIn"    ) . toBool ( ) ) ;
  ag -> addAction ( aa )                                ;
  aa  = mm . add ( mx                                   ,
                   73105                                ,
                   tr("Selection")                      ,
                   true                                 ,
                   Value ( "Selection" ) . toBool ( ) ) ;
  ag -> addAction ( aa )                                ;
  ///////////////////////////////////////////////////////
  mm       . add ( ma                                   ,
                   74101                                ,
                   tr("Time tracking")                  ,
                   true                                 ,
                   Value ( "Tracking"  ) . toBool ( ) ) ;
  mm       . add ( ma                                   ,
                   74102                                ,
                   tr("Minute only")                    ,
                   true                                 ,
                   Value ( "MinuteOnly") . toBool ( ) ) ;
  ///////////////////////////////////////////////////////
  mm . setGroup ( 0 , ag )                              ;
  ///////////////////////////////////////////////////////
  return true                                           ;
}

void N::CalendarObject::ConfMenu(MenuManager & mm,QMenu * menu,int region)
{
  mm . add ( menu                                    ,
             71201                                   ,
             tr("Enable menu")                       ,
             true                                    ,
             Value ( "Menu"         ) . toBool ( ) ) ;
  mm . add ( menu                                    ,
             71202                                   ,
             tr("Control panel")                     ,
             true                                    ,
             Value ( "ControlPanel" ) . toBool ( ) ) ;
  mm . add ( menu                                    ,
             71203                                   ,
             tr("Follow window size")                ,
             true                                    ,
             Value ( "FollowWindow" ) . toBool ( ) ) ;
}

void N::CalendarObject::AdjustMenu(MenuManager & mm,QMenu * menu,int region)
{
  QMenu         * mf                                 ;
  QMenu         * ml                                 ;
  QMenu         * mt                                 ;
  QMenu         * mz                                 ;
  DoubleSpinBox * MinZ                               ;
  DoubleSpinBox * MaxZ                               ;
  double          maxv = 10000000000000.0f           ;
  ////////////////////////////////////////////////////
  MinZ = new DoubleSpinBox ( NULL , plan )           ;
  MaxZ = new DoubleSpinBox ( NULL , plan )           ;
  ////////////////////////////////////////////////////
  mf = mm . addMenu ( menu , tr("Display faces"  ) ) ;
  ml = mm . addMenu ( menu , tr("Time separators") ) ;
  mt = mm . addMenu ( menu , tr("Metric ticks"   ) ) ;
  mz = mm . addMenu ( menu , tr("Depth"          ) ) ;
  ////////////////////////////////////////////////////
  mm . add ( mf                                      ,
             71101                                   ,
             tr("Frontal face")                      ,
             true                                    ,
             Value ( "Front"        ) . toBool ( ) ) ;
  mm . add ( mf                                      ,
             71102                                   ,
             tr("Back face")                         ,
             true                                    ,
             Value ( "Back"         ) . toBool ( ) ) ;
  mm . add ( mf                                      ,
             71103                                   ,
             tr("Side faces")                        ,
             true                                    ,
             Value ( "Side"         ) . toBool ( ) ) ;
  ////////////////////////////////////////////////////
  mm . add ( ml                                      ,
             71111                                   ,
             tr("Day line")                          ,
             true                                    ,
             Value ( "Dayline"      ) . toBool ( ) ) ;
  mm . add ( ml                                      ,
             71112                                   ,
             tr("Time line")                         ,
             true                                    ,
             Value ( "Happened"     ) . toBool ( ) ) ;
  mm . add ( ml                                      ,
             71113                                   ,
             tr("Week days")                         ,
             true                                    ,
             Value ( "Weekdays"     ) . toBool ( ) ) ;
  mm . add ( ml                                      ,
             71114                                   ,
             tr("Day light")                         ,
             true                                    ,
             Value ( "Daylight"     ) . toBool ( ) ) ;
  mm . add ( ml                                      ,
             71115                                   ,
             tr("Weather")                           ,
             true                                    ,
             Value ( "Weather"      ) . toBool ( ) ) ;
  mm . addSeparator ( ml )                           ;
  mm . add ( ml                                      ,
             71116                                   ,
             tr("Current time")                      ,
             true                                    ,
             Value ( "CurrentTime"  ) . toBool ( ) ) ;
  mm . add ( ml                                      ,
             71117                                   ,
             tr("Time labels")                       ,
             true                                    ,
             Value ( "TimeLabels"   ) . toBool ( ) ) ;
  ////////////////////////////////////////////////////
  mm . add ( mt                                      ,
             71121                                   ,
             tr("Ticks")                             ,
             true                                    ,
             Value ( "Tick"         ) . toBool ( ) ) ;
  mm . add ( mt                                      ,
             71122                                   ,
             tr("Top metric lines")                  ,
             true                                    ,
             Value ( "TopMetric"    ) . toBool ( ) ) ;
  mm . add ( mt                                      ,
             71123                                   ,
             tr("Bottom metric lines")               ,
             true                                    ,
             Value ( "BottomMetric" ) . toBool ( ) ) ;
  mm . addSeparator ( mt )                           ;
  mm . add ( mt                                      ,
             71124                                   ,
             tr("Auto adjustment ticks")             ,
             true                                    ,
             Value ( "AutoTicks" ) . toBool ( ) )    ;
  ////////////////////////////////////////////////////
  MinZ -> setRange  ( -maxv , maxv )                 ;
  MaxZ -> setRange  ( -maxv , maxv )                 ;
  MinZ -> setValue  ( minimum . z  )                 ;
  MaxZ -> setValue  ( maximum . z  )                 ;
  MinZ -> External = &minimum . z                    ;
  MaxZ -> External = &maximum . z                    ;
  mm    . add       ( mz                             ,
                      71125                          ,
                      tr("Degrees of Freedom")     ) ;
  mm    . add       ( mz , 4413001 , MinZ )          ;
  mm    . add       ( mz , 4413002 , MaxZ )          ;
}

void N::CalendarObject::ToolsMenu(MenuManager & mm,QMenu * menu)
{
  mm . add ( menu , 81101 , tr("Crowds") ) ;
  mm . add ( menu , 81102 , tr("People") ) ;
}

bool N::CalendarObject::EditProcessor(MenuManager & mm,QAction * aa)
{
  switch ( mm [ aa ] )                                   {
    case 73101                                           :
      setVariable ( "BriefAdd"   , true                ) ;
      setVariable ( "AddEvent"   , false               ) ;
      setVariable ( "AddPeriod"  , false               ) ;
      setVariable ( "ZoomIn"     , false               ) ;
      setVariable ( "Selection"  , false               ) ;
      setVariable ( "Actions"    , false               ) ;
    break                                                ;
    case 73102                                           :
      setVariable ( "BriefAdd"   , false               ) ;
      setVariable ( "AddEvent"   , true                ) ;
      setVariable ( "AddPeriod"  , false               ) ;
      setVariable ( "ZoomIn"     , false               ) ;
      setVariable ( "Selection"  , false               ) ;
      setVariable ( "Actions"    , false               ) ;
    break                                                ;
    case 73103                                           :
      setVariable ( "BriefAdd"   , false               ) ;
      setVariable ( "AddEvent"   , false               ) ;
      setVariable ( "AddPeriod"  , true                ) ;
      setVariable ( "ZoomIn"     , false               ) ;
      setVariable ( "Selection"  , false               ) ;
      setVariable ( "Actions"    , false               ) ;
    break                                                ;
    case 73104                                           :
      setVariable ( "BriefAdd"   , false               ) ;
      setVariable ( "AddEvent"   , false               ) ;
      setVariable ( "AddPeriod"  , false               ) ;
      setVariable ( "ZoomIn"     , true                ) ;
      setVariable ( "Selection"  , false               ) ;
      setVariable ( "Actions"    , false               ) ;
    break                                                ;
    case 73105                                           :
      setVariable ( "BriefAdd"   , false               ) ;
      setVariable ( "AddEvent"   , false               ) ;
      setVariable ( "AddPeriod"  , false               ) ;
      setVariable ( "ZoomIn"     , false               ) ;
      setVariable ( "Selection"  , true                ) ;
      setVariable ( "Actions"    , false               ) ;
    break                                                ;
    case 73106                                           :
      setVariable ( "BriefAdd"   , false               ) ;
      setVariable ( "AddEvent"   , false               ) ;
      setVariable ( "AddPeriod"  , false               ) ;
      setVariable ( "ZoomIn"     , false               ) ;
      setVariable ( "Selection"  , false               ) ;
      setVariable ( "Actions"    , true                ) ;
    break                                                ;
    case 74101                                           :
      setVariable ( "Tracking"   , aa -> isChecked ( ) ) ;
    break                                                ;
    case 74102                                           :
      setVariable ( "MinuteOnly" , aa -> isChecked ( ) ) ;
    break                                                ;
    case 75101                                           :
      setVariable ( "Gantt"      , aa -> isChecked ( ) ) ;
      start       ( 10001                              ) ;
    break                                                ;
    case 75102                                           :
      start       ( 10004                              ) ;
    break                                                ;
    case 75201                                           :
      emit CloseObject ( node )                          ;
    break                                                ;
  }                                                      ;
  return false                                           ;
}

bool N::CalendarObject::ConfProcessor(MenuManager & mm,QAction * aa)
{
  QVariants vx                                             ;
  switch ( mm [ aa ] )                                     {
    case 71201                                             :
      setVariable ( "Menu"         , aa -> isChecked ( ) ) ;
      vx << aa -> isChecked ( )                            ;
      CallDynamic ( "IsCalendarMenu" , this , gui , vx   ) ;
    return true                                            ;
    case 71202                                             :
      setVariable ( "ControlPanel" , aa -> isChecked ( ) ) ;
      if ( IsNull ( plan -> pad ) )                        {
        if ( aa -> isChecked ( ) )                         {
          plan -> pad -> Show ( true )                     ;
        }                                                  ;
      }                                                    ;
    return true                                            ;
    case 71203                                             :
      setVariable ( "FollowWindow" , aa -> isChecked ( ) ) ;
    return true                                            ;
  }                                                        ;
  return false                                             ;
}

bool N::CalendarObject::AdjustProcessor(MenuManager & mm,QAction * aa)
{
  switch ( mm [ aa ] )                                     {
    case 71101                                             :
      setVariable ( "Front"        , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71102                                             :
      setVariable ( "Back"         , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71103                                             :
      setVariable ( "Side"         , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71111                                             :
      setVariable ( "Dayline"      , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71112                                             :
      setVariable ( "Happened"     , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71113                                             :
      setVariable ( "Weekdays"     , aa -> isChecked ( ) ) ;
      RemoveWeekdays ( )                                   ;
      AddWeekdays    ( )                                   ;
    return true                                            ;
    case 71114                                             :
      setVariable ( "Daylight"     , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71115                                             :
      setVariable ( "Weather"      , aa -> isChecked ( ) ) ;
      if ( aa -> isChecked ( ) ) start ( 10003 )           ;
    return true                                            ;
    case 71116                                             :
      setVariable ( "CurrentTime"  , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71117                                             :
      setVariable ( "TimeLabels"   , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71121                                             :
      setVariable ( "Tick"         , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71122                                             :
      setVariable ( "TopMetric"    , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71123                                             :
      setVariable ( "BottomMetric" , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71124                                             :
      setVariable ( "AutoTicks"    , aa -> isChecked ( ) ) ;
    return true                                            ;
    case 71125                                             :
      emit EditDOF ( this )                                ;
    return true                                            ;
  }                                                        ;
  return false                                             ;
}

bool N::CalendarObject::ToolsProcessor(MenuManager & mm,QAction * aa)
{
  switch ( mm [ aa ] )    {
    case 81101            :
      emit ShowCrowds ( ) ;
    return true           ;
    case 81102            :
      emit ShowPeople ( ) ;
    return true           ;
  }                       ;
  return false            ;
}

bool N::CalendarObject::EventsProcessor(MenuManager & mm,QAction * aa)
{
  switch ( mm [ aa ] )                                        {
    case 61101                                                :
      emit EventsList   (                                   ) ;
    return true                                               ;
    case 61102                                                :
      emit TriggersList (                                   ) ;
    return true                                               ;
    case 61201                                                :
      setVariable       ( "LocalOnly" , aa -> isChecked ( ) ) ;
      start             ( 10001                             ) ;
    return true                                               ;
  }                                                           ;
  return false                                                ;
}

bool N::CalendarObject::TasksProcessor(MenuManager & mm,QAction * aa)
{
  switch ( mm [ aa ] )   {
    case 61101           :
      emit TasksList ( ) ;
    return true          ;
  }                      ;
  return false           ;
}

void N::CalendarObject::MoveTime(QDateTime s,QDateTime f)
{
  StarDate STX                                            ;
  StarDate ETX                                            ;
  STX = s                                                 ;
  ETX = f                                                 ;
  start ( 10001 )                                         ;
  emit SectionChanged ( STX . Stardate , ETX . Stardate ) ;
  emit EmitSection    (                                 ) ;
  /////////////////////////////////////////////////////////
  QVariants v                                             ;
  v << UniverseUuid ( )                                   ;
  v << node                                               ;
  v << s                                                  ;
  v << f                                                  ;
  CallDynamic ( "RangeMoving" , this , gui , v )          ;
}

void N::CalendarObject::AddSection(QDateTime st,QDateTime et)
{
  qint64  dt = st . msecsTo ( et )                    ;
  VarArgs args                                        ;
  /////////////////////////////////////////////////////
  if ( Value ( "BriefAdd"  ) . toBool ( ) )           {
    if ( dt < ( 1 * 60 * 1000 ) ) return              ;
    args << st                                        ;
    args << et                                        ;
    start ( 10005 , args )                            ;
  }                                                   ;
  /////////////////////////////////////////////////////
  if ( Value ( "AddEvent"  ) . toBool ( ) )           {
    if ( dt < ( 1 * 60 * 1000 ) ) return              ;
    bool panel                                        ;
    panel = Value ( "ControlPanel" ) . toBool ( )     ;
    emit EditEvent ( this , 0 , st , et , panel )     ;
  }                                                   ;
  /////////////////////////////////////////////////////
  if ( Value ( "AddPeriod" ) . toBool ( ) )           {
    if ( dt < ( 5 * 60 * 1000 ) ) return              ;
    PeriodBlock * pob                                 ;
    double        baseline                            ;
    QString       name = tr("New period")             ;
    ///////////////////////////////////////////////////
    baseline = Value ( "Baseline" ) . toDouble ( )    ;
    baseline = maximum . y - baseline                 ;
    pob  = NewPeriodBlock ( st           , et       ) ;
    pob -> setVariable    ( "Start"      , st       ) ;
    pob -> setVariable    ( "End"        , et       ) ;
    pob -> setVariable    ( "Index"      , 5        ) ;
    pob -> setVariable    ( "Generate"   , false    ) ;
    pob -> setVariable    ( "BackColor"  , 3        ) ;
    pob -> setVariable    ( "FrontColor" , 3        ) ;
    pob -> setVariable    ( "Baseline"   , baseline ) ;
    pob -> setText        ( name                    ) ;
  }                                                   ;
  /////////////////////////////////////////////////////
  if ( Value ( "ZoomIn"    ) . toBool ( ) )           {
    if ( dt < ( 15 * 60 * 1000 ) ) return             ;
    qint64 gap = Value ( "Gap" ) . toLongLong ( )     ;
    setRange   ( st , et , gap )                      ;
    MoveTime   ( st , et       )                      ;
  }                                                   ;
  /////////////////////////////////////////////////////
  if ( Value ( "Selection" ) . toBool ( ) )           {
    Selecting  ( st , et       )                      ;
  }                                                   ;
  /////////////////////////////////////////////////////
  if ( Value ( "Actions"   ) . toBool ( ) )           {
    RunActions ( st , et       )                      ;
  }                                                   ;
}

void N::CalendarObject::BriefAdd(QDateTime st,QDateTime ft)
{
  SUID u                                                                    ;
  u = EventManager::Append ( plan , N::Period , tr("New event") , st , ft ) ;
  if ( u <= 0 ) return                                                      ;
  SqlConnection SC         ( plan -> sql                                  ) ;
  if ( SC . open ( FunctionString ) )                                       {
    QString Q                                                               ;
    /////////////////////////////////////////////////////////////////////////
    Q = SC . sql . InsertInto                                               (
          PlanTable(Groups)                                                 ,
          5                                                                 ,
          "first"                                                           ,
          "second"                                                          ,
          "t1"                                                              ,
          "t2"                                                              ,
          "relation"                                                      ) ;
    SC . Prepare ( Q                                                      ) ;
    SC . Bind    ( "first"    , plan -> Machine                           ) ;
    SC . Bind    ( "second"   , u                                         ) ;
    SC . Bind    ( "t1"       , Types::Equipment                          ) ;
    SC . Bind    ( "t2"       , Types::Schedule                           ) ;
    SC . Bind    ( "relation" , Groups::Subordination                     ) ;
    SC . Exec    (                                                        ) ;
    /////////////////////////////////////////////////////////////////////////
    Q = SC . sql . InsertInto                                               (
          PlanTable(Groups)                                                 ,
          5                                                                 ,
          "first"                                                           ,
          "second"                                                          ,
          "t1"                                                              ,
          "t2"                                                              ,
          "relation"                                                      ) ;
    SC . Prepare ( Q                                                      ) ;
    SC . Bind    ( "first"    , plan -> UserUuid                          ) ;
    SC . Bind    ( "second"   , u                                         ) ;
    SC . Bind    ( "t1"       , Types::People                             ) ;
    SC . Bind    ( "t2"       , Types::Schedule                           ) ;
    SC . Bind    ( "relation" , Groups::Subordination                     ) ;
    SC . Exec    (                                                        ) ;
    /////////////////////////////////////////////////////////////////////////
    SC . close             (                                              ) ;
  }                                                                         ;
  SC   . remove            (                                              ) ;
  Load                     (                                              ) ;
}

void N::CalendarObject::Selecting(QDateTime start,QDateTime final)
{
}

void N::CalendarObject::RunActions(QDateTime start,QDateTime final)
{
  QVariants v                                      ;
  v << start                                       ;
  v << final                                       ;
  CallDynamic ( "PeriodActions" , this , gui , v ) ;
}

bool N::CalendarObject::LastMoment(QDateTime now)
{
  if ( ! Variables . contains ( "LastMoment" ) )         {
    setVariable ( "LastMoment" , now )                   ;
    return true                                          ;
  }                                                      ;
  QDateTime LM = Value ( "LastMoment" ) . toDateTime ( ) ;
  qint64    dt = LM . msecsTo ( now )                    ;
  qint64    mt = 300                                     ;
  setVariable ( "LastMoment" , now )                     ;
  if ( Variables . contains ( "MomentTime" ) )           {
    mt = Value ( "MomentTime" ) . toLongLong ( )         ;
  }                                                      ;
  return ( dt > mt )                                     ;
}

void N::CalendarObject::MoveToNew(void)
{
  QDateTime st  = Value ( "OldStart" ) . toDateTime (    )      ;
  QDateTime et  = Value ( "OldEnd"   ) . toDateTime (    )      ;
  QDateTime bt  = Value ( "BaseTime" ) . toDateTime (    )      ;
  QDateTime tt  = Value ( "ToTime"   ) . toDateTime (    )      ;
  qint64    gap = Value ( "Gap"      ) . toLongLong (    )      ;
  qint64    xt  = st                   . msecsTo    ( et )      ;
  qint64    mt  = tt                   . msecsTo    ( bt )      ;
  QString   AS  = bt . toString ("yyyy/MM/dd hh:mm:ss")         ;
  QRect     RX                                                  ;
  ///////////////////////////////////////////////////////////////
  st = st . addMSecs ( mt )                                     ;
  et = st                                                       ;
  et = et . addMSecs ( xt )                                     ;
  ///////////////////////////////////////////////////////////////
  setRange ( st , et , gap )                                    ;
  ///////////////////////////////////////////////////////////////
  if ( ! LastMoment ( nTimeNow ) ) return                       ;
  QToolTip::showText ( QCursor::pos() , AS , NULL , RX , 3000 ) ;
  if ( NULL != gui ) gui -> setToolTip ( AS )                   ;
}

void N::CalendarObject::MoveToNow(void)
{
  QDateTime st  = Value ( "Start" ) . toDateTime (    ) ;
  QDateTime et  = Value ( "End"   ) . toDateTime (    ) ;
  qint64    gap = Value ( "Gap"   ) . toLongLong (    ) ;
  qint64    xt  = st                . msecsTo    ( et ) ;
  st = nTimeNow                                         ;
  st = st . addMSecs ( -xt / 2       )                  ;
  et = st                                               ;
  et = et . addMSecs (  xt           )                  ;
  setRange           ( st , et , gap )                  ;
  start              ( 10001         )                  ;
}

QDateTime N::CalendarObject::AtOldTime(ControlPoint & At)
{
  QDateTime st = Value ( "OldStart" ) . toDateTime ( ) ;
  QDateTime et = Value ( "OldEnd"   ) . toDateTime ( ) ;
  qint64    dt = st . msecsTo ( et )                   ;
  double    pt = At . x - minimum . x                  ;
  QDateTime T                                          ;
  pt /= ( maximum . x - minimum . x )                  ;
  pt *= dt                                             ;
  dt  = pt                                             ;
  T   = st                                             ;
  T   = T . addMSecs ( dt )                            ;
  return T                                             ;
}

QDateTime N::CalendarObject::AtTime(ControlPoint & At)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( ) ;
  QDateTime et = Value ( "End"   ) . toDateTime ( ) ;
  qint64    dt = st . msecsTo ( et )                ;
  double    pt = At . x - minimum . x               ;
  QDateTime T                                       ;
  pt /= ( maximum . x - minimum . x )               ;
  pt *= dt                                          ;
  dt  = pt                                          ;
  T   = st                                          ;
  T   = T . addMSecs ( dt )                         ;
  return T                                          ;
}

QDateTime N::CalendarObject::AtFixTime(ControlPoint & At)
{
  QDateTime T = AtTime ( At )                               ;
  if ( ! Value ( "MinuteOnly" ) . toBool ( ) ) return T     ;
  QDate     D = T . date ( )                                ;
  QTime     Z = T . time ( )                                ;
  QTime     H = QTime ( Z . hour ( ) , Z . minute ( ) , 0 ) ;
  QDateTime S = QDateTime ( D , H )                         ;
  return    S                                               ;
}

bool N::CalendarObject::HitEvent (
       ControlPoint & From       ,
       ControlPoint & To         ,
       ControlPoint & At         )
{
  if ( ! matrices . contains ( 2 ) ) return false                 ;
  UUIDs U = list ( "Event" )                                      ;
  if ( U . count ( ) <= 0          ) return false                 ;
  /////////////////////////////////////////////////////////////////
  SUID         u                                                  ;
  QPointF      p ( At . x , At . y )                              ;
  ControlPoint F                                                  ;
  ControlPoint T                                                  ;
  /////////////////////////////////////////////////////////////////
  F = matrices [ 2 ] * From                                       ;
  T = matrices [ 2 ] * To                                         ;
  foreach ( u , U ) if ( SceneObject::children . contains ( u ) ) {
    EventObject * eol = ChildOf<EventObject> ( u )                ;
    QRectF        R   = eol -> BoxPlane ( 0 )                     ;
    if ( R . contains ( p ) )                                     {
      SUID rx                                                     ;
      int  region = eol -> AtRegion ( At )                        ;
      foreach ( rx , U )                                          {
        EventObject * eox = ChildOf<EventObject> ( rx )           ;
        eox -> setVariable ( "Hold" , false )                     ;
      }                                                           ;
      eol -> setFocus    ( true                 )                 ;
      setVariable        ( "HitEvent"  , true   )                 ;
      setVariable        ( "EventUUID" , u      )                 ;
      eol -> setVariable ( "Hold"      , true   )                 ;
      eol -> setVariable ( "MouseAt"   , region )                 ;
      /////////////////////////////////////////////////////////////
      switch ( region )                                           {
        case 1                                                    :
        case 2                                                    :
          emit assignCursor ( Qt::SplitHCursor     )              ;
        break                                                     ;
        default                                                   :
          emit assignCursor ( Qt::ClosedHandCursor )              ;
        break                                                     ;
      }                                                           ;
      /////////////////////////////////////////////////////////////
      Alert ( Click )                                             ;
      /////////////////////////////////////////////////////////////
      return true                                                 ;
    }                                                             ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  return false                                                    ;
}

bool N::CalendarObject::MovingEvent (
       ControlPoint & From          ,
       ControlPoint & To            ,
       ControlPoint & At            )
{
  if ( ! Value                ( "HitEvent"  ) . toBool ( ) ) return false    ;
  if ( ! Variables . contains ( "EventUUID" )              ) return false    ;
  SUID u = Value ( "EventUUID" ) .toULongLong( )                             ;
  if ( u <= 0                                              ) return false    ;
  EventObject * eol = ChildOf<EventObject> ( u )                             ;
  if ( IsNull ( eol )                                      ) return false    ;
  ////////////////////////////////////////////////////////////////////////////
  int       region = eol -> Value ( "MouseAt" ) . toInt      ( )             ;
  QString   EN     = eol -> Value ( "Name"    ) . toString   ( )             ;
  QDateTime T1     = Value        ( "T1"      ) . toDateTime ( )             ;
  QDateTime T2     = Value        ( "T2"      ) . toDateTime ( )             ;
  QDateTime ST     = eol -> Value ( "Start"   ) . toDateTime ( )             ;
  QDateTime ET     = eol -> Value ( "End"     ) . toDateTime ( )             ;
  qint64    dt     = T1 . msecsTo ( T2        )                              ;
  QDateTime st     = ST                                                      ;
  QDateTime et     = ET                                                      ;
  QRectF    Area   = BarArea (                )                              ;
  int       metric = Value   ( "BarMetric"    ) . toInt      ( )             ;
  int       tg     = Value   ( "TextGap"      ) . toInt      ( )             ;
  bool      top    = Value   ( "TopMetric"    ) . toInt      ( )             ;
  bool      bottom = Value   ( "BottomMetric" ) . toInt      ( )             ;
  int       gap    = - ( metric + 8 )                                        ;
  QRectF    eor                                                              ;
  double    miny                                                             ;
  double    maxy                                                             ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( region )                                                          {
    case 1                                                                   :
      st = T2                                                                ;
      if ( st > et )                                                         {
        st = ET                                                              ;
        et = T2                                                              ;
      }                                                                      ;
    break                                                                    ;
    case 2                                                                   :
      et = T2                                                                ;
      if ( st > et )                                                         {
        st = T2                                                              ;
        et = ST                                                              ;
      }                                                                      ;
    break                                                                    ;
    default                                                                  :
      st = st . addMSecs ( dt )                                              ;
      et = et . addMSecs ( dt )                                              ;
    break                                                                    ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( ! top ) && bottom ) gap = ( metric + tg )                           ;
  eol -> setVariable ( "Start" , st )                                        ;
  eol -> setVariable ( "End"   , et )                                        ;
  miny = eol -> minimum . y                                                  ;
  maxy = eol -> maximum . y                                                  ;
  if ( EventRectangle ( eol , eor , Area , gap , metric ) )                  {
    eol -> setRect ( eor )                                                   ;
  }                                                                          ;
  eol -> minimum . y = miny                                                  ;
  eol -> maximum . y = maxy                                                  ;
  eol -> setVariable ( "Start" , ST )                                        ;
  eol -> setVariable ( "End"   , ET )                                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( LastMoment ( nTimeNow ) )                                             {
    QString TT                                                               ;
    QRect   RX                                                               ;
    TT = tr   ( "Moving <%1>\nFrom : %2\nTo : %3"                            )
        . arg ( EN                                                           )
        . arg ( st . toString ( "yyyy/MM/dd hh:mm:ss")                       )
        . arg ( et . toString ( "yyyy/MM/dd hh:mm:ss")                     ) ;
    QToolTip::showText ( QCursor::pos() , TT , NULL , RX , 3000 )            ;
    if ( NULL != gui ) gui -> setToolTip ( TT )                              ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  return false                                                               ;
}

bool N::CalendarObject::FinalEvent (
       ControlPoint & From         ,
       ControlPoint & To           ,
       ControlPoint & At           )
{
  if ( ! Value                ( "HitEvent"  ) . toBool ( ) ) return false    ;
  if ( ! Variables . contains ( "EventUUID" )              ) return false    ;
  SUID u = Value ( "EventUUID" ) .toULongLong( )                             ;
  if ( u <= 0                                              ) return false    ;
  EventObject * eol = ChildOf<EventObject> ( u )                             ;
  if ( IsNull ( eol )                                      ) return false    ;
  ////////////////////////////////////////////////////////////////////////////
  int       region = eol -> Value ( "MouseAt" ) . toInt       ( )            ;
  QDateTime T1     = Value        ( "T1"      ) . toDateTime  ( )            ;
  QDateTime T2     = Value        ( "T2"      ) . toDateTime  ( )            ;
  QDateTime ST     = eol -> Value ( "Start"   ) . toDateTime  ( )            ;
  QDateTime ET     = eol -> Value ( "End"     ) . toDateTime  ( )            ;
  qint64    dt     = T1 . msecsTo ( T2        )                              ;
  SUID      eu     = eol -> Value ( "UUID"    ) . toULongLong ( )            ;
  QDateTime st     = ST                                                      ;
  QDateTime et     = ET                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  if ( 0 == dt ) return false                                                ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( region )                                                          {
    case 1                                                                   :
      st = T2                                                                ;
      if ( st > et )                                                         {
        st = ET                                                              ;
        et = T2                                                              ;
      }                                                                      ;
    break                                                                    ;
    case 2                                                                   :
      et = T2                                                                ;
      if ( st > et )                                                         {
        st = T2                                                              ;
        et = ST                                                              ;
      }                                                                      ;
    break                                                                    ;
    default                                                                  :
      st = st . addMSecs ( dt )                                              ;
      et = et . addMSecs ( dt )                                              ;
    break                                                                    ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  VarArgs args                                                               ;
  args << eu                                                                 ;
  args << st                                                                 ;
  args << et                                                                 ;
  start              ( 10002  , args  )                                      ;
  eol -> setVariable ( "Hold" , false )                                      ;
  ////////////////////////////////////////////////////////////////////////////
  setVariable ( "HitEvent" , false )                                         ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

bool N::CalendarObject::HitObjects (
       ControlPoint & From         ,
       ControlPoint & To           ,
       ControlPoint & At           )
{
  if ( HitEvent ( From , To , At ) ) return true ;
  return false                                   ;
}

bool N::CalendarObject::MovingObjects (
       ControlPoint & From            ,
       ControlPoint & To              ,
       ControlPoint & At              )
{
  if ( MovingEvent ( From , To , At ) ) return true ;
  return false                                      ;
}

bool N::CalendarObject::FinalObjects (
       ControlPoint & From           ,
       ControlPoint & To             ,
       ControlPoint & At             )
{
  if ( FinalEvent ( From , To , At ) ) return true ;
  return false                                     ;
}

bool N::CalendarObject::EventMenu (
       QWidget      * widget      ,
       QPointF        pos         ,
       ControlPoint & From        ,
       ControlPoint & To          ,
       ControlPoint & At          )
{
  EventObject * eol = LocateEvent ( From , To , At ) ;
  if ( IsNull ( eol ) ) return false                 ;
  ControlPoint F                                     ;
  ControlPoint T                                     ;
  F = matrices [ 2 ] * From                          ;
  T = matrices [ 2 ] * To                            ;
  return eol -> Menu ( widget , pos , F , T )        ;
}

bool N::CalendarObject::PeriodMenu (
       QWidget      * widget       ,
       QPointF        pos          ,
       ControlPoint & From         ,
       ControlPoint & To           ,
       ControlPoint & At           )
{
  if ( ! matrices . contains ( 2 ) ) return false                 ;
  UUIDs U = list ( "PeriodBlock" )                                ;
  if ( U . count ( ) <= 0          ) return false                 ;
  /////////////////////////////////////////////////////////////////
  SUID         u                                                  ;
  QPointF      p ( At . x , At . y )                              ;
  ControlPoint F                                                  ;
  ControlPoint T                                                  ;
  /////////////////////////////////////////////////////////////////
  F = matrices [ 2 ] * From                                       ;
  T = matrices [ 2 ] * To                                         ;
  foreach ( u , U ) if ( SceneObject::children . contains ( u ) ) {
    PeriodBlock * pob = ChildOf<PeriodBlock> ( u )                ;
    if ( pob -> Value ( "Menu" ) . toBool ( ) )                   {
      if ( pob -> Within ( p ) )                                  {
        if ( pob -> Menu ( widget , pos , F , T ) ) return true   ;
      }                                                           ;
    }                                                             ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  return false                                                    ;
}

void N::CalendarObject::ZoomIn(void)
{
  QDateTime st  = Value ( "Start" ) . toDateTime ( ) ;
  QDateTime et  = Value ( "End"   ) . toDateTime ( ) ;
  qint64    gap = Value ( "Gap"   ) . toLongLong ( ) ;
  qint64    dt  = st . secsTo ( et ) / 2             ;
  if ( dt <= 150 ) return                            ;
  ////////////////////////////////////////////////////
  st  = st . addSecs ( dt )                          ;
  et  = st                                           ;
  dt /= 2                                            ;
  if ( dt < 150 ) dt = 150                           ;
  st  = st . addSecs ( -dt )                         ;
  et  = et . addSecs (  dt )                         ;
  ////////////////////////////////////////////////////
  setRange   ( st , et , gap )                       ;
  MoveTime   ( st , et       )                       ;
}

void N::CalendarObject::ZoomOut(void)
{
  QDateTime st  = Value ( "Start" ) . toDateTime ( ) ;
  QDateTime et  = Value ( "End"   ) . toDateTime ( ) ;
  qint64    gap = Value ( "Gap"   ) . toLongLong ( ) ;
  qint64    dt  = st . secsTo ( et ) / 2             ;
  ////////////////////////////////////////////////////
  st  = st . addSecs ( dt )                          ;
  et  = st                                           ;
  dt *= 2                                            ;
  st  = st . addSecs ( -dt )                         ;
  et  = et . addSecs (  dt )                         ;
  ////////////////////////////////////////////////////
  setRange   ( st , et , gap )                       ;
  MoveTime   ( st , et       )                       ;
}

bool N::CalendarObject::Menu (
       QWidget      * widget ,
       QPointF        pos    ,
       ControlPoint & From   ,
       ControlPoint & To     )
{
  if ( ! Value ( "Mouse" ) . toBool ( ) ) return false                       ;
  emit assignCursor ( Qt::ArrowCursor )                                      ;
  if ( isLoading ( )                    ) return false                       ;
  ////////////////////////////////////////////////////////////////////////////
  ControlPoint At                                                            ;
  if ( ! Collide ( From , To , At ) ) return false                           ;
  int region = AtRegion ( At )                                               ;
  if ( region <= 0 ) return false                                            ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( region )                                                          {
    case 1                                                                   :
    break                                                                    ;
    case 2                                                                   :
    break                                                                    ;
    case 3                                                                   :
      if ( EventMenu  ( widget , pos , From , To , At ) ) return true        ;
      if ( PeriodMenu ( widget , pos , From , To , At ) ) return true        ;
    break                                                                    ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  MenuManager     mm ( widget )                                              ;
  QMenu         * md                                                         ;
  QMenu         * ma                                                         ;
  QMenu         * me                                                         ;
  QMenu         * mk                                                         ;
  QMenu         * mc                                                         ;
  QMenu         * mt                                                         ;
  QAction       * aa                                                         ;
  QDateTimeEdit * CT  = new QDateTimeEdit ( NULL        )                    ;
  QDateTimeEdit * ST  = new QDateTimeEdit ( NULL        )                    ;
  QDateTimeEdit * ET  = new QDateTimeEdit ( NULL        )                    ;
  QDateTime       st  = Value ( "Start" ) . toDateTime ( )                   ;
  QDateTime       et  = Value ( "End"   ) . toDateTime ( )                   ;
  QDateTime       ct                                                         ;
  QDateTime       ts                                                         ;
  QDateTime       te                                                         ;
  QDateTime       tc                                                         ;
  qint64          xt                                                         ;
  qint64          gap = Value ( "Gap"       ) . toLongLong ( )               ;
  qint64          dt  = st . secsTo ( et )                                   ;
  QVariants       vargs                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "Name" ) )                                     {
    QString n = Variables [ "Name" ] . toString ( )                          ;
    aa  = mm . add          ( 0   , n                            )           ;
    aa -> setEnabled        ( false                              )           ;
    mm       . addSeparator (                                    )           ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  xt  = st . msecsTo        ( et                                 )           ;
  ct  = st                                                                   ;
  ct  = ct . addMSecs       ( xt / 2                             )           ;
  CT -> setDisplayFormat    ( "yyyy/MM/dd hh:mm:ss"              )           ;
  ST -> setDisplayFormat    ( "yyyy/MM/dd hh:mm:ss"              )           ;
  ET -> setDisplayFormat    ( "yyyy/MM/dd hh:mm:ss"              )           ;
  CT -> setCalendarPopup    ( true                               )           ;
  ST -> setCalendarPopup    ( true                               )           ;
  ET -> setCalendarPopup    ( true                               )           ;
  CT -> setDateTime         ( ct                                 )           ;
  ST -> setDateTime         ( st                                 )           ;
  ET -> setDateTime         ( et                                 )           ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( region )                                                          {
    case 1                                                                   :
    case 2                                                                   :
    break                                                                    ;
    case 3                                                                   :
      mm . add          ( 101 , tr("Refresh"  ) )                            ;
      mm . add          ( 102 , tr("Add event") )                            ;
      mm . addSeparator (                       )                            ;
    break                                                                    ;
    case 4                                                                   :
    break                                                                    ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  md = mm . addMenu         ( tr("Edit")                                   ) ;
  ma = mm . addMenu         ( tr("Adjustments")                            ) ;
  me = mm . addMenu         ( tr("Events")                                 ) ;
  mk = mm . addMenu         ( tr("Tasks")                                  ) ;
  mm      . addSeparator    (                                              ) ;
  mc = mm . addMenu         ( tr("Configuration")                          ) ;
  mt = mm . addMenu         ( tr("Tools")                                  ) ;
  ////////////////////////////////////////////////////////////////////////////
  mm . addSeparator         (                                              ) ;
  mm . add                  ( 301 , tr("24 hours only")                    ) ;
  if                        ( dt > 300                                     ) {
    mm . add                ( 302 , tr("Zoom in" )                         ) ;
  }                                                                          ;
  mm . add                  ( 303 , tr("Zoom out")                         ) ;
  ////////////////////////////////////////////////////////////////////////////
  mm . add                  ( ma , 103     , tr("Move to current time ")   ) ;
  mm . add                  ( ma , 4412001 , CT                            ) ;
  mm . add                  ( ma , 4412002 , ST                            ) ;
  mm . add                  ( ma , 4412003 , ET                            ) ;
  mm . addSeparator         ( ma                                           ) ;
  ////////////////////////////////////////////////////////////////////////////
  EditMenu   ( mm , md , region )                                            ;
  ConfMenu   ( mm , mc , region )                                            ;
  AdjustMenu ( mm , ma , region )                                            ;
  EventsMenu ( mm , me , region )                                            ;
  TasksMenu  ( mm , mk , region )                                            ;
  ToolsMenu  ( mm , mt          )                                            ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( region )                                                          {
    case 1                                                                   :
    case 2                                                                   :
    break                                                                    ;
    case 3                                                                   :
    break                                                                    ;
    case 4                                                                   :
    break                                                                    ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  CallDynamic          ( "AttacheCalendar" , mm . menu , gui , vargs )       ;
  CallToMenu           ( mm , NULL , false                           )       ;
  mm  . setFont        ( plan )                                              ;
  ////////////////////////////////////////////////////////////////////////////
  aa  = mm . exec      (      )                                              ;
  ts  = ST -> dateTime (      )                                              ;
  te  = ET -> dateTime (      )                                              ;
  tc  = CT -> dateTime (      )                                              ;
  ////////////////////////////////////////////////////////////////////////////
  if ( NotNull(aa) && ( 103 == mm [ aa ] ) )                                 {
    MoveToNow ( )                                                            ;
    return true                                                              ;
  } else
  if ( tc != ct )                                                            {
    st = tc                                                                  ;
    st = st . addMSecs ( -xt / 2       )                                     ;
    et = st                                                                  ;
    et = et . addMSecs (  xt           )                                     ;
    setRange           ( st , et , gap )                                     ;
    MoveTime           ( st , et       )                                     ;
  } else
  if ( ts != st )                                                            {
    if ( ts > et )                                                           {
      st = et                                                                ;
      et = ts                                                                ;
    } else                                                                   {
      st = ts                                                                ;
    }                                                                        ;
    setRange           ( st , et , gap )                                     ;
    MoveTime           ( st , et       )                                     ;
  } else
  if ( te != et )                                                            {
    if ( te < st )                                                           {
      et = st                                                                ;
      st = te                                                                ;
    } else                                                                   {
      et = te                                                                ;
    }                                                                        ;
    setRange           ( st , et , gap )                                     ;
    MoveTime           ( st , et       )                                     ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  nKickOut ( IsNull ( aa ) , true )                                          ;
  if ( EditProcessor   ( mm , aa        ) ) return true                      ;
  if ( ConfProcessor   ( mm , aa        ) ) return true                      ;
  if ( AdjustProcessor ( mm , aa        ) ) return true                      ;
  if ( ToolsProcessor  ( mm , aa        ) ) return true                      ;
  if ( EventsProcessor ( mm , aa        ) ) return true                      ;
  if ( TasksProcessor  ( mm , aa        ) ) return true                      ;
  if ( 0 != CallToMenu ( mm , aa , true ) ) return true                      ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                                       {
    case  101                                                                :
      startup ( )                                                            ;
    break                                                                    ;
    case  102                                                                :
      ts = AtFixTime ( At )                                                  ;
      te = QDateTime ( ts . date ( )                                         ,
                       QTime( ts . time ( ) . hour   ( )                     ,
                              ts . time ( ) . minute ( )                     ,
                              0                                              ,
                              0                                          ) ) ;
      ts = te                                                                ;
      te = te . addSecs ( 3600 )                                             ;
      emit EditEvent ( this                                                  ,
                       0                                                     ,
                       ts                                                    ,
                       te                                                    ,
                       Value ( "ControlPanel" ) . toBool ( ) )               ;
    break                                                                    ;
    case  301                                                                :
      st  = Value ( "Start" ) . toDateTime (       )                         ;
      et  = Value ( "End"   ) . toDateTime (       )                         ;
      dt  = st                . secsTo     ( et    )                         ;
      dt  = ( dt / 2 ) - 43200                                               ;
      st  = st                . addSecs    ( dt    )                         ;
      et  = st                                                               ;
      et  = et                . addSecs    ( 86400 )                         ;
      gap = Value ( "Gap"   ) . toLongLong (       )                         ;
      setRange ( st , et , gap )                                             ;
      MoveTime ( st , et       )                                             ;
    break                                                                    ;
    case  302                                                                :
      ZoomIn  ( )                                                            ;
    break                                                                    ;
    case  303                                                                :
      ZoomOut ( )                                                            ;
    break                                                                    ;
  }                                                                          ;
  return true                                                                ;
}

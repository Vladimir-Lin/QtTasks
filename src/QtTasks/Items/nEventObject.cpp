#include <qttasks.h>

N::EventObject:: EventObject ( QObject * parent , Plan * p )
               : SceneWidget (           parent ,        p )
               , calendar    ( NULL                        )
{
  Configure ( ) ;
}

N::EventObject:: EventObject ( QObject * parent , Plan * p ,SceneDestructor * des )
               : SceneWidget (           parent ,        p ,                  des )
               , calendar    ( NULL                                               )
{
  Configure ( ) ;
}

N::EventObject::~EventObject (void)
{
}

void N::EventObject::Configure(void)
{
  int          flag = Qt::AlignCenter                  ;
  ControlPoint color                                   ;
  QColor       black    (   0 ,    0 ,   0 , 192     ) ;
  color  = QColor       ( 192 ,  192 , 192 , 192     ) ;
  addColor              (   0 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   1 , 0.02    ) ;
  addColor              (   1 , color                ) ;
  color  = ControlPoint (   1 ,    0 ,   0 , 0.02    ) ;
  addColor              (   2 , color                ) ;
  color  = ControlPoint (   0 ,  0.6 ,   0 , 0.01    ) ;
  addColor              (   3 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   0 , 0.25    ) ;
  addColor              (   4 , color                ) ;
  color  = ControlPoint ( 0.1 , 0.70 ,   1 , 0.03    ) ;
  addColor              (   5 , color                ) ;
  color  = ControlPoint ( 0.2 , 0.75 , 0.2 , 0.10    ) ;
  addColor              (   6 , color                ) ;
  //////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"     , "EventObject" ) ;
  setVariable           ( "Type"           , "Event" ) ;
  setVariable           ( "Focus"          , false   ) ;
  setVariable           ( "Hold"           , false   ) ;
  setVariable           ( "Menu"           , false   ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "GridColor"      , 0       ) ;
  setVariable           ( "BackColor"      , 1       ) ;
  setVariable           ( "FrontColor"     , 2       ) ;
  setVariable           ( "SideColor"      , 3       ) ;
  setVariable           ( "BorderColor"    , 4       ) ;
  setVariable           ( "SeparatorColor" , 5       ) ;
  setVariable           ( "MetricColor"    , 6       ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Front"          , true    ) ;
  setVariable           ( "Back"           , true    ) ;
  setVariable           ( "Side"           , true    ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "External"       , false   ) ;
  setVariable           ( "TextGap"        , 4       ) ;
  setVariable           ( "Length"         , 40      ) ;
  setVariable           ( "TextColor"      , black   ) ;
  setVariable           ( "TextFlags"      , flag    ) ;
  setVariable           ( "Margin"         , 3       ) ;
  //////////////////////////////////////////////////////
  TypeNames [ N::None          ] = tr("None"         ) ;
  TypeNames [ N::Notify        ] = tr("Notify"       ) ;
  TypeNames [ N::Period        ] = tr("Period"       ) ;
  TypeNames [ N::Record        ] = tr("Record"       ) ;
  TypeNames [ N::Meeting       ] = tr("Meeting"      ) ;
  TypeNames [ N::Automation    ] = tr("Automation"   ) ;
  TypeNames [ N::Operation     ] = tr("Operation"    ) ;
  TypeNames [ N::Sync          ] = tr("Sync"         ) ;
  TypeNames [ N::Download      ] = tr("Download"     ) ;
  TypeNames [ N::Upload        ] = tr("Upload"       ) ;
  TypeNames [ N::Audio         ] = tr("Audio"        ) ;
  TypeNames [ N::Video         ] = tr("Video"        ) ;
  TypeNames [ N::TV            ] = tr("TV"           ) ;
  TypeNames [ N::Programming   ] = tr("Programming"  ) ;
  TypeNames [ N::Backup        ] = tr("Backup"       ) ;
  TypeNames [ N::FileUpdate    ] = tr("FileUpdate"   ) ;
  TypeNames [ N::Cooking       ] = tr("Cooking"      ) ;
  TypeNames [ N::Sleep         ] = tr("Sleep"        ) ;
  TypeNames [ N::Housework     ] = tr("Housework"    ) ;
  TypeNames [ N::Shopping      ] = tr("Shopping"     ) ;
  TypeNames [ N::Communication ] = tr("Communication") ;
  TypeNames [ N::Finish        ] = tr("Finish"       ) ;
  TypeNames [ N::Obsolete      ] = tr("Obsolete"     ) ;
  TypeNames [ N::Others        ] = tr("Others"       ) ;
  TypeNames [ N::ForexTrade    ] = tr("FOREX"        ) ;
}

int N::EventObject::DurationStatus(void)
{
  QDateTime st = Value ( "Start" ) . toDateTime ( ) ;
  QDateTime et = Value ( "End"   ) . toDateTime ( ) ;
  QDateTime nt = nTimeNow                           ;
  if ( et < nt ) return -1                          ;
  if ( st > nt ) return  1                          ;
  return                 0                          ;
}

int N::EventObject::AtRegion(ControlPoint & At)
{
  int    m = Value ( "Margin" ) . toInt ( ) ;
  double dx                                 ;
  ///////////////////////////////////////////
  if ( At . y < minimum . y ) return -1     ;
  if ( At . y > maximum . y ) return -1     ;
  ///////////////////////////////////////////
  dx = At . x - minimum . x                 ;
  if ( dx < 0 ) dx = -dx                    ;
  if ( dx < m ) return 1                    ;
  ///////////////////////////////////////////
  dx = At . x - maximum . x                 ;
  if ( dx < 0 ) dx = -dx                    ;
  if ( dx < m ) return 2                    ;
  ///////////////////////////////////////////
  return 0                                  ;
}

QString N::EventObject::ToolTip(void)
{
  QString   tt = ""                                                        ;
  QString   du = ""                                                        ;
  QString   na = Value ( "Name"  ) . toString   ( )                        ;
  QString   nt = Value ( "Note"  ) . toString   ( )                        ;
  QDateTime st = Value ( "Start" ) . toDateTime ( )                        ;
  QDateTime et = Value ( "End"   ) . toDateTime ( )                        ;
  qint64    dt = st . secsTo ( et )                                        ;
  qint64    ds = dt / 86400                                                ;
  int       ex = Value ( "EventType" ) . toInt  ( )                        ;
  QTime     T ( 0 , 0 , 0 , 0 )                                            ;
  //////////////////////////////////////////////////////////////////////////
  dt %= 86400                                                              ;
  T   = T . addSecs  ( dt % 86400 )                                        ;
  du  = T . toString ( "hh:mm:ss" )                                        ;
  if ( ds > 0 ) du = tr("%1 days %2") .arg ( ds ) . arg ( du )             ;
  //////////////////////////////////////////////////////////////////////////
  tt  = na                                                                 ;
  tt  . append ( "\n" )                                                    ;
  tt += tr("Event type : %1") . arg ( TypeNames [ ex ] )                   ;
  tt  . append ( "\n" )                                                    ;
  tt += tr("From : %1"  ) . arg ( st . toString ( "yyyy/MM/dd hh:mm:ss") ) ;
  tt  . append ( "\n" )                                                    ;
  tt += tr("To : %1"    ) . arg ( et . toString ( "yyyy/MM/dd hh:mm:ss") ) ;
  tt  . append ( "\n" )                                                    ;
  tt += tr("Period : %1") . arg ( du                                     ) ;
  if ( nt . length ( ) > 0 )                                               {
    tt  . append ( "\n------------------\n" )                              ;
    tt += nt                                                               ;
  }                                                                        ;
  //////////////////////////////////////////////////////////////////////////
  return tt                                                                ;
}

QRect N::EventObject::TextRegion(QString text,int H)
{
  QFont F = plan -> fonts [ Fonts::Editor ] . toQFont ( ) ;
  F . setPixelSize ( H )                                  ;
  /////////////////////////////////////////////////////////
  QFontMetrics FM ( F )                                   ;
#pragma message("Potential startTimer bug here, check it out")
  return FM . boundingRect ( text )                       ;
}

bool N::EventObject::Within(QPointF & p)
{
  QList<QRectF> r                                     ;
  if ( Rectangles ( r ) <= 0 ) return false           ;
  while ( r . count ( ) > 0 )                         {
    if ( r . first ( ) . contains ( p ) ) return true ;
    r . takeFirst ( )                                 ;
  }                                                   ;
  return false                                        ;
}

int N::EventObject::Rectangles(QList<QRectF> & rectangles)
{
  QRectF r                                         ;
  int    t = 0                                     ;
  r . setLeft   ( minimum . x )                    ;
  r . setRight  ( maximum . x )                    ;
  r . setTop    ( maximum . y )                    ;
  r . setBottom ( minimum . y )                    ;
  rectangles << r                                  ;
  t ++                                             ;
  if ( Value ( "External" ) . toBool ( ) )         {
    rectangles << Value ( "Region" ) . toRectF ( ) ;
    t ++                                           ;
  }                                                ;
  if ( Variables . contains ( "Icon" ) )           {
    rectangles << Value ( "Icon"   ) . toRectF ( ) ;
    t ++                                           ;
  }                                                ;
  return t                                         ;
}

bool N::EventObject::Spot  (
       ControlPoint & From ,
       ControlPoint & To   ,
       ControlPoint & At   )
{
  return xymSpot ( From , To , At ) ;
}

void N::EventObject::setText (
       QString  description  ,
       QRectF   range        ,
       QRectF & area         ,
       bool     generate     )
{
  int     L = Value ( "Length" ) . toInt ( )                  ;
  QString n = description                                     ;
  int     h = range . height ( ) - 1                          ;
  int     d = range . width  ( )                              ;
  double  m                                                   ;
  double  v                                                   ;
  int     w                                                   ;
  QRect   r                                                   ;
  QRectF  t                                                   ;
  bool    e = false                                           ;
  /////////////////////////////////////////////////////////////
  m = range . center ( ) . x ( )                              ;
  v = range . center ( ) . y ( )                              ;
  if ( n . length ( ) > L )                                   {
    n = n . left ( L         )                                ;
    n . append   ( "..."     )                                ;
  }                                                           ;
  r = TextRegion ( n , h - 4 )                                ;
  h = r . height (           )                                ;
  if ( h <= 0 ) h = range . height ( ) - 4                    ;
  h = MipSize    ( h         )                                ;
  r = TextRegion ( n , h - 4 )                                ;
  w = r . width  (           )                                ;
  w = MipSize    ( w         )                                ;
  /////////////////////////////////////////////////////////////
  if ( w > d ) e = true                                       ;
  if ( e )                                                    {
    m = m - ( w / 2 )                                         ;
    if (   m       < area . left  ( ) )                       {
      m = area . left ( )                                     ;
    } else
    if ( ( m + w ) > area . right ( ) )                       {
      m = area . right ( ) - w                                ;
    }                                                         ;
    v = v - ( h / 2 )                                         ;
    v = v - h - Value ( "TextGap" ) . toInt ( )               ;
  } else                                                      {
    m = m - ( w / 2 )                                         ;
    v = v - ( h / 2 )                                         ;
  }                                                           ;
  t . setTop    ( v )                                         ;
  t . setLeft   ( m )                                         ;
  t . setWidth  ( w )                                         ;
  t . setHeight ( h )                                         ;
  /////////////////////////////////////////////////////////////
  setVariable ( "External" , e )                              ;
  setVariable ( "Region"   , t )                              ;
  if ( ! generate ) return                                    ;
  /////////////////////////////////////////////////////////////
  SceneTexture * tz                                           ;
  QSize          s              ( w , h                     ) ;
  QImage       * O = new QImage ( s , QImage::Format_ARGB32 ) ;
  tz        = new SceneTexture  ( destructor                ) ;
  tz -> node      = 101                                       ;
  tz -> create                  ( O , true , false          ) ;
  if ( textures . contains ( 101 ) )                          {
    LockAt   ( "Operate" )                                    ;
    SceneTexture * dxt = textures [ 101 ]                     ;
    textures . remove ( 101 )                                 ;
    UnlockAt ( "Operate" )                                    ;
    delete dxt                                                ;
  }                                                           ;
  textures [ 101 ]  = tz                                      ;
  tz -> original -> fill        ( 0                         ) ;
  /////////////////////////////////////////////////////////////
  QColor c (   0 ,   0 , 0 , 255 )                            ;
  QRectF z (   0 ,   0 , w ,   h )                            ;
  QFont  F = plan -> fonts [ Fonts::Editor ] . toQFont ( )    ;
  int    flag = Qt::AlignVCenter | Qt::AlignHCenter           ;
  F . setPixelSize ( h - 6 )                                  ;
  if ( Variables . contains ( "TextColor" ) )                 {
    c = Variables [ "TextColor" ] . value <QColor> ( )        ;
  }                                                           ;
  if ( Variables . contains ( "TextFlags" ) )                 {
    flag = Variables [ "TextFlags" ] . toInt ( )              ;
  }                                                           ;
  textures [ 101 ] -> drawText ( c , F , z , flag , n )       ;
}

void N::EventObject::setIcon (
       int      et           ,
       QRectF   range        ,
       QRectF & area         ,
       bool     generate     )
{
  QImage * I = NULL                                                          ;
  double   v = range . bottom ( ) - 64                                       ;
  double   m                                                                 ;
  QRectF   t                                                                 ;
  switch ( et )                                                              {
    case N::Meeting                                                          :
      if ( generate ) I = new QImage ( ":/images/peoplegroups.png" )         ;
    break                                                                    ;
    case N::Automation                                                       :
      if ( generate ) I = new QImage ( ":/images/taskicon.png" )             ;
    break                                                                    ;
    case N::Sync                                                             :
      if ( generate ) I = new QImage ( ":/images/updateEvent.png" )          ;
    break                                                                    ;
    case N::Download                                                         :
      if ( generate ) I = new QImage ( ":/images/moveDown.png" )             ;
    break                                                                    ;
    case N::Upload                                                           :
      if ( generate ) I = new QImage ( ":/images/moveUp.png"   )             ;
    break                                                                    ;
    case N::Audio                                                            :
      Variables . remove ( "Icon" )                                          ;
    break                                                                    ;
    case N::Video                                                            :
      if ( generate ) I = new QImage ( ":/images/videocollection.png" )      ;
    break                                                                    ;
    case N::TV                                                               :
      Variables . remove ( "Icon" )                                          ;
    break                                                                    ;
    case N::Backup                                                           :
      if ( generate ) I = new QImage ( ":/images/backup.png"   )             ;
    break                                                                    ;
    case N::FileUpdate                                                       :
      if ( generate ) I = new QImage ( ":/images/projectobject.png" )        ;
    break                                                                    ;
    case N::Sleep                                                            :
      if ( generate ) I = new QImage ( ":/images/sleepz.png" )               ;
    break                                                                    ;
    case N::Communication                                                    :
      if ( generate ) I = new QImage ( ":/images/talk.png"   )               ;
    break                                                                    ;
    case N::Notify                                                           :
    case N::Period                                                           :
    case N::Record                                                           :
    case N::Operation                                                        :
    case N::Programming                                                      :
    case N::Cooking                                                          :
    case N::Housework                                                        :
    case N::Shopping                                                         :
    case N::Finish                                                           :
    case N::Obsolete                                                         :
    case N::Others                                                           :
    case N::ForexTrade                                                       :
    default                                                                  :
      Variables . remove ( "Icon" )                                          ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  m = range . left ( ) - 66                                                  ;
  if ( m < area . left  ( ) )                                                {
    m = range . right ( ) + 2                                                ;
  }                                                                          ;
  if ( m > area . right ( ) )                                                {
    v = v                          - 64                                      ;
    m = range . center ( ) . x ( ) - 32                                      ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  t . setTop    ( v  )                                                       ;
  t . setLeft   ( m  )                                                       ;
  t . setWidth  ( 64 )                                                       ;
  t . setHeight ( 64 )                                                       ;
  setVariable ( "Icon" , t )                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( I ) ) return                                                 ;
  if ( ! generate   ) return                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  SceneTexture * tz = NULL                                                   ;
  if ( ! textures . contains ( 102 ) )                                       {
    tz         = new SceneTexture  ( destructor )                            ;
    tz -> node = 102                                                         ;
  } else                                                                     {
    tz = textures [ 102 ]                                                    ;
    if ( NotNull ( tz -> original ) )                                        {
      QImage * ii = tz -> original                                           ;
      tz -> original = NULL                                                  ;
      (*destructor) -= ii                                                    ;
      delete ii                                                              ;
    }                                                                        ;
  }                                                                          ;
  if ( NotNull ( tz ) ) tz -> create ( I , true , false )                    ;
  if ( ! textures . contains ( 102 ) )                                       {
    textures [ 102 ]  = tz                                                   ;
  }                                                                          ;
}

void N::EventObject::renderFaces(void)
{
  QtGL::PushMatrix             (                                    ) ;
  /////////////////////////////////////////////////////////////////////
  QtGL::Disable                ( GL_CULL_FACE                       ) ;
  QtGL::Disable                ( GL_DEPTH_TEST                      ) ;
  QtGL::Disable                ( GL_LINE_SMOOTH                     ) ;
  QtGL::Disable                ( GL_POLYGON_SMOOTH                  ) ;
  /////////////////////////////////////////////////////////////////////
  if ( Value ( "Hold" ) . toBool ( ) )                                {
    setVariable                ( "BackColor"      , 5               ) ;
    setVariable                ( "FrontColor"     , 1               ) ;
  } else                                                              {
    switch                     ( DurationStatus ( )                 ) {
      case -1                                                         :
        setVariable            ( "BackColor"      , 5               ) ;
        setVariable            ( "FrontColor"     , 3               ) ;
      break                                                           ;
      case  0                                                         :
        setVariable            ( "BackColor"      , 2               ) ;
        setVariable            ( "FrontColor"     , 5               ) ;
      break                                                           ;
      case  1                                                         :
        setVariable            ( "BackColor"      , 1               ) ;
        setVariable            ( "FrontColor"     , 2               ) ;
      break                                                           ;
    }                                                                 ;
  }                                                                   ;
  FeatureCube                  ( minimum , maximum                  ) ;
  /////////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "Icon" ) )                              {
    if ( textures . contains ( 102 ) )                                {
      double z       = maximum . z + 0.25                             ;
      QRectF r       = Variables [ "Icon" ] . toRectF ( )             ;
      bool   texture = ( bindTexture  ( 102 ) >= 0 )                  ;
      if ( texture ) TextureRect    ( r , z )                         ;
      if ( texture ) releaseTexture ( 102   )                         ;
    }                                                                 ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "Region" ) )                            {
    if ( textures . contains ( 101 ) )                                {
      double z       = maximum . z + 0.50                             ;
      QRectF r       = Variables [ "Region" ] . toRectF ( )           ;
      if ( Value ( "External" ) . toBool ( ) )                        {
        double rz = z - 0.20                                          ;
        double lp                                                     ;
        double rp                                                     ;
        double mp                                                     ;
        double cp = minimum . y + 4                                   ;
        lp = r . left  ( )                                            ;
        rp = r . right ( )                                            ;
        if ( minimum . x > lp ) lp = minimum . x                      ;
        if ( maximum . x < rp ) rp = maximum . x                      ;
        mp = ( lp + rp ) / 2                                          ;
        if ( ( rp - lp ) > 10 )                                       {
          lp = mp - 5                                                 ;
          rp = mp + 5                                                 ;
        }                                                             ;
        QtGL::Disable       ( GL_LINE_SMOOTH                      )   ;
        QtGL::Disable       ( GL_POLYGON_SMOOTH                   )   ;
//        assumeColor         ( "SideColor"                         )   ;
        assumeColor         ( "SeparatorColor"                    )   ;
        QtGL::Quadrilateral (                                     )   ;
        QtGL::Vertex3d      ( r . left  ( ) , r . top    ( ) , rz )   ;
        QtGL::Vertex3d      ( r . right ( ) , r . top    ( ) , rz )   ;
        QtGL::Vertex3d      ( r . right ( ) , r . bottom ( ) , rz )   ;
        QtGL::Vertex3d      ( r . left  ( ) , r . bottom ( ) , rz )   ;
        QtGL::End           (                                     )   ;
        if ( ( r.left() < mp ) && ( mp < r.right() ) )                {
          QtGL::Triangles   (                                     )   ;
          QtGL::Vertex3d    ( rp            , r . bottom ( ) , rz )   ;
          QtGL::Vertex3d    ( mp            , cp             , rz )   ;
          QtGL::Vertex3d    ( lp            , r . bottom ( ) , rz )   ;
          QtGL::End         (                                     )   ;
        }                                                             ;
        QtGL::Enable        ( GL_LINE_SMOOTH                      )   ;
        QtGL::Enable        ( GL_POLYGON_SMOOTH                   )   ;
        assumeColor         ( "BorderColor"                       )   ;
        QtGL::Loop          (                                     )   ;
        QtGL::Vertex3d      ( r . left  ( ) , r . top    ( ) , rz )   ;
        QtGL::Vertex3d      ( r . right ( ) , r . top    ( ) , rz )   ;
        QtGL::Vertex3d      ( r . right ( ) , r . bottom ( ) , rz )   ;
        if ( ( r.left() < mp ) && ( mp < r.right() ) )                {
          QtGL::Vertex3d    ( rp            , r . bottom ( ) , rz )   ;
          QtGL::Vertex3d    ( mp            , cp             , rz )   ;
          QtGL::Vertex3d    ( lp            , r . bottom ( ) , rz )   ;
        }                                                             ;
        QtGL::Vertex3d      ( r . left  ( ) , r . bottom ( ) , rz )   ;
        QtGL::End           (                                     )   ;
        QtGL::Disable       ( GL_LINE_SMOOTH                      )   ;
        QtGL::Disable       ( GL_POLYGON_SMOOTH                   )   ;
      }                                                               ;
      /////////////////////////////////////////////////////////////////
      bool texture = ( bindTexture  ( 101 ) >= 0 )                    ;
      if ( texture ) TextureRect    ( r , z )                         ;
      if ( texture ) releaseTexture ( 101   )                         ;
    }                                                                 ;
  }                                                                   ;
  /////////////////////////////////////////////////////////////////////
  QtGL::Enable                 ( GL_CULL_FACE                       ) ;
  QtGL::Enable                 ( GL_DEPTH_TEST                      ) ;
  /////////////////////////////////////////////////////////////////////
  QtGL::PopMatrix              (                                    ) ;
}

void N::EventObject::run(int type,ThreadData * data)
{
  switch ( type )                                             {
    case 10011                                                :
      if ( 2 == data -> Arguments . count ( ) )               {
        SUID    u = data -> Arguments [ 0 ] . toULongLong ( ) ;
        int     t = data -> Arguments [ 1 ] . toInt       ( ) ;
        UpdateEvent ( u , t )                                 ;
      }                                                       ;
    break                                                     ;
    case 10012                                                :
      if ( 1 == data -> Arguments . count ( ) )               {
        SUID    u = data -> Arguments [ 0 ] . toULongLong ( ) ;
        JobCompleted ( u )                                    ;
      }                                                       ;
    break                                                     ;
    case 10013                                                :
      if ( 2 == data -> Arguments . count ( ) )               {
        SUID    u = data -> Arguments [ 0 ] . toULongLong ( ) ;
        QString n = data -> Arguments [ 1 ] . toString    ( ) ;
        UpdateName ( u , n )                                  ;
      }                                                       ;
    break                                                     ;
    case 10014                                                :
      SetupExecution    ( )                                   ;
    break                                                     ;
    case 10015                                                :
      SetupMusic        ( )                                   ;
    break                                                     ;
    case 10016                                                :
      SetupAlbumGroup   ( )                                   ;
    break                                                     ;
    case 10017                                                :
      SelectClip        ( )                                   ;
    break                                                     ;
    case 10018                                                :
      ProcessDependency ( )                                   ;
    break                                                     ;
  }                                                           ;
}

void N::EventObject::UpdateName(SUID u,QString n)
{
  SqlConnection SC  ( plan->sql        ) ;
  ////////////////////////////////////////
  if ( SC . open    ( FunctionString ) ) {
    SC . assureName ( PlanTable(Names)   ,
                      u                  ,
                      plan->LanguageId   ,
                      n                ) ;
    SC . close      (                  ) ;
  }                                      ;
  SC   . remove     (                  ) ;
  ////////////////////////////////////////
  emit Update       (                  ) ;
}

void N::EventObject::UpdateEvent(SUID u,int t)
{
  EventManager  EM  ( plan             )                     ;
  SqlConnection SC  ( plan->sql        )                     ;
  ////////////////////////////////////////////////////////////
  if ( SC . open    ( FunctionString ) )                     {
    EM . UpdateType ( SC , PlanTable(EventHistory) , u , t ) ;
    EM . UpdateType ( SC , PlanTable(Events      ) , u , t ) ;
    setVariable     ( "EventType" , t  )                     ;
    SC . close      (                  )                     ;
  }                                                          ;
  SC   . remove     (                  )                     ;
  ////////////////////////////////////////////////////////////
  Alert             ( Done             )                     ;
}

void N::EventObject::JobCompleted(SUID u)
{
  EventManager  EM ( plan      )               ;
  SqlConnection SC ( plan->sql )               ;
  //////////////////////////////////////////////
  if ( SC . open          ( FunctionString ) ) {
    EM . Delete           ( SC , u           ) ;
    EM . DeleteScheduling ( SC , u           ) ;
    SC . close            (                  ) ;
  }                                            ;
  SC   . remove           (                  ) ;
  //////////////////////////////////////////////
  Alert                   ( Done             ) ;
}

void N::EventObject::ProcessDependency(void)
{
  SUID u = Value ( "UUID" ) . toULongLong ( )          ;
  if ( u <= 0 ) return                                 ;
  FoundationManager FM ( NULL , plan                 ) ;
  FM.HandleDependency  ( u , N::Groups::FinalTrigger ) ;
  Alert                ( Done                        ) ;
}

void N::EventObject::ConnectCalendar (QObject * calendar)
{
  nConnect ( this     , SIGNAL ( Update     ( )                        )   ,
             calendar , SLOT   ( startup    ( )                        ) ) ;
  nConnect ( this     , SIGNAL ( UpdateSpot (SUID,QDateTime,QDateTime) )   ,
             calendar , SLOT   ( UpdateSpot (SUID,QDateTime,QDateTime) ) ) ;
}

void N::EventObject::EmptyEditTool(void)
{
  QAction     * action = NULL                         ;
  QAction     * widget = NULL                         ;
  EditToolBar * etb    = NULL                         ;
  ComboBox    * combo  = NULL                         ;
  LineEdit    * line   = NULL                         ;
  int           aid    = EditToolBar::AttacheId       ;
  /////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 ) ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 ) ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 ) ;
  action = (QAction     *) plan -> Action ( aid + 4 ) ;
  widget = (QAction     *) plan -> Action ( aid + 5 ) ;
  /////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                     ;
  if ( IsNull ( line   ) ) return                     ;
  if ( IsNull ( combo  ) ) return                     ;
  if ( IsNull ( action ) ) return                     ;
  if ( IsNull ( widget ) ) return                     ;
  /////////////////////////////////////////////////////
  etb    -> setWindowTitle ( tr("Edit Tool Bar") )    ;
  etb    -> hide           (                     )    ;
  action -> setMenu        ( NULL                )    ;
  action -> setEnabled     ( false               )    ;
  widget -> setEnabled     ( false               )    ;
  /////////////////////////////////////////////////////
  QObject::disconnect      ( combo                    ,
                             SIGNAL(activated(int))   ,
                             NULL                     ,
                             NULL                   ) ;
  combo  -> blockSignals   ( true                )    ;
  combo  -> clear          (                     )    ;
  combo  -> blockSignals   ( false               )    ;
}

void N::EventObject::SetupExecution(void)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  QString name = Value ( "Name" ) . toString ( )                             ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  SUID          eu = 0                                                       ;
  SqlConnection SC ( plan -> sql )                                           ;
  if ( SC . open ( FunctionString ) )                                        {
    QString Q                                                                ;
    Q = SC . sql . SelectFrom                                                (
          "second"                                                           ,
          PlanTable(Groups)                                                  ,
          QString("where `first` = %1"
                   " and `t1` = %2"
                   " and `t2` = %3"
                   " and `relation` = %4"                                    )
          . arg ( ev                                                         )
          . arg ( Types::Schedule                                            )
          . arg ( Types::Execution                                           )
          . arg ( Groups::Subordination                                  ) ) ;
    if ( SC . Fetch ( Q ) ) eu = SC . Uuid ( 0 )                             ;
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QString tt = tr("Automation for %1").arg(name)                             ;
  combo -> setToolTip ( tt )                                                 ;
  etb   -> setToolTip ( tt )                                                 ;
  etb   -> show       (    )                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  action -> setIcon      ( QIcon(":/images/menu.png")  )                     ;
  action -> setToolTip   ( tr("Automation menu")       )                     ;
  action -> setEnabled   ( true                        )                     ;
  widget -> setEnabled   ( true                        )                     ;
  ////////////////////////////////////////////////////////////////////////////
  QObject::disconnect ( combo                                                ,
                        SIGNAL(activated(int))                               ,
                        NULL                                                 ,
                        NULL                                               ) ;
  combo  -> blockSignals ( true                        )                     ;
  combo  -> clear        (                             )                     ;
  combo  -> setMaxVisibleItems ( 30                    )                     ;
  combo  -> blockSignals ( false                       )                     ;
  combo  -> addItems     ( PlanTable(Executions)                             ,
                           Qt::DescendingOrder         )                     ;
  if ( eu > 0 ) (*combo) <= eu                                               ;
  nConnect ( combo , SIGNAL ( activated     (int) )                          ,
             this  , SLOT   ( ExecutionMenu (int) )                          ,
             Qt::DirectConnection                                          ) ;
  ////////////////////////////////////////////////////////////////////////////
  QMenu   * me = new QMenu ( NULL )                                          ;
  QAction * aa                                                               ;
  aa = me -> addAction ( tr("Complete automation") )                         ;
  nConnect ( aa   , SIGNAL ( triggered       ( ) )                           ,
             this , SLOT   ( EmptyEditTool   ( ) )                           ,
             Qt::DirectConnection                                          ) ;
  aa = me -> addAction ( tr("FOREX control scripts") )                       ;
  nConnect ( aa   , SIGNAL ( triggered       ( ) )                           ,
             this , SLOT   ( ForexAutomation ( ) )                           ,
             Qt::DirectConnection                                          ) ;
  aa = me -> addAction ( tr("Private automation scripts") )                  ;
  nConnect ( aa   , SIGNAL ( triggered         ( ) )                         ,
             this , SLOT   ( PrivateAutomation ( ) )                         ,
             Qt::DirectConnection                                          ) ;
  action -> setMenu   ( me                                                 ) ;
  ////////////////////////////////////////////////////////////////////////////
  etb   -> Relocation (    )                                                 ;
}

void N::EventObject::ExecutionMenu(int)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  SUID          eu = N::GetUuid ( combo )                                    ;
  SqlConnection SC ( plan -> sql )                                           ;
  ////////////////////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                                        {
    QString Q                                                                ;
    Q = SC . sql . DeleteFrom                                                (
          PlanTable(Groups)                                                  ,
          QString("where `first` = %1"
                   " and `t1` = %2"
                   " and `t2` = %3"
                   " and `relation` = %4"                                    )
          . arg  ( ev                                                        )
          . arg  ( Types::Schedule                                           )
          . arg  ( Types::Execution                                          )
          . arg  ( Groups::Subordination                                 ) ) ;
    SC . Query ( Q                                                         ) ;
    if ( eu > 0 )                                                            {
      Q = SC . sql . InsertInto                                              (
            PlanTable(Groups)                                                ,
            5                                                                ,
            "first"                                                          ,
            "second"                                                         ,
            "t1"                                                             ,
            "t2"                                                             ,
            "relation"                                                     ) ;
      SC . Prepare ( Q                                                     ) ;
      SC . Bind    ( "first"    , ev                                       ) ;
      SC . Bind    ( "second"   , eu                                       ) ;
      SC . Bind    ( "t1"       , Types::Schedule                          ) ;
      SC . Bind    ( "t2"       , Types::Execution                         ) ;
      SC . Bind    ( "relation" , Groups::Subordination                    ) ;
      SC . Exec    (                                                       ) ;
      Alert        ( Done                                                  ) ;
    }                                                                        ;
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  Alert ( Done )                                                             ;
}

QString N::EventObject::GetForexJs(void)
{
  SUID          u         = Value ( "UUID" ) . toULongLong ( ) ;
  QString       ForexJs = ""                                   ;
  SqlConnection SC ( plan -> sql )                             ;
  EventManager  EM ( plan        )                             ;
  if ( SC . open ( FunctionString ) )                          {
    QVariant V                                                 ;
    ////////////////////////////////////////////////////////////
    if ( EM . LoadVariable ( SC , u , "ForexJs" , V ) )        {
      ForexJs = V . toString ( )                               ;
    }                                                          ;
    SC.close()                                                 ;
  }                                                            ;
  SC.remove()                                                  ;
  return ForexJs                                               ;
}

bool N::EventObject::SaveForexJs(QString ForexJs)
{
  bool          correct = false                         ;
  SqlConnection SC ( plan -> sql )                      ;
  EventManager  EM ( plan        )                      ;
  ///////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                   {
    QString Q                                           ;
    QVariant V                                          ;
    SUID     u = Value ( "UUID" ) . toULongLong ( )     ;
    V = ForexJs                                         ;
    /////////////////////////////////////////////////////
    if ( EM . LoadVariable ( SC , u , "ForexJs" , V ) ) {
      Q = SC . sql . DeleteFrom                         (
            PlanTable(Groups)                           ,
            QString("where `first` = %1"
                     " and `t1` = %2"
                     " and `t2` = %3"
                     " and `relation` = %4"             )
            . arg  ( u                                  )
            . arg  ( Types::Schedule                    )
            . arg  ( Types::Execution                   )
            . arg  ( Groups::Subordination          ) ) ;
      SC . Query   ( Q                                ) ;
      correct = true                                    ;
    }                                                   ;
    SC.close()                                          ;
  }                                                     ;
  SC.remove()                                           ;
  ///////////////////////////////////////////////////////
  return correct                                        ;
}

void N::EventObject::ForexAutomation(void)
{
  QString filename = GetForexJs ( )          ;
  filename = QFileDialog::getOpenFileName    (
               gui                           ,
               tr("Forex automation script") ,
               filename                      ,
               tr("Javascript (*.js)")     ) ;
  if ( filename . length ( ) <= 0 ) return   ;
  ////////////////////////////////////////////
  bool correct = SaveForexJs ( filename )    ;
  if ( correct )                             {
    Alert ( Done  )                          ;
  } else                                     {
    Alert ( Error )                          ;
  }                                          ;
  ////////////////////////////////////////////
  EmptyEditTool ( )                          ;
}


QString N::EventObject::GetPrivateJs(void)
{
  SUID          u         = Value ( "UUID" ) . toULongLong ( ) ;
  QString       PrivateJs = ""                                 ;
  SqlConnection SC ( plan -> sql )                             ;
  EventManager  EM ( plan        )                             ;
  if ( SC . open ( FunctionString ) )                          {
    QVariant V                                                 ;
    ////////////////////////////////////////////////////////////
    if ( EM . LoadVariable ( SC , u , "PrivateJs" , V ) )      {
      PrivateJs = V . toString ( )                             ;
    }                                                          ;
    SC.close()                                                 ;
  }                                                            ;
  SC.remove()                                                  ;
  return PrivateJs                                             ;
}

bool N::EventObject::SavePrivateJs(QString PrivateJs)
{
  bool          correct = false                           ;
  SqlConnection SC ( plan -> sql )                        ;
  EventManager  EM ( plan        )                        ;
  /////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                     {
    QString Q                                             ;
    QVariant V                                            ;
    SUID     u = Value ( "UUID" ) . toULongLong ( )       ;
    V = PrivateJs                                         ;
    ///////////////////////////////////////////////////////
    if ( EM . LoadVariable ( SC , u , "PrivateJs" , V ) ) {
      Q = SC . sql . DeleteFrom                           (
            PlanTable(Groups)                             ,
            QString("where `first` = %1"
                     " and `t1` = %2"
                     " and `t2` = %3"
                     " and `relation` = %4"               )
            . arg  ( u                                    )
            . arg  ( Types::Schedule                      )
            . arg  ( Types::Execution                     )
            . arg  ( Groups::Subordination            ) ) ;
      SC . Query   ( Q                                  ) ;
      correct = true                                      ;
    }                                                     ;
    SC.close()                                            ;
  }                                                       ;
  SC.remove()                                             ;
  /////////////////////////////////////////////////////////
  return correct                                          ;
}

void N::EventObject::PrivateAutomation(void)
{
  QString filename = GetPrivateJs ( )          ;
  filename = QFileDialog::getOpenFileName      (
               gui                             ,
               tr("Private automation script") ,
               filename                        ,
               tr("Javascript (*.js)")       ) ;
  if ( filename . length ( ) <= 0 ) return     ;
  //////////////////////////////////////////////
  bool correct = SavePrivateJs ( filename )    ;
  if ( correct )                               {
    Alert ( Done  )                            ;
  } else                                       {
    Alert ( Error )                            ;
  }                                            ;
  //////////////////////////////////////////////
  EmptyEditTool ( )                            ;
}

void N::EventObject::SetupMusic(void)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  QString name = Value ( "Name" ) . toString ( )                             ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  SUID          eu = 0                                                       ;
  EventManager  EM ( plan        )                                           ;
  SqlConnection SC ( plan -> sql )                                           ;
  if ( SC . open ( FunctionString ) )                                        {
    QVariant V                                                               ;
    if ( EM . LoadVariable ( SC , ev ,"MusicUUID" , V ) )                    {
      eu = V . toULongLong ( )                                               ;
    }                                                                        ;
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QString tt = tr("Select music for %1").arg(name)                           ;
  combo -> setToolTip ( tt )                                                 ;
  etb   -> setToolTip ( tt )                                                 ;
  etb   -> show       (    )                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  action -> setIcon      ( QIcon(":/images/menu.png")  )                     ;
  action -> setToolTip   ( tr("Select music menu")      )                     ;
  action -> setEnabled   ( true                        )                     ;
  widget -> setEnabled   ( true                        )                     ;
  ////////////////////////////////////////////////////////////////////////////
  QObject::disconnect ( combo                                                ,
                        SIGNAL(activated(int))                               ,
                        NULL                                                 ,
                        NULL                                               ) ;
  combo  -> blockSignals ( true                        )                     ;
  combo  -> clear        (                             )                     ;
  combo  -> setMaxVisibleItems ( 30                    )                     ;
  combo  -> blockSignals ( false                       )                     ;
  combo  -> addItems     ( PlanTable(AudioFiles)                             ,
                           Qt::DescendingOrder         )                     ;
  if ( eu > 0 ) (*combo) <= eu                                               ;
  nConnect ( combo , SIGNAL ( activated (int) )                              ,
             this  , SLOT   ( MusicMenu (int) )                              ,
             Qt::DirectConnection                                          ) ;
  ////////////////////////////////////////////////////////////////////////////
  QMenu   * me = new QMenu ( NULL )                                          ;
  QAction * aa                                                               ;
  aa = me -> addAction ( tr("Complete music selection") )                    ;
  nConnect ( aa   , SIGNAL ( triggered       ( ) )                           ,
             this , SLOT   ( EmptyEditTool   ( ) )                           ,
             Qt::DirectConnection                                          ) ;
  action -> setMenu   ( me                                                 ) ;
  ////////////////////////////////////////////////////////////////////////////
  etb   -> Relocation (    )                                                 ;
}

void N::EventObject::MusicMenu(int index)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  SUID          eu = N::GetUuid ( combo )                                    ;
  EventManager  EM ( plan        )                                           ;
  SqlConnection SC ( plan -> sql )                                           ;
  ////////////////////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                                        {
    QVariant V                                                               ;
    V = eu                                                                   ;
    EM . SaveVariable ( SC , ev ,"MusicUUID" , V )                           ;
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  Alert ( Done )                                                             ;
}

void N::EventObject::SelectClip(void)
{
}

void N::EventObject::SetupAlbumGroup(void)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  QString name = Value ( "Name" ) . toString ( )                             ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  QString tt = tr("Select album group for %1").arg(name)                     ;
  combo -> setToolTip ( tt )                                                 ;
  etb   -> setToolTip ( tt )                                                 ;
  etb   -> show       (    )                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  action -> setIcon      ( QIcon(":/images/menu.png")  )                     ;
  action -> setToolTip   ( tr("Select album group")    )                     ;
  action -> setEnabled   ( true                        )                     ;
  widget -> setEnabled   ( true                        )                     ;
  ////////////////////////////////////////////////////////////////////////////
  QObject::disconnect ( combo                                                ,
                        SIGNAL(activated(int))                               ,
                        NULL                                                 ,
                        NULL                                               ) ;
  combo  -> blockSignals ( true                        )                     ;
  combo  -> clear        (                             )                     ;
  combo  -> setMaxVisibleItems ( 30                    )                     ;
  combo  -> blockSignals ( false                       )                     ;
  combo  -> addItems     ( PlanTable(VideoGroups)                            ,
                           Qt::DescendingOrder         )                     ;
  ////////////////////////////////////////////////////////////////////////////
  QMenu   * me = new QMenu ( NULL )                                          ;
  QAction * aa                                                               ;
  aa = me -> addAction ( tr("album group selected") )                        ;
  nConnect ( aa   , SIGNAL ( triggered        ( ) )                          ,
             this , SLOT   ( SetupVideoAlbums ( ) )                          ,
             Qt::DirectConnection                                          ) ;
  aa = me -> addAction ( tr("Complete album group selection") )              ;
  nConnect ( aa   , SIGNAL ( triggered        ( ) )                          ,
             this , SLOT   ( EmptyEditTool    ( ) )                          ,
             Qt::DirectConnection                                          ) ;
  action -> setMenu   ( me                                                 ) ;
  ////////////////////////////////////////////////////////////////////////////
  etb   -> Relocation (    )                                                 ;
}

void N::EventObject::SetupVideoAlbums(void)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  QString name = Value ( "Name" ) . toString ( )                             ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  SUID    ag = combo -> toUuid ( )                                           ;
  QString tt = tr("Select video album for %1").arg(name)                     ;
  combo -> setToolTip ( tt )                                                 ;
  etb   -> setToolTip ( tt )                                                 ;
  etb   -> show       (    )                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  action -> setIcon      ( QIcon(":/images/menu.png")  )                     ;
  action -> setToolTip   ( tr("Select video album")    )                     ;
  action -> setEnabled   ( true                        )                     ;
  widget -> setEnabled   ( true                        )                     ;
  ////////////////////////////////////////////////////////////////////////////
  QObject::disconnect ( combo                                                ,
                        SIGNAL(activated(int))                               ,
                        NULL                                                 ,
                        NULL                                               ) ;
  combo  -> blockSignals ( true                        )                     ;
  combo  -> clear        (                             )                     ;
  combo  -> setMaxVisibleItems ( 30                    )                     ;
  combo  -> blockSignals ( false                       )                     ;
  combo  -> addGroups    ( ag                                                ,
                           Types::Division                                   ,
                           Types::Album                                      ,
                           Groups::Subordination                             ,
                           Qt::DescendingOrder                             ) ;
  ////////////////////////////////////////////////////////////////////////////
  QMenu   * me = new QMenu ( NULL )                                          ;
  QAction * aa                                                               ;
  aa = me -> addAction ( tr("video album selected") )                        ;
  nConnect ( aa   , SIGNAL ( triggered        ( ) )                          ,
             this , SLOT   ( SetupVideoClips  ( ) )                          ,
             Qt::DirectConnection                                          ) ;
  aa = me -> addAction ( tr("Complete video album selection") )              ;
  nConnect ( aa   , SIGNAL ( triggered        ( ) )                          ,
             this , SLOT   ( EmptyEditTool    ( ) )                          ,
             Qt::DirectConnection                                          ) ;
  action -> setMenu   ( me                                                 ) ;
  ////////////////////////////////////////////////////////////////////////////
  etb   -> Relocation (    )                                                 ;
}

void N::EventObject::SetupVideoClips(void)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  QString name = Value ( "Name" ) . toString ( )                             ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  SUID    vc = 0                                                             ;
  SUID    vg = combo -> toUuid ( )                                           ;
  QString tt = tr("Select video clip for %1").arg(name)                      ;
  combo -> setToolTip ( tt )                                                 ;
  etb   -> setToolTip ( tt )                                                 ;
  etb   -> show       (    )                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  action -> setIcon      ( QIcon(":/images/menu.png")  )                     ;
  action -> setToolTip   ( tr("Select video clip")     )                     ;
  action -> setEnabled   ( true                        )                     ;
  widget -> setEnabled   ( true                        )                     ;
  ////////////////////////////////////////////////////////////////////////////
  QObject::disconnect ( combo                                                ,
                        SIGNAL(activated(int))                               ,
                        NULL                                                 ,
                        NULL                                               ) ;
  combo  -> blockSignals ( true                        )                     ;
  combo  -> clear        (                             )                     ;
  combo  -> setMaxVisibleItems ( 30                    )                     ;
  combo  -> blockSignals ( false                       )                     ;
  ////////////////////////////////////////////////////////////////////////////
  EventManager  EM ( plan        )                                           ;
  GroupItems    GI ( plan        )                                           ;
  SqlConnection SC ( plan -> sql )                                           ;
  if ( SC . open ( FunctionString ) )                                        {
    QVariant V                                                               ;
    UUIDs    U                                                               ;
    SUID     u                                                               ;
    if ( EM . LoadVariable ( SC , ev ,"VideoUUID" , V ) )                    {
      vc = V . toULongLong ( )                                               ;
    }                                                                        ;
    U = GI . Subordination                                                   (
          SC                                                                 ,
          vg                                                                 ,
          Types::Album                                                       ,
          Types::Video                                                       ,
          Groups::Subordination                                              ,
          SC . OrderByAsc ( "position" )                                   ) ;
    foreach ( u , U )                                                        {
      QStringList S                                                          ;
      if ( Manager :: UuidNames ( *plan , SC , u , S ) )                     {
        if ( S . count ( ) > 0 )                                             {
          combo -> addItem ( S [ 0 ] , u )                                   ;
        }                                                                    ;
      }                                                                      ;
    }                                                                        ;
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( vc > 0 ) (*combo) <= vc                                               ;
  nConnect ( combo , SIGNAL ( activated (int) )                              ,
             this  , SLOT   ( ClipMenu  (int) )                              ,
             Qt::DirectConnection                                          ) ;
  ////////////////////////////////////////////////////////////////////////////
  QMenu   * me = new QMenu ( NULL )                                          ;
  QAction * aa                                                               ;
  aa = me -> addAction ( tr("Complete video clip selection") )               ;
  nConnect ( aa   , SIGNAL ( triggered        ( ) )                          ,
             this , SLOT   ( EmptyEditTool    ( ) )                          ,
             Qt::DirectConnection                                          ) ;
  action -> setMenu   ( me                                                 ) ;
  ////////////////////////////////////////////////////////////////////////////
  etb   -> Relocation (    )                                                 ;
}

void N::EventObject::ClipMenu(int index)
{
  SUID ev = Value ( "UUID" ) . toULongLong ( )                               ;
  if ( ev <= 0 ) return                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  QAction     * action = NULL                                                ;
  QAction     * widget = NULL                                                ;
  EditToolBar * etb    = NULL                                                ;
  ComboBox    * combo  = NULL                                                ;
  LineEdit    * line   = NULL                                                ;
  int           aid    = EditToolBar::AttacheId                              ;
  ////////////////////////////////////////////////////////////////////////////
  etb    = (EditToolBar *) plan -> Widget ( aid + 1 )                        ;
  line   = (LineEdit    *) plan -> Widget ( aid + 2 )                        ;
  combo  = (ComboBox    *) plan -> Widget ( aid + 3 )                        ;
  action = (QAction     *) plan -> Action ( aid + 4 )                        ;
  widget = (QAction     *) plan -> Action ( aid + 5 )                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( IsNull ( etb    ) ) return                                            ;
  if ( IsNull ( line   ) ) return                                            ;
  if ( IsNull ( combo  ) ) return                                            ;
  if ( IsNull ( action ) ) return                                            ;
  if ( IsNull ( widget ) ) return                                            ;
  ////////////////////////////////////////////////////////////////////////////
  SUID          eu = N::GetUuid           ( combo )                          ;
  QString       nn = combo -> currentText (       )                          ;
  EventManager  EM ( plan        )                                           ;
  SqlConnection SC ( plan -> sql )                                           ;
  ////////////////////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                                        {
    QVariant V                                                               ;
    V = eu                                                                   ;
    SC . assureName   ( PlanTable(Names) , ev , plan -> LanguageId , nn    ) ;
    EM . SaveVariable ( SC , ev ,"VideoUUID" , V                           ) ;
    SC . close  ( )                                                          ;
  }                                                                          ;
  SC   . remove ( )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  Alert ( Done )                                                             ;
}

QString N::EventObject::GetBackup(void)
{
  SUID          u         = Value ( "UUID" ) . toULongLong ( ) ;
  QString       BackupINI = ""                                 ;
  SqlConnection SC ( plan -> sql )                             ;
  EventManager  EM ( plan        )                             ;
  if ( SC . open ( FunctionString ) )                          {
    QVariant V                                                 ;
    ////////////////////////////////////////////////////////////
    if ( EM . LoadVariable ( SC , u , "BackupINI" , V ) )      {
      BackupINI = V . toString ( )                             ;
    }                                                          ;
    SC.close()                                                 ;
  }                                                            ;
  SC.remove()                                                  ;
  return BackupINI                                             ;
}

bool N::EventObject::SaveBackup(QString BackupINI)
{
  bool          correct = false                           ;
  SqlConnection SC ( plan -> sql )                        ;
  EventManager  EM ( plan        )                        ;
  /////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                     {
    QVariant V                                            ;
    SUID     u = Value ( "UUID" ) . toULongLong ( )       ;
    V = BackupINI                                         ;
    ///////////////////////////////////////////////////////
    if ( EM . SaveVariable ( SC , u , "BackupINI" , V ) ) {
      correct = true                                      ;
    }                                                     ;
    SC.close()                                            ;
  }                                                       ;
  SC.remove()                                             ;
  /////////////////////////////////////////////////////////
  return correct                                          ;
}

bool N::EventObject::BrowseBackup(void)
{
  QString filename = GetBackup ( )               ;
  filename = QFileDialog::getOpenFileName        (
               gui                               ,
               tr("Backup plan")                 ,
               filename                          ,
               tr("Backup plan (*.ini)")       ) ;
  if ( filename . length ( ) <= 0 ) return false ;
  bool correct = SaveBackup ( filename )         ;
  if ( correct )                                 {
    Alert ( Done  )                              ;
  } else                                         {
    Alert ( Error )                              ;
  }                                              ;
  return correct                                 ;
}

void N::EventObject::EditBackup(void)
{
  QString filename = GetBackup ( )            ;
  if ( filename . length ( ) <= 0 )           {
    if ( BrowseBackup ( ) )                   {
      filename = GetBackup ( )                ;
    }                                         ;
  }                                           ;
  /////////////////////////////////////////////
  if ( filename . length ( ) <= 0 )           {
    Alert ( Error )                           ;
    return                                    ;
  }                                           ;
  /////////////////////////////////////////////
  SUID u = Value ( "UUID" ) . toULongLong ( ) ;
  emit EditEvent  ( 41403 , u )               ;
  emit OpenBackup ( filename  )               ;
}

void N::EventObject::AdjustMenu(MenuManager & mm,QMenu * menu)
{
  int status = DurationStatus ( )                    ;
  switch ( status )                                  {
    case -1                                          :
      mm . add ( menu , 401 , tr("Job completed" ) ) ;
      mm . add ( menu , 402 , tr("Job finish now") ) ;
      mm . add ( menu , 404 , tr("Move job now"  ) ) ;
    break                                            ;
    case  0                                          :
      mm . add ( menu , 403 , tr("Job start now" ) ) ;
      mm . add ( menu , 402 , tr("Job finish now") ) ;
    break                                            ;
    case  1                                          :
      mm . add ( menu , 403 , tr("Job start now" ) ) ;
      mm . add ( menu , 404 , tr("Move job now"  ) ) ;
    break                                            ;
  }                                                  ;
}

void N::EventObject::TypesMenu(MenuManager & mm,QMenu * menu)
{
  int            etype  = Value ( "EventType" ) . toInt (      ) ;
  int            status = Value ( "Status"    ) . toInt (      ) ;
  int            adjust = Value ( "Adjust"    ) . toInt (      ) ;
  QActionGroup * ag = new QActionGroup                  ( this ) ;
  QAction      * aa                                              ;
  ////////////////////////////////////////////////////////////////
  for (int i=N::None;i<N::MaxEventTypeNumber;i++)                {
    aa  = mm . add ( menu                                        ,
                     69101 + i                                   ,
                     TypeNames [ i ]                             ,
                      true                                       ,
                     ( i == etype )                            ) ;
    ag -> addAction ( aa )                                       ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  mm . setGroup ( 0 , ag )                                       ;
}

void N::EventObject::AttacheMenu(MenuManager & mm,QMenu * menu)
{
  int etype = Value ( "EventType" ) . toInt ( )                              ;
  mm . add          ( menu , 40001 , tr("Event note" ) )                     ;
  mm . add          ( menu , 40002 , tr("Event tasks") )                     ;
  switch ( etype )                                                           {
    case N::Notify                                                           :
    break                                                                    ;
    case N::Period                                                           :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
    break                                                                    ;
    case N::Record                                                           :
    break                                                                    ;
    case N::Meeting                                                          :
      mm . add          ( menu , 40003 , tr("Decisions"  ) )                 ;
      mm . addSeparator ( menu                             )                 ;
      mm . add          ( menu , 40401 , tr("Edit meeting details") )        ;
    break                                                                    ;
    case N::Automation                                                       :
      mm . add          ( menu , 40003 , tr("Decisions"  ) )                 ;
      mm . addSeparator ( menu                             )                 ;
      mm . add          ( menu , 40501 , tr("Edit automation settings") )    ;
    break                                                                    ;
    case N::Operation                                                        :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
    break                                                                    ;
    case N::Sync                                                             :
      mm . add          ( menu , 40003 , tr("Decisions")     )               ;
      mm . addSeparator ( menu                               )               ;
      mm . add ( menu , 40701 , tr("Edit file sync details") )               ;
    break                                                                    ;
    case N::Download                                                         :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                             )                 ;
      mm . add ( menu , 40801 , tr("Download details") )                     ;
    break                                                                    ;
    case N::Upload                                                           :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                             )                 ;
      mm . add ( menu , 40901 , tr("Upload details") )                       ;
    break                                                                    ;
    case N::Audio                                                            :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                             )                 ;
      mm . add ( menu , 41001 , tr("Assign music") )                         ;
    break                                                                    ;
    case N::Video                                                            :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                             )                 ;
      mm . add ( menu , 41101 , tr("Schedule video clip") )                  ;
      mm . add ( menu , 41102 , tr("Select video clip")   )                  ;
    break                                                                    ;
    case N::TV                                                               :
    break                                                                    ;
    case N::Programming                                                      :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
    break                                                                    ;
    case N::Backup                                                           :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                    )                          ;
      mm . add ( menu , 41401 , tr("Backup plan") )                          ;
      mm . add ( menu , 41402 , tr("Edit Backup plan") )                     ;
    break                                                                    ;
    case N::FileUpdate                                                       :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                    )                          ;
      mm . add ( menu , 41501 , tr("File update plan") )                     ;
    break                                                                    ;
    case N::Cooking                                                          :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                )                              ;
      mm . add ( menu , 41601 , tr("Recipts") )                              ;
    break                                                                    ;
    case N::Sleep                                                            :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
    break                                                                    ;
    case N::Housework                                                        :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
    break                                                                    ;
    case N::Shopping                                                         :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                      )                        ;
      mm . add ( menu , 41901 , tr("Shopping list") )                        ;
    break                                                                    ;
    case N::Communication                                                    :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
      mm . addSeparator ( menu                              )                ;
      mm . add ( menu , 42001 , tr("Communication profile") )                ;
    break                                                                    ;
    case N::Finish                                                           :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
    break                                                                    ;
    case N::Obsolete                                                         :
    break                                                                    ;
    case N::Others                                                           :
    break                                                                    ;
    case N::ForexTrade                                                       :
      mm . add          ( menu , 40003 , tr("Decisions"   ) )                ;
    break                                                                    ;
    default                                                                  :
    break                                                                    ;
  }                                                                          ;
}

bool N::EventObject::AdjustProcessor(MenuManager & mm,QAction * aa)
{
  SUID      u  = Value ( "UUID"  ) . toULongLong ( ) ;
  QDateTime st = Value ( "Start" ) . toDateTime  ( ) ;
  QDateTime et = Value ( "End"   ) . toDateTime  ( ) ;
  QDateTime t1 = st                                  ;
  QDateTime t2 = et                                  ;
  qint64    dt                                       ;
  VarArgs   args                                     ;
  ////////////////////////////////////////////////////
  if ( st > et )                                     {
    t1 = et                                          ;
    t2 = st                                          ;
  }                                                  ;
  ////////////////////////////////////////////////////
  switch ( mm [ aa ] )                               {
    case 401                                         : // Job completed
      args << u                                      ;
      start           ( 10012 , args )               ;
    return true                                      ;
    case 402                                         : // Job finish now
      t2 = nTimeNow                                  ;
      emit UpdateSpot ( u , t1 , t2  )               ;
    return true                                      ;
    case 403                                         : // Job start now
      t1 = nTimeNow                                  ;
      emit UpdateSpot ( u , t1 , t2  )               ;
    return true                                      ;
    case 404                                         : // Move job now
      dt = t1 . msecsTo  ( t2   )                    ;
      t1 = nTimeNow                                  ;
      t1 = t1 . addMSecs ( 5000 )                    ;
      t2 = t1                                        ;
      t2 = t2 . addMSecs ( dt   )                    ;
      emit UpdateSpot ( u , t1 , t2  )               ;
    return true                                      ;
    case 411                                         : // Process dependency
      start ( 10018 )                                ;
    return true                                      ;
  }                                                  ;
  ////////////////////////////////////////////////////
  return false                                       ;
}

bool N::EventObject::TypesProcessor(MenuManager & mm,QAction * aa)
{
  if ( IsNull(aa)        ) return false                ;
  int etype = mm [ aa ]                                ;
  etype -= 69101                                       ;
  if ( etype < 0         ) return false                ;
  if ( etype > N::Others ) return false                ;
  int otype  = Value ( "EventType" ) . toInt       ( ) ;
  if ( otype == etype    ) return false                ;
  //////////////////////////////////////////////////////
  SUID u     = Value ( "UUID"      ) . toULongLong ( ) ;
  if ( u     <= 0        ) return false                ;
  //////////////////////////////////////////////////////
  VarArgs args                                         ;
  args << u                                            ;
  args << etype                                        ;
  start ( 10011 , args )                               ;
  //////////////////////////////////////////////////////
  return true                                          ;
}

bool N::EventObject::AttacheProcessor(MenuManager & mm,QAction * aa)
{
  SUID u  = Value ( "UUID" ) . toULongLong ( ) ;
  int  id = mm [ aa ]                          ;
  switch ( id )                                {
    case 40001                                 : // Event note
    case 40002                                 : // Event tasks
    case 40003                                 : // Decisions
    case 40401                                 : // Edit meeting details
    case 40701                                 : // Edit file sync details
    case 40801                                 : // Download details
    case 40901                                 : // Upload details
    case 41501                                 : // File update plan
    case 41601                                 : // Recipts
    case 41901                                 : // Shopping list
    case 42001                                 : // Communication profile
      emit EditEvent ( id , u )                ;
    return true                                ;
    case 41401                                 :
      BrowseBackup   (        )                ;
    return true                                ;
    case 41402                                 :
      EditBackup     (        )                ;
    return true                                ;
    case 41403                                 : // Actually, this came from 41402
    return true                                ;
    case 40501                                 : // Setup Execution
      start          ( 10014  )                ;
    return true                                ;
    case 41001                                 : // Assign music
      start          ( 10015  )                ;
    return true                                ;
    case 41101                                 : // Schedule video clip
      start          ( 10016  )                ;
    return true                                ;
    case 41102                                 : // Select video clip
      start          ( 10017  )                ;
    return true                                ;
  }                                            ;
  return false                                 ;
}

bool N::EventObject::Menu    (
       QWidget      * widget ,
       QPointF        pos    ,
       ControlPoint & From   ,
       ControlPoint & To     )
{
  ControlPoint At                                                            ;
  if ( ! Collide ( From , To , At ) ) return false                           ;
  setCursor ( Qt::ArrowCursor )                                              ;
  ////////////////////////////////////////////////////////////////////////////
  MenuManager     mm ( widget )                                              ;
  QMenu         * ma                                                         ;
  QMenu         * mt                                                         ;
  QMenu         * mx                                                         ;
  QAction       * aa                                                         ;
  QLineEdit     * ne    = new QLineEdit     ( NULL )                         ;
  QDateTimeEdit * ST    = new QDateTimeEdit ( NULL )                         ;
  QDateTimeEdit * ET    = new QDateTimeEdit ( NULL )                         ;
  SUID            u     = Value ( "UUID"         ) . toULongLong ( )         ;
  QDateTime       st    = Value ( "Start"        ) . toDateTime  ( )         ;
  QDateTime       et    = Value ( "End"          ) . toDateTime  ( )         ;
  QString         nn    = Value ( "Name"         ) . toString    ( )         ;
  bool            panel = Value ( "ControlPanel" ) . toBool      ( )         ;
  QVariants       vargs                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "Name" ) )                                     {
    QString tt = tr("Event name")                                            ;
    ne -> setText            ( nn                    )                       ;
    ne -> setToolTip         ( tt                    )                       ;
    ne -> setCursorPosition  ( 0                     )                       ;
    ne -> setPlaceholderText ( tt                    )                       ;
    mm  . add                ( 4412001 , ne          )                       ;
    mm  . addSeparator       (                       )                       ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  mm  . add                  ( 101 , tr("Edit")      )                       ;
  mm  . addSeparator         (                       )                       ;
  ////////////////////////////////////////////////////////////////////////////
  ma = mm . addMenu          ( tr("Adjustments" )    )                       ;
  mt = mm . addMenu          ( tr("Event types" )    )                       ;
  mx = mm . addMenu          ( tr("Attachements")    )                       ;
  ////////////////////////////////////////////////////////////////////////////
  AdjustMenu                 ( mm , ma               )                       ;
  TypesMenu                  ( mm , mt               )                       ;
  AttacheMenu                ( mm , mx               )                       ;
  ////////////////////////////////////////////////////////////////////////////
  ST -> setToolTip           ( tr("Start" )          )                       ;
  ST -> setToolTip           ( tr("Finish")          )                       ;
  ST -> setDisplayFormat     ( "yyyy/MM/dd hh:mm:ss" )                       ;
  ET -> setDisplayFormat     ( "yyyy/MM/dd hh:mm:ss" )                       ;
  ST -> setCalendarPopup     ( true                  )                       ;
  ET -> setCalendarPopup     ( true                  )                       ;
  ST -> setDateTime          ( st                    )                       ;
  ET -> setDateTime          ( et                    )                       ;
  ////////////////////////////////////////////////////////////////////////////
  mm . addSeparator          ( ma                    )                       ;
  mm . add                   ( ma , 4412002 , ST     )                       ;
  mm . add                   ( ma , 4412003 , ET     )                       ;
  mm . addSeparator          ( ma                    )                       ;
  mm . add                   ( ma , 411 , tr("Process dependency") )         ;
  ////////////////////////////////////////////////////////////////////////////
  CallDynamic                ( "AttacheEvent" , mm . menu , gui , vargs )    ;
  CallToMenu                 ( mm , NULL , false                        )    ;
  mm  . setFont              ( plan                  )                       ;
  ////////////////////////////////////////////////////////////////////////////
  aa = mm . exec             (                       )                       ;
  if ( IsNull(aa) )                                                          {
    QString   nx  = ne -> text     ( )                                       ;
    QDateTime t1  = ST -> dateTime ( )                                       ;
    QDateTime t2  = ET -> dateTime ( )                                       ;
    QDateTime ste = t1                                                       ;
    QDateTime ete = t2                                                       ;
    if ( ste > ete )                                                         {
      ste = t2                                                               ;
      ete = t1                                                               ;
    }                                                                        ;
    if ( nx != nn )                                                          {
      VarArgs args                                                           ;
      args << u                                                              ;
      args << nx                                                             ;
      start ( 10013 , args )                                                 ;
    }                                                                        ;
    if ( ( ste != st ) || ( ete != et ) )                                    {
      emit UpdateSpot ( u , ste , ete )                                      ;
    }                                                                        ;
    return true                                                              ;
  }                                                                          ;
  if ( AdjustProcessor  ( mm , aa        ) ) return true                     ;
  if ( TypesProcessor   ( mm , aa        ) ) return true                     ;
  if ( AttacheProcessor ( mm , aa        ) ) return true                     ;
  if ( 0 != CallToMenu  ( mm , aa , true ) ) return true                     ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                                       {
    case  101                                                                :
      if ( NotNull ( calendar ) )                                            {
        emit EditEvent ( calendar , u , st , et , panel )                    ;
      } else                                                                 {
        emit EditEvent ( this     , u , st , et , panel )                    ;
      }                                                                      ;
    break                                                                    ;
  }                                                                          ;
  return true                                                                ;
}

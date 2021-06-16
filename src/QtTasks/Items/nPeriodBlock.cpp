#include <qttasks.h>

N::PeriodBlock:: PeriodBlock ( QObject * parent , Plan * p )
               : SceneWidget (           parent ,        p )
{
  Configure ( ) ;
}

N::PeriodBlock:: PeriodBlock ( QObject * parent , Plan * p , SceneDestructor * des )
               : SceneWidget (           parent ,        p ,                   des )
{
  Configure ( ) ;
}

N::PeriodBlock::~PeriodBlock (void)
{
}

void N::PeriodBlock::Configure(void)
{
  int          flag = Qt::AlignCenter                  ;
  ControlPoint color                                   ;
  QColor       black    ( 192 ,  192 , 224 , 192     ) ;
  color  = QColor       ( 192 ,  192 , 192 , 192     ) ;
  addColor              (   0 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   1 , 0.02    ) ;
  addColor              (   1 , color                ) ;
  color  = ControlPoint (   1 ,    0 ,   0 , 0.02    ) ;
  addColor              (   2 , color                ) ;
  color  = ControlPoint (   0 ,  0.6 ,   0 , 0.02    ) ;
  addColor              (   3 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   0 , 0.25    ) ;
  addColor              (   4 , color                ) ;
  color  = ControlPoint ( 0.7 ,  0.7 , 0.7 , 0.20    ) ;
  addColor              (   5 , color                ) ;
  color  = ControlPoint ( 0.7 ,  0.7 , 0.7 , 0.20    ) ;
  addColor              (   6 , color                ) ;
  color  = ControlPoint ( 0.7 ,  0.7 , 0.7 , 0.20    ) ;
  addColor              (   7 , color                ) ;
  //////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"  , "PeriodBlock"    ) ;
  setVariable           ( "Type"  , "PeriodBlock"    ) ;
  setVariable           ( "Focus" , false            ) ;
  setVariable           ( "Hold"  , false            ) ;
  setVariable           ( "Menu"  , true             ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "GridColor"      , 0       ) ;
  setVariable           ( "BackColor"      , 2       ) ;
  setVariable           ( "FrontColor"     , 2       ) ;
  setVariable           ( "SideColor"      , 3       ) ;
  setVariable           ( "BorderColor"    , 5       ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Front"          , true    ) ;
  setVariable           ( "Back"           , true    ) ;
  setVariable           ( "Side"           , true    ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Length"         , 40      ) ;
  setVariable           ( "FontSize"       , 32      ) ;
  setVariable           ( "TextColor"      , black   ) ;
  setVariable           ( "TextFlags"      , flag    ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Generate"       , false   ) ;
  setVariable           ( "Index"          , 6       ) ;
  setVariable           ( "Baseline"       , 0.0     ) ;
}

bool N::PeriodBlock::Within(QPointF & p)
{
  if ( p . x ( ) < minimum . x ) return false           ;
  if ( p . x ( ) > maximum . x ) return false           ;
  double baseline = Value ( "Baseline" ) . toDouble ( ) ;
  double fontsize = Value ( "FontSize" ) . toDouble ( ) ;
  double y1       = baseline - ( fontsize / 2 )         ;
  double y2       = y1       +   fontsize               ;
  if ( p . y ( ) < y1          ) return false           ;
  if ( p . y ( ) > y2          ) return false           ;
  return true                                           ;
}

bool N::PeriodBlock::Spot  (
       ControlPoint & From ,
       ControlPoint & To   ,
       ControlPoint & At   )
{
  if ( ! xymSpot ( From , To , At ) ) return false      ;
  if ( At . x < minimum . x ) return false              ;
  if ( At . x > maximum . x ) return false              ;
  double baseline = Value ( "Baseline" ) . toDouble ( ) ;
  double fontsize = Value ( "FontSize" ) . toDouble ( ) ;
  double y1       = baseline - ( fontsize / 2 )         ;
  double y2       = y1       +   fontsize               ;
  if ( At . y < y1          ) return false              ;
  if ( At . y > y2          ) return false              ;
  return true                                           ;
}

QRect N::PeriodBlock::TextRegion(QString text,int H)
{
  QFont F = plan -> fonts [ Fonts::Editor ] . toQFont ( ) ;
  F . setPixelSize ( H )                                  ;
  /////////////////////////////////////////////////////////
  QFontMetrics FM ( F )                                   ;
  return FM . boundingRect ( text )                       ;
}

void N::PeriodBlock::setText(QString description)
{
  if ( description . length ( ) <= 0 ) return                 ;
  setVariable ( "Name" , description )                        ;
  /////////////////////////////////////////////////////////////
  int     L = Value ( "Length"   ) . toInt    ( )             ;
  int     f = Value ( "FontSize" ) . toInt    ( )             ;
  QString n = description                                     ;
  int     h                                                   ;
  int     w                                                   ;
  QRect   r                                                   ;
  QRectF  t                                                   ;
  double  b = Value ( "Baseline" ) . toDouble ( )             ;
  double  v                                                   ;
  double  m                                                   ;
  /////////////////////////////////////////////////////////////
  if ( n . length ( ) > L )                                   {
    n = n . left ( L     )                                    ;
    n . append   ( "..." )                                    ;
  }                                                           ;
  r = TextRegion ( n , f )                                    ;
  h = r . height (       )                                    ;
  h = MipSize    ( h     )                                    ;
  w = r . width  (       )                                    ;
  w = MipSize    ( w     )                                    ;
  /////////////////////////////////////////////////////////////
  v  =   minimum . y + b                                      ;
  v -= ( h / 2 )                                              ;
  m  = ( minimum . x + maximum . x ) / 2                      ;
  m -= ( w / 2 )                                              ;
  /////////////////////////////////////////////////////////////
  t . setTop    ( v )                                         ;
  t . setLeft   ( m )                                         ;
  t . setWidth  ( w )                                         ;
  t . setHeight ( h )                                         ;
  /////////////////////////////////////////////////////////////
  SceneTexture * tz                                           ;
  QSize          s              ( w , h                     ) ;
  QImage       * O = new QImage ( s , QImage::Format_ARGB32 ) ;
  tz        = new SceneTexture  ( destructor                ) ;
  tz -> node      = 101                                       ;
  tz -> create                  ( O , true , false          ) ;
  if ( textures . contains ( 101 ) )                          {
    SceneTexture * dxt = textures [ 101 ]                     ;
    textures . remove ( 101 )                                 ;
    delete dxt                                                ;
  }                                                           ;
  textures [ 101 ]  = tz                                      ;
  tz -> original -> fill        ( 0                         ) ;
  /////////////////////////////////////////////////////////////
  QColor c (   0 ,   0 , 0 , 255 )                            ;
  QRectF z (   0 ,   0 , w ,   h )                            ;
  QFont  F = plan -> fonts [ Fonts::Editor ] . toQFont ( )    ;
  int    flag = Qt::AlignVCenter | Qt::AlignHCenter           ;
  F . setPixelSize ( h - 2 )                                  ;
  if ( Variables . contains ( "TextColor" ) )                 {
    c = Variables [ "TextColor" ] . value <QColor> ( )        ;
  }                                                           ;
  if ( Variables . contains ( "TextFlags" ) )                 {
    flag = Variables [ "TextFlags" ] . toInt ( )              ;
  }                                                           ;
  textures [ 101 ] -> drawText ( c , F , z , flag , n )       ;
  /////////////////////////////////////////////////////////////
  setVariable ( "Region"   , t )                              ;
}

void N::PeriodBlock::renderText(void)
{
  if ( ! Variables . contains ( "Region" ) ) return  ;
  if ( ! textures  . contains ( 101      ) ) return  ;
  double z = minimum . z + 0.5                       ;
  QRectF r = Variables [ "Region" ] . toRectF ( )    ;
  QRectF w = r                                       ;
  bool   texture = ( bindTexture  ( 101 ) >= 0 )     ;
  if ( w . width ( ) > length . x )                  {
    QPointF c = w      . center ( )                  ;
    double  f = length . x                           ;
    double  h                                        ;
    f /= w . width  ( )                              ;
    h  = w . height ( )                              ;
    h *= f                                           ;
    w . setTop    ( c . y ( ) - ( h          / 2 ) ) ;
    w . setLeft   ( c . x ( ) - ( length . x / 2 ) ) ;
    w . setWidth  ( length . x )                     ;
    w . setHeight ( h          )                     ;
  }                                                  ;
  if ( texture ) TextureRect    ( w ,z )             ;
  if ( texture ) releaseTexture ( 101  )             ;
}

void N::PeriodBlock::renderBox(void)
{
  int x = Value ( "Index" ) . toInt ( )            ;
  QtGL::PushMatrix       (                       ) ;
  QtGL::Disable          ( GL_CULL_FACE          ) ;
  QtGL::Disable          ( GL_DEPTH_TEST         ) ;
  QtGL::Disable          ( GL_LINE_SMOOTH        ) ;
  QtGL::Disable          ( GL_POLYGON_SMOOTH     ) ;
  FeatureCube            ( minimum , maximum     ) ;
  renderText             (                       ) ;
  QtGL::Enable           ( GL_CULL_FACE          ) ;
  QtGL::Enable           ( GL_DEPTH_TEST         ) ;
  QtGL::Enable           ( GL_LINE_SMOOTH        ) ;
  QtGL::Enable           ( GL_POLYGON_SMOOTH     ) ;
  colors [ x ] . Color3d (                       ) ;
  LineWidth              ( "BorderWidth" , 0.75f ) ;
  SceneObject::renderBox (                       ) ;
  QtGL::PopMatrix        (                       ) ;
}

void N::PeriodBlock::ChangeColor(QWidget * widget)
{
  int          front = Value ( "FrontColor" ) . toInt ( )    ;
  QColor       c     = colors [ front ]       . Color ( )    ;
  ControlPoint p                                             ;
  c                  = QColorDialog::getColor ( c , widget ) ;
  p                  = c                                     ;
  p . t              = colors [ front ] . t                  ;
  colors [ front ]   = p                                     ;
}

void N::PeriodBlock::TextColor(QWidget * widget)
{
  QString n = Value ( "Name"      ) . toString       ( ) ;
  QColor  c = Value ( "TextColor" ) . value <QColor> ( ) ;
  QColor  r = c                                          ;
  r = QColorDialog::getColor ( r , widget )              ;
  r . setAlphaF ( c . alphaF ( )  )                      ;
  setVariable   ( "TextColor" , r )                      ;
  setText       ( n               )                      ;
}

bool N::PeriodBlock::Menu    (
       QWidget      * widget ,
       QPointF        pos    ,
       ControlPoint & From   ,
       ControlPoint & To     )
{
  ControlPoint At                                                            ;
  if ( ! Collide ( From , To , At ) ) return false                           ;
  ////////////////////////////////////////////////////////////////////////////
  MenuManager     mm ( widget )                                              ;
  QAction       * aa                                                         ;
  QString         nn  = Value ( "Name"      ) . toString   ( )               ;
  QDateTime       st  = Value ( "DrawStart" ) . toDateTime ( )               ;
  QDateTime       et  = Value ( "DrawEnd"   ) . toDateTime ( )               ;
  QLineEdit     * le  = new QLineEdit     ( NULL )                           ;
  QDateTimeEdit * stx = NULL                                                 ;
  QDateTimeEdit * etx = NULL                                                 ;
  bool            gen = Value ( "Generate" ) . toBool ( )                    ;
  VarArgs         vargs                                                      ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ! gen )                                                               {
    stx = new QDateTimeEdit ( NULL )                                         ;
    etx = new QDateTimeEdit ( NULL )                                         ;
  }                                                                          ;
  le  -> setText            ( nn                    )                        ;
  if ( ! gen )                                                               {
    stx -> setDisplayFormat ( "yyyy/MM/dd hh:mm:ss" )                        ;
    etx -> setDisplayFormat ( "yyyy/MM/dd hh:mm:ss" )                        ;
    stx -> setDateTime      ( st                    )                        ;
    etx -> setDateTime      ( et                    )                        ;
  }                                                                          ;
  mm   . add                ( 4412001 , le          )                        ;
  if ( ! gen )                                                               {
    mm . add                ( 4412002 , stx         )                        ;
    mm . add                ( 4412003 , etx         )                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ! gen )                                                               {
    mm  . add     ( 101 , tr("Delete")       )                               ;
  }                                                                          ;
  mm    . add     ( 102 , tr("Surface color") )                              ;
  mm    . add     ( 103 , tr("Text color") )                                 ;
  ////////////////////////////////////////////////////////////////////////////
  CallDynamic     ( "AttachePeriod" , mm . menu , gui , vargs )              ;
  CallToMenu      ( mm , NULL , false                         )              ;
  mm    . setFont ( plan                     )                               ;
  aa = mm . exec  (                          )                               ;
  ////////////////////////////////////////////////////////////////////////////
  QString   nt = le  -> text     ( )                                         ;
  QDateTime sc                                                               ;
  QDateTime ec                                                               ;
  bool      cc = false                                                       ;
  if ( ! gen )                                                               {
    sc = stx -> dateTime ( )                                                 ;
    ec = etx -> dateTime ( )                                                 ;
  }                                                                          ;
  if ( nt != nn ) setText ( nt )                                             ;
  if ( ! gen )                                                               {
    if ( sc != st ) cc = true                                                ;
    if ( ec != et ) cc = true                                                ;
    setVariable ( "DrawStart" , sc )                                         ;
    setVariable ( "DrawEnd"   , ec )                                         ;
  }                                                                          ;
  if ( IsNull ( aa ) )                                                       {
    if ( cc ) emit Changed ( node )                                          ;
    return true                                                              ;
  }                                                                          ;
  if ( 0 != CallToMenu  ( mm , aa , true ) ) return true                     ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                                       {
    case  101                                                                :
      emit Close  ( node   )                                                 ;
    break                                                                    ;
    case  102                                                                :
      ChangeColor ( widget )                                                 ;
    break                                                                    ;
    case  103                                                                :
      TextColor   ( widget )                                                 ;
    break                                                                    ;
    default                                                                  :
      if ( cc ) emit Changed ( node )                                        ;
    break                                                                    ;
  }                                                                          ;
  return true                                                                ;
}

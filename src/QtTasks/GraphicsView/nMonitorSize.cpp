#include <qttasks.h>


N::MonitorSize:: MonitorSize (QWidget * parent,Plan * p)
               : VcfView     (          parent,       p)
{
  Configure ( ) ;
}

N::MonitorSize::~MonitorSize(void)
{
}

void N::MonitorSize::Configure(void)
{
  setWindowTitle   ( tr("Monitor calibration") )             ;
  setScene         ( Scene                     )             ;
  setTransform     ( Transform                 )             ;
  setMouseTracking ( true                      )             ;
  ScreenSize  = new VcfScreenSize ( this , NULL , plan )     ;
  ScreenSize -> Options = &Options                           ;
  ScreenSize -> monitor = QImage(":/images/calibration.png") ;
  ScreenSize -> screen  = &screen                            ;
  ScreenSize -> font    = font()                             ;
  scene ( )  -> addItem (ScreenSize)                         ;
  ScreenSize -> Attribute ()                                 ;
  if ( plan  -> Booleans [ "Desktop" ] )                     {
  } else
  if ( plan  -> Booleans [ "Pad"     ] )                     {
  } else
  if ( plan  -> Booleans [ "Phone"   ] )                     {
  }                                                          ;
}

bool N::MonitorSize::FocusIn(void)
{
  nKickOut     ( IsNull(plan) , false           ) ;
  AssignAction ( Label        , windowTitle ( ) ) ;
  LinkAction   ( GoUp         , Up          ( ) ) ;
  LinkAction   ( GoDown       , Down        ( ) ) ;
  LinkAction   ( Previous     , Left        ( ) ) ;
  LinkAction   ( Next         , Right       ( ) ) ;
  LinkAction   ( GoEnd        , Finalize    ( ) ) ;
  return true                                     ;
}

bool N::MonitorSize::FocusOut(void)
{
  return true ;
}

bool N::MonitorSize::Relocation(void)
{
  QWidget * vp = viewport()          ;
  if (IsNull(vp)) return false       ;
  QSize  A = available(size())       ;
  QSizeF C = centimeter (A)          ;
  QRectF V(0,0,C.width(),C.height()) ;
  PerfectView ()                     ;
  ScreenSize->setPos(Origin)         ;
  ScreenSize->setRect(V)             ;
  ScreenSize->Park(A)                ;
  return false                       ;
}

void N::MonitorSize::Left(void)
{
  screen.WidthLength--               ;
  QSize  A = available(size())       ;
  QSizeF C = centimeter (A)          ;
  QRectF V(0,0,C.width(),C.height()) ;
  PerfectView           (        )   ;
  ScreenSize -> setPos  ( Origin )   ;
  ScreenSize -> setRect ( V      )   ;
  ScreenSize -> Park    ( A      )   ;
  ScreenSize -> update  (        )   ;
  UpdateScreen          (        )   ;
}

void N::MonitorSize::Right(void)
{
  screen.WidthLength++               ;
  QSize  A = available(size())       ;
  QSizeF C = centimeter (A)          ;
  QRectF V(0,0,C.width(),C.height()) ;
  PerfectView ()                     ;
  ScreenSize -> setPos  ( Origin )   ;
  ScreenSize -> setRect ( V      )   ;
  ScreenSize -> Park    ( A      )   ;
  ScreenSize -> update  (        )   ;
  UpdateScreen          (        )   ;
}

void N::MonitorSize::Up(void)
{
  screen.HeightLength++              ;
  QSize  A = available(size())       ;
  QSizeF C = centimeter (A)          ;
  QRectF V(0,0,C.width(),C.height()) ;
  PerfectView ()                     ;
  ScreenSize -> setPos  ( Origin )   ;
  ScreenSize -> setRect ( V      )   ;
  ScreenSize -> Park    ( A      )   ;
  ScreenSize -> update  (        )   ;
  UpdateScreen          (        )   ;
}

void N::MonitorSize::Down(void)
{
  screen.HeightLength--              ;
  QSize  A = available(size())       ;
  QSizeF C = centimeter (A)          ;
  QRectF V(0,0,C.width(),C.height()) ;
  PerfectView ()                     ;
  ScreenSize->setPos(Origin)         ;
  ScreenSize->setRect(V)             ;
  ScreenSize->Park   (A)             ;
  ScreenSize->update ( )             ;
  UpdateScreen ( )                   ;
}

void N::MonitorSize::UpdateScreen(void)
{
  plan -> screen = screen ;
}

bool N::MonitorSize::Shutdown(void)
{
  emit Apply ( )  ;
  DoProcessEvents ;
  return true     ;
}

bool N::MonitorSize::Finalize(void)
{
  emit Apply  ( ) ;
  DoProcessEvents ;
  deleteLater ( ) ;
  return true     ;
}

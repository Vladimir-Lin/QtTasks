#include <qttasks.h>
#include "ui_nRepeatedEvent.h"

N::RepeatedEvent:: RepeatedEvent ( QWidget * parent , Plan * p )
                 : Widget        (           parent ,        p )
                 , ui            ( new Ui::nRepeatedEvent      )
{
  Configure ( ) ;
}

N::RepeatedEvent::~RepeatedEvent(void)
{
  delete ui ;
}

void N::RepeatedEvent::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
  Relocation           (   ) ;
}

void N::RepeatedEvent::showEvent(QShowEvent * e)
{
  QWidget::showEvent ( e ) ;
  Relocation         (   ) ;
}

void N::RepeatedEvent::closeEvent(QCloseEvent * e)
{
  QWidget::closeEvent ( e ) ;
}

void N::RepeatedEvent::SendActivity(int state)
{
  emit Activity ( state ) ;
}

void N::RepeatedEvent::Configure(void)
{
  ui   -> setupUi                  ( this         )   ;
  ui   -> Entry -> addItem         ( tr("Start" ) )   ;
  ui   -> Entry -> addItem         ( tr("Finish") )   ;
  ui   -> Entry -> setCurrentIndex ( 1            )   ;
  plan -> setFont                  ( this         )   ;
  nConnect ( this , SIGNAL ( PrivateActivity(int) )   ,
             this , SLOT   ( SendActivity   (int) ) ) ;
}

void N::RepeatedEvent::run(int type,ThreadData * data)
{
  switch ( type )                                                        {
    case 10001                                                           :
      emit PrivateActivity ( 0                                         ) ;
      startLoading         (                                           ) ;
      Load                 ( data -> Arguments [ 0 ] . toULongLong ( ) ) ;
      stopLoading          (                                           ) ;
      emit PrivateActivity ( 1                                         ) ;
    break                                                                ;
  }                                                                      ;
}

bool N::RepeatedEvent::Relocation(void)
{
  QRect g                                             ;
  /////////////////////////////////////////////////////
  g = ui -> Entry  -> geometry    (                 ) ;
  g . setRight                    ( width  ( ) - 10 ) ;
  ui     -> Entry  -> setGeometry ( g               ) ;
  /////////////////////////////////////////////////////
  g = ui -> Script -> geometry    (                 ) ;
  g . setRight                    ( width  ( ) - 10 ) ;
  ui     -> Script -> setGeometry ( g               ) ;
  /////////////////////////////////////////////////////
  return true                                         ;
}

bool N::RepeatedEvent::startup(SUID uuid)
{
  VarArgs args           ;
  args << uuid           ;
  start ( 10001 , args ) ;
  return true            ;
}

void N::RepeatedEvent::Load(SUID u)
{
  if ( 0 == u ) return                                     ;
  EventManager  EM ( plan        )                         ;
  SqlConnection SC ( plan -> sql )                         ;
  if ( SC . open ( FunctionString ) )                      {
    QVariant rep                                           ;
    QVariant ent                                           ;
    QVariant scr                                           ;
    if ( EM . LoadVariable ( SC,u,"Repeated"      ,rep ) ) {
      int repi = rep . toInt ( )                           ;
      ui -> Repeat -> blockSignals ( true      )           ;
      ui -> Repeat -> setChecked   ( repi == 1 )           ;
      ui -> Repeat -> blockSignals ( false     )           ;
    }                                                      ;
    if ( EM . LoadVariable ( SC,u,"RepeatedEntry" ,ent ) ) {
      int enti = ent . toInt ( )                           ;
      ui -> Entry  -> blockSignals    ( true   )           ;
      ui -> Entry  -> setCurrentIndex ( enti   )           ;
      ui -> Entry  -> blockSignals    ( false  )           ;
    }                                                      ;
    if ( EM . LoadVariable ( SC,u,"RepeatedScript",scr ) ) {
      QString scrs = scr . toString   (       )            ;
      ui -> Script -> blockSignals    ( true  )            ;
      ui -> Script -> setText         ( scrs  )            ;
      ui -> Script -> blockSignals    ( false )            ;
    }                                                      ;
    SC . close  ( )                                        ;
  }                                                        ;
  SC   . remove ( )                                        ;
}

bool N::RepeatedEvent::store(SqlConnection & SC,SUID u)
{
  if ( u <= 0 ) return false                               ;
  //////////////////////////////////////////////////////////
  EventManager EM ( plan )                                 ;
  QString  S    = ui -> Script -> text         ( )         ;
  int      repi = ui -> Repeat -> isChecked    ( ) ? 1 : 0 ;
  int      enti = ui -> Entry  -> currentIndex ( )         ;
  QVariant SV   = S                                        ;
  QVariant RV   = repi                                     ;
  QVariant EV   = enti                                     ;
  EM . SaveVariable ( SC , u , "Repeated"       , RV )     ;
  EM . SaveVariable ( SC , u , "RepeatedEntry"  , EV )     ;
  EM . SaveVariable ( SC , u , "RepeatedScript" , SV )     ;
  //////////////////////////////////////////////////////////
  return true                                              ;
}

void N::RepeatedEvent::Browse(void)
{
  QString filename = plan->Dirs[N::Directory::Scripts].absoluteFilePath("")  ;
  filename = QFileDialog::getOpenFileName                                    (
               this                                                          ,
               tr("Repeated event script")                                   ,
               filename                                                      ,
               tr("Javascript (*.js)")                                     ) ;
  if ( filename . length ( ) <= 0 ) return                                   ;
  ui -> Script -> setText ( filename )                                       ;
}

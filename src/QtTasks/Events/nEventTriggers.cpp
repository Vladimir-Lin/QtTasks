#include <qttasks.h>
#include "ui_nEventTriggers.h"

N::EventTriggers:: EventTriggers ( QWidget * parent , Plan * p )
                 : Widget        (           parent ,        p )
                 , ui            ( new Ui::nEventTriggers      )
                 , StartUuid     ( 0                           )
                 , FinalUuid     ( 0                           )
{
  Configure ( ) ;
}

N::EventTriggers::~EventTriggers(void)
{
  delete ui ;
}

SUID N::EventTriggers::StartTrigger(void)
{
  return N::GetUuid ( ui -> StartTrigger  ) ;
}

SUID N::EventTriggers::FinishTrigger(void)
{
  return N::GetUuid ( ui -> FinishTrigger ) ;
}

void N::EventTriggers::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
  Relocation           (   ) ;
}

void N::EventTriggers::showEvent(QShowEvent   * e)
{
  QWidget::showEvent ( e ) ;
  Relocation         (   ) ;
}

void N::EventTriggers::SendActivity(int state)
{
  emit Activity ( state ) ;
}

void N::EventTriggers::AssignTrigger(int type,SUID u)
{
  switch ( type )                                          {
    case Groups::StartTrigger                              :
      if ( u > 0 )                                         {
        (*(ui->StartTrigger) ) <= u                        ;
      } else                                               {
        int t = ui -> StartTrigger  -> count ( )           ;
        if ( t > 0 )                                       {
          int i = rand ( ) % t                             ;
          ui -> StartTrigger  -> blockSignals    ( true  ) ;
          ui -> StartTrigger  -> setCurrentIndex ( i     ) ;
          ui -> StartTrigger  -> blockSignals    ( false ) ;
        }                                                  ;
      }                                                    ;
    break                                                  ;
    case Groups::FinalTrigger                              :
      if ( u > 0 )                                         {
        (*(ui->FinishTrigger) ) <= u                       ;
      } else                                               {
        int t = ui -> StartTrigger -> count ( )            ;
        if ( t > 0 )                                       {
          int i = rand ( ) % t                             ;
          ui -> FinishTrigger -> blockSignals    ( true  ) ;
          ui -> FinishTrigger -> setCurrentIndex ( i     ) ;
          ui -> FinishTrigger -> blockSignals    ( false ) ;
        }                                                  ;
      }                                                    ;
    break                                                  ;
  }
}

void N::EventTriggers::TriggerComplete(void)
{
  AssignTrigger ( Groups::StartTrigger , StartUuid ) ;
  AssignTrigger ( Groups::FinalTrigger , FinalUuid ) ;
}

void N::EventTriggers::Configure(void)
{
  ui   -> setupUi ( this )                             ;
  plan -> setFont ( this )                             ;
  nConnect ( this , SIGNAL ( PrivateComplete (   ) )   ,
             this , SLOT   ( TriggerComplete (   ) ) ) ;
  nConnect ( this , SIGNAL ( PrivateActivity (int) )   ,
             this , SLOT   ( SendActivity    (int) ) ) ;
}

void N::EventTriggers::run(int type,ThreadData * data)
{
  switch ( type )                {
    case 10001                   :
      emit PrivateActivity ( 0 ) ;
      startLoading         (   ) ;
      Load                 (   ) ;
      stopLoading          (   ) ;
      emit PrivateActivity ( 1 ) ;
    break                        ;
  }                              ;
}

void N::EventTriggers::Load(void)
{
  setEnabled                          ( false )      ;
  ui -> StartTrigger  -> blockSignals ( true  )      ;
  ui -> FinishTrigger -> blockSignals ( true  )      ;
  ui -> StartTrigger  -> clear        (       )      ;
  ui -> FinishTrigger -> clear        (       )      ;
  ////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                   ;
  if ( SC . open ( FunctionString ) )                {
    UUIDs   U                                        ;
    SUID    u                                        ;
    //////////////////////////////////////////////////
    U = SC . Uuids ( PlanTable(Triggers)             ,
                     "uuid"                          ,
                     SC . OrderByAsc("id")         ) ;
    foreach ( u , U )                                {
      QString n = SC . getName                       (
                    PlanTable(Names)                 ,
                    "uuid"                           ,
                    vLanguageId                      ,
                    u                              ) ;
      ui -> StartTrigger  -> addItem ( n , u  )      ;
      ui -> FinishTrigger -> addItem ( n , u  )      ;
    }                                                ;
    //////////////////////////////////////////////////
    SC . close  ( )                                  ;
  }                                                  ;
  SC   . remove ( )                                  ;
  ////////////////////////////////////////////////////
  setEnabled                          ( true  )      ;
  emit PrivateComplete                (       )      ;
}

bool N::EventTriggers::Relocation(void)
{
  QRect g                                                    ;
  ////////////////////////////////////////////////////////////
  g = ui -> StartTrigger  -> geometry    (                 ) ;
  g . setRight                           ( width  ( ) - 10 ) ;
  ui     -> StartTrigger -> setGeometry  ( g               ) ;
  ////////////////////////////////////////////////////////////
  g = ui -> FinishTrigger -> geometry    (                 ) ;
  g . setRight                           ( width  ( ) - 10 ) ;
  ui     -> FinishTrigger -> setGeometry ( g               ) ;
  return true                                                ;
}

void N::EventTriggers::startup(SUID S,SUID F)
{
  StartUuid = S   ;
  FinalUuid = F   ;
  start ( 10001 ) ;
}

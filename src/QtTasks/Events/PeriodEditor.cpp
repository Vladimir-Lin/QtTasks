#include <qttasks.h>
#include "ui_PeriodEditor.h"

N::PeriodEditor:: PeriodEditor ( QWidget      * parent , Plan * p )
                : Splitter     ( Qt::Vertical , parent ,        p )
                , ui           ( new Ui::PeriodEditor             )
                , StartTime    ( NULL                             )
                , FinishTime   ( NULL                             )
{
  Configure ( ) ;
}

N::PeriodEditor::~PeriodEditor(void)
{
  if (NotNull(StartTime )) StartTime ->deleteLater() ;
  if (NotNull(FinishTime)) FinishTime->deleteLater() ;
  StartTime  = NULL                                  ;
  FinishTime = NULL                                  ;
  delete ui                                          ;
}

QSize N::PeriodEditor::sizeHint (void) const
{
  return QSize ( 400 , 300 ) ;
}

int N::PeriodEditor::Type(void)
{
  int idx = ui->PeriodType->currentIndex()        ;
  int vid = ui->PeriodType->itemData(idx).toInt() ;
  return vid                                      ;
}

TUID N::PeriodEditor::Start(void)
{
  return period.L ;
}

TUID N::PeriodEditor::Finish(void)
{
  return period.R ;
}

N::TimePeriod N::PeriodEditor::Period(void)
{
  return period ;
}

void N::PeriodEditor::setStart(TUID startTime)
{
  period.L = startTime                               ;
  if (period.L>period.R) period.R = period.L + 86400 ;
}

void N::PeriodEditor::setFinish(TUID finishTime)
{
  period.R = finishTime ;
}

void N::PeriodEditor::setRange(TimePeriod tp)
{
  period = tp ;
}

void N::PeriodEditor::Configure (void)
{
  ui -> setupUi               ( this                             ) ;
  //////////////////////////////////////////////////////////////////
  ui -> TimeType   -> addItem ( tr("Gregorian calendar"    ) , 0 ) ;
  ui -> TimeType   -> addItem ( tr("Stardate (Time Anchor)") , 1 ) ;
  ui -> TimeType   -> addItem ( tr("Holocene calendar"     ) , 2 ) ;
  ui -> TimeType   -> addItem ( tr("Buddhist calendar"     ) , 3 ) ;
  ui -> TimeType   -> addItem ( tr("Taiwan calendar"       ) , 4 ) ;
  ui -> TimeType   -> addItem ( tr("Star Date (Star Trek)" ) , 5 ) ;
  //////////////////////////////////////////////////////////////////
  ui -> PeriodType -> addItem ( tr("Period"                ) , 0 ) ;
  ui -> PeriodType -> addItem ( tr("Start time"            ) , 1 ) ;
  ui -> PeriodType -> addItem ( tr("Finish time"           ) , 2 ) ;
  ui -> PeriodType -> addItem ( tr("Time spot"             ) , 3 ) ;
  //////////////////////////////////////////////////////////////////
  DateTime NX = DateTime::local()                                  ;
  ui -> TimeZone -> addItem ( tr("Local time") , NX.timeshift()  ) ;
  ui -> TimeZone -> addItem ( tr("UTC"       ) ,     0           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+1"     ) ,  3600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-1"     ) , -3600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+2"     ) ,  7200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-2"     ) , -7200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+3"     ) , 10800           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-3"     ) ,-10800           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+3:30"  ) , 12600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-3:30"  ) ,-12600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+4"     ) , 14400           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-4"     ) ,-14400           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+4:30"  ) , 16200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-4:30"  ) ,-16200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+5"     ) , 18000           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-5"     ) ,-18000           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+5:30"  ) , 19800           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+5:45"  ) , 20700           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+6"     ) , 21600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-6"     ) ,-21600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+6:30"  ) , 23400           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+7"     ) , 25200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-7"     ) ,-25200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+8"     ) , 28800           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-8"     ) ,-28800           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+9"     ) , 32400           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-9"     ) ,-32400           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+9:30"  ) , 34200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-9:30"  ) ,-34200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+10"    ) , 36000           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-10"    ) ,-36000           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+10:30" ) , 37800           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+11"    ) , 39600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-11"    ) ,-39600           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+11:30" ) , 41400           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+12"    ) , 43200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC-12"    ) ,-43200           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+12:45" ) , 45900           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+13"    ) , 46800           ) ;
  ui -> TimeZone -> addItem ( tr("UTC+14"    ) , 50400           ) ;
  //////////////////////////////////////////////////////////////////
  period.L  = StarDate::now()                                      ;
  period.R  = period.L                                             ;
  period.R += 86400                                                ;
  //////////////////////////////////////////////////////////////////
  CalendarIDs [ 0                    ] = Calendars::Geogrian       ;
  CalendarIDs [ 1                    ] = Calendars::StarDate       ;
  CalendarIDs [ 2                    ] = Calendars::Holocene       ;
  CalendarIDs [ 3                    ] = Calendars::Buddhist       ;
  CalendarIDs [ 4                    ] = Calendars::Taiwanese      ;
  CalendarIDs [ 5                    ] = Calendars::StarTrek       ;
  //////////////////////////////////////////////////////////////////
  IdCalendars [ Calendars::Geogrian  ] =  0                        ;
  IdCalendars [ Calendars::StarDate  ] =  1                        ;
  IdCalendars [ Calendars::Holocene  ] =  2                        ;
  IdCalendars [ Calendars::Buddhist  ] =  3                        ;
  IdCalendars [ Calendars::Taiwanese ] =  4                        ;
  IdCalendars [ Calendars::StarTrek  ] =  5                        ;
  //////////////////////////////////////////////////////////////////
  PageChanged     ( 0    )                                         ;
  plan -> setFont ( this )                                         ;
}

void N::PeriodEditor::resizeEvent(QResizeEvent * e)
{
  QSplitter::resizeEvent ( e ) ;
  Relocation             (   ) ;
}

void N::PeriodEditor::showEvent(QShowEvent * e)
{
  QSplitter::showEvent ( e ) ;
  Relocation           (   ) ;
}

bool N::PeriodEditor::Relocation(void)
{
  nIfSafe ( StartTime  )            {
    QRect g                         ;
    g = StartTime  -> geometry ( )  ;
    g . setRight ( width ( ) - 10 ) ;
    StartTime  -> setGeometry ( g ) ;
  }                                 ;
  nIfSafe ( FinishTime )            {
    QRect g                         ;
    g = FinishTime -> geometry ( )  ;
    g . setRight ( width ( ) - 10 ) ;
    FinishTime -> setGeometry ( g ) ;
  }                                 ;
  return true                       ;
}

N::CalendarTimeEdit * N::PeriodEditor::New(int Type,int periodType)
{
  QWidget * w                         ;
  w = ui->Stacked->widget(periodType) ;
  switch ( Type )                     {
    case 0                            :
    return new GeogrianEdit ( w )     ;
    case 1                            :
    return new StardateEdit ( w )     ;
    case 2                            :
    return new HoloceneEdit ( w )     ;
    case 3                            :
    return new BuddhistEdit ( w )     ;
    case 4                            :
    return new TaiwanEdit   ( w )     ;
    case 5                            :
    return new StarTrekEdit ( w )     ;
  }                                   ;
  return NULL                         ;
}

void N::PeriodEditor::setType(int type)
{
  ui -> PeriodType -> blockSignals    ( true  ) ;
  ui -> PeriodType -> setCurrentIndex ( type  ) ;
  ui -> PeriodType -> blockSignals    ( false ) ;
  PageChanged                         ( type  ) ;
}

void N::PeriodEditor::show(int index)
{
  switch ( index )                 {
    case 0                         :
      ui -> TimeType   -> show ( ) ;
    break                          ;
    case 1                         :
      ui -> PeriodType -> show ( ) ;
    break                          ;
    case 2                         :
      ui -> TimeZone   -> show ( ) ;
    break                          ;
  }                                ;
}

void N::PeriodEditor::hide(int index)
{
  switch ( index )                 {
    case 0                         :
      ui -> TimeType   -> hide ( ) ;
    break                          ;
    case 1                         :
      ui -> PeriodType -> hide ( ) ;
    break                          ;
    case 2                         :
      ui -> TimeZone   -> hide ( ) ;
    break                          ;
  }                                ;
}

void N::PeriodEditor::selectCalendar(int type)
{
  int index = -1                              ;
  if ( IdCalendars . contains ( type ) )      {
    index = IdCalendars [ type ]              ;
  }                                           ;
  if ( index < 0 ) return                     ;
  /////////////////////////////////////////////
  ui -> TimeType -> blockSignals    ( true  ) ;
  ui -> TimeType -> setCurrentIndex ( index ) ;
  ui -> TimeType -> blockSignals    ( false ) ;
  PageChanged                       ( index ) ;
}

void N::PeriodEditor::selectPeriod(int period)
{
  ui -> PeriodType -> blockSignals    ( true   ) ;
  ui -> PeriodType -> setCurrentIndex ( period ) ;
  ui -> PeriodType -> blockSignals    ( false  ) ;
  PageChanged                         ( period ) ;
}

void N::PeriodEditor::selectTimeZone(int timeZone)
{
  int index = -1                                       ;
  for (int i=0;index<0 && i<ui->TimeZone->count();i++) {
    int tz = ui->TimeZone->itemData(i).toInt()         ;
    if ( tz == timeZone ) index = i                    ;
  }                                                    ;
  if ( index < 0 ) return                              ;
  ui -> TimeZone -> blockSignals    ( true  )          ;
  ui -> TimeZone -> setCurrentIndex ( index )          ;
  ui -> TimeZone -> blockSignals    ( false )          ;
  TimeZoneChanged                   ( index )          ;
}

void N::PeriodEditor::TimeZoneChanged(int index)
{
  int tt = ui->TimeZone->itemData(index).toInt() ;
  if (NotNull(StartTime ))                       {
    StartTime  -> blockSignals ( true     )      ;
    StartTime  -> setTimeZone  ( tt       )      ;
    StartTime  -> setStardate  ( period.L )      ;
    StartTime  -> blockSignals ( true     )      ;
  }                                              ;
  if (NotNull(FinishTime))                       {
    FinishTime -> blockSignals ( true     )      ;
    FinishTime -> setTimeZone  ( tt       )      ;
    FinishTime -> setStardate  ( period.R )      ;
    FinishTime -> blockSignals ( true     )      ;
  }                                              ;
  emit Changed ( )                               ;
}

void N::PeriodEditor::StartChanged(TUID time)
{
  period.L = time                       ;
  if (NotNull(FinishTime))              {
    FinishTime -> setRange ( time , 0 ) ;
  }                                     ;
  emit Changed ( )                      ;
}

void N::PeriodEditor::FinishChanged(TUID time)
{
  period.R = time  ;
  emit Changed ( ) ;
}

void N::PeriodEditor::PageChanged(int)
{
  int tt = N :: GetUuid( ui->TimeType   )                    ;
  int pt = N :: GetUuid( ui->PeriodType )                    ;
  ui -> Stacked -> setCurrentIndex ( pt )                    ;
  ////////////////////////////////////////////////////////////
  if (NotNull(StartTime )) StartTime ->deleteLater()         ;
  if (NotNull(FinishTime)) FinishTime->deleteLater()         ;
  StartTime  = NULL                                          ;
  FinishTime = NULL                                          ;
  ////////////////////////////////////////////////////////////
  int tz = ui->TimeZone->currentIndex()                      ;
  tz = ui->TimeZone->itemData(tz).toInt()                    ;
  switch ( pt )                                              {
    case 0                                                   :
      StartTime          = New         ( tt  ,  pt   )       ;
      StartTime         -> move        ( 140 ,  20   )       ;
      StartTime         -> resize      ( 300 ,  24   )       ;
      StartTime         -> setTimeZone ( tz          )       ;
      StartTime         -> setStardate ( period.L    )       ;
      StartTime         -> show        (             )       ;
      FinishTime         = New         ( tt  ,  pt   )       ;
      FinishTime        -> move        ( 140 ,  60   )       ;
      FinishTime        -> setTimeZone ( tz          )       ;
      FinishTime        -> setStardate ( period.R    )       ;
      FinishTime        -> resize      ( 300 ,  24   )       ;
      FinishTime        -> show        (             )       ;
    break                                                    ;
    case 1                                                   :
      StartTime          = New         ( tt  ,  pt   )       ;
      StartTime         -> move        ( 140 ,  40   )       ;
      StartTime         -> resize      ( 300 ,  24   )       ;
      StartTime         -> setTimeZone ( tz          )       ;
      StartTime         -> setStardate ( period.L    )       ;
      StartTime         -> show        (             )       ;
    break                                                    ;
    case 2                                                   :
      FinishTime         = New         ( tt  ,  pt   )       ;
      FinishTime        -> move        ( 140 ,  40   )       ;
      FinishTime        -> resize      ( 300 ,  24   )       ;
      FinishTime        -> setTimeZone ( tz          )       ;
      FinishTime        -> setStardate ( period.R    )       ;
      FinishTime        -> show        (             )       ;
    break                                                    ;
    case 3                                                   :
      StartTime          = New         ( tt  ,  pt   )       ;
      StartTime         -> move        ( 140 ,  40   )       ;
      StartTime         -> resize      ( 300 ,  24   )       ;
      StartTime         -> setTimeZone ( tz          )       ;
      StartTime         -> setStardate ( period.R    )       ;
      StartTime         -> show        (             )       ;
    break                                                    ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  if (NotNull(StartTime))                                    {
    nConnect ( StartTime  , SIGNAL ( Changed      (TUID) )   ,
               this       , SLOT   ( StartChanged (TUID) ) ) ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  if (NotNull(FinishTime))                                   {
    nConnect ( FinishTime , SIGNAL ( Changed      (TUID) )   ,
               this       , SLOT   ( FinishChanged(TUID) ) ) ;
  }                                                          ;
}

#include <qttasks.h>
#include "ui_nGanttDuration.h"

N::GanttDuration:: GanttDuration (QWidget * parent,Plan * p)
                 : Widget        (          parent,       p)
                 , ui            (new Ui::nGanttDuration   )
                 , Gantt         (NULL                     )
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

N::GanttDuration::~GanttDuration (void)
{
  delete ui ;
}

void N::GanttDuration::Prepare (void)
{
  ui -> Start  -> setDateTime (Gantt->Start) ;
  ui -> Finish -> setDateTime (Gantt->Final) ;
}

void N::GanttDuration::startChanged(QDateTime dt)
{
  ui -> Finish -> setMinimumDateTime ( dt ) ;
}

void N::GanttDuration::Done (void)
{
  QDateTime S = ui -> Start  -> dateTime ( ) ;
  QDateTime F = ui -> Finish -> dateTime ( ) ;
  if (S>F) return                            ;
  Gantt -> Start = S                         ;
  Gantt -> Final = F                         ;
  emit GanttChanged ( Gantt )                ;
  emit Finish       (       )                ;
}

void N::GanttDuration::Cancel (void)
{
  emit Finish ( ) ;
}

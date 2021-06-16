#include <qttasks.h>
#include "ui_nGanttNote.h"

N::GanttNote:: GanttNote    (QWidget * parent,Plan * p)
             : Widget       (          parent,       p)
             , EventManager (                        p)
             , ui           (new Ui::nGanttNote       )
{
  ui->setupUi(this) ;
}

N::GanttNote::~GanttNote (void)
{
  delete ui ;
}

void N::GanttNote::setGantt(SUID uuid,QString name)
{
  ui   -> Name -> setText ( name )               ;
  plan -> setFont         ( this )               ;
  if (uuid<=0) return                            ;
  Uuid = uuid                                    ;
  EnterSQL ( SC , plan->sql )                    ;
    QString note                                 ;
    note = EventNote ( SC , uuid , vLanguageId ) ;
    ui -> Note -> setPlainText ( note )          ;
  LeaveSQL ( SC , plan->sql )                    ;
}

void N::GanttNote::Save(void)
{
  QString note = ui -> Note -> toPlainText (   ) ;
  EnterSQL    ( SC , plan -> sql               ) ;
    SaveNote  ( SC , Uuid , vLanguageId , note ) ;
  LeaveSQL    ( SC , plan -> sql               ) ;
  emit Finish (                                ) ;
}

void N::GanttNote::Cancel(void)
{
  emit Finish ( ) ;
}

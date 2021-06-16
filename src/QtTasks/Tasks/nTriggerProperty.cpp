#include <qttasks.h>
#include "ui_nTriggerProperty.h"

#pragma message("What the hell is this TriggerProperty doing")

#define TABLES(ID) TaskPlan->Tables[Tables::ID]

N::TriggerProperty:: TriggerProperty (QWidget * parent,Plan * p)
                   : StackedWidget   (          parent,       p)
                   , TaskManager     (                        p)
                   , ui              (new Ui::nTriggerProperty )
{
  Configure   (      ) ;
}

N::TriggerProperty::~TriggerProperty (void)
{
  delete ui;
}

void N::TriggerProperty::closeEvent (QCloseEvent * event)
{
  shutdown        () ;
  event -> accept () ;
}

void N::TriggerProperty::showEvent(QShowEvent * event)
{
  QStackedWidget::showEvent(event) ;
  if (!isVisible()) return         ;
  DoProcessEvents                  ;
  Relocation          ( )          ;
}

void N::TriggerProperty::resizeEvent(QResizeEvent * event)
{
  QStackedWidget::resizeEvent (event) ;
  DoProcessEvents                     ;
  Relocation                  (     ) ;
}

void N::TriggerProperty::Configure(void)
{
  ui   -> setupUi                    ( this                   ) ;
  ui   -> Triggers -> setHeaderLabel ( tr("Trigger styles")   ) ;
  NewTreeWidgetItem                  ( IT                     ) ;
  IT   -> setData                    ( 0 , Qt::UserRole , 101 ) ;
  IT   -> setText                    ( 0 , tr("Notifier")     ) ;
  ui   -> Triggers->addTopLevelItem  ( IT                     ) ;
  plan -> setFont                    ( this                   ) ;
}

void N::TriggerProperty::Relocation(void)
{
}

bool N::TriggerProperty::load(SUID uuid)
{
  Uuid = uuid ;
  return true ;
}

void N::TriggerProperty::shutdown(void)
{
  if (IsNull(plan)) return ;
  if (Uuid<=0     ) return ;
}

void N::TriggerProperty::Finish(void)
{
  QMdiSubWindow * msw = qobject_cast<QMdiSubWindow *>(parent()) ;
  if (NotNull(msw)) msw -> deleteLater ( )                      ;
               else emit Closed ( )                             ;
}

void N::TriggerProperty::triggerClicked(QTreeWidgetItem * item,int column)
{
  int               Id = item->data(0,Qt::UserRole).toInt() ;
  N::NotifierTrigger * nt                                   ;
  switch (Id)                                               {
    case 101                                                :
      nt = new N::NotifierTrigger ( this , plan )           ;
      addWidget                   ( nt          )           ;
      setCurrentWidget            ( nt          )           ;
      nt -> load                  ( Uuid        )           ;
      connect(nt,SIGNAL(Finish()),this,SLOT(Finish()))      ;
    break                                                   ;
  }                                                         ;
}

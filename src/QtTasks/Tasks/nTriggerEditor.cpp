#include <qttasks.h>

N::TriggerEditor:: TriggerEditor (QWidget * parent,Plan * p)
                 : ItemEditor    (          parent,       p)
{
  Configure ( ) ;
}

N::TriggerEditor::~TriggerEditor(void)
{
}

void N::TriggerEditor::Configure(void)
{
  setWindowTitle  ( tr("Trigger lists") ) ;
  setHeaderHidden ( true                ) ;
  ItemTable = PlanTable ( Triggers      ) ;
  ItemType  = Types::Trigger              ;
  plan -> setFont ( this                ) ;
}

bool N::TriggerEditor::Menu(QPoint pos)
{
  QTreeWidgetItem * item = itemAt(pos)           ;
  SUID uuid = 0                                  ;
  if (NotNull(item))                             {
    uuid = N::RetrieveUuid (item,0)              ;
  }                                              ;
  nScopedMenu ( mm , this )                      ;
  QAction    * a = NULL                          ;
  mm.add(101,tr("New"))                          ;
  if (NotNull(item)) mm.add(102,tr("Edit"  ))    ;
  if (NotNull(item)) mm.add(103,tr("Rename"))    ;
  mm.setFont(plan)                               ;
  a = mm.exec(mapToGlobal(pos))                  ;
  switch (mm[a])                                 {
    case 101: New();                 break       ;
    case 102: emit Clicked(uuid);    break       ;
    case 103: doubleClicked(item,0); break       ;
  }                                              ;
  return true                                    ;
}

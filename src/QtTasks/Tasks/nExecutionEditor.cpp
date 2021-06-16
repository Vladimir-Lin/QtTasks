#include <qttasks.h>
#include "ui_nExecutionEditor.h"

#pragma message("An ExecutionManager is required")

N::ExecutionEditor:: ExecutionEditor (QWidget * parent,Plan * p)
                   : Widget          (          parent,       p)
                   , Object          (0,Types::Execution       )
                   , ui              (new Ui::nExecutionEditor )
                   , IconUuid        (0                        )
{
  Configure ( ) ;
}

N::ExecutionEditor::~ExecutionEditor(void)
{
  delete ui;
}

QSize N::ExecutionEditor::sizeHint(void) const
{
  return QSize ( 400 , 300 ) ;
}

void N::ExecutionEditor::Configure(void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::ExecutionEditor::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QWidget::focusInEvent (event) ;
}

bool N::ExecutionEditor::FocusIn(void)
{
  DisableAllActions (                          ) ;
  AssignAction      ( Label  , windowTitle ( ) ) ;
  LinkAction        ( Insert , Update      ( ) ) ;
  return true                                    ;
}

void N::ExecutionEditor::Clear(void)
{
  QIcon blank                                        ;
  ui -> ProgramIcon   -> setIcon  ( blank          ) ;
  ui -> nameEdit      -> clear    (                ) ;
  ui -> registerEdit  -> clear    (                ) ;
  ui -> Executable    -> clear    (                ) ;
  ui -> Paraments     -> clear    (                ) ;
  ui -> Environment   -> clear    (                ) ;
  ui -> identifierBox -> setValue ( rand()%1000000 ) ;
  setObjectUuid                   ( 0              ) ;
}

void N::ExecutionEditor::Update(void)
{
  QString Name        = ui -> nameEdit      -> text      ( )               ;
  QString Register    = ui -> registerEdit  -> text      ( )               ;
  QString Executable  = ui -> Executable    -> text      ( )               ;
  QString Environment = ui -> Environment   -> text      ( )               ;
  QString Paraments   = ui -> Paraments     -> text      ( )               ;
  int     Identifier  = ui -> identifierBox -> value     ( )               ;
  int     Parallel    = ui -> parallelBox   -> isChecked ( ) ? 1 : 0       ;
  nDropOut ( Name        . length ( ) <= 0 )                               ;
  nDropOut ( Register    . length ( ) <= 0 )                               ;
  nDropOut ( Executable  . length ( ) <= 0 )                               ;
  nDropOut ( Environment . length ( ) <= 0 )                               ;
  nDropOut ( IconUuid                 <= 0 )                               ;
  SqlConnection SC ( plan->sql )                                           ;
  if (SC.open("ExecutionEditor","Update"))                                 {
    QString Q                                                              ;
    SUID    platform = 0                                                   ;
    bool    adding   = false                                               ;
    Q = SC.sql.SelectFrom                                                  (
          "uuid"                                                           ,
          PlanTable(Platforms)                                             ,
          "where id = 1 ;"                                               ) ;
    if (SC.Fetch(Q)) platform = SC.Uuid(0)                                 ;
    if (ObjectUuid()<=0)                                                   {
      adding = true                                                        ;
      uuid   = SC.Unique ( PlanTable(MajorUuid) , "uuid" , 3624 )          ;
      SC.assureUuid( PlanTable(MajorUuid  ),ObjectUuid(),Types::Execution) ;
      SC.insertUuid( PlanTable(Automations),ObjectUuid(),"uuid"          ) ;
    }                                                                      ;
    SC.assureName(PlanTable(Names),ObjectUuid(),vLanguageId,Name)          ;
    if (adding)                                                            {
      Q = SC.sql.InsertInto                                                (
            PlanTable(Executions)                                          ,
            9                                                              ,
            "uuid"                                                         ,
            "icon"                                                         ,
            "platform"                                                     ,
            "identifier"                                                   ,
            "parallel"                                                     ,
            "register"                                                     ,
            "executable"                                                   ,
            "environment"                                                  ,
            "paraments"                                                  ) ;
    } else                                                                 {
      Q = SC.sql.Update                                                    (
            PlanTable(Executions)                                          ,
            SC.sql.Where(1,"uuid")                                         ,
            8                                                              ,
            "icon"                                                         ,
            "platform"                                                     ,
            "identifier"                                                   ,
            "parallel"                                                     ,
            "register"                                                     ,
            "executable"                                                   ,
            "environment"                                                  ,
            "paraments"                                                  ) ;
    }                                                                      ;
    SC . Prepare ( Q                                        )              ;
    SC . Bind    ( "uuid"        , ObjectUuid()             )              ;
    SC . Bind    ( "icon"        , IconUuid                 )              ;
    SC . Bind    ( "platform"    , platform                 )              ;
    SC . Bind    ( "identifier"  , Identifier               )              ;
    SC . Bind    ( "parallel"    , Parallel                 )              ;
    SC . Bind    ( "register"    , Register    . toUtf8 ( ) )              ;
    SC . Bind    ( "executable"  , Executable  . toUtf8 ( ) )              ;
    SC . Bind    ( "environment" , Environment . toUtf8 ( ) )              ;
    SC . Bind    ( "paraments"   , Paraments   . toUtf8 ( ) )              ;
    SC . Exec    (                                          )              ;
    SC . close   (                                          )              ;
    emit Updated (                                          )              ;
  }                                                                        ;
  SC.remove()                                                              ;
}

void N::ExecutionEditor::Fetch(SUID u)
{
  setObjectUuid    ( u         )                                              ;
  nDropOut         ( u <=0     )                                              ;
  SqlConnection SC ( plan->sql )                                              ;
  if (SC.open("ExecutionEditor","Fetch"))                                     {
    QString Q                                                                 ;
    QString Name                                                              ;
    QString Register                                                          ;
    QString Executable                                                        ;
    QString Environment                                                       ;
    QString Paraments                                                         ;
    int     Identifier                                                        ;
    int     Parallel                                                          ;
    IconUuid = 0                                                              ;
    Name = SC.getName(PlanTable(Names),"uuid",vLanguageId,u)                  ;
    Q = SC.sql.SelectFrom                                                     (
          "icon,identifier,parallel,register,executable,environment,paraments",
          PlanTable(Executions)                                               ,
          SC.WhereUuid(u)                                                   ) ;
    if (SC.Fetch(Q))                                                          {
      IconUuid    = SC . Uuid   ( 0 )                                         ;
      Identifier  = SC . Int    ( 1 )                                         ;
      Parallel    = SC . Int    ( 2 )                                         ;
      Register    = SC . String ( 3 )                                         ;
      Executable  = SC . String ( 4 )                                         ;
      Environment = SC . String ( 5 )                                         ;
      Paraments   = SC . String ( 6 )                                         ;
      ui -> identifierBox -> setValue   ( Identifier    )                     ;
      ui -> parallelBox   -> setChecked ( Parallel == 1 )                     ;
      ui -> nameEdit      -> setText    ( Name          )                     ;
      ui -> registerEdit  -> setText    ( Register      )                     ;
      ui -> Executable    -> setText    ( Executable    )                     ;
      ui -> Paraments     -> setText    ( Paraments     )                     ;
      ui -> Environment   -> setText    ( Environment   )                     ;
    }                                                                         ;
    if (IconUuid>0)                                                           {
      PictureManager PM ( plan )                                              ;
      QImage * Thumb = NULL                                                   ;
      Thumb = PM.Thumb( SC , IconUuid )                                       ;
      if (NotNull(Thumb))                                                     {
        QSize is(64,64)                                                       ;
        QIcon ic = PM . Icon ( Thumb , is )                                   ;
        delete Thumb                                                          ;
        ui->ProgramIcon->setIcon(ic)                                          ;
      }                                                                       ;
    }                                                                         ;
    SC.close()                                                                ;
  }                                                                           ;
  SC.remove()                                                                 ;
}

void N::ExecutionEditor::ProgramIcon(void)
{
  QString filename = QFileDialog::getOpenFileName                         (
                       this                                               ,
                       tr("Program icon")                                 ,
                       plan->Dirs[Directory::Images].absoluteFilePath("") ,
                       Images::ImageFilters()                           ) ;
  if (filename.length()<=0) return                                        ;
  ui->ProgramIcon->setIcon(QIcon(filename))                               ;
  PictureManager PM ( plan                )                               ;
  PM . Import       ( filename , IconUuid )                               ;
}

void N::ExecutionEditor::BrowseExecution(void)
{
  QString filename = QFileDialog::getOpenFileName (
                       this                       ,
                       tr("Executable program")   ,
                       ""                         ,
                       "*.*"                    ) ;
  if (filename.length()<=0) return                ;
  ui->Executable->setText(filename)               ;
}

void N::ExecutionEditor::BrowseEnvironment(void)
{
  QString dir = QFileDialog::getExistingDirectory (
                  this                            ,
                  tr("Execution environment")     ,
                  ""                            ) ;
  if (dir.length()<=0) return                     ;
  ui->Environment->setText(dir)                   ;
}

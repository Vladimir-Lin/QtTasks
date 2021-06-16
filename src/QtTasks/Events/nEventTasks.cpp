#include <qttasks.h>
#include "ui_nEventTasks.h"

N::EventTasks:: EventTasks ( QWidget * parent , Plan * p )
              : Widget     (           parent ,        p )
              , ui         ( new Ui::nEventTasks         )
{
  Configure ( ) ;
}

N::EventTasks::~EventTasks(void)
{
  delete ui ;
}

void N::EventTasks::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
  Relocation           (   ) ;
}

void N::EventTasks::showEvent(QShowEvent * e)
{
  QWidget::showEvent ( e ) ;
  Relocation         (   ) ;
}

void N::EventTasks::closeEvent(QCloseEvent * e)
{
  if ( isLoading ( ) )      {
    stopForcely  ( )        ;
  }                         ;
  QWidget::closeEvent ( e ) ;
}

void N::EventTasks::SendActivity(int state)
{
  emit Activity ( state ) ;
}

void N::EventTasks::Configure(void)
{
  NewTreeWidgetItem                   ( head                ) ;
  ui   -> setupUi                     ( this                ) ;
  head -> setText                     ( 0 , tr("Task")      ) ;
  head -> setTextAlignment            ( 0 , Qt::AlignCenter ) ;
  ui   -> Belongings -> setHeaderItem ( head                ) ;
  plan -> setFont                     ( this                ) ;
  nConnect ( this , SIGNAL ( PrivateActivity(int)         )   ,
             this , SLOT   ( SendActivity   (int)         ) ) ;
  start                               ( 11001               ) ;
}

void N::EventTasks::run(int type,ThreadData * data)
{
  switch ( type )                                                        {
    case 10001                                                           :
      emit PrivateActivity ( 0                                         ) ;
      Load                 ( data -> Arguments [ 0 ] . toULongLong ( ) ) ;
      emit PrivateActivity ( 1                                         ) ;
    break                                                                ;
    case 11001                                                           :
      if ( isLoading ( ) ) return                                        ;
      emit PrivateActivity ( 0                                         ) ;
      startLoading         (                                           ) ;
      pushCanStop          (                                           ) ;
      List                 (                                           ) ;
      popCanStop           (                                           ) ;
      stopLoading          (                                           ) ;
      emit PrivateActivity ( 1                                         ) ;
    break                                                                ;
  }                                                                      ;
}

bool N::EventTasks::Relocation(void)
{
  QRect g                                            ;
  ////////////////////////////////////////////////////
  g = ui -> Tasks      -> geometry    (            ) ;
  g . setRight                        ( width  ( ) ) ;
  ui     -> Tasks      -> setGeometry ( g          ) ;
  ////////////////////////////////////////////////////
  g = ui -> Belongings -> geometry    (            ) ;
  g . setRight                        ( width  ( ) ) ;
  g . setBottom                       ( height ( ) ) ;
  ui     -> Belongings -> setGeometry ( g          ) ;
  ////////////////////////////////////////////////////
  return true                                        ;
}

bool N::EventTasks::startup(SUID uuid)
{
  VarArgs args                  ;
  ui -> Belongings -> clear ( ) ;
  args << uuid                  ;
  start ( 10001 , args )        ;
  return true                   ;
}

void N::EventTasks::List(void)
{
  ui -> Add   -> setEnabled                 ( false )           ;
  ui -> Tasks -> blockSignals               ( true  )           ;
  ui -> Tasks -> clear                      (       )           ;
  ui -> Tasks -> setEnabled                 ( false )           ;
  ui -> Tasks -> lineEdit ( ) -> setEnabled ( false )           ;
  ///////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                              ;
  if ( SC.open( FunctionString , QtUUID::createUuidString() ) ) {
    QString Q                                                   ;
    UUIDs U                                                     ;
    SUID  u                                                     ;
    U = SC . Uuids                                              (
          PlanTable(Tasks)                                      ,
          "uuid"                                                ,
          SC . OrderByAsc ( "id" )                            ) ;
    foreach ( u , U )                                           {
      QString s                                                 ;
      s = SC . getName                                          (
            PlanTable(Names)                                    ,
            "uuid"                                              ,
            vLanguageId                                         ,
            u                                                 ) ;
      ui -> Tasks -> addItem ( s , u )                          ;
    }                                                           ;
    SC . close  ( )                                             ;
  }                                                             ;
  SC   . remove ( )                                             ;
  ///////////////////////////////////////////////////////////////
  ui -> Tasks -> setEnabled                 ( true  )           ;
  ui -> Tasks -> lineEdit ( ) -> setEnabled ( true  )           ;
  ui -> Tasks -> blockSignals               ( false )           ;
  ui -> Add   -> setEnabled                 ( true  )           ;
}

void N::EventTasks::Load(SUID uuid)
{
  ui -> Belongings -> clear ( )                                    ;
  if ( 0 == uuid ) return                                          ;
  //////////////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                                 ;
  if ( SC . open ( FunctionString , QtUUID::createUuidString() ) ) {
    QString Q                                                      ;
    UUIDs   U                                                      ;
    SUID    u                                                      ;
    Q = SC . sql . SelectFrom                                      (
          "first,t1"                                               ,
          PlanTable(Groups)                                        ,
          QString("where `t2` = %1"
                   " and `t1` = %2"
                   " and `relation` = %3"
                   " and `second` = %4"                            )
          . arg ( Types::Schedule                                  )
          . arg ( Types::Task                                      )
          . arg ( Groups::Subordination                            )
          . arg ( uuid                                           ) ,
          SC . OrderByAsc ( "id" )                               ) ;
    SqlLoopNow ( SC , Q )                                          ;
      U << SC . Uuid ( 0 )                                         ;
    SqlLoopErr ( SC , Q )                                          ;
    SqlLoopEnd ( SC , Q )                                          ;
    foreach ( u , U )                                              {
      NewTreeWidgetItem ( IT )                                     ;
      QString n                                                    ;
      n   = SC . getName(PlanTable(Names),"uuid",vLanguageId,u)    ;
      IT -> setData ( 0 , Qt::UserRole , u )                       ;
      IT -> setText ( 0 , n                )                       ;
      ui -> Belongings -> addTopLevelItem ( IT )                   ;
    }                                                              ;
    SC . close  ( )                                                ;
  }                                                                ;
  SC   . remove ( )                                                ;
}

bool N::EventTasks::store(SqlConnection & SC,SUID uuid)
{
  if ( uuid <= 0 ) return false                                          ;
  ////////////////////////////////////////////////////////////////////////
  QString Q                                                              ;
  ////////////////////////////////////////////////////////////////////////
  Q = QString ( "delete from `%1`"
                " where `t2` = %2"
                  " and `t1` = %3"
                  " and `relation` = %4"
                  " and `second` = %5 ;"                                 )
      . arg   ( PlanTable(Groups)                                        )
      . arg   ( Types::Schedule                                          )
      . arg   ( Types::Task                                              )
      . arg   ( Groups::Subordination                                    )
      . arg   ( uuid                                                   ) ;
  SC . Query ( Q )                                                       ;
  ////////////////////////////////////////////////////////////////////////
  for (int i = 0 ; i < ui -> Belongings -> topLevelItemCount ( ) ; i++ ) {
    QTreeWidgetItem * it = ui -> Belongings -> topLevelItem ( i )        ;
    SUID              v  = nTreeUuid ( it , 0 )                          ;
    int               p  = i + 1                                         ;
    Q = QString ( "insert into `%1`"
                  " (`first`,`second`,`t1`,`t2`,`relation`,`position`)"
                  " values (%2,%3,%4,%5,%6,%7) ;"                        )
        . arg   ( PlanTable(Groups)                                      )
        . arg   ( v                                                      )
        . arg   ( uuid                                                   )
        . arg   ( Types::Task                                            )
        . arg   ( Types::Schedule                                        )
        . arg   ( Groups::Subordination                                  )
        . arg   ( p                                                    ) ;
    SC . Query  ( Q                                                    ) ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  return true                                                            ;
}

void N::EventTasks::Add(void)
{
  int index = ui -> Tasks -> currentIndex ( )                       ;
  if ( index < 0 ) return                                           ;
  ///////////////////////////////////////////////////////////////////
  SUID    u   = ui -> Tasks -> itemData ( index ) . toULongLong ( ) ;
  QString ons = ui -> Tasks -> currentText                      ( ) ;
  NewTreeWidgetItem                   ( IT                   )      ;
  IT -> setData                       ( 0 , Qt::UserRole , u )      ;
  IT -> setText                       ( 0 , ons              )      ;
  ui -> Belongings -> addTopLevelItem ( IT                   )      ;
  Alert                               ( Action               )      ;
}

void N::EventTasks::Remove(void)
{
  QList<QTreeWidgetItem *> items                           ;
  items = ui -> Belongings -> selectedItems ( )            ;
  if ( items . count ( ) <= 0 )                            {
    Alert ( Error )                                        ;
    return                                                 ;
  }                                                        ;
  for (int i = 0 ; i < items . count ( ) ; i++ )           {
    QTreeWidgetItem * it = items [ i ]                     ;
    int               index                                ;
    index = ui -> Belongings -> indexOfTopLevelItem ( it ) ;
    if ( index >= 0 )                                      {
      ui -> Belongings -> takeTopLevelItem ( index )       ;
    }                                                      ;
  }                                                        ;
  ui -> Remove -> setEnabled ( false )                     ;
  Alert                      ( Done  )                     ;
}

void N::EventTasks::itemClicked(QTreeWidgetItem * item,int column)
{
  if ( NULL != item )                   {
    ui -> Remove -> setEnabled ( true ) ;
  }                                     ;
  Alert ( Click )                       ;
}

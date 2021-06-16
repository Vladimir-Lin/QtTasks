#include <qttasks.h>

N::SchedulerView:: SchedulerView ( QWidget * parent , Plan * p )
                 : VcfView       (           parent ,        p )
                 , scheduler     ( NULL                        )
                 , locking       ( false                       )
{
  Configure ( ) ;
}

N::SchedulerView::~SchedulerView(void)
{
}

QSize N::SchedulerView::sizeHint(void) const
{
  if ( plan  -> Booleans [ "Desktop" ] ) {
    return QSize ( 1024 ,  720 )         ;
  } else
  if ( plan  -> Booleans [ "Pad"     ] ) {
    return QSize ( 1024 ,  720 )         ;
  } else
  if ( plan  -> Booleans [ "Phone"   ] ) {
    return QSize (  320 ,  480 )         ;
  }                                      ;
  return   QSize ( 1024 ,  720 )         ;
}

void N::SchedulerView::Configure(void)
{
  setOptimizationFlag          ( DontAdjustForAntialiasing  , true ) ;
  setRenderHint                ( QPainter::Antialiasing     , true ) ;
  setRenderHint                ( QPainter::TextAntialiasing , true ) ;
  setWindowTitle               ( tr("Scheduler")                   ) ;
  setScene                     ( Scene                             ) ;
  setTransform                 ( Transform                         ) ;
  setAttribute                 ( Qt::WA_InputMethodEnabled         ) ;
  viewport ( ) -> setAttribute ( Qt::WA_InputMethodEnabled         ) ;
  DefaultZooms                 (                                   ) ;
}

bool N::SchedulerView::Shutdown(void)
{
  return true ;
}

bool N::SchedulerView::Menu(QPoint pos)
{
  return false ;
}

void N::SchedulerView::Reload(void)
{
  FocusIn();
}

void N::SchedulerView::Initialize(void)
{
  scheduler = new VcfScheduler ( this , NULL , plan )   ;
  connect(scheduler,SIGNAL(Append(VcfItem*,VcfItem*))   ,
          this     ,SLOT  (Append(VcfItem*,VcfItem*)) ) ;
  connect(scheduler,SIGNAL(RemoveItem(VcfItem*))        ,
          this     ,SLOT  (Remove    (VcfItem*))      ) ;
  connect(scheduler,SIGNAL(RegionUpdated())             ,
          this     ,SLOT  (RegionUpdated())           ) ;
  connect(scheduler,SIGNAL(Zoom())                      ,
          this     ,SLOT  (Zoom())                    ) ;
  connect(scheduler,SIGNAL(ItemUpdate(SUID))            ,
          this     ,SLOT  (ItemUpdate(SUID))          ) ;
  scheduler -> Options = &Options                       ;
  scene ( ) -> addItem    ( scheduler        )          ;
  addItem                 ( scheduler , NULL )          ;
  scheduler -> setZValue  ( 0.50f            )          ;
  scheduler -> setOpacity ( 0.75f            )          ;
  scheduler -> show       (                  )          ;
  scheduler -> Initialize (                  )          ;
  Zoom                    (                  )          ;
}

void N::SchedulerView::Zoom(void)
{
  if (locking            ) return                   ;
  if (!Mutex.tryLock(100)) return                   ;
  locking = true                                    ;
  QSize  A = available(size())                      ;
  QSizeF C = centimeter (A)                         ;
  QRectF V(0,0,C.width(),C.height())                ;
  QRectF P = plan->paper["A4"].rect(Qt::Horizontal) ;
  QRectF R = Options.Region(P)                      ;
  QRectF Z = asPaper ( A )                          ;
  double dx = ( R.width() - Z.width() ) / 2         ;
  View = Z                                          ;
  if (dx<0) View.setLeft(dx)                        ;
  View.setWidth  (Z.width())                        ;
  setTransform   (Transform)                        ;
  setSceneRect   (View     )                        ;
  QPointF pos = View.topLeft()                      ;
  QRectF  S(0,0,View.width(),View.height())         ;
  pos = Options . Standard ( pos )                  ;
  S   = Options . Standard ( S   )                  ;
  locking = false                                   ;
  Mutex . unlock( )                                 ;
  nIfSafe(scheduler)                                {
    scheduler -> setPos    ( pos )                  ;
    scheduler -> setRegion ( S   )                  ;
  }                                                 ;
}

void N::SchedulerView::PaperMoving(QString name,QPointF pos,QPointF paper,QPointF scene)
{
}

void N::SchedulerView::RegionUpdated(void)
{
  if (locking            ) return                      ;
  if (IsNull(scheduler  )) return                      ;
  if (!Mutex.tryLock(100)) return                      ;
  locking = true                                       ;
  //////////////////////////////////////////////////////
  DMAPs Borders                                        ;
  QRectF P = scheduler -> PaperDPI (      )            ;
  int    X = scheduler -> PaperX   (      )            ;
  int    Y = scheduler -> PaperY   (      )            ;
  double L = scheduler -> LeftBase ( View )            ;
  Borders [ VcfPaper :: Left   ] = 1.00                ;
  Borders [ VcfPaper :: Top    ] = 1.00                ;
  Borders [ VcfPaper :: Right  ] = 1.00                ;
  Borders [ VcfPaper :: Bottom ] = 1.00                ;
  //////////////////////////////////////////////////////
  ClearPapers  (                                     ) ;
  CreatePapers ( Options.DPI,this,Scene,&Options       ,
    SLOT(PaperMoving(QString,QPointF,QPointF,QPointF)) ,
    X,Y,Qt::Horizontal,"A4",Borders                  ) ;
  for (int i=0;i<papers.count();i++)                   {
    papers[i]->Style = VcfPaper::FrameOnly             ;
    papers[i]->setRect(P)                              ;
  }                                                    ;
  //////////////////////////////////////////////////////
  int i = 0                                            ;
  for (int x=0;x<X;x++)                                {
    for (int y=0;y<Y;y++)                              {
      double  V = P.height() * y                       ;
      QPointF B(L,V)                                   ;
      papers [ i ] -> setPos ( B )                     ;
      i++                                              ;
    }                                                  ;
    L += P.width()                                     ;
  }                                                    ;
  //////////////////////////////////////////////////////
  locking = false                                      ;
  Mutex . unlock( )                                    ;
  Alert ( Action )                                     ;
}

void N::SchedulerView::ItemUpdate(SUID uuid)
{
  emit Update ( uuid ) ;
}

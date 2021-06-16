#include <qttasks.h>

N::VcfScheduler:: VcfScheduler ( VcfHeadParaments  )
                : VcfCanvas    ( parent , item , p )
                , Thread       (                   )
                , TimeBar      ( NULL              )
                , Section      ( NULL              )
                , TimeBlock    ( NULL              )
{
  Configure ( ) ;
}

N::VcfScheduler::~VcfScheduler(void)
{
  Timer . stop ( ) ;
}

void N::VcfScheduler::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
  ScheduleMenu ( event -> pos ( ) ) ;
  event -> accept ( )               ;
}

void N::VcfScheduler::Paint(QPainter * painter,QRectF Region,bool clip,bool color)
{
  VcfCanvas::Paint(painter,Region,clip,color) ;
}

void N::VcfScheduler::Configure(void)
{
  Printable = true                                      ;
  Scaling   = false                                     ;
  Editable  = true                                      ;
  setFlag ( ItemIsMovable            , false )          ;
  setFlag ( ItemIsSelectable         , true  )          ;
  setFlag ( ItemIsFocusable          , true  )          ;
  setFlag ( ItemClipsToShape         , false )          ;
  setFlag ( ItemClipsChildrenToShape , false )          ;
  Painter . addMap   ( "Default" , 0                  ) ;
  Painter . addPen   ( 0 , QColor ( 192 , 192 , 192 ) ) ;
  Painter . addPen   ( 1 , QColor (   0 ,   0 ,   0 ) ) ;
  Painter . addBrush ( 0 , QColor ( 252 , 252 , 252 ) ) ;
  nConnect ( &Timer , SIGNAL ( timeout() )              ,
             this   , SLOT   ( Refresh() )            ) ;
  setDropFlag ( DropText     , true  )                  ;
  setDropFlag ( DropUrls     , true  )                  ;
  setDropFlag ( DropImage    , false )                  ;
  setDropFlag ( DropHtml     , true  )                  ;
  setDropFlag ( DropColor    , true  )                  ;
  setDropFlag ( DropTag      , true  )                  ;
  setDropFlag ( DropPicture  , true  )                  ;
  setDropFlag ( DropPeople   , true  )                  ;
  setDropFlag ( DropVideo    , true  )                  ;
  setDropFlag ( DropAlbum    , true  )                  ;
  setDropFlag ( DropGender   , false )                  ;
  setDropFlag ( DropDivision , false )                  ;
  setDropFlag ( DropURIs     , true  )                  ;
  setDropFlag ( DropBookmark , true  )                  ;
  setDropFlag ( DropFont     , true  )                  ;
  setDropFlag ( DropPen      , true  )                  ;
  setDropFlag ( DropBrush    , true  )                  ;
  setDropFlag ( DropGradient , true  )                  ;
  setDropFlag ( DropShape    , false )                  ;
  setDropFlag ( DropMember   , false )                  ;
  setDropFlag ( DropSet      , false )                  ;
}

void N::VcfScheduler::Initialize(void)
{
  Mutex .   lock ( )                                         ;
  QTime T(12,0,0,0)                                          ;
  ////////////////////////////////////////////////////////////
  QDateTime CC = QDateTime::currentDateTime()                ;
  QTime     TT = CC . time ( )                               ;
  if (TT.hour()< 6) T . setHMS ( 6,0,0)                 ; else
  if (TT.hour()>18) T . setHMS (18,0,0)                      ;
  MidDay       = CC                                          ;
  MidDay       . setTime ( T )                               ;
  ////////////////////////////////////////////////////////////
  QGraphicsView * gv = GraphicsView()                        ;
  TimeBar    = new VcfTimeBar ( gv , this , plan    )        ;
  TimeBar   -> Options = Options                             ;
  TimeBar   -> setZValue  ( 0.75f                   )        ;
  TimeBar   -> setOpacity ( 0.90f                   )        ;
  TimeBar   -> setPos     (QPointF(0,0)             )        ;
  TimeBar   -> setRect    (QRectF(0,0,1.0,0.75)     )        ;
  TimeBar   -> setToday   (                         )        ;
  nConnect ( TimeBar , SIGNAL ( TimeUpdated() )              ,
             this    , SLOT   ( TimeUpdated() )     )        ;
  ////////////////////////////////////////////////////////////
  QPen   Pxn ( QColor(128,128, 32)                  )        ;
  QBrush Bxn ( QColor(248,248,  0)                  )        ;
  Pxn . setStyle ( Qt::DashLine                     )        ;
  Bxn . setStyle ( Qt::Dense6Pattern                )        ;
  TimeBlock  = new QGraphicsRectItem ( this         )        ;
  TimeBlock -> setZValue  ( 0.60f                   )        ;
  TimeBlock -> setOpacity ( 0.20f                   )        ;
  TimeBlock -> setPen   ( Pxn                       )        ;
  TimeBlock -> setBrush ( Bxn                       )        ;
  ////////////////////////////////////////////////////////////
  Section = new VcfTimeSection ( gv , this , plan   )        ;
  Section   -> Options = Options                             ;
  Section   -> Start   = TimeBar->Start                      ;
  Section   -> Final   = TimeBar->Final                      ;
  Section   -> setZValue  ( 0.50f                   )        ;
  Section   -> setOpacity ( 0.80f                   )        ;
  Section   -> setPos     (QPointF(0.0,0.75)        )        ;
  Section   -> setRect    (QRectF(0,0,1.0,1.0)      )        ;
  Section   -> FetchFont  (0,"Default"              )        ;
  Section   -> FetchFont  (1,"ToolTip"              )        ;
  nConnect ( Section , SIGNAL(Append(QDateTime,QDateTime))   ,
             this    , SLOT  (Append(QDateTime,QDateTime)) ) ;
  ////////////////////////////////////////////////////////////
  Mutex .   unlock ( )                                       ;
  ////////////////////////////////////////////////////////////
  emit Append ( TimeBar , this )                             ;
  emit Append ( Section , this )                             ;
  ////////////////////////////////////////////////////////////
  Timer . start ( 1000 )                                     ;
}

bool N::VcfScheduler::contains(QDateTime start,QDateTime final)
{
  if (IsNull(TimeBar)                               ) return false ;
  if (final< TimeBar->Start                         ) return false ;
  if (start> TimeBar->Final                         ) return false ;
  if (start>=TimeBar->Start && start<=TimeBar->Final) return true  ;
  if (final>=TimeBar->Start && final<=TimeBar->Final) return true  ;
  if (start<=TimeBar->Start && final>=TimeBar->Final) return true  ;
  return false                                                     ;
}

int N::VcfScheduler::PaperX(void)
{
  if (IsNull(TimeBar)) return 0 ;
  int       x = 1               ;
  QDateTime S = TimeBar->Start  ;
  QDateTime F = TimeBar->Final  ;
  QDateTime E                   ;
  QTime     T(23,59,59,0)       ;
  QTime     Z( 0, 0, 0,0)       ;
  do                            {
    E = S                       ;
    E.setTime(T)                ;
    if (E<F)                    {
      x++                       ;
      S = S.addSecs(86400)      ;
      S . setTime  (Z    )      ;
    }                           ;
  } while (E<F)                 ;
  return    x                   ;
}

int N::VcfScheduler::PaperY(void)
{
  if (IsNull(TimeBar)) return 0   ;
  QRectF P  = PaperDPI()          ;
  double dh = ScreenRect.height() ;
  P   = Options->Region(P)        ;
  int DH = (int)dh                ;
  int DP = (int)P.height()        ;
  int Y  = DH / DP                ;
  int M  = DH % DP                ;
  if (M>0) Y++                    ;
  return Y                        ;
}

QRectF N::VcfScheduler::PaperDPI(void)
{
  return plan->paper["A4"].rect(Qt::Horizontal) ;
}

double N::VcfScheduler::LeftBase(QRectF View)
{
  if (IsNull(TimeBar)) return 0          ;
  QRectF     Z = Options->Standard(View) ;
  QDateTime  S = TimeBar->Start          ;
  QDateTime  F = TimeBar->Final          ;
  QDateTime  L = S                       ;
  QTime      T (0,0,0,0)                 ;
  double x                               ;
  L.setTime(T)                           ;
  int        dt = S.secsTo(F)            ;
  int        ds = L.secsTo(S)            ;
  if (dt<=0) return Z . left ()          ;
  x  = ScreenRect.width()                ;
  x *= ds                                ;
  x /= dt                                ;
  QPointF v(x,x)                         ;
  v = Options->Standard(v)               ;
  x = v.x()                              ;
  return Z . left ( ) - x                ;
}

void N::VcfScheduler::setRegion(QRectF Region)
{
  Mutex .   lock ()                      ;
  ////////////////////////////////////////
  QRectF P = PaperDPI()                  ;
  VcfRectangle::setRect ( Region )       ;
  double dw = ScreenRect.width()         ;
  P   = Options->Region(P)               ;
  dw /= P.width()                        ;
  dw *= 43200                            ;
  ////////////////////////////////////////
  QRectF R = Region                      ;
  R.setHeight(0.75f)                     ;
  if (NotNull(TimeBar))                  {
    TimeBar->Start = MidDay.addSecs(-dw) ;
    TimeBar->Final = MidDay.addSecs( dw) ;
    TimeBar->setRect(R)                  ;
  }                                      ;
  ////////////////////////////////////////
  if (NotNull(Section))                  {
    R.setTop    (0.00f)                  ;
    R.setHeight (1.00f)                  ;
    Section->Start = TimeBar->Start      ;
    Section->Final = TimeBar->Final      ;
    Section->setRect ( R )               ;
    Section->update  (   )               ;
  }                                      ;
  Mutex . unlock ()                      ;
  emit RegionUpdated()                   ;
  QTimer::singleShot(200,this,SLOT(UpdateItems()))  ;
}

void N::VcfScheduler::Refresh(void)
{
  if (IsNull(TimeBar  )) return       ;
  if (IsNull(TimeBlock)) return       ;
  QDateTime S = TimeBar->Start        ;
  QDateTime F = TimeBar->Final        ;
  QDateTime C = nTimeNow              ;
  QRectF    R = ScreenRect            ;
  if (C<S)                            {
    TimeBlock -> setVisible ( false ) ;
    return                            ;
  }                                   ;
  if (C<F)                            {
    int    dt = S.secsTo(F)           ;
    int    ds = S.secsTo(C)           ;
    double dw = ScreenRect.width()    ;
    if (dt>0)                         {
      dw *= ds                        ;
      dw /= dt                        ;
      R . setWidth ( dw )             ;
    }                                 ;
  }                                   ;
  TimeBlock -> setVisible ( true )    ;
  TimeBlock -> setRect    ( R    )    ;
}

void N::VcfScheduler::TimeUpdated(void)
{
  if (IsNull(TimeBar)) return                    ;
  if (IsNull(Section)) return                    ;
  Mutex .   lock ( )                             ;
  int dt = TimeBar->Start.secsTo(TimeBar->Final) ;
  dt /= 2                                        ;
  MidDay = TimeBar -> Start                      ;
  MidDay = MidDay   . addSecs ( dt )             ;
  if (NotNull(Section))                          {
    Section->Start = TimeBar->Start              ;
    Section->Final = TimeBar->Final              ;
    Section->update  (   )                       ;
  }                                              ;
  Mutex . unlock ( )                             ;
  UpdateItems()                                  ;
  emit RegionUpdated ( )                         ;
}

void N::VcfScheduler::Append(QDateTime start,QDateTime final)
{
  int        ds = start.secsTo(final)                 ;
  if (ds<60) return                                   ;
  Font F1 = Section -> Painter . fonts [ 0 ]          ;
  Font F2 = Section -> Painter . fonts [ 1 ]          ;
  VcfGantt * Gantt                                    ;
  Gantt  = new VcfGantt(GraphicsView(),this,plan)     ;
  Gantt -> Uuid             = 0                       ;
  Gantt -> Task             = 0                       ;
  Gantt -> Owner            = 0                       ;
  Gantt -> EventType        = Period                  ;
  Gantt -> Status           = 0                       ;
  Gantt -> Adjust           = 0                       ;
  Gantt -> Painter.fonts[0] = F1                      ;
  Gantt -> Painter.fonts[1] = F2                      ;
  Gantt -> plan             = plan                    ;
  Gantt -> Options          = Options                 ;
  Gantt -> Start            = start                   ;
  Gantt -> Final            = final                   ;
  Gantt -> TabletStart      = TimeBar->Start          ;
  Gantt -> TabletFinal      = TimeBar->Final          ;
  Gantt -> Content          = ""                      ;
  Gantt -> Note             = ""                      ;
  Gantt -> setZValue   ( 0.50f                  )     ;
  Gantt -> setOpacity  ( 1.00f                  )     ;
  Gantt -> setPos      ( QPointF(0,2.00)        )     ;
  Gantt -> setRect     ( QRectF(0,0,0.01,0.75)  )     ;
  Gantt -> DropChanged (                        )     ;
  UpdateGantt          ( Gantt                  )     ;
  Gantts << Gantt                                     ;
  nConnect ( Gantt,SIGNAL(Changed     (VcfGantt*))    ,
             this ,SLOT  (GanttChanged(VcfGantt*)))   ;
  nConnect ( Gantt,SIGNAL(Updated     (VcfGantt*))    ,
             this ,SLOT  (GanttUpdated(VcfGantt*)))   ;
  nConnect ( Gantt,SIGNAL(Edit     (VcfGantt*,int))   ,
             this ,SLOT  (GanttEdit(VcfGantt*,int)) ) ;
  emit Append ( Gantt , this )                        ;
  ArrangeItems ( )                                    ;
  DoProcessEvents                                     ;
  Gantt -> MountEditor   ( )                          ;
}

void N::VcfScheduler::DateTimeFinished(void)
{
  QDateTimeEdit * dte = NULL                       ;
  dte = qobject_cast<QDateTimeEdit *>(Widgets[99]) ;
  if (NotNull(dte))                                {
    MidDay = dte->dateTime()                       ;
  }                                                ;
  DeleteGadgets ( )                                ;
  int dt = TimeBar->Start.secsTo(TimeBar->Final)   ;
  dt /= 2                                          ;
  TimeBar->Start = MidDay                          ;
  TimeBar->Start = TimeBar->Start.addSecs(-dt)     ;
  TimeBar->Final = MidDay                          ;
  TimeBar->Final = TimeBar->Final.addSecs( dt)     ;
  if (NotNull(Section))                            {
    Section->Start = TimeBar->Start                ;
    Section->Final = TimeBar->Final                ;
    Section->update  (   )                         ;
  }                                                ;
  UpdateItems()                                    ;
  emit RegionUpdated ( )                           ;
  Alert ( Done )                                   ;
}

void N::VcfScheduler::UpdateItems(void)
{
  if (IsNull(TimeBar)) return                             ;
  if (IsNull(Section)) return                             ;
  if (!Mutex.tryLock(100)) return                         ;
  setCursor ( Qt::WaitCursor )                            ;
  /////////////////////////////////////////////////////////
  QList<VcfGantt *> OldGantts = Gantts                    ;
  Gantts . clear ( )                                      ;
  for (int i=0;i<OldGantts.count();i++)                   {
    emit RemoveItem(OldGantts[i])                         ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  EventManager  EM ( plan      )                          ;
  SqlConnection SC ( plan->sql )                          ;
  if (SC.open("VcfScheduler","UpdateItems"))              {
    QString Q                                             ;
    UUIDs   Uuids                                         ;
    SUID    uuid                                          ;
    Uuids   = EM.Events(SC,TimeBar->Start,TimeBar->Final) ;
    Font F1 = Section -> Painter  . fonts [ 0 ]           ;
    Font F2 = Section -> Painter  . fonts [ 1 ]           ;
    foreach (uuid,Uuids)                                  {
      Q = SC.sql.SelectFrom                               (
        "owner,type,status,adjust,start,final"            ,
        PlanTable(EventHistory)                           ,
        SC.WhereUuid(uuid)                              ) ;
      if (SC.Fetch(Q))                                    {
        QDateTime S = EM.toDateTime(SC.Tuid(4) )          ;
        QDateTime F = EM.toDateTime(SC.Tuid(5) )          ;
        if (contains(S,F))                                {
          VcfGantt * Gantt                                ;
          Gantt  = new VcfGantt(GraphicsView(),this,plan) ;
          Gantt -> Uuid                 = uuid            ;
          Gantt -> Task                 = 0               ;
          Gantt -> Owner                = SC.Uuid(0)      ;
          Gantt -> EventType            = SC.Int (1)      ;
          Gantt -> Status               = SC.Int (2)      ;
          Gantt -> Adjust               = SC.Int (3)      ;
          Gantt -> Painter.fonts    [0] = F1              ;
          Gantt -> Painter.fonts    [1] = F2              ;
          Gantt -> plan      = plan                       ;
          Gantt -> Options   = Options                    ;
          Gantt -> Start     = EM.toDateTime(SC.Tuid(4))  ;
          Gantt -> Final     = EM.toDateTime(SC.Tuid(5))  ;
          Gantt -> TabletStart = TimeBar->Start           ;
          Gantt -> TabletFinal = TimeBar->Final           ;
          Gantt -> Note = SC.getName                      (
            PlanTable(EventNotes)                         ,
            "uuid",vLanguageId,uuid                    )  ;
          Gantt -> setZValue  ( 0.50f                  )  ;
          Gantt -> setOpacity ( 1.00f                  )  ;
          Gantt -> setPos     (QPointF(0,2.00)         )  ;
          Gantt -> setRect    (QRectF(0,0,0.01,0.75)   )  ;
          Gantt -> Content = EM . Name ( SC , uuid     )  ;
          Gantt -> DropChanged(                        )  ;
          Gantts << Gantt                                 ;
          connect(Gantt,SIGNAL(Changed     (VcfGantt*))   ,
                  this ,SLOT  (GanttChanged(VcfGantt*)))  ;
          connect(Gantt,SIGNAL(Updated     (VcfGantt*))   ,
                  this ,SLOT  (GanttUpdated(VcfGantt*)))  ;
          connect(Gantt,SIGNAL(Edit     (VcfGantt*,int))  ,
                  this ,SLOT  (GanttEdit(VcfGantt*,int))) ;
        }                                                 ;
      }                                                   ;
    }                                                     ;
    SC.close ( )                                          ;
  }                                                       ;
  SC.remove  ( )                                          ;
  setCursor ( Qt::ArrowCursor )                           ;
  Mutex . unlock ( )                                      ;
  for (int i=0;i<Gantts.count();i++)                      {
    VcfGantt * Gantt = Gantts [ i ]                       ;
    emit Append ( Gantt , this )                          ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  DoProcessEvents                                         ;
  ArrangeItems          ( )                               ;
}

void N::VcfScheduler::ArrangeItems(void)
{
  if (IsNull(TimeBar)    ) return                             ;
  if (IsNull(Section)    ) return                             ;
  if (Gantts.count()<=0  ) return                             ;
  if (!Mutex.tryLock(500)) return                             ;
  QPainterPath Path                                           ;
  for (int i=0;i<Gantts.count();i++)                          {
    VcfGantt * Gantt = Gantts[i]                              ;
    QDateTime S = Gantt->Start                                ;
    QDateTime F = Gantt->Final                                ;
    if (TimeBar->Start>S)                                     {
      S = TimeBar->Start                                      ;
    }                                                         ;
    if (TimeBar->Final<F)                                     {
      F = TimeBar->Final                                      ;
    }                                                         ;
    double  x1 = Section->X(S)                                ;
    double  x2 = Section->X(F)                                ;
    double  dx = x2 - x1                                      ;
    double  dy = 2.00                                         ;
    QPointF dw ( dx ,  0 )                                    ;
    QPointF dp ( x1 ,  0 )                                    ;
    QPointF yh (  0 , dy )                                    ;
    QRectF  ss = ScreenRect                                   ;
    dw = Options->Standard(dw)                                ;
    dp = Options->Standard(dp)                                ;
    yh = Options->Standard(yh)                                ;
    ss.setTop   (yh.y()             )                         ;
    ss.setBottom(ScreenRect.bottom())                         ;
    QPainterPath B                                            ;
    do                                                        {
      QPainterPath path                                       ;
      QPointF ds(dp.x(),dy         )                          ;
      QRectF  dr(0,0,dw.x(),0.75   )                          ;
      Gantt -> setPos  ( ds        )                          ;
      Gantt -> setRect ( dr        )                          ;
      Gantt -> Available = mapToItem(Gantt,ss).boundingRect() ;
      Gantt -> update  (           )                          ;
      DoProcessEvents                                         ;
      path   = Gantt->shape()                                 ;
      B      = mapFromItem(Gantt,path)                        ;
      dy    += 1.0                                            ;
    } while (Path.intersects(B))                              ;
    Path . addPath ( B )                                      ;
  }                                                           ;
  for (int i=0;i<Gantts.count();i++)                          {
    Gantts [ i ] -> GanttUpdated ( )                          ;
    Gantts [ i ] -> DropChanged  ( )                          ;
  }                                                           ;
  Mutex . unlock ( )                                          ;
  update ( )                                                  ;
}

void N::VcfScheduler::GoToNow(void)
{
  QTime T(12,0,0,0)                              ;
  ////////////////////////////////////////////////
  QDateTime CC = QDateTime::currentDateTime()    ;
  QTime     TT = CC . time ( )                   ;
  if (TT.hour()< 6) T . setHMS ( 6,0,0)     ; else
  if (TT.hour()>18) T . setHMS (18,0,0)          ;
  MidDay       = CC                              ;
  MidDay       . setTime ( T )                   ;
  DeleteGadgets ( )                              ;
  int dt = TimeBar->Start.secsTo(TimeBar->Final) ;
  dt /= 2                                        ;
  TimeBar->Start = MidDay                        ;
  TimeBar->Start = TimeBar->Start.addSecs(-dt)   ;
  TimeBar->Final = MidDay                        ;
  TimeBar->Final = TimeBar->Final.addSecs( dt)   ;
  if (NotNull(Section))                          {
    Section->Start = TimeBar->Start              ;
    Section->Final = TimeBar->Final              ;
    Section->update  (   )                       ;
  }                                              ;
  UpdateItems()                                  ;
  emit RegionUpdated ( )                         ;
  Alert ( Done )                                 ;
}

void N::VcfScheduler::GoToTime(void)
{
  QDateTimeEdit        * dte   = new QDateTimeEdit        (    ) ;
  QGraphicsProxyWidget * proxy = new QGraphicsProxyWidget (this) ;
  proxy -> setFlag   ( ItemAcceptsInputMethod , true )           ;
  proxy -> setWidget ( dte                           )           ;
  Proxys  [ 99 ] = proxy                                         ;
  Widgets [ 99 ] = dte                                           ;
  dte -> setDateTime ( MidDay )                                  ;
  Font F1 = Section -> Painter.fonts[0]                          ;
  F1   . setDPI  ( Options->DPI )                                ;
  dte -> setFont ( F1           )                                ;
  QRectF  SR = Section -> ScreenRect                             ;
  QPointF CR = SR       . center ( )                             ;
  QPointF GR ( 5.60 , 0.60 )                                     ;
  CR = mapFromItem ( Section , CR )                              ;
  GR = Options -> position( GR )                                 ;
  QRectF  DR(CR.x()-(GR.x()/2),CR.y()-(GR.y()/2),GR.x(),GR.y())  ;
  proxy -> setGeometry (  DR  )                                  ;
  proxy -> setZValue   ( 1.00 )                                  ;
  proxy -> setOpacity  ( 1.00 )                                  ;
  connect(dte ,SIGNAL(editingFinished ())                        ,
          this,SLOT  (DateTimeFinished())                      ) ;
  dte -> setFocus ( Qt::TabFocusReason )                         ;
}

void N::VcfScheduler::GanttChanged(VcfGantt * gantt)
{
  UpdateGantt  ( gantt ) ;
  ArrangeItems (       ) ;
}

void N::VcfScheduler::GanttUpdated(VcfGantt * gantt)
{
  update ( ) ;
}

bool N::VcfScheduler::UpdateGantt(VcfGantt * gantt)
{
  EventManager EM ( plan )                         ;
  EnterSQL ( SC , plan->sql )                      ;
    ////////////////////////////////////////////////
    QString   Q                                    ;
    QDateTime CC = QDateTime::currentDateTime()    ;
    StarDate ST                                    ;
    StarDate FT                                    ;
    if (gantt->Uuid<=0)                            {
      gantt->Uuid = EM . AssureUuid ( SC )         ;
    }                                              ;
    EM.UpdateType                                  (
      SC                                           ,
      PlanTable(EventHistory)                      ,
      gantt->Uuid,gantt->EventType               ) ;
    ////////////////////////////////////////////////
    if (CC>gantt->Final)                           {
      EM.Delete(SC,gantt->Uuid)                    ;
    } else                                         {
      EM.AssureEvent                               (
        SC                                         ,
        gantt->Uuid                                ,
        gantt->EventType                         ) ;
      EM.UpdateType                                (
        SC                                         ,
        PlanTable(Events)                          ,
        gantt->Uuid,gantt->EventType             ) ;
    }                                              ;
    ////////////////////////////////////////////////
    EM . assureName                                (
      SC                                           ,
      gantt -> Uuid                                ,
      plan  -> LanguageId                          ,
      gantt -> Content                           ) ;
    ST = gantt->Start                              ;
    FT = gantt->Final                              ;
    EM.UpdateEvent                                 (
      SC,gantt->Uuid                               ,
      Calendars::Duration                          ,
      ST.Stardate,FT.Stardate                    ) ;
    EM.attachSpot                                  (
      SC,gantt->Uuid                               ,
      History::WorkingPeriod                       ,
      ST.Stardate,FT.Stardate                    ) ;
    ////////////////////////////////////////////////
    if (CC>gantt->Final)                           {
      EM . DeleteScheduling ( SC , gantt->Uuid )   ;
    } else                                         {
      EM . AddScheduling    ( SC , gantt->Uuid )   ;
    }                                              ;
    ////////////////////////////////////////////////
  LeaveSQL ( SC , plan->sql )                      ;
  gantt -> DropChanged (                     )     ;
  emit ItemUpdate  ( gantt->Uuid             )     ;
  Alert            ( Done                    )     ;
  update           (                         )     ;
  return true                                      ;
}

void N::VcfScheduler::DeleteGantt(VcfGantt * gantt)
{
}

void N::VcfScheduler::ItemFinished(VcfItem * item)
{
  emit RemoveItem ( item ) ;
}

void N::VcfScheduler::AttachNote(VcfGantt * gantt)
{
  QPointF        GC   = gantt->ScreenRect.topLeft()        ;
  VcfInterface * vine = NULL                               ;
  GanttNote    * note = NULL                               ;
  vine = new VcfInterface ( GraphicsView() , this , plan ) ;
  note = new GanttNote    ( NULL , plan                  ) ;
  QRect RN = note->geometry()                              ;
  QRect RF( 0, 0,RN.width()+8,RN.height()+36)              ;
  QRect RC( 4,32,RN.width()  ,RN.height()   )              ;
  QRect RH( 4, 4,RN.width()  ,            24)              ;
  GC = mapFromItem(gantt,GC)                               ;
  GC = Options->Standard(GC)                               ;
  QPointF GP (GC.x(),GC.y()+3.0)                           ;
  vine -> plan       = plan                                ;
  vine -> Scaling    = false                               ;
  vine -> showHeader = true                                ;
  vine -> Title      = note->windowTitle()                 ;
  vine -> setOptions      ( *Options , true      )         ;
  vine -> setZValue       ( 1.00f                )         ;
  vine -> setWidget       ( note  , GP , RF , RC )         ;
  vine -> HeaderRect = RH                                  ;
  emit Append ( vine , this )                              ;
  note -> setGantt ( gantt->Uuid , gantt->Content )        ;
  nConnect ( vine , SIGNAL(Finish      (VcfItem*))         ,
             this , SLOT  (ItemFinished(VcfItem*))       ) ;
  nConnect ( note , SIGNAL(Finish())                       ,
             vine , SLOT  (Finish())                     ) ;
}

void N::VcfScheduler::EditGantt(VcfGantt * gantt)
{
  switch ( gantt->EventType ) {
    case N::Notify            :
    break                     ;
    case N::Period            :
    break                     ;
    case N::Record            :
    break                     ;
    case N::Meeting           :
    break                     ;
    case N::Automation        :
    break                     ;
    case N::Operation         :
    break                     ;
    case N::Sync              :
    break                     ;
    case N::Download          :
    break                     ;
    case N::Upload            :
    break                     ;
    case N::Audio             :
    break                     ;
    case N::Video             :
    break                     ;
    case N::TV                :
    break                     ;
    case N::Programming       :
    break                     ;
    case N::Backup            :
    break                     ;
    case N::FileUpdate        :
    break                     ;
    case N::Cooking           :
    break                     ;
    case N::Sleep             :
    break                     ;
    case N::Housework         :
    break                     ;
    case N::Shopping          :
    break                     ;
    case N::Communication     :
    break                     ;
    default                   :
    break                     ;
  }                           ;
}

void N::VcfScheduler::GanttTime(VcfGantt * gantt)
{
  QPointF         GC   = gantt->ScreenRect.topLeft()        ;
  VcfInterface  * vine = NULL                               ;
  GanttDuration * Dura = NULL                               ;
  vine = new VcfInterface  ( GraphicsView() , this , plan ) ;
  Dura = new GanttDuration ( NULL , plan                  ) ;
  QRect  RN = Dura->geometry()                              ;
  QRect  RF( 0, 0,RN.width()+8,RN.height()+36)              ;
  QRect  RC( 4,32,RN.width()  ,RN.height()   )              ;
  QRectF RH( 4, 4,RN.width()  ,            24)              ;
  GC = mapFromItem(gantt,GC)                                ;
  GC = Options->Standard(GC)                                ;
  QPointF GP (GC.x(),GC.y()+3.0)                            ;
  vine -> Scaling    = false                                ;
  vine -> showHeader = true                                 ;
  vine -> Title      = Dura->windowTitle()                  ;
  vine -> setOptions      ( *Options , true      )          ;
  vine -> setZValue       ( 1.00f                )          ;
  vine -> setWidget       ( Dura  , GP , RF , RC )          ;
  vine -> HeaderRect = RH                                   ;
  emit Append ( vine , this )                               ;
  Dura -> Gantt = gantt                                     ;
  connect(vine,SIGNAL(Finish      (VcfItem*))               ,
          this,SLOT  (ItemFinished(VcfItem*))       )       ;
  connect(Dura,SIGNAL(Finish())                             ,
          vine,SLOT  (Finish())                     )       ;
  connect(Dura ,SIGNAL(GanttChanged(VcfGantt*))             ,
          this ,SLOT  (GanttChanged(VcfGantt*))     )       ;
  Dura -> Prepare ( )                                       ;
}

void N::VcfScheduler::GanttTriggers(VcfGantt * gantt)
{
  QPointF         GC   = gantt->ScreenRect.topLeft()  ;
  VcfInterface     * vine = NULL                      ;
  N::GanttTriggers * Trig = NULL                      ;
  vine = new VcfInterface  (GraphicsView(),this,plan) ;
  Trig = new N::GanttTriggers ( NULL , plan         ) ;
  QRect RN = Trig->geometry()                         ;
  QRect RF( 0, 0,RN.width()+8,RN.height()+36)         ;
  QRect RC( 4,32,RN.width()  ,RN.height()   )         ;
  QRect RH( 4, 4,RN.width()  ,            24)         ;
  GC = mapFromItem(gantt,GC)                          ;
  GC = Options->Standard(GC)                          ;
  QPointF GP (GC.x(),GC.y()+3.0)                      ;
  vine -> Scaling    = false                          ;
  vine -> showHeader = true                           ;
  vine -> Title      = Trig->windowTitle()            ;
  vine -> setOptions      ( *Options , true      )    ;
  vine -> setZValue       ( 1.00f                )    ;
  vine -> setWidget       ( Trig  , GP , RF , RC )    ;
  vine -> HeaderRect = RH                             ;
  emit Append ( vine , this )                         ;
  Trig -> Gantt = gantt                               ;
  connect(vine,SIGNAL(Finish      (VcfItem*))         ,
          this,SLOT  (ItemFinished(VcfItem*))       ) ;
  connect(Trig,SIGNAL(Finish())                       ,
          vine,SLOT  (Finish())                     ) ;
  connect(Trig ,SIGNAL(GanttChanged(VcfGantt*))       ,
          this ,SLOT  (GanttChanged(VcfGantt*))     ) ;
  Trig -> Prepare ( )                                 ;
}

void N::VcfScheduler::GanttEdit(VcfGantt * gantt,int Id)
{
  switch (Id)                                     {
    case 101                                      : // Edit
      EditGantt     ( gantt )                     ;
    break                                         ;
    case 102                                      : // Set start time
    case 103                                      : // Set finish time
      GanttTime     ( gantt )                     ;
    break                                         ;
    case 104                                      : // Delete
      DeleteGantt   ( gantt )                     ;
    break                                         ;
    case 105                                      : // Job start now
      gantt->Start = QDateTime::currentDateTime() ;
      if (gantt->Final<gantt->Start)              {
        QDateTime GS = gantt->Start               ;
        GS = GS.addSecs(60*30)                    ;
        gantt->Final = GS                         ;
      }                                           ;
      UpdateGantt   ( gantt )                     ;
      ArrangeItems  (       )                     ;
    break                                         ;
    case 106                                      : // Job finished
      gantt->Final = QDateTime::currentDateTime() ;
      UpdateGantt   ( gantt )                     ;
      ArrangeItems  (       )                     ;
    break                                         ;
    case 901                                      : // Owner
    break                                         ;
    case 902                                      : // Task
    break                                         ;
    case 903                                      : // Note
      AttachNote    ( gantt )                     ;
    break                                         ;
    case 904                                      : // Set start trigger
    case 905                                      : // Set finish trigger
      GanttTriggers ( gantt )                     ;
    break                                         ;
  }                                               ;
}

void N::VcfScheduler::MountAudios(void)
{
  ///////////////////////////////////////////////////
  //                Start position                 //
  ///////////////////////////////////////////////////
  QPointF PS(8.5,4.0)                               ;
  QPointF RX = ScreenRect.topRight()                ;
  QPointF SS                                        ;
  PS = Options->position(PS)                        ;
  PS . setX ( RX . x ( ) - PS . x ( ) )             ;
  PS . setY ( RX . y ( ) + PS . y ( ) )             ;
  SS = PS                                           ;
  PS = Options->Standard(PS)                        ;
  ///////////////////////////////////////////////////
  //                   Regions                     //
  ///////////////////////////////////////////////////
  QRect    RF ( 0 ,  0 , 1 ,  1 )                   ;
  QRect    RC ( 4 , 32 , 1 ,  1 )                   ;
  QRect    RH ( 4 ,  4 , 1 , 24 )                   ;
  QRect    RR                                       ;
  QRectF   MS ( SS.x() , SS.y() , 0 , 0 )           ;
  QPolygon PR                                       ;
  MS . setRight   ( ScreenRect . right  ( ) - 40 )  ;
  MS . setBottom  ( ScreenRect . bottom ( ) - 40 )  ;
  MS = mapToScene ( MS ) . boundingRect ( )         ;
  PR = GraphicsView() -> mapFromScene ( MS )        ;
  RR = PR . boundingRect ( )                        ;
  RF . setWidth   ( RR . width  ( )              )  ;
  RF . setHeight  ( RR . height ( )              )  ;
  RC . setWidth   ( RR . width  ( ) - 8          )  ;
  RC . setHeight  ( RR . height ( ) - 36         )  ;
  RH . setWidth   ( RR . width  ( ) - 8          )  ;
  ///////////////////////////////////////////////////
  VcfInterface  * vine = NULL                       ;
  N::AudioLists * alsw = NULL                       ;
  vine = new VcfInterface(GraphicsView(),this,plan) ;
  alsw = new N::AudioLists ( NULL , plan          ) ;
  ///////////////////////////////////////////////////
  vine -> showHeader = true                         ;
  vine -> Title      = alsw -> windowTitle ()       ;
  vine -> setOptions ( *Options , true     )        ;
  vine -> setZValue  ( 1.00f               )        ;
  vine -> setOpacity ( 1.00f               )        ;
  vine -> setWidget  ( alsw , PS , RF , RC )        ;
  vine -> HeaderRect = RH                           ;
  emit Append ( vine , this )                       ;
  alsw -> List ( )                                  ;
  connect(vine,SIGNAL(Finish      (VcfItem*))       ,
          this,SLOT  (ItemFinished(VcfItem*))     ) ;
  connect(alsw,SIGNAL(Finish())                     ,
          vine,SLOT  (Finish())                   ) ;
}

void N::VcfScheduler::MountTriggers(void)
{
  ///////////////////////////////////////////////////
  //                Start position                 //
  ///////////////////////////////////////////////////
  QPointF PS(8.5,4.0)                               ;
  QPointF RX = ScreenRect.topRight()                ;
  QPointF SS                                        ;
  PS = Options->position(PS)                        ;
  PS . setX ( RX . x ( ) - PS . x ( ) )             ;
  PS . setY ( RX . y ( ) + PS . y ( ) )             ;
  SS = PS                                           ;
  PS = Options->Standard(PS)                        ;
  ///////////////////////////////////////////////////
  //                   Regions                     //
  ///////////////////////////////////////////////////
  QRect    RF ( 0 ,  0 , 1 ,  1 )                   ;
  QRect    RC ( 4 , 32 , 1 ,  1 )                   ;
  QRect    RH ( 4 ,  4 , 1 , 24 )                   ;
  QRect    RR                                       ;
  QRectF   MS ( SS.x() , SS.y() , 0 , 0 )           ;
  QPolygon PR                                       ;
  MS . setRight   ( ScreenRect . right  ( ) - 40 )  ;
  MS . setBottom  ( ScreenRect . bottom ( ) - 40 )  ;
  MS = mapToScene ( MS ) . boundingRect ( )         ;
  PR = GraphicsView() -> mapFromScene ( MS )        ;
  RR = PR . boundingRect ( )                        ;
  RF . setWidth   ( RR . width  ( )              )  ;
  RF . setHeight  ( RR . height ( )              )  ;
  RC . setWidth   ( RR . width  ( ) - 8          )  ;
  RC . setHeight  ( RR . height ( ) - 36         )  ;
  RH . setWidth   ( RR . width  ( ) - 8          )  ;
  ///////////////////////////////////////////////////
  VcfInterface     * vine = NULL                    ;
  N::TriggerEditor * nte  = NULL                    ;
  vine = new VcfInterface(GraphicsView(),this,plan) ;
  nte  = new N::TriggerEditor ( NULL , plan       ) ;
  ///////////////////////////////////////////////////
  vine -> showHeader = true                         ;
  vine -> Title      = nte -> windowTitle ()        ;
  vine -> setOptions ( *Options , true     )        ;
  vine -> setZValue  ( 1.00f               )        ;
  vine -> setOpacity ( 1.00f               )        ;
  vine -> setWidget  ( nte , PS , RF , RC  )        ;
  vine -> HeaderRect = RH                           ;
  emit Append ( vine , this )                       ;
  connect(nte           ,SIGNAL(Clicked    (SUID))  ,
          this          ,SLOT  (Trigger    (SUID))) ;
  nte -> List ( )                                   ;
  nConnect ( vine , SIGNAL(Finish      (VcfItem*))  ,
             this , SLOT  (ItemFinished(VcfItem*))) ;
}

void N::VcfScheduler::Trigger(SUID uuid)
{
  ///////////////////////////////////////////////////
  //                Start position                 //
  ///////////////////////////////////////////////////
  QPointF PS(12.0,12.0)                             ;
  QPointF PW                                        ;
  QPointF RX = ScreenRect.center()                  ;
  QPointF SS                                        ;
  PS = Options->position(PS)                        ;
  PW = PS                                           ;
  PS . setX ( RX . x ( ) - (PS . x ( ) / 2) )       ;
  PS . setY ( RX . y ( ) - (PS . y ( ) / 2) )       ;
  SS = PS                                           ;
  PS = Options->Standard(PS)                        ;
  ///////////////////////////////////////////////////
  //                   Regions                     //
  ///////////////////////////////////////////////////
  QRect    RF ( 0 ,  0 , 1 ,  1 )                   ;
  QRect    RC ( 4 , 32 , 1 ,  1 )                   ;
  QRect    RH ( 4 ,  4 , 1 , 24 )                   ;
  QRect    RR                                       ;
  QRectF   MS ( PS.x() , PS.y() , 0 , 0 )           ;
  QPolygon PR                                       ;
  MS . setWidth  ( PW.x() )                         ;
  MS . setHeight ( PW.y() )                         ;
  MS = mapToScene ( MS ) . boundingRect ( )         ;
  PR = GraphicsView() -> mapFromScene ( MS )        ;
  RR = PR . boundingRect ( )                        ;
  RF . setWidth   ( RR . width  ( )              )  ;
  RF . setHeight  ( RR . height ( )              )  ;
  RC . setWidth   ( RR . width  ( ) - 8          )  ;
  RC . setHeight  ( RR . height ( ) - 36         )  ;
  RH . setWidth   ( RR . width  ( ) - 8          )  ;
  ///////////////////////////////////////////////////
  VcfInterface       * vine = NULL                  ;
  N::TriggerProperty * ntp  = NULL                  ;
  vine = new VcfInterface(GraphicsView(),this,plan) ;
  ntp  = new N::TriggerProperty ( NULL , plan     ) ;
  ///////////////////////////////////////////////////
  vine -> showHeader = true                         ;
  vine -> Title      = ntp -> windowTitle ()        ;
  vine -> setOptions ( *Options , true     )        ;
  vine -> setZValue  ( 1.00f               )        ;
  vine -> setOpacity ( 1.00f               )        ;
  vine -> setWidget  ( ntp , PS , RF , RC  )        ;
  vine -> HeaderRect = RH                           ;
  emit Append ( vine , this )                       ;
  ntp -> load   (uuid)                              ;
  nConnect ( vine , SIGNAL(Finish      (VcfItem*))  ,
             this , SLOT  (ItemFinished(VcfItem*))) ;
  nConnect ( ntp  , SIGNAL(Closed())                ,
             vine , SLOT  (Finish())              ) ;
}

bool N::VcfScheduler::dropText(QWidget * source,QPointF pos,const QString & text)
{
  return false ;
}

bool N::VcfScheduler::dropUrls(QWidget * source,QPointF pos,const QList<QUrl> & urls)
{
  return false ;
}

bool N::VcfScheduler::dropHtml(QWidget * source,QPointF pos,const QString & html)
{
  return false ;
}

bool N::VcfScheduler::dropColor(QWidget * source,QPointF pos,const QColor & color)
{
  return false ;
}

bool N::VcfScheduler::dropTags(QWidget * source,QPointF pos,const UUIDs & Uuids)
{
  return false ;
}

bool N::VcfScheduler::dropPictures(QWidget * source,QPointF pos,const UUIDs & Uuids)
{
  return false ;
}

bool N::VcfScheduler::dropPeople(QWidget * source,QPointF pos,const UUIDs & Uuids)
{
  return false ;
}

bool N::VcfScheduler::dropVideos(QWidget * source,QPointF pos,const UUIDs & Uuids)
{
  return false ;
}

bool N::VcfScheduler::dropAlbums(QWidget * source,QPointF pos,const UUIDs & Uuids)
{
  return false ;
}

bool N::VcfScheduler::dropURIs(QWidget * source,QPointF pos,const UUIDs & Uuids)
{
  return false ;
}

bool N::VcfScheduler::dropBookmarks(QWidget * source,QPointF pos,const UUIDs & Uuids)
{
  return false ;
}

bool N::VcfScheduler::dropFont(QWidget * source,QPointF pos,const SUID font)
{
  return false ;
}

bool N::VcfScheduler::dropPen(QWidget * source,QPointF pos,const SUID pen)
{
  return false ;
}

bool N::VcfScheduler::dropBrush(QWidget * source,QPointF pos,const SUID brush)
{
  return false ;
}

bool N::VcfScheduler::dropGradient(QWidget * source,QPointF pos,const SUID gradient)
{
  return false ;
}

bool N::VcfScheduler::ScheduleMenu(QPointF)
{
  VcfScopedMenu ( mm )                       ;
  QMenu      * ma                            ;
  QMenu      * mt                            ;
  QAction    * aa                            ;
  ma = mm.addMenu(tr("Adjustments"))         ;
  mt = mm.addMenu(tr("Tools"      ))         ;
  mm.add(ma,101,tr("Show current duration")) ;
  mm.add(ma,102,tr("Go to specific time"  )) ;
  mm.add(ma,103,tr("Refresh"              )) ;
  mm.add(mt,201,tr("Trigger lists"        )) ;
  mm.add(mt,202,tr("Audio lists"          )) ;
  mm.setFont(plan)                           ;
  aa = mm.exec(QCursor::pos())               ;
  if (IsNull(aa)) return false               ;
  switch (mm[aa])                            {
    case 101                                 :
      GoToNow       ( )                      ;
    break                                    ;
    case 102                                 :
      GoToTime      ( )                      ;
    break                                    ;
    case 103                                 :
      emit Zoom     ( )                      ;
    break                                    ;
    case 201                                 :
      MountTriggers ( )                      ;
    break                                    ;
    case 202                                 :
      MountAudios   ( )                      ;
    break                                    ;
  }                                          ;
  return true                                ;
}

void N::VcfScheduler::run(int Type,ThreadData * data)
{ Q_UNUSED ( Type ) ;
  Q_UNUSED ( data ) ;
}

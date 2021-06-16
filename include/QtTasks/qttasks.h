/****************************************************************************
 *                                                                          *
 * Copyright (C) 2015 Neutrino International Inc.                           *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_TASKS_H
#define QT_TASKS_H

#include <QtVCF>
#include <DataWidgets>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTTASKS_LIB)
#      define Q_TASKS_EXPORT Q_DECL_EXPORT
#    else
#      define Q_TASKS_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_TASKS_EXPORT
#endif

namespace Ui                          {
class Q_TASKS_EXPORT nGanttNote       ;
class Q_TASKS_EXPORT nGanttDuration   ;
class Q_TASKS_EXPORT nGanttTriggers   ;
class Q_TASKS_EXPORT nEventTriggers   ;
class Q_TASKS_EXPORT NotifierTrigger  ;
class Q_TASKS_EXPORT nTriggerProperty ;
class Q_TASKS_EXPORT PeriodEditor     ;
class Q_TASKS_EXPORT nExecutionEditor ;
class Q_TASKS_EXPORT nEventOwners     ;
class Q_TASKS_EXPORT nEventTasks      ;
class Q_TASKS_EXPORT nEventDependency ;
class Q_TASKS_EXPORT nRepeatedEvent   ;
class Q_TASKS_EXPORT nBriefEvent      ;
class Q_TASKS_EXPORT FileTransferUI   ;
}

namespace N
{

class Q_TASKS_EXPORT TaskDocks       ;
class Q_TASKS_EXPORT EventDocks      ;
class Q_TASKS_EXPORT ExecutionLists  ;
class Q_TASKS_EXPORT ExecutionView   ;
class Q_TASKS_EXPORT ExecutionEditor ;
class Q_TASKS_EXPORT GanttNote       ;
class Q_TASKS_EXPORT GanttDuration   ;
class Q_TASKS_EXPORT GanttTriggers   ;
class Q_TASKS_EXPORT EventTriggers   ;
class Q_TASKS_EXPORT NotifierTrigger ;
class Q_TASKS_EXPORT TriggerProperty ;
class Q_TASKS_EXPORT TriggerEditor   ;
class Q_TASKS_EXPORT EventOwners     ;
class Q_TASKS_EXPORT EventTasks      ;
class Q_TASKS_EXPORT EventDependency ;
class Q_TASKS_EXPORT RepeatedEvent   ;
class Q_TASKS_EXPORT PeriodEditor    ;
class Q_TASKS_EXPORT BriefEvent      ;
class Q_TASKS_EXPORT VcfScheduler    ;
class Q_TASKS_EXPORT MonitorSize     ;
class Q_TASKS_EXPORT SchedulerView   ;
class Q_TASKS_EXPORT PeriodBlock     ;
class Q_TASKS_EXPORT EventObject     ;
class Q_TASKS_EXPORT CalendarObject  ;

/*****************************************************************************
 *                                                                           *
 *                              Scheduler and tasks                          *
 *                                                                           *
 *****************************************************************************/

class Q_TASKS_EXPORT TaskDocks : public TreeDock
                               , public TaskManager
{
  Q_OBJECT
  public:

    explicit TaskDocks           (StandardConstructor) ;
    virtual ~TaskDocks           (void);

    void Store                   (QMainWindow * Main);

  protected:

    NAMEs behaviors ;
    NAMEs states    ;

    virtual bool FocusIn         (void);
    virtual void Configure       (void) ;

    virtual QMimeData * dragMime (void);

    virtual bool    dropNew      (QWidget * source,const QMimeData * mime,QPoint pos);
    virtual bool    dropMoving   (QWidget * source,const QMimeData * mime,QPoint pos);
    virtual bool    dropAppend   (QWidget * source,const QMimeData * mime,QPoint pos);

    virtual QString MimeType     (const QMimeData * mime);
    virtual UUIDs   MimeUuids    (const QMimeData * mime,QString mimetype) ;

    virtual void    run          (int Type,ThreadData * data) ;

  private:

  public slots:

    virtual void Docking         (QMainWindow * Main,QString title,Qt::DockWidgetArea area,Qt::DockWidgetAreas areas);

    virtual bool Shutdown        (void) ;
    virtual bool List            (void) ;
    virtual void New             (void) ;
    virtual void Obsolete        (void) ;

    virtual bool startup         (void) ;

  protected slots:

    virtual void doubleClicked   (QTreeWidgetItem * item,int column) ;
    virtual bool Menu            (QPoint pos);

    void removeOldItem           (void) ;
    void editingFinished         (void) ;
    void behaviorChanged         (int behavior) ;
    void stateChanged            (int state) ;

  private slots:

  signals:

    void Details                 (UUIDs & Uuids) ;

} ;

class Q_TASKS_EXPORT EventDocks : public TreeDock
{
  Q_OBJECT
  public:

    bool    Editable   ;
    QString EventTable ;

    explicit EventDocks          (StandardConstructor) ;
    virtual ~EventDocks          (void);

    void Store                   (QMainWindow * Main);

  protected:

    NAMEs TypeNames ;
    UUIDs NameUuids ;
    CMAPs TypeUuids ;
    RMAPs UuidTypes ;

    virtual bool FocusIn         (void) ;
    virtual void Configure       (void) ;

    virtual QMimeData * dragMime (void);

    virtual bool    dropNew      (QWidget * source,const QMimeData * mime,QPoint pos);
    virtual bool    dropMoving   (QWidget * source,const QMimeData * mime,QPoint pos);
    virtual bool    dropAppend   (QWidget * source,const QMimeData * mime,QPoint pos);

    virtual QString MimeType     (const QMimeData * mime);
    virtual UUIDs   MimeUuids    (const QMimeData * mime,QString mimetype) ;
    virtual bool    Load         (SqlConnection & Connection,SUID uuid,QTreeWidgetItem * item);

    virtual void    run          (int Type,ThreadData * data) ;

  private:

  public slots:

    virtual void Docking         (QMainWindow * Main,QString title,Qt::DockWidgetArea area,Qt::DockWidgetAreas areas);

    virtual bool startup         (void) ;
    virtual bool Shutdown        (void) ;
    virtual bool List            (void) ;
    virtual void New             (void) ;
    virtual void Obsolete        (void) ;
    virtual void Update          (SUID uuid) ;

  protected slots:

    virtual void singleClicked   (QTreeWidgetItem * item,int column) ;
    virtual void doubleClicked   (QTreeWidgetItem * item,int column) ;
    virtual void setTrigger      (QTreeWidgetItem * item,int column) ;
    virtual void setDateTime     (QTreeWidgetItem * item,int column) ;
    virtual bool Menu            (QPoint pos);

    void removeOldItem           (void) ;
    void editingFinished         (void) ;

    void TypeChanged             (int index) ;
    void NotifyChanged           (int index) ;
    void TimeFinished            (void) ;

  private slots:

  signals:

    void Details                 (UUIDs & Uuids) ;
    void Update                  (QWidget * widget,SUID uuid) ;

} ;

class Q_TASKS_EXPORT ExecutionLists : public TreeDock
{
  Q_OBJECT
  public:

    explicit  ExecutionLists       (StandardConstructor) ;
    virtual  ~ExecutionLists       (void) ;

  protected:

    QPoint dragPoint ;

    virtual void Configure         (void) ;
    virtual bool FocusIn           (void) ;

    virtual bool        hasItem    (void);
    virtual bool        startDrag  (QMouseEvent * event);
    virtual bool        fetchDrag  (QMouseEvent * event);
    virtual QMimeData * dragMime   (void);
    virtual void        dragDone   (Qt::DropAction dropIt,QMimeData * mime);
    virtual bool        finishDrag (QMouseEvent * event);

    virtual void        run        (int Type,ThreadData * data) ;

  private:

  public slots:

    virtual bool startup           (void) ;
    virtual void List              (void) ;
    virtual void Insert            (void) ;
    virtual void Rename            (void) ;
    virtual void Copy              (void) ;
    virtual void Execution         (void) ;

  protected slots:

    bool         Menu              (QPoint pos) ;
    virtual void doubleClicked     (QTreeWidgetItem *item, int column) ;

  private slots:

    virtual void removeOldItem     (void) ;
    virtual void NameFinished      (void) ;

  signals:

    void         Update            (QWidget * widget,SUID uuid) ;
    void         Edit              (QWidget * widget,QString name,SUID uuid) ;

} ;

class Q_TASKS_EXPORT ExecutionView : public IconDock
{
  Q_OBJECT
  public:

    explicit ExecutionView (StandardConstructor) ;
    virtual ~ExecutionView (void);

    virtual QSize sizeHint (void) const ;

  protected:

    virtual void Configure (void) ;
    virtual bool FocusIn   (void) ;

  private:

  public slots:

    virtual bool startup   (void) ;
    virtual void List      (void) ;
    virtual void New       (void) ;

  protected slots:

    virtual bool Menu      (QPoint pos) ;

  private slots:

  signals:

    void         Append    (void) ;

} ;

class Q_TASKS_EXPORT ExecutionEditor : public Widget
                                     , public Object
{
  Q_OBJECT
  public:

    explicit ExecutionEditor  (StandardConstructor) ;
    virtual ~ExecutionEditor  (void) ;

    virtual QSize sizeHint    (void) const ;

  protected:

    Ui::nExecutionEditor * ui       ;
    SUID                   IconUuid ;

    virtual void focusInEvent (QFocusEvent * event) ;

    virtual void Configure    (void) ;
    virtual bool FocusIn      (void) ;

  private:

  public slots:

    virtual void Clear        (void) ;
    virtual void Update       (void) ;
    virtual void Fetch        (SUID uuid) ;

    void ProgramIcon          (void) ;
    void BrowseExecution      (void) ;
    void BrowseEnvironment    (void) ;

  protected slots:

  private slots:

  signals:

    void Updated              (void) ;

} ;

class Q_TASKS_EXPORT GanttNote : public Widget
                               , public EventManager
{
  Q_OBJECT
  public:

    explicit GanttNote  (StandardConstructor) ;
    virtual ~GanttNote  (void) ;

  protected:

    SUID Uuid ;

  private:

    Ui::nGanttNote * ui;

  public slots:

    void setGantt       (SUID uuid,QString name) ;
    void Save           (void) ;
    void Cancel         (void) ;

  protected slots:

  private slots:

  signals:

    void Finish         (void) ;

} ;

class Q_TASKS_EXPORT GanttDuration : public Widget
{
  Q_OBJECT
  public:

    VcfGantt * Gantt ;

    explicit GanttDuration  (StandardConstructor) ;
    virtual ~GanttDuration  (void) ;

  protected:

    Ui::nGanttDuration * ui;

  private:

  public slots:

    virtual void Prepare    (void) ;
    virtual void Done       (void) ;
    virtual void Cancel     (void) ;

  protected slots:

    void startChanged       (QDateTime dt) ;

  private slots:

  signals:

    void GanttChanged       (VcfGantt * gantt) ;
    void Finish             (void) ;

} ;

class Q_TASKS_EXPORT GanttTriggers : public Widget
{
  Q_OBJECT
  public:

    VcfGantt * Gantt ;

    explicit GanttTriggers  (StandardConstructor);
    virtual ~GanttTriggers  (void);

  protected:

    Ui::nGanttTriggers * ui ;

  private:

  public slots:

    virtual void Prepare    (void) ;
    virtual void Done       (void) ;
    virtual void Cancel     (void) ;

  protected slots:

  private slots:

  signals:

    void GanttChanged       (VcfGantt * gantt) ;
    void Finish             (void) ;

} ;

class Q_TASKS_EXPORT EventTriggers : public Widget
{
  Q_OBJECT
  public:

    explicit     EventTriggers   (StandardConstructor);
    virtual     ~EventTriggers   (void) ;

    SUID         StartTrigger    (void) ;
    SUID         FinishTrigger   (void) ;

  protected:

    Ui::nEventTriggers * ui        ;
    SUID                 StartUuid ;
    SUID                 FinalUuid ;

    virtual void resizeEvent     (QResizeEvent * e) ;
    virtual void showEvent       (QShowEvent   * e) ;

    virtual void Configure       (void) ;

    virtual void run             (int type,ThreadData * data) ;

    virtual void Load            (void) ;

  private:

  public slots:

    virtual bool Relocation      (void) ;
    virtual void startup         (SUID start,SUID finish) ;

  protected slots:

    virtual void AssignTrigger   (int type,SUID uuid) ;

  private slots:

    void         TriggerComplete (void) ;
    void         SendActivity    (int state) ;

  signals:

    void         PrivateComplete (void) ;
    void         PrivateActivity (int state) ;
    void         Activity        (int state) ;

} ;

class Q_TASKS_EXPORT NotifierTrigger : public Widget
                                     , public TaskManager
{
  Q_OBJECT
  public:

    explicit NotifierTrigger (StandardConstructor) ;
    virtual ~NotifierTrigger (void);

  protected:

    SUID                  Uuid ;
    Ui::NotifierTrigger * ui   ;

  private:

  public slots:

    void load                (SUID uuid) ;
    void Done                (void) ;

  protected slots:

  private slots:

  signals:

    void Finish              (void) ;

} ;

class Q_TASKS_EXPORT TriggerProperty : public StackedWidget
                                     , public TaskManager
{
  Q_OBJECT
  public:

    SUID Uuid     ;
    bool Editable ;

    explicit TriggerProperty  (StandardConstructor) ;
    virtual ~TriggerProperty  (void);

  protected:

    Ui::nTriggerProperty * ui;

    virtual void showEvent    (QShowEvent   * event) ;
    virtual void resizeEvent  (QResizeEvent * event) ;
    virtual void closeEvent   (QCloseEvent  * event) ;

    virtual void Configure    (void) ;

  private:

  public slots:

    void Relocation           (void) ;
    void shutdown             (void) ;
    bool load                 (SUID uuid) ;
    void Finish               (void) ;

  protected slots:

    void triggerClicked       (QTreeWidgetItem * item,int column) ;

  private slots:

  signals:

    void Closed               (void) ;

} ;

class Q_TASKS_EXPORT TriggerEditor : public ItemEditor
{
  Q_OBJECT
  public:

    explicit     TriggerEditor (StandardConstructor) ;
    virtual     ~TriggerEditor (void);

  protected:

    virtual void Configure     (void) ;

  private:

  public slots:

  protected slots:

    virtual bool Menu          (QPoint pos) ;

  private slots:

  signals:

} ;

class Q_TASKS_EXPORT PeriodEditor : public Splitter
{
  Q_OBJECT
  Q_PROPERTY(int TimeType READ Type WRITE setType)
  public:

    explicit PeriodEditor       (StandardConstructor) ;
    virtual ~PeriodEditor       (void) ;

    virtual QSize sizeHint      (void) const ;

    int           Type          (void) ;
    TUID          Start         (void) ;
    TUID          Finish        (void) ;
    TimePeriod    Period        (void) ;
    void          setStart      (TUID startTime) ;
    void          setFinish     (TUID finishTime) ;
    void          setRange      (TimePeriod period) ;
    void          setType       (int type) ;

    virtual CalendarTimeEdit * New (int CalendarType,int periodType) ;

  protected:

    Ui::PeriodEditor * ui          ;
    TimePeriod         period      ;
    IMAPs              CalendarIDs ;
    IMAPs              IdCalendars ;
    CalendarTimeEdit * StartTime   ;
    CalendarTimeEdit * FinishTime  ;

    virtual void Configure      (void) ;

    virtual void resizeEvent    (QResizeEvent * event) ;
    virtual void showEvent      (QShowEvent * event) ;

  private:

  public slots:

    virtual bool Relocation     (void) ;

    virtual void show           (int index) ;
    virtual void hide           (int index) ;
    virtual void selectCalendar (int type) ;
    virtual void selectPeriod   (int period) ;
    virtual void selectTimeZone (int timeZone) ;

  protected slots:

  private slots:

    void PageChanged            (int index) ;
    void TimeZoneChanged        (int index) ;
    void StartChanged           (TUID time) ;
    void FinishChanged          (TUID time) ;

  signals:

    void Changed                (void) ;

} ;

class Q_TASKS_EXPORT EventOwners : public Widget
{
  Q_OBJECT
  public:

    explicit     EventOwners       (StandardConstructor) ;
    virtual     ~EventOwners       (void) ;

  protected:

    Ui::nEventOwners * ui           ;
    SUID               uuid         ;
    SUID               crowd        ;
    SUID               organization ;

    virtual void resizeEvent       (QResizeEvent * e) ;
    virtual void showEvent         (QShowEvent   * e) ;
    virtual void closeEvent        (QCloseEvent  * e) ;

    virtual void Configure         (void) ;

    virtual void run               (int type,ThreadData * data) ;

  private:

  public slots:

    virtual bool Relocation        (void) ;
    virtual bool startup           (SUID uuid) ;
    virtual bool store             (SqlConnection & SC,SUID uuid) ;

    virtual void Load              (void) ;
    virtual void LoadEquipments    (void) ;
    virtual void LoadPeople        (void) ;
    virtual void LoadOrganizations (void) ;
    virtual void LoadApplications  (void) ;

    virtual void setCrowd          (SUID uuid) ;
    virtual void setOrganization   (SUID uuid) ;

  protected slots:

    virtual void Add               (void) ;
    virtual void Remove            (void) ;
    virtual void Type              (int index) ;
    virtual void Items             (int index) ;
    virtual void itemClicked       (QTreeWidgetItem * item,int column) ;

  private slots:

    void         SendActivity      (int state) ;

  signals:

    void         PrivateActivity   (int state) ;
    void         Activity          (int state) ;

} ;

class Q_TASKS_EXPORT EventTasks : public Widget
{
  Q_OBJECT
  public:

    explicit     EventTasks      (StandardConstructor) ;
    virtual     ~EventTasks      (void) ;

  protected:

    Ui::nEventTasks * ui ;

    virtual void resizeEvent     (QResizeEvent * e) ;
    virtual void showEvent       (QShowEvent   * e) ;
    virtual void closeEvent      (QCloseEvent  * e) ;

    virtual void Configure       (void) ;

    virtual void run             (int type,ThreadData * data) ;

  private:

  public slots:

    virtual bool Relocation      (void) ;
    virtual bool startup         (SUID uuid) ;

    virtual void Load            (SUID uuid) ;
    virtual bool store           (SqlConnection & SC,SUID uuid) ;

  protected slots:

    virtual void List            (void) ;

    virtual void Add             (void) ;
    virtual void Remove          (void) ;
    virtual void itemClicked     (QTreeWidgetItem * item,int column) ;

  private slots:

    void         SendActivity    (int state) ;

  signals:

    void         PrivateActivity (int state) ;
    void         Activity        (int state) ;

} ;

class Q_TASKS_EXPORT EventDependency : public Widget
{
  Q_OBJECT
  public:

    explicit     EventDependency     (StandardConstructor) ;
    virtual     ~EventDependency     (void) ;

  protected:

    Ui::nEventDependency * ui          ;
    SpinBox              * TimeDepend  ;
    QTreeWidgetItem      * EditingItem ;

    virtual void resizeEvent         (QResizeEvent * e) ;
    virtual void showEvent           (QShowEvent   * e) ;
    virtual void closeEvent          (QCloseEvent  * e) ;

    virtual void Configure           (void) ;

    virtual void run                 (int type,ThreadData * data) ;

  private:

  public slots:

    virtual bool Relocation        (void) ;
    virtual bool startup           (SUID uuid) ;

    virtual void Load              (SUID uuid) ;
    virtual bool store             (SqlConnection & SC,SUID uuid) ;

  protected slots:

    virtual void List              (void) ;

    virtual void Add               (void) ;
    virtual void Remove            (void) ;
    virtual void itemClicked       (QTreeWidgetItem * item,int column) ;
    virtual void itemDoubleClicked (QTreeWidgetItem * item,int column) ;

    virtual void timeChanged       (void) ;

  private slots:

    void         SendActivity      (int state) ;

  signals:

    void         PrivateActivity   (int state) ;
    void         Activity          (int state) ;

} ;

class Q_TASKS_EXPORT RepeatedEvent : public Widget
{
  Q_OBJECT
  public:

    explicit     RepeatedEvent (StandardConstructor) ;
    virtual     ~RepeatedEvent (void) ;

  protected:

    Ui::nRepeatedEvent * ui ;

    virtual void resizeEvent         (QResizeEvent * e) ;
    virtual void showEvent           (QShowEvent   * e) ;
    virtual void closeEvent          (QCloseEvent  * e) ;

    virtual void Configure           (void) ;

    virtual void run                 (int type,ThreadData * data) ;

  private:

  public slots:

    virtual bool Relocation        (void) ;
    virtual bool startup           (SUID uuid) ;

    virtual void Load              (SUID uuid) ;
    virtual bool store             (SqlConnection & SC,SUID uuid) ;

  protected slots:

    virtual void Browse            (void) ;

  private slots:

    void         SendActivity      (int state) ;

  signals:

    void         PrivateActivity   (int state) ;
    void         Activity          (int state) ;

} ;

class Q_TASKS_EXPORT BriefEvent : public Widget
{
  Q_OBJECT
  public:

    VcfInterface * vif ;

    explicit     BriefEvent    (StandardConstructor) ;
    virtual     ~BriefEvent    (void) ;

  protected:

    Ui::nBriefEvent * ui         ;
    PeriodEditor    * period     ;
    PlainEditor     * editor     ;
    EventTriggers   * trigger    ;
    EventOwners     * owners     ;
    EventTasks      * tasks      ;
    EventDependency * dependency ;
    RepeatedEvent   * repeated   ;
    NAMEs             TypeNames  ;
    SUID              uuid       ;
    int               RunThreads ;

    virtual void resizeEvent   (QResizeEvent * e) ;
    virtual void showEvent     (QShowEvent   * e) ;

    virtual void Configure     (void) ;

    virtual void run           (int type,ThreadData * data) ;

    virtual bool UpdateEvent   (SqlConnection & SC,SUID uuid,int type,QString name,TUID StartTime,TUID FinalTime) ;
    virtual SUID AppendEvent   (SqlConnection & SC,int type,QString name) ;
    virtual bool StoreNote     (SqlConnection & SC) ;
    virtual bool FetchNote     (SqlConnection & SC) ;
    virtual bool StoreTrigger  (SqlConnection & SC) ;
    virtual bool FetchTrigger  (SqlConnection & SC) ;
    virtual bool StoreOwners   (SqlConnection & SC) ;
    virtual bool StoreTasks    (SqlConnection & SC) ;
    virtual bool StoreDepends  (SqlConnection & SC) ;
    virtual bool StoreRepeated (SqlConnection & SC) ;

  private:

    virtual void WaitComplete  (void) ;

  public slots:

    virtual bool Relocation    (void) ;
    virtual bool startup       (SUID uuid,QDateTime start,QDateTime end) ;

    virtual void Load          (void) ;
    virtual void Append        (void) ;
    virtual void Modify        (void) ;
    virtual void FetchNote     (void) ;
    virtual void FetchTrigger  (void) ;

  protected slots:

    virtual void Add           (void) ;
    virtual void Cancel        (void) ;

    virtual void Enabling      (int type,bool enable) ;
    virtual void Owner         (bool enabled) ;
    virtual void Trigger       (bool enabled) ;
    virtual void Dependency    (bool enabled) ;
    virtual void Repeat        (bool enabled) ;
    virtual void Tasks         (bool enabled) ;
    virtual void Note          (bool enabled) ;
    virtual void Description   (QString text) ;
    virtual void EventType     (int type) ;

    virtual void Validate      (void) ;

    virtual void RemoveEditor  (void) ;
    virtual void RemoveTrigger (void) ;
    virtual void RemoveOwners  (void) ;
    virtual void RemoveTasks   (void) ;
    virtual void RemoveDepends (void) ;
    virtual void RemoveRepeat  (void) ;

    virtual void Activity      (int state) ;
    virtual void AssignType    (int type) ;

  private slots:

    virtual void SendComplete  (void) ;
    virtual void WriteNote     (QString note) ;

  signals:

    void AssignNote            (QString note) ;
    void LoadingType           (int type) ;
    void EnableWidget          (int type,bool enable) ;
    void AssignTimeType        (int type) ;
    void PrivateComplete       (void) ;

    void Complete              (void) ;
    void Leave                 (QWidget      * widget) ;
    void EraseVIF              (VcfInterface * vif   ) ;

} ;

class Q_TASKS_EXPORT FileTransferUI : public TabWidget
{
  Q_OBJECT
  public:

    explicit     FileTransferUI (StandardConstructor) ;
    virtual     ~FileTransferUI (void) ;

  protected:

    Ui::FileTransferUI * ui         ;
    int                  EventType  ;
    SUID                 uuid       ;
    QMutex               StoreMutex ;

    virtual void Configure      (void) ;

    virtual void run            (int type,ThreadData * data) ;

  private:

    virtual void Relocate       (QWidget * w) ;

  public slots:

    virtual bool Relocation     (void) ;

    virtual void setEvent       (int type,SUID u) ;

    virtual void LoadEvent      (void) ;
    virtual void SaveEvent      (void) ;

  protected slots:

    virtual void BrowseJava     (void) ;
    virtual void BrowseOpen     (void) ;
    virtual void BrowseSave     (void) ;

    virtual void FtpState       (int index) ;
    virtual void FtpChanged     (void) ;

  private slots:

  signals:

} ;

class Q_TASKS_EXPORT VcfScheduler : public VcfCanvas
                                  , public Thread
{
  Q_OBJECT
  public:

    enum { Type = UserType + VCF::Scheduler };
    virtual int type(void) const { return Type; }

    explicit     VcfScheduler     (VcfConstructor) ;
    virtual     ~VcfScheduler     (void) ;

    bool           contains       (QDateTime start,QDateTime final) ;
    int            PaperX         (void) ;
    int            PaperY         (void) ;
    virtual QRectF PaperDPI       (void) ;
    double         LeftBase       (QRectF View) ;

  protected:

    QDateTime            MidDay    ;
    QTimer               Timer     ;
    VcfTimeBar        *  TimeBar   ;
    VcfTimeSection    *  Section   ;
    QGraphicsRectItem *  TimeBlock ;
    QList<VcfGantt    *> Gantts    ;

    virtual void contextMenuEvent (QGraphicsSceneContextMenuEvent * event) ;

    virtual void Configure        (void) ;

    virtual bool dropText         (QWidget * source,QPointF pos,const QString & text) ;
    virtual bool dropUrls         (QWidget * source,QPointF pos,const QList<QUrl> & urls) ;
    virtual bool dropHtml         (QWidget * source,QPointF pos,const QString & html) ;
    virtual bool dropColor        (QWidget * source,QPointF pos,const QColor  & color) ;
    virtual bool dropTags         (QWidget * source,QPointF pos,const UUIDs   & Uuids) ;
    virtual bool dropPictures     (QWidget * source,QPointF pos,const UUIDs   & Uuids) ;
    virtual bool dropPeople       (QWidget * source,QPointF pos,const UUIDs   & Uuids) ;
    virtual bool dropVideos       (QWidget * source,QPointF pos,const UUIDs   & Uuids) ;
    virtual bool dropAlbums       (QWidget * source,QPointF pos,const UUIDs   & Uuids) ;
    virtual bool dropURIs         (QWidget * source,QPointF pos,const UUIDs   & Uuids) ;
    virtual bool dropBookmarks    (QWidget * source,QPointF pos,const UUIDs   & Uuids) ;
    virtual bool dropFont         (QWidget * source,QPointF pos,const SUID      font) ;
    virtual bool dropPen          (QWidget * source,QPointF pos,const SUID      pen) ;
    virtual bool dropBrush        (QWidget * source,QPointF pos,const SUID      brush) ;
    virtual bool dropGradient     (QWidget * source,QPointF pos,const SUID      gradient) ;

    virtual void run              (int Type,ThreadData * data) ;

  private:

  public slots:

    virtual void Paint            (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void Initialize       (void) ;
    virtual void Refresh          (void) ;
    virtual void setRegion        (QRectF Region) ;
    virtual void UpdateItems      (void) ;
    virtual void ArrangeItems     (void) ;
    virtual void GoToNow          (void) ;
    virtual void GoToTime         (void) ;
    virtual bool UpdateGantt      (VcfGantt * gantt) ;
    virtual void EditGantt        (VcfGantt * gantt) ;
    virtual void MountAudios      (void) ;
    virtual void MountTriggers    (void) ;

  protected slots:

    void         TimeUpdated      (void) ;
    virtual bool ScheduleMenu     (QPointF pos) ;
    virtual void Append           (QDateTime Start,QDateTime Final) ;
    virtual void DateTimeFinished (void) ;

    virtual void GanttChanged     (VcfGantt * gantt) ;
    virtual void GanttUpdated     (VcfGantt * gantt) ;
    virtual void DeleteGantt      (VcfGantt * gantt) ;
    virtual void AttachNote       (VcfGantt * gantt) ;
    virtual void GanttTime        (VcfGantt * gantt) ;
    virtual void GanttTriggers    (VcfGantt * gantt) ;
    virtual void GanttEdit        (VcfGantt * gantt,int Id) ;

    virtual void ItemFinished     (VcfItem * item) ;
    virtual void Trigger          (SUID uuid) ;

  private slots:

  signals:

    void Append                   (VcfItem * item,VcfItem * parent) ;
    void RemoveItem               (VcfItem * item) ;
    void RegionUpdated            (void) ;
    void Zoom                     (void) ;
    void ItemUpdate               (SUID uuid) ;

} ;

class Q_TASKS_EXPORT MonitorSize : public VcfView
{
  Q_OBJECT
  public:

    explicit MonitorSize   (StandardConstructor) ;
    virtual ~MonitorSize   (void);

  protected:

    VcfScreenSize * ScreenSize ;

    virtual void Configure (void) ;
    bool Relocation        (void) ;

    virtual bool FocusIn   (void) ;
    virtual bool FocusOut  (void) ;

  private:

  public slots:

    void Left              (void) ;
    void Right             (void) ;
    void Up                (void) ;
    void Down              (void) ;
    void UpdateScreen      (void) ;

    virtual bool Shutdown  (void) ;
    virtual bool Finalize  (void) ;

  protected slots:

  private slots:

  signals:

    void Apply             (void) ;

} ;

class Q_TASKS_EXPORT SchedulerView : public VcfView
{
  Q_OBJECT
  public:

    explicit SchedulerView     (StandardConstructor) ;
    virtual ~SchedulerView     (void);

    virtual QSize sizeHint     (void) const ;

  protected:

    VcfScheduler * scheduler ;
    bool           locking   ;

    virtual void Configure     (void) ;

  private:

  public slots:

    virtual void Initialize    (void) ;
    virtual void Reload        (void) ;
    virtual bool Shutdown      (void) ;

    virtual void Zoom          (void) ;

  protected slots:

    virtual bool Menu          (QPoint pos);

    virtual void RegionUpdated (void) ;
    virtual void PaperMoving   (QString name,QPointF pos,QPointF paper,QPointF scene);
    virtual void ItemUpdate    (SUID uuid) ;

  private slots:

  signals:

    void Update                (SUID uuid) ;

} ;

class Q_TASKS_EXPORT PeriodBlock : public SceneWidget
{
  Q_OBJECT
  public:

    explicit     PeriodBlock (QObject * parent,Plan * plan) ;
    explicit     PeriodBlock (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~PeriodBlock (void) ;

    virtual void renderBox   (void) ;

    virtual void setText     (QString  description) ;

    virtual bool Within      (QPointF & p) ;
    virtual bool Spot        (ControlPoint & From ,
                              ControlPoint & To   ,
                              ControlPoint & At ) ;
    virtual bool Menu        (QWidget      * widget ,
                              QPointF        pos    ,
                              ControlPoint & From   ,
                              ControlPoint & To   ) ;

  protected:

    QRect        TextRegion  (QString text,int H) ;

    virtual void Configure   (void) ;

    virtual void renderText  (void) ;

  private:

  public slots:

  protected slots:

    virtual void ChangeColor (QWidget * widget) ;
    virtual void TextColor   (QWidget * widget) ;

  private slots:

  signals:

    void Changed             (SUID node) ;
    void Close               (SUID node) ;

} ;

class Q_TASKS_EXPORT EventObject : public SceneWidget
{
  Q_OBJECT
  public:

    QObject * calendar ;

    explicit     EventObject       (QObject * parent,Plan * plan) ;
    explicit     EventObject       (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~EventObject       (void) ;

    virtual bool Within            (QPointF & p) ;
    virtual int  Rectangles        (QList<QRectF> & rectangles) ;
    virtual void setText           (QString  description ,
                                    QRectF   range       ,
                                    QRectF & area        ,
                                    bool     generate  ) ;
    virtual void setIcon           (int      type        ,
                                    QRectF   range       ,
                                    QRectF & area        ,
                                    bool     generate  ) ;
    virtual bool Spot              (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;

    virtual void renderFaces       (void) ;

    virtual bool Menu              (QWidget      * widget ,
                                    QPointF        pos    ,
                                    ControlPoint & From   ,
                                    ControlPoint & To   ) ;

    virtual int  AtRegion          (ControlPoint & At) ;

    virtual QString ToolTip        (void) ;

  protected:

    NAMEs TypeNames ;

    virtual void Configure         (void) ;

    virtual void run               (int type,ThreadData * data) ;

    QRect        TextRegion        (QString text,int H) ;

    int          DurationStatus    (void) ;

  private:

  public slots:

    virtual void ConnectCalendar   (QObject * calendar) ;
    virtual void UpdateEvent       (SUID u,int type) ;
    virtual void JobCompleted      (SUID u) ;
    virtual void UpdateName        (SUID u,QString name) ;

    virtual QString GetBackup      (void) ;
    virtual bool    SaveBackup     (QString BackupINI) ;

    virtual QString GetForexJs     (void) ;
    virtual bool    SaveForexJs    (QString ForexJs) ;

    virtual QString GetPrivateJs   (void) ;
    virtual bool    SavePrivateJs  (QString PrivateJs) ;

  protected slots:

    virtual void AdjustMenu        (MenuManager & mm,QMenu * menu) ;
    virtual void TypesMenu         (MenuManager & mm,QMenu * menu) ;
    virtual void AttacheMenu       (MenuManager & mm,QMenu * menu) ;

    virtual bool AdjustProcessor   (MenuManager & mm,QAction * aa) ;
    virtual bool TypesProcessor    (MenuManager & mm,QAction * aa) ;
    virtual bool AttacheProcessor  (MenuManager & mm,QAction * aa) ;

    virtual void SetupExecution    (void) ;
    virtual void ExecutionMenu     (int index) ;

    virtual void EmptyEditTool     (void) ;
    virtual void ForexAutomation   (void) ;
    virtual void PrivateAutomation (void) ;

    virtual bool BrowseBackup      (void) ;
    virtual void EditBackup        (void) ;

    virtual void SetupMusic        (void) ;
    virtual void MusicMenu         (int index) ;

    virtual void SelectClip        (void) ;
    virtual void SetupAlbumGroup   (void) ;
    virtual void SetupVideoAlbums  (void) ;
    virtual void SetupVideoClips   (void) ;
    virtual void ClipMenu          (int index) ;

    virtual void ProcessDependency (void) ;

  private slots:

  signals:

    void EditEvent                 (int ServiceId,SUID u) ;
    void Update                    (void) ;
    void EditEvent                 (QObject * calendar ,
                                    SUID      uuid     ,
                                    QDateTime start    ,
                                    QDateTime end      ,
                                    bool      panel  ) ;
    void UpdateSpot                (SUID      u        ,
                                    QDateTime start    ,
                                    QDateTime final  ) ;
    void OpenBackup                (QString BackupINI) ;

} ;

class Q_TASKS_EXPORT CalendarObject : public SceneWidget
{
  Q_OBJECT
  public:

    explicit       CalendarObject  (QObject * parent,Plan * plan) ;
    explicit       CalendarObject  (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual       ~CalendarObject  (void) ;

    virtual void   renderGrids     (void) ;
    virtual void   renderChildren  (void) ;

    virtual bool   Animation       (void) ;
    virtual bool   FocusIn         (void) ;
    virtual bool   FocusOut        (void) ;

    virtual bool   MouseVector     (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;
    virtual bool   MouseHover      (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;
    virtual bool   MouseMove       (ControlPoint & From1     ,
                                    ControlPoint & To1       ,
                                    ControlPoint & From2     ,
                                    ControlPoint & To2       ,
                                    BMAPs        & buttons ) ;

    virtual bool   Spot            (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;

    virtual bool   Menu            (QWidget      * widget ,
                                    QPointF        pos    ,
                                    ControlPoint & From   ,
                                    ControlPoint & To   ) ;

    virtual bool   Relocation      (QRectF viewport) ;

    virtual bool   contains        (QDateTime start,QDateTime final) ;
    virtual bool   isLoading       (void) ;

    virtual int    AtRegion        (ControlPoint & At) ;

  protected:

    NAMEs TypeNames ;

    virtual void   Configure       (void) ;

    virtual void   drawTicks       (double y,double z,bool up) ;
    virtual void   drawHappened    (void) ;
    virtual void   drawDaylight    (double z) ;
    virtual void   drawWeather     (double z) ;
    virtual void   drawMarking     (void) ;

    virtual void   drawLabels      (void) ;
    virtual void   drawOneYear     (void) ;
    virtual void   drawYears       (void) ;
    virtual void   drawMonths      (void) ;
    virtual void   drawDays        (void) ;
    virtual void   drawHours       (void) ;
    virtual void   drawMinutes     (void) ;

    virtual void   run             (int type,ThreadData * data) ;

    virtual void   ThreadEvent     (void) ;

    virtual QRectF BarArea         (void) ;
    virtual bool   Intersects      (QRectF & r,QList<QRectF> & rects) ;
    virtual void   ArrangeItems    (QList<EventObject *> & EOLs) ;
    virtual bool   EventRectangle  (EventObject * eol      ,
                                    QRectF      & r        ,
                                    QRectF      & area     ,
                                    int           gap      ,
                                    int           metric ) ;

    virtual QDateTime AtOldTime    (ControlPoint & At) ;
    virtual QDateTime AtTime       (ControlPoint & At) ;
    virtual QDateTime AtFixTime    (ControlPoint & At) ;
    virtual bool      LastMoment   (QDateTime now) ;
    virtual bool      HoverEvent   (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;
    virtual void      TimeToolTip  (ControlPoint & At) ;

    virtual EventObject * LocateEvent    (ControlPoint & From ,
                                          ControlPoint & To   ,
                                          ControlPoint & At ) ;
    virtual bool          Filter         (SqlConnection & SC,EventObject * eol) ;
    virtual EventObject * NewEventObject (void) ;
    virtual PeriodBlock * NewPeriodBlock (QDateTime start,QDateTime final) ;
    virtual void CalculateBlock (PeriodBlock * pob,QDateTime start,QDateTime final) ;

    virtual void      RemoveWeekdays (void) ;
    virtual void      AddWeekdays    (void) ;
    virtual void      LocateWeekdays (void) ;

    virtual void      TrackingTime   (void) ;
    virtual void      MakeTime       (void) ;
    virtual void      renderTime     (void) ;

    virtual SceneTexture * GetLabel  (int id,QSize s) ;
    virtual SceneTexture * GetLabel  (int id) ;
    virtual void      drawLabel      (int     id                        ,
                                      QString text                    ) ;
    virtual void      drawLabel      (int     id                        ,
                                      QString text                      ,
                                      QColor  c                         ,
                                      int     flags = Qt::AlignCenter ) ;
    virtual void      drawLabel      (int     id                        ,
                                      QString text                      ,
                                      QRectF  s                         ,
                                      QColor  c                         ,
                                      int     flags = Qt::AlignCenter   ,
                                      int     pixel = 10              ) ;
    virtual void      renderLabel    (int id,QRectF & r,double z) ;

    virtual void      HandleDependency (SUID uuid,UUIDs & After,UUIDs & Current) ;

  private:

  public slots:

    virtual void   MoveRange       (QDateTime start,QDateTime final) ;
    virtual void   setRange        (QDateTime start,QDateTime end) ;
    virtual void   setRange        (QDateTime start,QDateTime end,qint64 gap) ;
    virtual void   setGap          (QDateTime separator,qint64 gap) ;

    virtual void   Clear           (void) ;
    virtual void   Load            (void) ;

    virtual void   startup         (void) ;
    virtual void   WeatherFeeder   (void) ;
    virtual void   OrganizeDepends (void) ;

    virtual void   ZoomIn          (void) ;
    virtual void   ZoomOut         (void) ;

    virtual void   MoveToNow       (void) ;
    virtual void   MoveToNew       (void) ;
    virtual void   BriefAdd        (QDateTime start,QDateTime final) ;
    virtual void   MoveTime        (QDateTime start,QDateTime final) ;
    virtual void   AddSection      (QDateTime start,QDateTime final) ;
    virtual void   Selecting       (QDateTime start,QDateTime final) ;
    virtual void   RunActions      (QDateTime start,QDateTime final) ;

    virtual void   UpdateSpot      (SUID u,QDateTime start,QDateTime final) ;

    virtual bool   HitEvent        (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;
    virtual bool   MovingEvent     (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;
    virtual bool   FinalEvent      (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;
    virtual bool   HitObjects      (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;
    virtual bool   MovingObjects   (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;
    virtual bool   FinalObjects    (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;

  protected slots:

    virtual bool   EventMenu       (QWidget      * widget ,
                                    QPointF        pos    ,
                                    ControlPoint & From   ,
                                    ControlPoint & To     ,
                                    ControlPoint & At   ) ;
    virtual bool   PeriodMenu      (QWidget      * widget ,
                                    QPointF        pos    ,
                                    ControlPoint & From   ,
                                    ControlPoint & To     ,
                                    ControlPoint & At   ) ;

    virtual bool   EventsMenu      (MenuManager & mm,QMenu * menu,int region) ;
    virtual bool   TasksMenu       (MenuManager & mm,QMenu * menu,int region) ;
    virtual bool   EditMenu        (MenuManager & mm,QMenu * menu,int region) ;
    virtual void   ConfMenu        (MenuManager & mm,QMenu * menu,int region) ;
    virtual void   AdjustMenu      (MenuManager & mm,QMenu * menu,int region) ;
    virtual void   ToolsMenu       (MenuManager & mm,QMenu * menu) ;

    virtual bool   EventsProcessor (MenuManager & mm,QAction * aa) ;
    virtual bool   TasksProcessor  (MenuManager & mm,QAction * aa) ;
    virtual bool   EditProcessor   (MenuManager & mm,QAction * aa) ;
    virtual bool   ConfProcessor   (MenuManager & mm,QAction * aa) ;
    virtual bool   AdjustProcessor (MenuManager & mm,QAction * aa) ;
    virtual bool   ToolsProcessor  (MenuManager & mm,QAction * aa) ;

    virtual void   ShowDuration    (void) ;
    virtual void   ChangePeriod    (SUID u) ;
    virtual void   ClosePeriod     (SUID u) ;
    virtual void   SendSection     (void) ;

  private slots:

  signals:

    void           CloseCalendar   (SUID u) ;
    void           ShowCrowds      (void) ;
    void           ShowPeople      (void) ;
    void           TasksList       (void) ;
    void           EventsList      (void) ;
    void           TriggersList    (void) ;
    void           EditDOF         (SceneObject * object) ;
    void           EditEvent       (QObject * calendar ,
                                    SUID      uuid     ,
                                    QDateTime start    ,
                                    QDateTime end      ,
                                    bool      panel  ) ;
    void           SectionChanged  (QString timezone,QDateTime start,QDateTime end) ;
    void           SectionChanged  (TUID start,TUID end) ;
    void           SectionChanged  (SceneWidget * widget) ;
    void           EmitSection     (void) ;

} ;

}

QT_END_NAMESPACE

#endif

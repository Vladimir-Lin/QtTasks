#include <qttasks.h>
#include "ui_FileTransferUI.h"

N::FileTransferUI:: FileTransferUI ( QWidget * parent , Plan * p )
                  : TabWidget      (           parent ,        p )
                  , ui             ( new Ui::FileTransferUI      )
                  , EventType      ( N::None                     )
                  , uuid           ( 0                           )
{
  Configure ( ) ;
}

N::FileTransferUI::~FileTransferUI(void)
{
  delete ui ;
}

void N::FileTransferUI::Configure(void)
{
  ui -> setupUi ( this ) ;
}

void N::FileTransferUI::run(int type,ThreadData * data)
{
  switch ( type )   {
    case 10001      :
      LoadEvent ( ) ;
    break           ;
    case 10002      :
      SaveEvent ( ) ;
    break           ;
  }                 ;
}

void N::FileTransferUI::setEvent(int type,SUID u)
{
  int index                              ;
  EventType = type                       ;
  uuid      = u                          ;
  switch ( EventType )                   {
    case N::Download                     :
      index = indexOf ( ui -> Upload   ) ;
      if ( index >= 0 )                  {
        removeTab     ( index          ) ;
      }                                  ;
    break                                ;
    case N::Upload                       :
      index = indexOf ( ui -> Download ) ;
      if ( index >= 0 )                  {
        removeTab     ( index          ) ;
      }                                  ;
    break                                ;
    default                              :
    return                               ;
  }                                      ;
  start ( 10001 )                        ;
}

void N::FileTransferUI::Relocate(QWidget * w)
{
  QRect g = w -> geometry ( )         ;
  g  . setRight    ( width ( ) - 10 ) ;
  w -> setGeometry ( g              ) ;
}

bool N::FileTransferUI::Relocation(void)
{
  Relocate ( ui -> Javascript   ) ;
  Relocate ( ui -> DownloadURL  ) ;
  Relocate ( ui -> SaveDownload ) ;
  Relocate ( ui -> OpenUpload   ) ;
  Relocate ( ui -> UploadURL    ) ;
  return false                    ;
}

void N::FileTransferUI::LoadEvent(void)
{
  bool correct = false                                            ;
  if ( N::Download == EventType ) correct = true                  ;
  if ( N::Upload   == EventType ) correct = true                  ;
  if ( 0           == uuid      ) correct = false                 ;
  if ( ! correct                )                                 {
    Alert ( Error )                                               ;
    return                                                        ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  EventManager  EM ( plan        )                                ;
  SqlConnection SC ( plan -> sql )                                ;
  if ( SC . open ( FunctionString ) )                             {
    bool     FtpUseJava     = false                               ;
    QString  FileTransferJS = ""                                  ;
    QString  DownloadURL    = ""                                  ;
    QString  DownloadFile   = ""                                  ;
    QString  UploadURL      = ""                                  ;
    QString  UploadFile     = ""                                  ;
    QString  UploadUser     = ""                                  ;
    QString  UploadPass     = ""                                  ;
    QVariant V                                                    ;
    ///////////////////////////////////////////////////////////////
    if ( EM . LoadVariable ( SC , uuid , "FtpUseJava"     , V ) ) {
      FtpUseJava     = V . toBool   ( )                           ;
    }                                                             ;
    if ( EM . LoadVariable ( SC , uuid , "FileTransferJS" , V ) ) {
      FileTransferJS = V . toString ( )                           ;
    }                                                             ;
    if ( EM . LoadVariable ( SC , uuid , "DownloadURL"    , V ) ) {
      DownloadURL    = V . toString ( )                           ;
    }                                                             ;
    if ( EM . LoadVariable ( SC , uuid , "DownloadFile"   , V ) ) {
      DownloadFile   = V . toString ( )                           ;
    }                                                             ;
    if ( EM . LoadVariable ( SC , uuid , "UploadURL"      , V ) ) {
      UploadURL      = V . toString ( )                           ;
    }                                                             ;
    if ( EM . LoadVariable ( SC , uuid , "UploadFile"     , V ) ) {
      UploadFile     = V . toString ( )                           ;
    }                                                             ;
    if ( EM . LoadVariable ( SC , uuid , "UploadUser"     , V ) ) {
      UploadUser     = V . toString ( )                           ;
    }                                                             ;
    if ( EM . LoadVariable ( SC , uuid , "UploadPass"     , V ) ) {
      UploadPass     = V . toString ( )                           ;
    }                                                             ;
    ///////////////////////////////////////////////////////////////
    ui -> Scriptable   -> blockSignals ( true           )         ;
    ui -> Javascript   -> blockSignals ( true           )         ;
    ui -> DownloadURL  -> blockSignals ( true           )         ;
    ui -> SaveDownload -> blockSignals ( true           )         ;
    ui -> UploadURL    -> blockSignals ( true           )         ;
    ui -> OpenUpload   -> blockSignals ( true           )         ;
    ui -> Username     -> blockSignals ( true           )         ;
    ui -> Password     -> blockSignals ( true           )         ;
    ///////////////////////////////////////////////////////////////
    ui -> Scriptable   -> setChecked   ( FtpUseJava     )         ;
    ui -> Javascript   -> setText      ( FileTransferJS )         ;
    ui -> DownloadURL  -> setText      ( DownloadURL    )         ;
    ui -> SaveDownload -> setText      ( DownloadFile   )         ;
    ui -> UploadURL    -> setText      ( UploadURL      )         ;
    ui -> OpenUpload   -> setText      ( UploadFile     )         ;
    ui -> Username     -> setText      ( UploadUser     )         ;
    ui -> Password     -> setText      ( UploadPass     )         ;
    ///////////////////////////////////////////////////////////////
    ui -> Scriptable   -> blockSignals ( false          )         ;
    ui -> Javascript   -> blockSignals ( false          )         ;
    ui -> DownloadURL  -> blockSignals ( false          )         ;
    ui -> SaveDownload -> blockSignals ( false          )         ;
    ui -> UploadURL    -> blockSignals ( false          )         ;
    ui -> OpenUpload   -> blockSignals ( false          )         ;
    ui -> Username     -> blockSignals ( false          )         ;
    ui -> Password     -> blockSignals ( false          )         ;
    ///////////////////////////////////////////////////////////////
    SC . close  (       )                                         ;
    Alert       ( Done  )                                         ;
  } else                                                          {
    Alert       ( Error )                                         ;
  }                                                               ;
  SC   . remove (       )                                         ;
}

void N::FileTransferUI::SaveEvent(void)
{ QMutexLocker LOCK ( &StoreMutex ) ;
  bool correct = false                                     ;
  if ( N::Download == EventType ) correct = true           ;
  if ( N::Upload   == EventType ) correct = true           ;
  if ( 0           == uuid      ) correct = false          ;
  if ( ! correct                )                          {
    Alert ( Error )                                        ;
    return                                                 ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  EventManager  EM ( plan        )                         ;
  SqlConnection SC ( plan -> sql )                         ;
  if ( SC . open ( FunctionString ) )                      {
    bool     FtpUseJava     = false                        ;
    QString  FileTransferJS = ""                           ;
    QString  DownloadURL    = ""                           ;
    QString  DownloadFile   = ""                           ;
    QString  UploadURL      = ""                           ;
    QString  UploadFile     = ""                           ;
    QString  UploadUser     = ""                           ;
    QString  UploadPass     = ""                           ;
    QVariant V                                             ;
    ////////////////////////////////////////////////////////
    FtpUseJava     = ui -> Scriptable   -> isChecked ( )   ;
    FileTransferJS = ui -> Javascript   -> text      ( )   ;
    DownloadURL    = ui -> DownloadURL  -> text      ( )   ;
    DownloadFile   = ui -> SaveDownload -> text      ( )   ;
    UploadURL      = ui -> UploadURL    -> text      ( )   ;
    UploadFile     = ui -> OpenUpload   -> text      ( )   ;
    UploadUser     = ui -> Username     -> text      ( )   ;
    UploadPass     = ui -> Password     -> text      ( )   ;
    ////////////////////////////////////////////////////////
    V = FtpUseJava                                         ;
    EM . SaveVariable ( SC , uuid , "FtpUseJava"     , V ) ;
    V = FileTransferJS                                     ;
    EM . SaveVariable ( SC , uuid , "FileTransferJS" , V ) ;
    V = DownloadURL                                        ;
    EM . SaveVariable ( SC , uuid , "DownloadURL"    , V ) ;
    V = DownloadFile                                       ;
    EM . SaveVariable ( SC , uuid , "DownloadFile"   , V ) ;
    V = UploadURL                                          ;
    EM . SaveVariable ( SC , uuid , "UploadURL"      , V ) ;
    V = UploadFile                                         ;
    EM . SaveVariable ( SC , uuid , "UploadFile"     , V ) ;
    V = UploadUser                                         ;
    EM . SaveVariable ( SC , uuid , "UploadUser"     , V ) ;
    V = UploadPass                                         ;
    EM . SaveVariable ( SC , uuid , "UploadPass"     , V ) ;
    ////////////////////////////////////////////////////////
    SC . close  (       )                                  ;
    Alert       ( Done  )                                  ;
  } else                                                   {
    Alert       ( Error )                                  ;
  }                                                        ;
  SC   . remove (       )                                  ;
}

void N::FileTransferUI::BrowseJava(void)
{
  QString filename = plan->Dirs[N::Directory::Scripts].absoluteFilePath("")  ;
  filename = QFileDialog::getOpenFileName                                    (
               this                                                          ,
               tr("File transfer script")                                    ,
               filename                                                      ,
               tr("Javascript (*.js)")                                     ) ;
  if ( filename . length ( ) <= 0 ) return                                   ;
  ui -> Javascript -> blockSignals ( true     )                              ;
  ui -> Javascript -> setText      ( filename )                              ;
  ui -> Javascript -> blockSignals ( false    )                              ;
  start ( 10002 )                                                            ;
}

void N::FileTransferUI::BrowseOpen(void)
{
  QString filename = plan -> Temporary ( "" )   ;
  filename = QFileDialog::getOpenFileName       (
               this                             ,
               tr("Upload file")                ,
               filename                         ,
               tr("All files (*.*)")          ) ;
  if ( filename . length ( ) <= 0 ) return      ;
  ui -> OpenUpload -> blockSignals ( true     ) ;
  ui -> OpenUpload -> setText      ( filename ) ;
  ui -> OpenUpload -> blockSignals ( false    ) ;
  start ( 10002 )                               ;
}

void N::FileTransferUI::BrowseSave(void)
{
  QString filename = plan -> Temporary ( "" )     ;
  filename = QFileDialog::getSaveFileName         (
               this                               ,
               tr("Save downloaded file")         ,
               filename                           ,
               tr("All files (*.*)")            ) ;
  if ( filename . length ( ) <= 0 ) return        ;
  ui -> SaveDownload -> blockSignals ( true     ) ;
  ui -> SaveDownload -> setText      ( filename ) ;
  ui -> SaveDownload -> blockSignals ( false    ) ;
  start ( 10002 )                                 ;
}

void N::FileTransferUI::FtpState(int index)
{
  FtpChanged ( ) ;
}

void N::FileTransferUI::FtpChanged(void)
{
  start ( 10002 ) ;
}

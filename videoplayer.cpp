#include "m3uparser.h"
#include "videoplayer.h"

// INITIALIZING FUNCTIONS

void VideoPlayer::loadUserInterface()
{
    createMediaPlayer();
    createPositionController();
    createButtons();
    createVolumeController();
    createAboutLabel();
    createTextEditor();

    setupWindow ();
    initLayout ();

    initConnections ();
}

void VideoPlayer::setupWindow()
{
    setStyleSheet(mainwindow_SS);

    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QColor("#405060"), Qt::Dense5Pattern));
    setPalette(palette);

    setGeometry(100, 100, 400, 400);
}

void VideoPlayer::createMediaPlayer()
{
    video = new VideoWidget;
    playlist = new QMediaPlaylist;

    player = new QMediaPlayer;
    player->setObjectName("Player");    
    player->setVideoOutput(video);
    player->setPlaylist(playlist);

    playlistModel = new PlaylistModel;
    playlistModel->setPlaylist(playlist);

    playlistView = new PlaylistView;
    playlistView->setModel(playlistModel);
    playlistView->setStyleSheet(playlist_SS);
    playlistView->setVisible(false);
}

void VideoPlayer::loadStyleSheets()
{    
    QFile file(qApp->applicationDirPath() + "/stylesheets/playlist.qss");
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        playlist_SS = file.readAll();
    }
    else
        playlist_SS = "";
    file.close();

    file.setFileName(qApp->applicationDirPath() + "/stylesheets/texteditor.qss");
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        texteditor_SS = file.readAll();
    }
    else
        texteditor_SS = "";
    file.close();

    file.setFileName(qApp->applicationDirPath() + "/stylesheets/menu.qss");
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        menu_SS = file.readAll();
    }
    else
        menu_SS = "";
    file.close();

    file.setFileName(qApp->applicationDirPath() + "/stylesheets/mainwindow.qss");
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        mainwindow_SS = file.readAll();
    }
    else
        mainwindow_SS = "";
    file.close();

    file.setFileName(qApp->applicationDirPath() + "/stylesheets/dialog.qss");
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        dialog_SS = file.readAll();
    }
    else
        dialog_SS = "";
    file.close();
}

void VideoPlayer::createTextEditor()
{
    text_editor = new TextEditor;
    text_editor->setStyleSheet(texteditor_SS);
}

void VideoPlayer::createButtons()
{
    pb_open_menu = new QMenu;
    pb_open_menu->addAction(tr("Настроить цветовую гамму"), this, SLOT(slotOpenHSVDialog()));
    pb_open_menu->addAction(tr("Открыть файл"), this, SLOT(slotOpenFile()));
    pb_open_menu->setStyleSheet(menu_SS);

    pb_open = new QPushButton;
    pb_open->setObjectName("OpenMovie");
    pb_open->setFixedSize(60,60);    
    pb_open->setMenu(pb_open_menu);

    pb_play = new QPushButton;
    pb_play->setObjectName("Play");
    pb_play->setFixedSize(60,60);

    pb_pause = new QPushButton;
    pb_pause->setObjectName("Pause");
    pb_pause->setFixedSize(60,60);

    pb_stop = new QPushButton;
    pb_stop->setObjectName("Stop");
    pb_stop->setFixedSize(60,60);

    pb_previous = new QPushButton;
    pb_previous->setObjectName("PlaylistPrevious");
    pb_previous->setFixedSize(60,60);

    pb_next = new QPushButton;
    pb_next->setObjectName("PlaylistNext");
    pb_next->setFixedSize(60,60);

    pb_playlist = new QPushButton(tr("Плейлист"));
    pb_playlist->setObjectName("Playlist");
    pb_playlist->setFixedSize(180,50);

    pb_playlistSave = new QPushButton(tr("Сохранить плейлист"));
    pb_playlistSave->setObjectName("Save Playlist");

    pb_playlistLoop = new QPushButton(tr("Циклическое"));
    pb_playlistLoop->setObjectName("Loop Playlist");
    pb_playlistLoop->setCheckable(true);

    pb_playlistRandom = new QPushButton(tr("Cлучайное"));
    pb_playlistRandom->setObjectName("Random Playlist");
    pb_playlistRandom->setCheckable(true);

    pb_playlistShuffle = new QPushButton(tr("Перетасовать"));
    pb_playlistShuffle->setObjectName("Shuffle Playlist");

    quitAfterFinished = false;
    pb_quit_menu = new QMenu;
    pb_quit_menu->addAction(tr("Выкл. ПК после завершения"), this, SLOT(slotStartMonitoringQAF()));
    pb_quit_menu->addAction(tr("Выйти"), qApp, SLOT(quit()));
    pb_quit_menu->setStyleSheet(menu_SS);

    pb_quit = new QPushButton;
    pb_quit->setObjectName("Quit");
    pb_quit->setFixedSize(60, 60);
    pb_quit->setMenu(pb_quit_menu);

    pb_sound = new QPushButton;
    pb_sound->setCheckable(true);
    pb_sound->setObjectName("Sound");
    pb_sound->setFixedSize(60,60);

    pb_show_hide_te = new QPushButton;
    pb_show_hide_te->setCheckable(true);
    pb_show_hide_te->setObjectName("Show-Hide TextEditor");
    pb_show_hide_te->setFixedSize(60,20);
}

void VideoPlayer::createVolumeController()
{
    volume = new QSlider (Qt::Horizontal);
    volume->setObjectName("Volume Controller");
    volume->setWindowFlags(Qt::WindowStaysOnTopHint);
    volume->setValue(player->volume());
    volume->setRange(0, 100);
    volume->setVisible(false);
}

void VideoPlayer::createPositionController()
{
    current_time_label = new QLabel;
    current_time_label->setAlignment(Qt::AlignRight);

    position = new QSlider (Qt::Horizontal);
    position->setObjectName("Position Controller");
    position->setWindowFlags(Qt::WindowStaysOnTopHint);
    position->setRange(0, duration/1000);

    total_time_label = new QLabel;
    total_time_label->setAlignment(Qt::AlignLeft);

    le_goto_position = new QLineEdit;
    le_goto_position->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}")));
    le_goto_position->setText("00:00:00");
    le_goto_position->setFixedWidth(60);
}

void VideoPlayer::createAboutLabel()
{
    about = new QLabel("Zamana's MultiMedia Player v1.35");
}

void VideoPlayer::initLayout()
{
    layout = new QGridLayout;
    layout->setMargin(0);
    layout->addWidget(video, 0, 0, 7, 13);

    layout->addWidget(current_time_label, 8, 0, 1, 3);
    layout->addWidget(position, 8, 3, 1, 6);
    layout->addWidget(total_time_label, 8, 9, 1, 3);
    layout->addWidget(le_goto_position, 8, 12, 1, 1);

    layout->addWidget(pb_open, 9, 0, 1, 1);
    layout->addWidget(pb_sound, 9, 1, 1, 1);
    layout->addWidget(volume, 9, 2, 1, 3);
    layout->addWidget(about, 9, 2, 1, 3);
    layout->addWidget(pb_play, 9, 5, 1, 1);
    layout->addWidget(pb_pause, 9, 6, 1, 1);
    layout->addWidget(pb_stop, 9, 7, 1, 1);
    layout->addWidget(pb_previous, 9, 8, 1, 1);
    layout->addWidget(pb_playlist, 9, 9, 1, 1);
    layout->addWidget(pb_next, 9, 10, 1, 1);
    layout->addWidget(pb_quit, 9, 11, 1, 1);
    layout->addWidget(pb_show_hide_te, 9, 12, 1, 1);
    setLayout(layout);
}

void VideoPlayer::initConnections()
{
    // PLAYER CONTROL BUTTONS
    connect(pb_play, SIGNAL(clicked()), player, SLOT(play()));
    connect(pb_pause, SIGNAL(clicked()), player, SLOT(pause()));
    connect(pb_stop, SIGNAL(clicked()), player, SLOT(stop()));

    // VOLUME CONTROLLER
    connect(pb_sound, SIGNAL(toggled(bool)), this, SLOT(slotShowVolumeController(bool)));
    connect(video, SIGNAL(signalChangeVolume(bool)), this, SLOT(slotChangeVolume(bool)));
    connect(volume, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));    

    // POSITION CONTROLLER
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(slotDurationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(slotPositionChanged(qint64)));
    connect(le_goto_position, SIGNAL(returnPressed()), this, SLOT(slotGoToPosition()));
    connect(position, SIGNAL(sliderMoved(int)), this, SLOT(slotSliderMoved(int)));

    // PLAYLIST
    connect(pb_playlist, SIGNAL(clicked()), this, SLOT(slotShowPlaylist()));
    connect(pb_previous, SIGNAL(clicked()), playlist, SLOT(previous()));
    connect(pb_next, SIGNAL(clicked()), playlist, SLOT(next()));
    connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(slotPlaylistPositionChanged(int)));
    connect(playlist, SIGNAL(currentMediaChanged(QMediaContent)), SLOT(slotCurrentMediaChanged(QMediaContent)));
    connect(pb_playlistSave, SIGNAL(clicked()), this, SLOT(slotSavePlaylist()));
    connect(pb_playlistLoop, SIGNAL(toggled(bool)), this, SLOT(slotLoopPlaylist(bool)));
    connect(pb_playlistRandom, SIGNAL(toggled(bool)), this, SLOT(slotRandomPlaylist(bool)));
    connect(pb_playlistShuffle, SIGNAL(clicked()), playlist, SLOT(shuffle()));
    connect(playlistView, SIGNAL(activated(QModelIndex)), this, SLOT(slotJumpToFile(QModelIndex)));
    connect(playlistView, SIGNAL(signalSendUrls(const QStringList&)), this, SLOT(slotAddToPlaylist(const QStringList&)));
    connect(playlistView, SIGNAL(removeFile(const QModelIndex&)), this, SLOT(slotRemoveFile(const QModelIndex&)));
    connect(playlistView, SIGNAL(swapIndexes(QModelIndex,QModelIndex)), playlistModel, SLOT(swapIndexes(QModelIndex,QModelIndex)));

    // TEXT EDITOR CONTROLLERS
    connect(pb_show_hide_te, SIGNAL(toggled(bool)), text_editor, SLOT(setVisible(bool)));
    connect(text_editor, SIGNAL(signalCloseButtonPushed()), pb_show_hide_te, SLOT(toggle()));

    // VIDEO CONTROLLERS
    connect(video, SIGNAL(signalPause()), this, SLOT(slotPause()));
    connect(video, SIGNAL(signalShowPlaylist()), this, SLOT(slotShowPlaylist()));
}

void VideoPlayer::loadMedia()
{
    QStringList filesToLoad = qApp->arguments();
    filesToLoad.removeAt(0);
    if (filesToLoad.value(0) == "-ua" || filesToLoad.value(0) == "-eng" || filesToLoad.value(0) == "-ru")
        filesToLoad.removeAt(0);
    slotAddToPlaylist(filesToLoad);
}

void VideoPlayer::saveSettings()
{
    settings.beginGroup("/Settings");
        settings.beginGroup("/Geometry");
            settings.setValue("/xpos", geometry().x());
            settings.setValue("/ypos", geometry().y());
            settings.setValue("/width", geometry().width());
            settings.setValue("/height", geometry().height());
        settings.endGroup();

        settings.beginGroup("/Playlist");
            settings.setValue("/last_video", playlist->currentMedia().canonicalUrl());
            settings.setValue("/last_video_position", player->position());
        settings.endGroup();
    settings.endGroup();
}

void VideoPlayer::loadSettings()
{
    settings.beginGroup("/Settings");
        settings.beginGroup("/Geometry");
            int xpos = settings.value("/xpos", 100).toInt();
            int ypos = settings.value("/ypos", 100).toInt();
            int width = settings.value("/width", 500).toInt();
            int height = settings.value("/height", 500).toInt();
            setGeometry (xpos, ypos, width, height);
        settings.endGroup();

        if (!settings.value("/Playlist/last_video").toUrl().isEmpty() &&
            QMessageBox::Ok == QMessageBox::question(this, tr("Подтвердите:"),
                                                           tr("Хотите ли вы продолжить просмотр медиафайла ") + QFileInfo(settings.value("/Playlist/last_video").toUrl().fileName()).baseName() + " ?",
                                                           QMessageBox::Ok, QMessageBox::Cancel))
        {
            settings.beginGroup("/Playlist");
                QUrl last_video = settings.value("/last_video", "").toUrl();
                qint64 last_video_position = settings.value("/last_video_position", 0).toLongLong();
                playlist->addMedia(last_video);
                player->setPosition(last_video_position);
            settings.endGroup();
        }
    settings.endGroup();
}

void VideoPlayer::closeEvent(QCloseEvent *ev)
{
    saveSettings();
    QWidget::closeEvent(ev);
}

void VideoPlayer::slotAddToPlaylist (const QStringList& fileNames)
{
    QUrl url;
    foreach (QString arg, fileNames)
    {        
        QFileInfo fileInfo(arg);
        if (fileInfo.exists())
        {
            url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());

            if (fileInfo.suffix().toLower() == QString("m3u") || fileInfo.suffix().toLower() == QString("m3u8"))
            {
                if (!playlist->isEmpty() && QMessageBox::Yes == QMessageBox::question(this, tr("Подтвердите:"),tr("Обновить плейлист?"), QMessageBox::Yes, QMessageBox::No))
                    playlist->clear();

                M3UParser parser (fileInfo.absoluteFilePath());
                if (!parser.isExtended())
                    playlist->load(url, "m3u8");
                else
                {
                    parser.parseExtendedM3U();
                    QStringList online_media_list = parser.getMedia();                   
                    foreach(QString online_media, online_media_list)
                    {
                        QStringList media_to_add = online_media.split("-,-");

                        QNetworkRequest request;
                        request.setHeader(QNetworkRequest::ContentDispositionHeader, media_to_add.at(0));
                        request.setUrl(media_to_add.at(1));

                        playlist->addMedia(QMediaContent(request));
                    }
                }
            }
            else
                playlist->addMedia(url);

        }
        else
        {
            QUrl url(arg);            
            if (url.isValid())
                playlist->addMedia(url);
        }
    }

    player->play();
}

// SLOTS
void VideoPlayer::slotOpenFile()
{    
    QStringList files = QFileDialog::getOpenFileNames(0, tr("Открыть медиа"),
                                                      QString(), tr("Все файлы (*.*) \n"
                                                                 "Видео (*.avi *.mkv *.wmv *.mp4 *.flv *.bik) \n"
                                                                 "Музыка (*.wav *.mp3 *.ogg *.flac) \n"
                                                                 "Плейлисты (*.m3u, *.m3u8)"));    

    slotAddToPlaylist (files);

    // QMediaResourceList resourses = player->media().resources(); // try to make audiotrack switcher
    // resourses.
}

void VideoPlayer::slotShowVolumeController(bool sound_button_toggled)
{
    if (sound_button_toggled)
    {
        volume->setVisible(true);
        about->setVisible(false);
    }
    else
    {
        volume->setVisible(false);
        about->setVisible(true);
    }
}

void VideoPlayer::slotChangeVolume(bool needToAdd)
{
    if (needToAdd)
        volume->setValue(volume->value() + 1);
    else
        volume->setValue(volume->value() - 1);
}

void VideoPlayer::slotPause()
{
    if (player->state() == QMediaPlayer::PlayingState)
        player->pause();
    else if (player->state() == QMediaPlayer::PausedState || player->state() == QMediaPlayer::StoppedState)
        player->play();
}

// QUIT AFTER FINISHED
void VideoPlayer::slotStartMonitoringQAF()
{
    quitAfterFinished = !quitAfterFinished;
    if (quitAfterFinished)
        connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(slotQuitAfterFinished(qint64)));
    else
        disconnect(player, SIGNAL(positionChanged(qint64)), this, SLOT(slotQuitAfterFinished(qint64)));
}

void VideoPlayer::slotQuitAfterFinished(qint64 cur_time)
{
    if (cur_time == player->duration())
        QProcess::startDetached("shutdown -s -f -t 00");
}

// PLAYLIST
void VideoPlayer::slotShowPlaylist()
{
    if (!playlistView->isVisible() && !video->isFullScreen())
    {
        layout->removeWidget(video);
        layout->removeWidget(playlistView);
        layout->addWidget(video, 0, 3, 8, 10);
        layout->addWidget(playlistView, 0, 0, 6, 3);
        layout->addWidget(pb_playlistLoop, 6, 0, 1, 1);
        layout->addWidget(pb_playlistRandom, 6, 1, 1, 1);
        layout->addWidget(pb_playlistShuffle, 6, 2, 1, 1);
        layout->addWidget(pb_playlistSave, 7, 0, 1, 3);

        playlistView->setVisible(true);
        pb_playlistSave->setVisible(true);
        pb_playlistLoop->setVisible(true);
        pb_playlistRandom->setVisible(true);
        pb_playlistShuffle->setVisible(true);
    }
    else
    {
        layout->removeWidget(video);
        layout->addWidget(video, 0, 0, 7, 13);

        playlistView->setVisible(false);
        pb_playlistSave->setVisible(false);
        pb_playlistLoop->setVisible(false);
        pb_playlistRandom->setVisible(false);
        pb_playlistShuffle->setVisible(false);
    }
}

void VideoPlayer::slotSavePlaylist()
{
    QString filename = QFileDialog::getSaveFileName(0, tr("Сохранить плейлист"), QString(), tr("Файл плейлистов (*.m3u)"));

    QFile file (filename);
    file.open(QIODevice::WriteOnly);

    QTextStream file_stream;
    file_stream.setDevice(&file);
    file_stream.setCodec("windows-1251");

    file_stream << "#EXTM3U" << "\n\n";

    for (int media_index = 0; media_index < playlist->mediaCount(); ++media_index)
    {
        file_stream << "#EXTINF:0, " << playlist->media(media_index).canonicalRequest().header(QNetworkRequest::ContentDispositionHeader).toString() << '\n';
        file_stream << playlist->media(media_index).canonicalUrl().toString() << "\n\n";
    }
}

void VideoPlayer::slotLoopPlaylist(bool isLoop)
{
    if (isLoop && !pb_playlistRandom->isChecked())
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    else
    {
        pb_playlistLoop->setChecked(false);
        if (pb_playlistRandom->isChecked())
            playlist->setPlaybackMode(QMediaPlaylist::Random);
        else
            playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
}

void VideoPlayer::slotRandomPlaylist(bool isRandom)
{
    if (isRandom && !pb_playlistLoop->isChecked())
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    else
    {
        pb_playlistRandom->setChecked(false);
        if (pb_playlistLoop->isChecked())
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
        else
            playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
}

void VideoPlayer::slotPlaylistPositionChanged(int currentItem)
{
    playlistView->setCurrentIndex(playlistModel->index(currentItem, 0, QModelIndex()));
}

void VideoPlayer::slotJumpToFile(QModelIndex activated_index)
{
    if (activated_index.isValid())
    {
        playlist->setCurrentIndex(activated_index.row());       
        player->play();
    }
}

void VideoPlayer::slotCurrentMediaChanged(const QMediaContent& current_media)
{
    QUrl url = current_media.canonicalUrl();
    if (url.isLocalFile())
        setWindowTitle("Zamp: " + QFileInfo(url.fileName()).baseName());
    else
        setWindowTitle("Zamp: " + current_media.canonicalRequest().header(QNetworkRequest::ContentDispositionHeader).toString());
}

void VideoPlayer::slotRemoveFile(const QModelIndex& fileIndex)
{
    playlist->removeMedia(fileIndex.row());
    // Need to try to make deletion faster
}

void VideoPlayer::slotAppendToPlaylist(const QString& file) // singleapp-player connection
{
    if (QFileInfo(file).suffix().toLower() == "m3u" || QFileInfo(file).suffix().toLower() == "m3u8")
        slotAddToPlaylist(QStringList(file));
    else
        playlist->addMedia(QUrl::fromLocalFile(file));
}

// POSITION SLIDER
void VideoPlayer::slotDurationChanged(qint64 new_duration)
{
    duration = new_duration / 1000;
    position->setMaximum(new_duration / 1000);
}

void VideoPlayer::slotPositionChanged(qint64 current_position)
{
    if (!position->isSliderDown())
        position->setValue(current_position / 1000);

    updateTimeInfo (current_position / 1000);
}

void VideoPlayer::slotSliderMoved(int current_position)
{
    player->setPosition(current_position*1000);
}

void VideoPlayer::slotGoToPosition()
{
    QString strWantedPosition = (static_cast<QLineEdit*>(sender()))->text();
    QStringList time = strWantedPosition.split(":");

    ushort hours = time.at(0).toShort();
    ushort minutes = time.at(1).toShort();
    ushort seconds = time.at(2).toShort();

    ulong time_in_msec = (hours*3600 + minutes*60 + seconds)*1000;

    if (time_in_msec <= player->duration())
        player->setPosition(time_in_msec);
}

void VideoPlayer::updateTimeInfo(qint64 current_position)
{
    if (current_position || duration)
    {
        QTime current_time (
                            (current_position/3600)%60,
                            (current_position/60)%60,
                            (current_position%60),
                            (current_position*1000)%1000
                           );

        QTime total_time (
                          (duration/3600)%60,
                          (duration/60)%60,
                          (duration%60),
                          (duration*1000)%1000
                         );

        QString format = tr("mm мин. ss сек.");
        if (duration > 3600)
            format = tr("hh час. mm мин. ss сек.");    

        current_time_label->setText(current_time.toString(format));
        total_time_label->setText(total_time.toString(format));
    }
}

void VideoPlayer::slotOpenHSVDialog()
{    
    if (!HSVDialog)
    {
        HSVDialog = new QDialog;
        HSVDialog->setAttribute(Qt::WA_DeleteOnClose);
        HSVDialog->setWindowTitle(tr("Настройка цветовой гаммы"));
        HSVDialog->setStyleSheet(dialog_SS);

        QSlider *hue = new QSlider (Qt::Horizontal);
        hue->setObjectName("HSVSlider");
        hue->setRange(-100,100);
        hue->setValue(video->hue());
        connect (hue, SIGNAL(sliderMoved(int)), video, SLOT(setHue(int)));
        connect (video, SIGNAL(hueChanged(int)), hue, SLOT(setValue(int)));

        QSlider *saturation = new QSlider (Qt::Horizontal);
        saturation->setObjectName("HSVSlider");
        saturation->setRange(-100,100);
        saturation->setValue(video->saturation());
        connect (saturation, SIGNAL(sliderMoved(int)), video, SLOT(setSaturation(int)));
        connect (video, SIGNAL(saturationChanged(int)), saturation, SLOT(setValue(int)));

        QSlider *contrast = new QSlider (Qt::Horizontal);
        contrast->setObjectName("HSVSlider");
        contrast->setRange(-100,100);
        contrast->setValue(video->contrast());
        connect (contrast, SIGNAL(sliderMoved(int)), video, SLOT(setContrast(int)));
        connect (video, SIGNAL(contrastChanged(int)), contrast, SLOT(setValue(int)));

        QPushButton *pb_close = new QPushButton (tr("Закрыть"));
        pb_close->setObjectName("CloseDialog");
        pb_close->setFixedWidth(100);
        connect(pb_close, SIGNAL(clicked()), HSVDialog, SLOT(hide()));

        QFormLayout *layout = new QFormLayout;
        layout->addRow(tr("Тон"), hue);
        layout->addRow(tr("Насыщенность"), saturation);
        layout->addRow(tr("Контраст"), contrast);
        layout->addWidget(pb_close);
        layout->setAlignment(pb_close, Qt::AlignRight);

        HSVDialog->setLayout(layout);

        HSVDialog->setMinimumWidth(300);
        HSVDialog->setFixedHeight(150);
    }

    HSVDialog->show();
}

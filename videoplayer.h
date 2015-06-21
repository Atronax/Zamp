#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

// LOGIC
#include <QApplication>
#include <QProcess>
#include <QTime>

#include <QMediaPlayer>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QMenu>
#include <QFile>
#include <QUrl>

// WIDGETS
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>

#include "playlistmodel.h"
#include "playlistview.h"
#include "videowidget.h"
#include "texteditor.h"

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = 0) :
        QWidget (parent),
        settings ("ZST Interaction", "Zamp"),
        HSVDialog (nullptr)
    {
        loadStyleSheets();
        loadUserInterface();
        loadSettings();

        loadMedia();
    }    

protected:
    virtual void closeEvent(QCloseEvent *ev);

    void saveSettings ();
    void loadSettings ();        

    void updateTimeInfo (qint64);

private:
    void loadStyleSheets();

    void createMediaPlayer();
    void createTextEditor();
    void createButtons();
    void createVolumeController();
    void createPositionController();
    void createAboutLabel();
    void setupWindow();
    void initLayout();
    void loadUserInterface();

    void initConnections();

    void loadMedia();

    // MAIN ELEMENTS OF VIDEOPLAYER
    QMediaPlayer* player;
    VideoWidget* video;
    QSettings settings;
    qint64 duration;

    // MISC CONTROLLERS
    bool quitAfterFinished;
    QPushButton *pb_open, *pb_play, *pb_stop, *pb_pause, *pb_quit;
    QMenu *pb_open_menu, *pb_quit_menu;
    QLabel *about;

    // STYLESHEETS
    QString mainwindow_SS, playlist_SS, menu_SS, texteditor_SS, dialog_SS;

    // TEXTEDITOR CONTROLLERS
    TextEditor* text_editor;
    QPushButton* pb_show_hide_te;

    // PLAYLIST CONTROLLERS
    QMediaPlaylist* playlist;
    PlaylistModel* playlistModel;
    PlaylistView* playlistView;
    QPushButton *pb_previous, *pb_next, *pb_playlist, *pb_playlistSave, *pb_playlistLoop, *pb_playlistRandom, *pb_playlistShuffle;

    // VOLUME CONTROLLERS
    QSlider* volume;
    QPushButton* pb_sound;

    // POSITION CONTROLLERS
    QSlider* position;
    QLabel *current_time_label, *total_time_label;
    QLineEdit *le_goto_position;

    QGridLayout* layout;

    QDialog* HSVDialog;

signals:    

public slots:
    void slotOpenFile (void);
    void slotPause (void);

    void slotStartMonitoringQAF (void);
    void slotQuitAfterFinished (qint64);

    void slotShowVolumeController(bool);
    void slotChangeVolume(bool);

    void slotShowPlaylist (void);
    void slotSavePlaylist (void);
    void slotLoopPlaylist (bool);
    void slotRandomPlaylist (bool);
    void slotPlaylistPositionChanged (int);
    void slotCurrentMediaChanged (const QMediaContent&);
    void slotJumpToFile (QModelIndex);
    void slotRemoveFile (const QModelIndex&);
    void slotAppendToPlaylist (const QString&); // singleapp<=>player connection
    void slotAddToPlaylist (const QStringList&); // for other uses

    void slotDurationChanged (qint64);
    void slotPositionChanged (qint64);
    void slotSliderMoved (int);
    void slotGoToPosition ();

    void slotOpenHSVDialog (void);
};

#endif // VIDEOPLAYER_H

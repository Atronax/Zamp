#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QListView>

class PlaylistView : public QListView
{
    Q_OBJECT
public:
    PlaylistView (QWidget *parent = 0)
        : QListView(parent)
    {
        enableDragAndDrop();
    }

protected:
    void enableDragAndDrop ();

    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);

    virtual void dragEnterEvent(QDragEnterEvent *ev);
    virtual void dragMoveEvent(QDragMoveEvent *ev);
    virtual void dropEvent(QDropEvent *ev);

private:
    bool formatIsAccepted (const QString& file);
    QModelIndex source, target;

signals:
    void signalSendUrls (const QStringList&);

    void removeFile (const QModelIndex&);
    void swapIndexes (const QModelIndex&, const QModelIndex&);

public slots:

};

#endif // LISTVIEW_H

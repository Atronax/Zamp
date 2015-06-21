// LOGIC
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include "playlistview.h"

// setup widgets
void PlaylistView::enableDragAndDrop()
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setAutoScroll(true);

    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::MoveAction);
}

// event handlers
void PlaylistView::keyPressEvent(QKeyEvent *ev)
{
    if (hasFocus())
    {
        if (ev->key() == Qt::Key_Delete)
            emit removeFile (currentIndex());
    }
    else
        QWidget::keyPressEvent(ev);
}

bool PlaylistView::formatIsAccepted (const QString& file)
{
    QString suffix = QFileInfo(file).suffix().toLower();

    if (suffix == "avi" || suffix == "flv" || suffix == "mp4" ||
        suffix == "wmv" || suffix == "mkv" || suffix == "bik" ||
        suffix == "mp3" || suffix == "ogg" || suffix == "wav" ||
        suffix == "fla" || suffix == "flac" || suffix == "m3u")
        return true;
    else
        return false;
}

void PlaylistView::dragEnterEvent(QDragEnterEvent *ev)
{
    if (ev->mimeData()->hasUrls() && formatIsAccepted(ev->mimeData()->data("FileName")))
        ev->acceptProposedAction();
    else
        QListView::dragEnterEvent(ev);
}

void PlaylistView::dragMoveEvent(QDragMoveEvent *ev)
{
    if (ev->mimeData()->hasUrls() && formatIsAccepted(ev->mimeData()->data("FileName")))
        ev->acceptProposedAction();
    else
        QListView::dragMoveEvent(ev);
}

void PlaylistView::dropEvent(QDropEvent *ev)
{
    if (ev->mimeData()->hasUrls())
    {
        QStringList filesToLoad;

        QList<QUrl> urls = ev->mimeData()->urls();
        foreach (QUrl url, urls)
            filesToLoad.append(url.path().mid(1)); // filepath without file:///

        emit signalSendUrls(filesToLoad);
    }

    if (ev->source() == this)
    {
        target = indexAt(ev->pos()); // remember place to drop draggable item

        if (source.isValid() && target.isValid())
            emit swapIndexes (source, target);

        source = QModelIndex();
        target = QModelIndex();
    }
}

void PlaylistView::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        source = indexAt(ev->pos()); // remember currently draggable item
    QListView::mousePressEvent(ev);
}

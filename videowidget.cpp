#include "videowidget.h"

void VideoWidget::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape)
    {
        if (isFullScreen())
            setFullScreen(false);
        ev->accept();
    }
    else if (ev->key() == Qt::Key_Space)
    {
        emit signalPause();
        ev->accept();
    }
    else
        QVideoWidget::keyPressEvent(ev);
}

void VideoWidget::mousePressEvent(QMouseEvent *ev)
{    
    if (ev->button() == Qt::MiddleButton)
    {
        emit signalShowPlaylist();
        ev->accept();
    }
    else
        QVideoWidget::mousePressEvent(ev);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        setFullScreen(!isFullScreen());
        ev->accept();
    }
}

void VideoWidget::wheelEvent(QWheelEvent *ev)
{
    if (ev->angleDelta().ry() > 0)
        emit signalChangeVolume (true);
    else if (ev->angleDelta().ry() < 0)
        emit signalChangeVolume (false);
    ev->accept();
}

void VideoWidget::contextMenuEvent(QContextMenuEvent *ev)
{
    context_menu->exec(ev->globalPos());
    ev->accept();
}

void VideoWidget::closeEvent(QCloseEvent *ev)
{
    ev->ignore();
}

void VideoWidget::slotSetAspectRatio()
{
    QString aspectRatio = ((QAction *) sender())->text();

    if (aspectRatio == tr("Игнорировать"))
        setAspectRatioMode(Qt::IgnoreAspectRatio);
    else if (aspectRatio == tr("Стандартный размер"))
        setAspectRatioMode(Qt::KeepAspectRatio);
}

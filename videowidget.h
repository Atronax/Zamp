#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

// helping includes
#include <QMenu>

// events
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = 0) : QVideoWidget (parent)
    {
        setAttribute(Qt::WA_OpaquePaintEvent);
        setWindowFlags(Qt::Window | Qt::SubWindow);
        setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

        QPalette pal = palette();
        pal.setColor(QPalette::Window, Qt::black);
        setPalette(pal);

        context_menu = new QMenu;
        QMenu* context_menu_AspectRatio = new QMenu (tr("Отношение сторон"));
        context_menu_AspectRatio->addAction(tr("Игнорировать"), this, SLOT(slotSetAspectRatio()));
        context_menu_AspectRatio->addAction(tr("Стандартный размер"), this, SLOT(slotSetAspectRatio()));
        context_menu->addMenu(context_menu_AspectRatio);
    }

protected:
    virtual void keyPressEvent (QKeyEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseDoubleClickEvent (QMouseEvent *ev);
    virtual void wheelEvent(QWheelEvent *ev);

    virtual void contextMenuEvent(QContextMenuEvent *ev);
    virtual void closeEvent(QCloseEvent *ev);

private:
    QMenu* context_menu;

signals:
    void signalPause();
    void signalShowPlaylist();
    void signalChangeVolume(bool isAdding);

public slots:
    void slotSetAspectRatio();

};

#endif // VIDEOWIDGET_H

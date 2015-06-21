// LOGIC
#include <QApplication>
#include <QStyleOptionButton>
#include <QPainter>
#include <QPainterPath>
#include <QGradient>

// WIDGETS
#include <QPushButton>

#include "megastyle.h"

void MegaStyle::polish(QWidget *w)
{
    if (qobject_cast<QPushButton*>(w))
        w->setAttribute(Qt::WA_Hover, true);
}

void MegaStyle::unpolish(QWidget *w)
{
    if (qobject_cast<QPushButton*>(w))
        w->setAttribute(Qt::WA_Hover, false);
}

void MegaStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    switch (pe)
    {
    case PE_FrameFocusRect:
        break;

    case PE_PanelButtonCommand:
        {
            const QStyleOptionButton *pOptionButton = qstyleoption_cast<const QStyleOptionButton*> (opt);
            if (pOptionButton)
            {
                p->setRenderHint(QPainter::Antialiasing, true);

                bool bDown = pOptionButton->state & State_Sunken || pOptionButton->state & State_On;
                bool bHover = pOptionButton->state & State_Enabled && pOptionButton->state & State_MouseOver;
                bool bHasFocus = pOptionButton->state & State_HasFocus;

                if (w->objectName() == "Quit")
                {                    
                    p->drawPixmap(opt->rect, QPixmap(":/megastyle/quit_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap(":/megastyle/quit_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/quit_button_infocus.png"));
                }
                else if (w->objectName() == "Play")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/play_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/play_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/play_button_infocus.png"));
                }
                else if (w->objectName() == "Pause")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/pause_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/pause_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/pause_button_infocus.png"));
                }
                else if (w->objectName() == "Stop")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/stop_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/stop_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/stop_button_infocus.png"));
                }
                else if (w->objectName() == "Sound")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/sound_button.png"));

                    if (bDown)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/sound_button_toggled.png"));

                    if (bHover && bDown)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/sound_button_toggled_hover.png"));
                    else if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/sound_button_hover.png"));

                    if (bHasFocus && bDown)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/sound_button_toggled_infocus.png"));                    
                    else if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/sound_button_infocus.png"));
                }
                else if (w->objectName() == "OpenMovie")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/open_movie_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/open_movie_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/open_movie_button_infocus.png"));
                }
                else if (w->objectName() == "PlaylistPrevious")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_previous_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_previous_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_previous_button_infocus.png"));
                }
                else if (w->objectName() == "PlaylistNext")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_next_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_next_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_next_button_infocus.png"));
                }
                else if (w->objectName() == "Playlist" || w->objectName() == "Save" || w->objectName() == "Load")
                {
                    p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_button.png"));

                    if (bHover)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_button_hover.png"));

                    if (bHasFocus)
                        p->drawPixmap(opt->rect, QPixmap (":/megastyle/playlist_button_infocus.png"));
                }
                else if (w->objectName() == "Loop Playlist" || w->objectName() == "Random Playlist" || w->objectName() == "Shuffle Playlist" || w->objectName() == "Save Playlist")
                {
                    QPainterPath button;
                    button.addRoundedRect(pOptionButton->rect, 20, 25);

                    if (bDown)
                        p->drawPath(button);

                }
                else if (w->objectName() == "CloseDialog")
                {
                    QProxyStyle::drawPrimitive(pe, opt, p, w);
                }
                else
                {
                    QLinearGradient button_pressed = makeLinearGradient(opt->rect, Qt::white, Qt::black);
                    QLinearGradient button_released = makeLinearGradient(opt->rect, Qt::black, Qt::white);
                    QBrush brButton = bDown ? QBrush(button_pressed) : QBrush(button_released);

                    QPainterPath button;
                    button.addRoundedRect(pOptionButton->rect, 20, 25);

                    p->fillPath(button, brButton);

                    if (bHover)
                    {
                        p->drawPath(button);
                        p->fillPath(button, QColor (100, 80, 180, 60));
                    }

                    if (bHasFocus)
                    {
                        p->drawPath(button);
                        p->fillPath(button, QColor (180, 80, 100, 60));
                    }
                }
            }
        }
        break;

    default:
        QProxyStyle::drawPrimitive(pe, opt, p, w);
        break;
    }
}

void MegaStyle::drawControl(ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    bool bHover = (opt->state & State_Enabled) && (opt->state & State_MouseOver);

    switch (element)
    {
    case CE_ShapedFrame:
        break;

    case CE_ScrollBarAddLine:
    {
        if (opt->state & QStyle::State_Horizontal)
            p->drawPixmap(opt->rect, QPixmap(":/megastyle/scrollbar_button_addline.png"));
        else
            p->drawPixmap(opt->rect, QPixmap(":/megastyle/scrollbar_button_addpage.png"));

        if (bHover)
            p->fillRect(opt->rect, QColor(40, 40, 40, 100));
    }
        break;

    case CE_ScrollBarSubLine:
    {
        if (opt->state & QStyle::State_Horizontal)
            p->drawPixmap(opt->rect, QPixmap(":/megastyle/scrollbar_button_subline.png"));
        else
            p->drawPixmap(opt->rect, QPixmap(":/megastyle/scrollbar_button_subpage.png"));

        if (bHover)
            p->fillRect(opt->rect, QColor(40, 40, 40, 100));
    }
        break;

    case CE_ScrollBarSubPage: case CE_ScrollBarAddPage:
    {
        p->eraseRect(opt->rect);
        p->fillRect(opt->rect, QBrush(Qt::darkGray, Qt::Dense5Pattern));
    }
        break;

    case CE_ScrollBarSlider:
    {
        if (opt->state & QStyle::State_Horizontal)
            p->drawPixmap(opt->rect, QPixmap(":/megastyle/scrollbar_slider_lefttoright.jpg"));
        else
            p->drawPixmap(opt->rect, QPixmap(":/megastyle/scrollbar_slider_uptobottom.jpg"));

        if (bHover)
            p->fillRect(opt->rect, QColor(40,40,40,100));
    }
        break;

    default:
        QProxyStyle::drawControl(element, opt, p, w);
        break;
    }
}

void MegaStyle::drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *w) const
{
    switch (cc)
    {
        case CC_Slider:
        {
            QRect handle = subControlRect(CC_Slider, opt, QCommonStyle::SC_SliderHandle, w);
            QRect groove = subControlRect(CC_Slider, opt, QCommonStyle::SC_SliderGroove, w);

            handle.setSize(QSize(17,17));
            groove.setHeight(18);

            if (w->objectName() == "HSVSlider")
                p->fillRect(groove, makeLinearGradient(opt->rect, QColor("#FFFFFF"), QColor("#7AB4EF")));
            else
                p->fillRect(groove, makeRadialGradient(opt->rect, Qt::gray, Qt::black));

            if (w->objectName() == "Volume Controller")
                p->drawPixmap(handle, QPixmap(":/megastyle/sound_slider_clicked.png"));
            else if (w->objectName() == "Position Controller")
                p->drawPixmap(handle, QPixmap(":/megastyle/down_pointer.png"));
            else
                p->fillRect(handle, QBrush("#0D1D36", Qt::Dense2Pattern));
        }
            break;

        default:
            QProxyStyle::drawComplexControl(cc, opt, p, w);
            break;
        }
}

// HELP FUNCZ
QLinearGradient MegaStyle::makeLinearGradient(const QRect& rect, const QColor& left, const QColor& right)
{
    QLinearGradient gradient (0, 0, rect.width(), rect.height());
    gradient.setColorAt(0, left);
    gradient.setColorAt(0.5,right);
    gradient.setColorAt(1, left);
    return gradient;
}

QRadialGradient MegaStyle::makeRadialGradient(const QRect& rect, const QColor& in_center, const QColor& around_center)
{
    QRadialGradient gradient (QPointF(rect.width()/2, rect.height()/2), rect.width() < rect.height() ? rect.width() : rect.height());
    gradient.setColorAt(0, in_center);
    gradient.setColorAt(1, around_center);
    return gradient;
}

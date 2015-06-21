#ifndef MEGASTYLE_H
#define MEGASTYLE_H

#include <QProxyStyle>

class MegaStyle: public QProxyStyle
{
public:
    explicit MegaStyle (QStyle* style = 0)
        : QProxyStyle (style)
    {

    }

    virtual ~MegaStyle ()
    {

    }

protected:
    virtual void polish (QWidget *w);
    virtual void unpolish (QWidget *w);

    virtual void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const;
    virtual void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w) const;
    virtual void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *w) const;

private:
    static QLinearGradient makeLinearGradient (const QRect& rect, const QColor& left, const QColor& right);
    static QRadialGradient makeRadialGradient (const QRect& rect, const QColor& in_center, const QColor& around_center);
};

#endif // MEGASTYLE_H

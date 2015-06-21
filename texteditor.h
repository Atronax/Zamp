#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

// LOGIC
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include <QMouseEvent>
#include <QCloseEvent>

// WIDGETS
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

class TextEditor : public QWidget
{
    Q_OBJECT
public:
    TextEditor(QWidget *parent = 0)
        : QWidget (parent, Qt::WindowStaysOnTopHint)
    {
        initGUI();
        setupWidget();
    }

protected:
    void setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br);

    void initGUI (void);
    void setupWidget (void);

    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);

    virtual void closeEvent(QCloseEvent *ev);

private:
    QTextEdit *te_editor;
    QPushButton *pb_save, *pb_load;
    QString title_filename;

    QPoint cur_mouse_pt;

signals:
    void signalCloseButtonPushed ();
    void signalChangeWindowTitle (const QString&);

public slots:
    void slotSave (void);
    void slotLoad (void);

};

#endif // TEXTEDITOR_H

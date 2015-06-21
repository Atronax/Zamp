#include "texteditor.h"

void TextEditor::initGUI()
{
    te_editor = new QTextEdit;
    connect (this, SIGNAL(signalChangeWindowTitle(QString)), this, SLOT(setWindowTitle(QString)));

    pb_save = new QPushButton (tr("Сохранить"));
    pb_save->setObjectName("Save");
    pb_save->setMinimumSize(60, 40);
    connect (pb_save, SIGNAL(clicked()), this, SLOT(slotSave()));

    pb_load = new QPushButton (tr("Загрузить"));
    pb_load->setObjectName("Load");
    pb_load->setMinimumSize(60, 40);
    connect (pb_load, SIGNAL(clicked()), this, SLOT(slotLoad()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(te_editor, 0, 0, 8, 2);
    layout->addWidget(  pb_save, 8, 0, 1, 1);
    layout->addWidget(  pb_load, 8, 1, 1, 1);

    setLayout(layout);
}

void TextEditor::setupWidget()
{
    setFixedSize(400, 500);
    setContentsMargins(5,10,5,10);

    QPalette pal = palette();
    pal.setBrush(backgroundRole(), QBrush(QColor("#405060"), Qt::Dense5Pattern));
    setPalette (pal);

    setAttribute(Qt::WA_DeleteOnClose);
}

void TextEditor::slotSave()
{
    QString filename = QFileDialog::getSaveFileName(0, title_filename);
    if (!filename.isEmpty())
    {
        title_filename = filename;

        QFile file (title_filename);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream (&file) << te_editor->toPlainText();
            file.close();
            emit signalChangeWindowTitle(title_filename);
        }
    }
}

void TextEditor::slotLoad()
{
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isEmpty())
        return;

    QFile file (filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream text_stream (&file);
        te_editor->setPlainText(text_stream.readAll());
        file.close();

        title_filename = filename;
        emit signalChangeWindowTitle(title_filename);
    }
}

void TextEditor::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        cur_mouse_pt = ev->globalPos() - frameGeometry().topLeft();
        ev->accept();
    }
}

void TextEditor::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
        move(ev->globalPos() - cur_mouse_pt);
        ev->accept();
    }
}

void TextEditor::closeEvent(QCloseEvent *ev)
{
    emit signalCloseButtonPushed();
    QWidget::closeEvent(ev);
}

void TextEditor::setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br)
{
    QRegion region;
    QRegion round;
    QRegion corner;

    region = QRegion(0, 0, width(), height(), QRegion::Rectangle);

    // top left
    round  = QRegion(0, 0, 2*radius_tl, 2*radius_tl, QRegion::Ellipse);
    corner = QRegion(0, 0,   radius_tl,   radius_tl, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round)); // вычитаем из угла кусок эллипса

    // top right
    round  = QRegion(width()-2*radius_tr, 0, 2*radius_tr, 2*radius_tr, QRegion::Ellipse);
    corner = QRegion(width()-  radius_tr, 0,   radius_tr,   radius_tr, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // bottom right
    round  = QRegion(width()-2*radius_br, height()-2*radius_br, 2*radius_br, 2*radius_br, QRegion::Ellipse);
    corner = QRegion(width()-  radius_br, height()-  radius_br,   radius_br,   radius_br, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // bottom left
    round  = QRegion(0, height()-2*radius_bl, 2*radius_bl, 2*radius_bl, QRegion::Ellipse);
    corner = QRegion(0, height()-  radius_bl,   radius_bl,   radius_bl, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    setMask(region);
}

TEMPLATE = app

QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11

RESOURCES = resources.qrc
RC_FILE = zamp.rc

include(qtsingleapplication/src/qtsingleapplication.pri)

SOURCES += main.cpp \
    megastyle.cpp \
    videoplayer.cpp \
    playlistmodel.cpp \
    playlistview.cpp \
    videowidget.cpp \
    texteditor.cpp \
    m3uparser.cpp

HEADERS += \
    megastyle.h \
    videoplayer.h \
    playlistmodel.h \
    playlistview.h \
    videowidget.h \
    texteditor.h \
    appwithtranslator.h \
    m3uparser.h

TARGET = Zamp



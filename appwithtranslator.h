#ifndef APPWITHTRANSLATOR_H
#define APPWITHTRANSLATOR_H

#include <QtSingleApplication>
#include <QTranslator>

class AppWithTranslator : public QtSingleApplication
{
    Q_OBJECT

public:
    explicit AppWithTranslator (int argc, char *argv[])
        : QtSingleApplication(argc, argv)
    {
        if (argv[1] != '\0')
        {
            QString lang = QString(argv[1]).remove(0,1);

            QTranslator *app_translator = new QTranslator; //2mb usage of memory
            app_translator->load(lang, qApp->applicationDirPath() + "/translations/");
            if (!app_translator->isEmpty())
                installTranslator(app_translator);
        }
    }

signals:    

public slots:
};

#endif // APPWITHTRANSLATOR_H

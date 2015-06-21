#include "appwithtranslator.h"
#include "videoplayer.h"
#include "megastyle.h"

int main (int argc, char *argv[])
{    
    AppWithTranslator app (argc, argv);
    app.setOrganizationName("ZST Interaction");
    app.setApplicationName("Zamp");
    app.setWindowIcon(QIcon(app.applicationDirPath() + "/zamp.ico"));
    app.setStyle(new MegaStyle); // 10mb of memory usage

    if (app.isRunning())
    {
        QStringList args = app.arguments();
        args.removeAt(0);
        foreach (QString arg, args)
            app.sendMessage(arg);

        return 0;
    }

    VideoPlayer *player = new VideoPlayer;        
    player->show();

    QObject::connect(&app, SIGNAL(messageReceived(const QString&)), player, SLOT(slotAppendToPlaylist(const QString&)));
    app.setActivationWindow(player);

    return app.exec();
}

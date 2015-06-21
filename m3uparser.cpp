#include "m3uparser.h"

void M3UParser::parseExtendedM3U()
{
    QString line, url, cur_media;
    QStringList line_list;

    while(!in.atEnd())
    {
        line = in.readLine();

        if (line.startsWith("#EXTINF:"))
        {
            line_list = line.split(","); // at (1) - name of channel
            url = in.readLine();

            cur_media = line_list.at(1) + "-,-" + url;

            if (!url.startsWith("rtmp") && !url.startsWith("udp")) // blocks rtmps and udps
                media.append(cur_media);
        }
    }
}

bool M3UParser::isExtended()
{
    QString line = in.readLine();
    if (line.startsWith("#EXTM3U"))
        return true;
    else
        return false;        
}

const QStringList& M3UParser::getMedia() const
{
    return media;
}

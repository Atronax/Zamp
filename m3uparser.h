#ifndef M3UPARSER_H
#define M3UPARSER_H

#include <QFile>
#include <QTextStream>
#include <QStringList>

class M3UParser
{
public:
    explicit M3UParser (const QString& file_to_parse)
    {
        to_parse.setFileName(file_to_parse);
        if (!to_parse.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        in.setDevice(&to_parse);
        // in.setCodec("UTF-8");
        in.setCodec("Windows-1251");
    }

    ~M3UParser()
    {
        to_parse.close();
    }

    bool isExtended ();
    void parseExtendedM3U ();

    const QStringList& getMedia () const;

private:
    QFile to_parse;
    QTextStream in;
    QStringList media;
};

#endif // M3UPARSER_H

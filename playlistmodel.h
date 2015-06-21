#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractItemModel>
#include <QMediaPlaylist>

class PlaylistModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Column {Title = 0, ColumnCount};

    explicit PlaylistModel (QObject *parent = 0)
        : QAbstractItemModel (parent),
          m_playlist (nullptr)
    {
        m_playlist = new QMediaPlaylist;
    }

    QMediaPlaylist* playlist () const;
    void setPlaylist (QMediaPlaylist *playlist);

    QModelIndex index (int row, int column, const QModelIndex &parent) const;

protected:
    int rowCount (const QModelIndex &parent = QModelIndex()) const;
    int columnCount (const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent (const QModelIndex &child) const;    

    QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    Qt::DropActions supportedDropActions() const;

signals:

public slots:
    void beginInsertItems (int start, int end);
    void endInsertItems ();

    void beginRemoveItems (int start, int end);
    void endRemoveItems ();

    void changeItems (int start, int end);
    void swapIndexes (const QModelIndex&, const QModelIndex&);

private:
    QMediaPlaylist *m_playlist;
    QMap<QModelIndex, QVariant> m_data;
};

#endif // PLAYLISTMODEL_H

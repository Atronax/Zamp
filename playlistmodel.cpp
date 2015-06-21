// LOGIC
#include <QFileInfo>
#include <QUrl>

#include "playlistmodel.h"

// ROW/COLUMN COUNTER

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    return (m_playlist && !parent.isValid()) ? m_playlist->mediaCount() : 0;
}

int PlaylistModel::columnCount(const QModelIndex &parent) const
{
    return !parent.isValid() ? ColumnCount : 0;
}

QModelIndex PlaylistModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

// INDEX GETTER
QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent) const
{
    return (m_playlist && !parent.isValid() && row >= 0 && row < m_playlist->mediaCount() && column >= 0 && column < ColumnCount)
                      ? createIndex(row, column) : QModelIndex();
}

// DATA GETTER/SETTER
QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole)
    {
        QVariant value = m_data[index];

        if (!value.isValid() && index.column() == Title)
        {
            QUrl url = m_playlist->media(index.row()).canonicalUrl();
            if (url.isLocalFile())
                return QFileInfo(url.path()).baseName();
            else // url is an internet link
                return m_playlist->media(index.row()).canonicalRequest().header(QNetworkRequest::ContentDispositionHeader);
        }
        else
            return value;
    }
    else
        return QVariant();
}

bool PlaylistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    m_data[index] = value;
    emit dataChanged(index, index);

    return true;
}

// PLAYLIST GETTER/SETTER
QMediaPlaylist* PlaylistModel::playlist() const
{
    return m_playlist;
}

void PlaylistModel::setPlaylist (QMediaPlaylist *new_playlist)
{
    if (m_playlist)
    {
        disconnect(m_playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginInsertItems(int,int)));
        disconnect(m_playlist, SIGNAL(mediaInserted(int,int)), this, SLOT(endInsertItems()));
        disconnect(m_playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginRemoveItems(int,int)));
        disconnect(m_playlist, SIGNAL(mediaRemoved(int,int)), this, SLOT(endRemoveItems()));
        disconnect(m_playlist, SIGNAL(mediaChanged(int,int)), this, SLOT(changeItems(int,int)));
    }

    beginResetModel();
        m_playlist = new_playlist;

        if (m_playlist)
        {
            connect(m_playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginInsertItems(int,int)));
            connect(m_playlist, SIGNAL(mediaInserted(int,int)), this, SLOT(endInsertItems()));
            connect(m_playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginRemoveItems(int,int)));
            connect(m_playlist, SIGNAL(mediaRemoved(int,int)), this, SLOT(endRemoveItems()));
            connect(m_playlist, SIGNAL(mediaChanged(int,int)), this, SLOT(changeItems(int,int)));
        }
    endResetModel();
}

// SLOTS
void PlaylistModel::beginInsertItems(int start, int end)
{
    m_data.clear();
    beginInsertRows(QModelIndex(), start, end);
}

void PlaylistModel::endInsertItems()
{
    endInsertRows();
}

void PlaylistModel::beginRemoveItems(int start, int end)
{
    m_data.clear();
    beginRemoveRows(QModelIndex(), start, end);
}

void PlaylistModel::endRemoveItems()
{
    endRemoveRows();
}

void PlaylistModel::changeItems(int start, int end)
{
    m_data.clear();
    emit dataChanged(index(start,0, QModelIndex()), index(end,ColumnCount, QModelIndex()));
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
    else
        return Qt::NoItemFlags;
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

void PlaylistModel::swapIndexes(const QModelIndex& source, const QModelIndex& target)
{
    beginMoveRows(source, source.row(), source.row(), target, target.row());
        QVariant temp = source.data();
        m_data[source] = target.data();
        m_data[target] = temp;

        QMediaContent source_content = m_playlist->media(source.row());
        QMediaContent target_content = m_playlist->media(target.row());

        bool isSourceLesser = source < target; // 2-->1 leads to invalid indexes. Why???
        beginRemoveItems(isSourceLesser ? source.row() : target.row(), isSourceLesser ? target.row() : source.row());
            m_playlist->removeMedia(target.row());
            m_playlist->insertMedia(target.row(), source_content);
            m_playlist->removeMedia(source.row());
            m_playlist->insertMedia(source.row(), target_content);
        endRemoveItems();
    endMoveRows();
}

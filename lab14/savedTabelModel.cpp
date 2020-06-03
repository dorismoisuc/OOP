#include "savedTabelModel.h"
#include "qfont.h"
#include "qbrush.h"

int savedTabelModel::rowCount(const QModelIndex& parent) const
{
    return this->repoServant.getForServant().size();
}

int savedTabelModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant savedTabelModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();
    Chore currentChore = this->repoServant.getForServant()[row];
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
        case 0:
            return QString::fromStdString(currentChore.getTitle());
        case 1:
            return QString::fromStdString(currentChore.getType());
        case 2:
            return QString::fromStdString(currentChore.getLastPerformed());
        case 3:
            return QString::fromStdString(to_string(currentChore.getTimesPerformed()));
        case 4:
            return QString::fromStdString(currentChore.getVision());
        default:
            break;
        }
    }
    return QVariant();
}

QVariant savedTabelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("TITLE");
            case 1:
                return QString("TYPE");
            case 2:
                return QString("LAST PERFORMED");
            case 3:
                return QString("TIMES PERFORMED");
            case 4:
                return QString("VISION");
            default:break;
            }
        }
    }
    if (role == Qt::FontRole)
    {
        QFont serifFont("Times", 10, QFont::Bold);
        return serifFont;
    }
   
    return QVariant();
}

void savedTabelModel::Update()
{
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}


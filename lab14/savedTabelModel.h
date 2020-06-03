#pragma once
#include <qabstractitemmodel.h>
#include "Repo.h"
#include "FileRepository.h"
#include <qvariant.h>

class savedTabelModel :
    public QAbstractTableModel
{
private:
    RepoServant& repoServant;
public:
    savedTabelModel(RepoServant& r) :repoServant{ r } {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void Update();
};


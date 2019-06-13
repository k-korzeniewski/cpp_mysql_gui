#include "authdialog.h"

AuthDialog::AuthDialog(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant AuthDialog::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex AuthDialog::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex AuthDialog::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int AuthDialog::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int AuthDialog::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant AuthDialog::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

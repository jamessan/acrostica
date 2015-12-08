#ifndef ACROSTICA_MISSINGLETTERSMODEL_H
#define ACROSTICA_MISSINGLETTERSMODEL_H

#include <QList>
#include <QMap>
#include <QAbstractTableModel>

class MissingLettersModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MissingLettersModel(QWidget *parent = 0);
    MissingLettersModel(const QStringList& letters, QWidget *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

private:
    QStringList letters_;
    QMap<uint, QString> cache_;
};

#endif

#ifndef ACROSTICA_MISSINGLETTERSMODEL_H
#define ACROSTICA_MISSINGLETTERSMODEL_H

#include <QList>
#include <QMap>
#include <QAbstractTableModel>

class MissingLettersModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  MissingLettersModel(const QString& name, QWidget *parent = 0);
  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  Qt::ItemFlags flags(const QModelIndex& index) const;

public slots:
  void addLetters();
  void addLetters(const QString& str);
  void removeLetters();
  void removeLetters(const QString& str);

private:
  void setLetters(uint hash, const QString& str, int sign);

  QMap<uint, QString> cache_;
  QList<int> added_, removed_;
  QStringList letters_;
  QString name_;
};

#endif

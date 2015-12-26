#include <QtWidgets>
#include "MissingLettersModel.h"

#include <QMap>
#include <QModelIndex>
#include <QString>
#include <QVector>

#include <algorithm>
#include <cstring>

#include "ClueWidget.h"

namespace
{
  void getHashAndBody(QObject* obj, uint& hash, QString& body);
}

MissingLettersModel::MissingLettersModel(const QString& name, QWidget *parent)
  : QAbstractTableModel(parent), name_(name)
{
  for (int i = rowCount() * columnCount(); i > 0; i--)
  {
    added_ << 0;
    removed_ << 0;
    letters_ << "";
  }
}

int MissingLettersModel::rowCount(const QModelIndex& parent) const
{
  return 13;
}

int MissingLettersModel::columnCount(const QModelIndex& parent) const
{
  return 2;
}

QVariant MissingLettersModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount() || index.column() >= columnCount())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  return letters_[index.row() + index.column() * rowCount()];
}

QVariant MissingLettersModel::headerData(int section, Qt::Orientation orientation,
                                         int role) const
{
  return QVariant();
}

Qt::ItemFlags MissingLettersModel::flags(const QModelIndex& index) const
{
  return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void MissingLettersModel::addLetters()
{
  uint hash;
  QString text;

  getHashAndBody(sender(), hash, text);

  setLetters(hash, text, 1);
}

void MissingLettersModel::removeLetters()
{
  uint hash;
  QString text;

  getHashAndBody(sender(), hash, text);

  setLetters(hash, text, -1);
}

void MissingLettersModel::setLetters(uint hash, const QString& str, int sign)
{
  QString oldval = cache_.value(hash);
  QString newval = cache_[hash] = str.toUpper();

  QMap<char, int> delta;

  for (auto c : oldval.toLatin1())
  {
    if (::isalpha(c))
    {
      delta[c]--;
    }
  }

  for (auto c : newval.toLatin1())
  {
    if (::isalpha(c))
    {
      delta[c]++;
    }
  }

  for (auto it = delta.begin(); it != delta.end(); ++it)
  {
    char c = it.key();
    int i = c - 'A';
    int count = it.value();
    QModelIndex index = this->index(i % 13, i / 13);
    if (sign > 0)
    {
      added_[i] = std::max(added_[i] + count, 0);
    }
    else
    {
      removed_[i] = std::max(removed_[i] + count, 0);
    }
    letters_[i] = QString(std::max(added_[i] - removed_[i], 0), QChar(c));
    setData(index, letters_[i], Qt::DisplayRole);
    emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
  }
}

namespace
{
  void getHashAndBody(QObject *obj, uint& hash, QString& body)
  {
    const char* name = obj->metaObject()->className();

    if (strcmp(name, "ClueWidget") == 0)
    {
      ClueWidget *widget = qobject_cast<ClueWidget*>(obj);

      hash = qHash(widget);
      body = widget->toPlainText();
    }
    else if (strcmp(name, "QPlainTextEdit") == 0)
    {
      QPlainTextEdit *widget = qobject_cast<QPlainTextEdit*>(obj);

      hash = qHash(widget);
      body = widget->toPlainText();
    }
    else
    {
      qDebug() << "Unknown class: " << name;
      abort();
    }
  }
}

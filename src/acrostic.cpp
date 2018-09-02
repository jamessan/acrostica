/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2016-2018 James McCoy <jamessan@jamessan.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "acrostica/acrostic.h"
#include <QtWidgets>

#include <memory>

#include <QVariant>

namespace acrostica
{

void Clue::read(const QJsonObject &json)
{
  if (json.contains("hint") && json["hint"].isString())
  {
    hint = json["hint"].toString();
  }

  if (json.contains("answer") && json["answer"].isString())
  {
    answer = json["answer"].toString();
  }
}

void Clue::write(QJsonObject &json) const
{
  json["hint"] = hint;
  json["answer"] = answer;
}

void Acrostic::read(const QJsonObject &json)
{
  if (json.contains("message") && json["message"].isString())
  {
    message = json["message"].toString();
  }

  if (json.contains("clues") && json["clues"].isArray())
  {
    QJsonArray clueArray = json["clues"].toArray();

    clues.clear();
    clues.reserve(clueArray.size());
    for (int i = 0, max = clueArray.size(); i < max; i++)
    {
      QJsonObject obj = clueArray[i].toObject();
      Clue clue;
      clue.read(obj);
      this->clues.append(clue);
    }
  }
}

void Acrostic::write(QJsonObject &json) const
{
  json["message"] = message;
  QJsonArray clueArray;
  for (auto const clue : clues)
  {
    QJsonObject obj;
    clue.write(obj);
    clueArray.append(obj);
  }
  json["clues"] = clueArray;
}

ClueModel::ClueModel(std::shared_ptr<Acrostic> acrostic, QObject *parent)
  : QAbstractTableModel(parent)
  , mAcrostic(acrostic)
{}

QVariant ClueModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (index.row() >= rowCount() || index.column() >= columnCount())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    auto c = mAcrostic->clues.at(index.row());
    return QVariant::fromValue((index.column() == 0) ? c.hint : c.answer);
  }
  else
  {
    return QVariant();
  }
}

Qt::ItemFlags ClueModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return Qt::ItemIsEnabled;
  }

  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool ClueModel::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
  if (index.isValid() && role == Qt::EditRole)
  {
    auto clue = mAcrostic->clues.value(index.row());

    if (index.column() % 2)
    {
      clue.answer = value.toString();
    }
    else
    {
      clue.hint = value.toString();
    }

    mAcrostic->clues.replace(index.row(), clue);

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
  }

  return false;
}

QVariant ClueModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }
  if (orientation == Qt::Horizontal)
  {
    return QVariant::fromValue(section == 0 ? tr("Hint") : tr("Answer"));
  }

  QString s;
  // Change to 1-based indexing so the following loop works
  section++;
  while (section > 0)
  {
    s.prepend(QChar('A' + (section - 1) % 26));
    section = (section - 1) / 26;
  }
  return QVariant::fromValue(s);
}

bool ClueModel::insertRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);

  beginInsertRows(QModelIndex(), row, row + count - 1);
  for (int i = 0; i < count; ++i)
  {
    mAcrostic->clues.insert(row, { QString(), QString() });
  }
  endInsertRows();
  return true;
}

bool ClueModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);

  beginRemoveRows(QModelIndex(), row, row + count - 1);
  for (int i = 0; i < count; ++i)
  {
    mAcrostic->clues.removeAt(row);
  }
  endRemoveRows();
  return true;
}

void ClueModel::propagateDownMsg(const QString &downMsg)
{
  int rows = rowCount();
  int msglen = downMsg.size();

  if (msglen > rows)
  {
    insertRows(rows, msglen - rows);
  }
  else if (msglen < rows)
  {
    removeRows(msglen, rows - msglen);
  }

  for (int row = 0; row < msglen; row++)
  {
    auto idx = index(row, 1);
    auto s = idx.data().toString();
    if (s.isEmpty())
    {
      s.push_back(downMsg.at(row));
    }
    else
    {
      s = s.replace(0, 1, downMsg.at(row));
    }
    setData(idx, QVariant::fromValue(s));
  }
}

}

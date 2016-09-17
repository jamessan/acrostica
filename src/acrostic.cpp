/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2016 James McCoy <jamessan@jamessan.com>
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

#include "acrostic.h"

#include <memory>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "clue.h"

namespace acrostica
{
  acrostic::acrostic(QObject *parent)
    : QAbstractListModel(parent), clues_(), message_()
  {}

  void acrostic::load(const QJsonObject &json)
  {
    message_ = json["message"].toString();

    clues_.clear();
    QJsonArray clues = json["clues"].toArray();
    for (const QJsonValue &v : clues)
    {
      const QJsonObject obj = v.toObject();
      std::shared_ptr<clue> c(new clue(this));
      c->load(obj);
      clues_ << c;
    }
  }

  void acrostic::dump(QJsonObject &json) const
  {
    json["message"] = message_;

    QJsonArray clues;
    for (const auto &c : clues_)
    {
      QJsonObject obj;
      c->dump(obj);
      clues.append(obj);
    }
  }

  int acrostic::rowCount(const QModelIndex &parent) const
  {
    return clues_.count();
  }

  QVariant acrostic::data(const QModelIndex &index, int role) const
  {
    if (!index.isValid())
    {
      return QVariant();
    }

    if (index.row() >= clues_.size())
    {
      return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      return QVariant::fromValue(clues_.at(index.row()));
    }
    else
    {
      return QVariant();
    }
  }

  Qt::ItemFlags acrostic::flags(const QModelIndex &index) const
  {
    if (!index.isValid())
    {
      return Qt::ItemIsEnabled;
    }

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
  }

  bool acrostic::setData(const QModelIndex &index,
                         const QVariant &value, int role)
  {
    if (index.isValid() && role == Qt::EditRole)
    {
      auto c(value.value<std::shared_ptr<clue>>());
      clues_[index.row()]->setHint(c->hint());
      clues_[index.row()]->setAnswer(c->answer());
      emit dataChanged(index, index);
      return true;
    }

    return false;
  }

  void acrostic::updateClues(const QString& msg)
  {
    int nclues = clues_.size();
    int msglen = msg.length();
    int clueidx;
    int i;

    for (clueidx = 0, i = 0; clueidx < nclues && i < msglen; clueidx++, i++)
    {
      auto clue = clues_[clueidx];
      if (msg[i].isLetter() && clue->answer()[0] != msg[i].toUpper())
      {
        QString ans(clue->answer());
        clue->setAnswer(ans.replace(0, 1, msg[i].toUpper()));
        setData(index(clueidx, 0, QModelIndex()),
                QVariant::fromValue(clue));
      }
    }

    if (i < msglen)
    {
      QList<int> letters;
      for (; i < msglen; i++)
      {
        if (msg[i].isLetter())
        {
          letters << i;
        }
      }

      beginInsertRows(QModelIndex(), rowCount(),
                      rowCount() + letters.size() - 1);
      for (auto n : letters)
      {
        auto clue(std::shared_ptr<clue>(new class clue(this)));
        clues_ << clue;
        clues_[clueidx]->setAnswer(msg[n].toUpper());
        clueidx++;
      }
      endInsertRows();
    }
    else if (clueidx < nclues)
    {
      beginRemoveRows(QModelIndex(), clueidx, nclues - 1);
      while (nclues > clueidx)
      {
        auto c(clues_.takeLast());
        nclues--;
        c->setAnswer("");
      }
      endRemoveRows();
    }
  }
}

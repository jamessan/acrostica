/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2016-2018 James McCoy <jamessan@jamessan.com>
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

#ifndef ACROSTICA_ACROSTIC_H
#define ACROSTICA_ACROSTIC_H

#include <memory>

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QString>

Q_DECLARE_SMART_POINTER_METATYPE(std::shared_ptr)

namespace acrostica
{

struct Clue
{
  QString hint;
  QString answer;

  bool operator==(const Clue &other) const
  {
    return hint == other.hint && answer == other.answer;
  }
};

typedef QString Message;

struct Acrostic
{
  Message message;
  QList<Clue> clues;

  bool operator==(const Acrostic &other) const
  {
    return message == other.message
      && clues == other.clues;
  }
};

class ClueModel : public QAbstractTableModel
{
  Q_OBJECT

 public:
  ClueModel(std::shared_ptr<Acrostic> acrostic, QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override
  {
    Q_UNUSED(parent)
    return mAcrostic->clues.size();
  }
  int columnCount(const QModelIndex &parent = QModelIndex()) const override
  {
    Q_UNUSED(parent)
    return 2;
  }
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;

 private:
  std::shared_ptr<Acrostic> mAcrostic;
};

}

#endif

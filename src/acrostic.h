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

#ifndef ACROSTICA_ACROSTIC_H
#define ACROSTICA_ACROSTIC_H

#include <memory>

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QPair>
#include <QString>

#include "clue.h"

class QJsonObject;

Q_DECLARE_SMART_POINTER_METATYPE(std::shared_ptr)

namespace acrostica
{
  typedef QString message;
  class acrostic : public QAbstractListModel
  {
    Q_OBJECT

  public:
    acrostic(QObject *parent = nullptr);

    void load(const QJsonObject &json);
    void dump(QJsonObject &json) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

  public slots:
    void updateClues(const QString& msg);

  private:
    QList<std::shared_ptr<clue>> clues_;
    message message_;
  };
}

#endif

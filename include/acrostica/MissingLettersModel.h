/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2014-2018 James McCoy <jamessan@jamessan.com>
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

#ifndef ACROSTICA_MISSINGLETTERSMODEL_H
#define ACROSTICA_MISSINGLETTERSMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <QVector>

enum AdditiveSource
{
  Message,
  Clues
};

namespace acrostica
{
struct Acrostic;

class Q_DECL_EXPORT MissingLettersModel : public QAbstractListModel
{
  Q_OBJECT

public:
  MissingLettersModel(std::shared_ptr<acrostica::Acrostic> acrostic,
                      AdditiveSource source, QWidget *parent = 0);
  QVariant data(const QModelIndex& index, int role) const override;

  int rowCount(const QModelIndex& parent = QModelIndex()) const override
  {
    Q_UNUSED(parent);
    return mLetters.size();
  }
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override
  {
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
  }
  Qt::ItemFlags flags(const QModelIndex& index) const override
  {
    Q_UNUSED(index);
    return Qt::ItemIsEnabled;
  }

public slots:
  void update();

private:
  QVector<QString> mLetters;
  AdditiveSource mSource;
  std::shared_ptr<acrostica::Acrostic> mAcrostic;
};

}

#endif

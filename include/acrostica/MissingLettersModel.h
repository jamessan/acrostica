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

#include <QAbstractTableModel>
#include <QVector>

namespace acrostica
{
struct Acrostic;
}

enum AdditiveSource
{
  Message,
  Clues
};

class Q_DECL_EXPORT MissingLettersModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  MissingLettersModel(std::shared_ptr<acrostica::Acrostic> acrostic,
                      AdditiveSource source, QWidget *parent = 0);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override
  {
    Q_UNUSED(parent);
    return 6;
  }
  int columnCount(const QModelIndex& parent = QModelIndex()) const override
  {
    Q_UNUSED(parent);
    return 5;
  }
  QVariant data(const QModelIndex& index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

public slots:
  void update();

private:
  QVector<QString> mLetters;
  AdditiveSource mSource;
  std::shared_ptr<acrostica::Acrostic> mAcrostic;
};

#endif

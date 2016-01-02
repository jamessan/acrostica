/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2014-2015 James McCoy <jamessan@jamessan.com>
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

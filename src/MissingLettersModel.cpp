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

#include "acrostica/MissingLettersModel.h"

#include <algorithm>
#include <memory>

#include <QMap>
#include <QString>
#include <QtWidgets>
#include <QVector>

#include "acrostica/acrostic.h"

namespace acrostica
{

MissingLettersModel::MissingLettersModel(std::shared_ptr<acrostica::Acrostic> acrostic,
                                         AdditiveSource source, QWidget *parent)
  : QAbstractListModel(parent)
  , mLetters()
  , mSource(source)
  , mAcrostic(acrostic)
{
  // XXX Fix handling of the non-ASCII QChars
}

QVariant MissingLettersModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  return mLetters[index.row()];
}

void MissingLettersModel::update()
{
  QMap<QChar, int> delta;

  int msgVal = (mSource == AdditiveSource::Message) ? 1 : -1;
  int clueVal = (mSource == AdditiveSource::Clues) ? 1 : -1;

  for (auto c : mAcrostic->message.toUpper())
  {
    if (c.isLetter())
    {
      delta[c] += msgVal;
    }
  }

  for (auto clue : mAcrostic->clues)
  {
    for (auto c : clue.answer.toUpper())
    {
      if (c.isLetter())
      {
        delta[c] += clueVal;
      }
    }
  }

  QVector<QString> letters;
  for (auto pair : delta.toStdMap())
  {
    QChar c = pair.first;
    int count = std::max(pair.second, 0);
    if (count > 0) {
      letters.append(QString(QChar(c)) + QString::number(count));
    }
  }

  beginResetModel();
  mLetters = letters;
  endResetModel();
}

}

#include "acrostica/moc_MissingLettersModel.cpp"

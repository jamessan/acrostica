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

#include "clue.h"

#include <QJsonObject>
#include <QString>

namespace acrostica
{
  void swap(clue &lhs, clue &rhs)
  {
    using std::swap;

    swap(lhs.hint_, rhs.hint_);
    swap(lhs.answer_, rhs.answer_);
  }

  clue::clue(QObject *parent) : QObject(parent)
  {}

  clue::clue(const QString &hint, const QString &answer, QObject *parent)
    : QObject(parent), hint_(hint), answer_(answer)
  {}

  clue::clue(const clue &c) : clue(c.hint_, c.answer_, c.parent())
  {}

  clue::clue(clue &&c) : clue()
  {
    swap(*this, c);
  }

  clue& clue::operator=(clue c)
  {
    swap(*this, c);
    return *this;
  }

  void clue::load(const QJsonObject &json)
  {
    hint_ = json["hint"].toString();
    answer_ = json["answer"].toString();
  }

  void clue::dump(QJsonObject &json) const
  {
    json["hint"] = hint_;
    json["answer"] = answer_;
  }
}

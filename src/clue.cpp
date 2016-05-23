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

namespace acrostica
{
  clue::clue() : hint_(), answer_()
  {}

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

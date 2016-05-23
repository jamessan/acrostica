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

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "clue.h"

namespace acrostica
{
  acrostic::acrostic() : clues_(), message_()
  {}

  void acrostic::load(const QJsonObject &json)
  {
    message_ = json["message"].toString();

    clues_.clear();
    QJsonArray clues = json["clues"].toArray();
    for (const QJsonValue &v : clues)
    {
      const QJsonObject obj = v.toObject();
      clue c;
      c.load(obj);
      clues_ << c;
    }
  }

  void acrostic::dump(QJsonObject &json) const
  {
    json["message"] = message_;

    QJsonArray clues;
    for (const clue &c : clues_)
    {
      QJsonObject obj;
      c.dump(obj);
      clues.append(obj);
    }
  }
}

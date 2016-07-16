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

#ifndef ACROSTICA_CLUE_H_
#define ACROSTICA_CLUE_H_

#include <QObject>
#include <QString>

class QJsonObject;

namespace acrostica
{
  class clue : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QString hint READ hint WRITE setHint)
    Q_PROPERTY(QString answer READ answer WRITE setAnswer)

  public:
    clue(QObject *parent = nullptr);

    void load(const QJsonObject &json);
    void dump(QJsonObject &json) const;

    const QString& hint() const { return hint_; }
    const QString& answer() const { return answer_; }

  public slots:
    void setHint(const QString& hint) { hint_ = hint; }
    void setAnswer(const QString& answer) { answer_ = answer; }

  private:
    QString hint_;
    QString answer_;
  };
}

#endif

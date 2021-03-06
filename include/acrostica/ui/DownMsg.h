/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2016-2018 James McCoy <jamessan@jamessan.com>
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

#ifndef ACROSTICA_UI_DOWNMESSAGE_
#define ACROSTICA_UI_DOWNMESSAGE_

#include <QGroupBox>
#include <QString>

class QLabel;
class QLineEdit;

namespace acrostica
{
namespace ui
{

class Q_DECL_EXPORT downmsg : public QGroupBox
{
  Q_OBJECT

public:
  downmsg(QWidget *parent = 0);
  void reset(const QString &text);

public slots:
  void mergeMsg(const QModelIndex &parent, int first, int last);
  void mergeMsg(const QModelIndex &first, const QModelIndex &last,
                const QVector<int> &roles = QVector<int>());

signals:
  void textEdited(const QString& text);

private:
  void morphToLabel(const QString &text);
  void morphToLineEdit(const QString &text);

  bool useLabel;
  QLineEdit *lineEdit;
  QLabel *label;
};

}
}

#endif

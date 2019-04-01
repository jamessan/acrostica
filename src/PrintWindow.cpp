/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2018 James McCoy <jamessan@jamessan.com>
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

#include "acrostica/PrintWindow.h"

#include <QtWidgets>

namespace acrostica
{

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
  Q_UNUSED(index);
  auto fm = QFontMetrics(option.font);
  auto rect = fm.boundingRect("⁰⁰ M ⁰⁰");
  rect.setHeight(rect.height() * 3);
  rect.setWidth(rect.width() * 2);
  return rect.size();
}

void ItemDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
  QString text = index.data().toString();
  if (text.isEmpty() || text[0].isSpace()) {
    painter->save();
    painter->fillRect(option.rect, Qt::black);
    painter->restore();
  } else {
    QStyledItemDelegate::paint(painter, option, index);
  }
}

PrintWindow::PrintWindow(QWidget *parent)
  : QWidget(parent)
  , mModel(new QStringListModel(this))
  , mView(new QListView(this))
  , mItemDelegate(new ItemDelegate(this))
{
  setWindowFlags(Qt::Window);
  hide();

  auto title = new QLineEdit(this);
  title->setPlaceholderText(tr("Title"));
  title->setAlignment(Qt::AlignCenter);

  mView->setModel(mModel);
  mView->setFlow(QListView::LeftToRight);
  mView->setWrapping(true);
  mView->setResizeMode(QListView::Adjust);
  mView->setItemDelegate(mItemDelegate);

  auto font = mView->font();
  font.setStyleHint(QFont::Monospace);
  font.setCapitalization(QFont::AllUppercase);
  mView->setFont(font);
  mView->setUniformItemSizes(true);

  auto layout = new QVBoxLayout(this);
  layout->addWidget(title);
  layout->addWidget(mView);
}

void PrintWindow::setMessage(const QString &msg)
{
  QString norm = msg.simplified();
  QStringList chars;
  QStringList sup;
  int n = 1;
  sup << "⁰" << "¹" << "²" << "³" << "⁴" << "⁵" << "⁶" << "⁷" << "⁸" << "⁹";

  for (const auto &c : norm) {
    if (c.isSpace()) {
      chars << c;
    } else if (c.isLetter()) {
      QString s;
      int i = n;
      while (i > 0) {
        s.prepend(sup[i % 10]);
        i /= 10;
      }
      n++;
      s.append(' ');
      chars << s;
    }
  }

  mModel->setStringList(chars);
}

}

#include "acrostica/moc_PrintWindow.cpp"

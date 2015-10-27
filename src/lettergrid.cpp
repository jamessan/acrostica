#include <QtWidgets>
#include "lettergrid.h"

#include <QHash>

#include <cctype>

LetterGrid::LetterGrid(const QString& title, QWidget *parent) : QGroupBox(title, parent)
{
  QGridLayout *layout = new QGridLayout;
  letters.reserve(26);
  for (int i = 0; i < 26; i++)
  {
    letters.append(new QLabel(this));
    if (i < 13)
      layout->addWidget(letters[i], i, 0);
    else
      layout->addWidget(letters[i], i - 13, 1);
  }
  setLayout(layout);
}

void LetterGrid::setText(const QString& str, uint hash)
{
  QString oldStr = widgetCaches.value(hash);
  QString newStr = widgetCaches[hash] = str.toUpper();

  QMap<char, int> deltas;

  for (auto c : oldStr.toLatin1())
  {
    if (isalpha(c))
      deltas[c]--;
  }

  for (auto c : newStr.toLatin1())
  {
    if (isalpha(c))
      deltas[c]++;
  }

  for (auto it = deltas.begin(); it != deltas.end(); ++it)
  {
    QLabel *label = letters[it.key() - 'A'];
    int delta = it.value();
    if (delta > 0)
    {
      label->setText(label->text() + QString(delta, it.key()));
    }
    else if (delta < 0)
    {
      label->setText(label->text().remove(0, -delta));
    }
  }
}

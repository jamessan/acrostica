/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2014-2016 James McCoy <jamessan@jamessan.com>
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

#ifndef ACROSTICA_MAINWINDOW_H
#define ACROSTICA_MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class ClueWidget;
class MissingLettersModel;
class MissingLettersUI;
class QAction;
class QGroupBox;
class QMenu;
class QPlainTextEdit;
class QScrollArea;
class QWidget;

namespace acrostica
{
  namespace widget
  {
    class downmsg;
  }
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

protected:
  void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
  void newAcrostic();
  void open();
  bool save();
  void print();

  void setClues();

private:
  void createActions();
  void createMenus();
  void createWidgets();
  void layoutWidgets();

  QMenu *fileMenu;

  QAction *newAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *printAction;
  QAction *exitAction;

  QWidget *centralWidget;

  QGroupBox *message;
  QPlainTextEdit *messageText;
  QGroupBox *messageLetters;
  MissingLettersUI *messageLettersView;
  MissingLettersModel *missingMessageLetters;

  acrostica::widget::downmsg *downMessage;

  QScrollArea *scroller;
  QGroupBox *clueBox;
  QList<ClueWidget*> clueList;

  QGroupBox *clueLetters;
  MissingLettersUI *clueLettersView;
  MissingLettersModel *missingClueLetters;
};

#endif // ACROSTICA_H

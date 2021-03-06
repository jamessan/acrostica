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

#ifndef ACROSTICA_MAINWINDOW_H
#define ACROSTICA_MAINWINDOW_H

#include <memory>

#include <QList>
#include <QMainWindow>

class MissingLettersUI;
class QAction;
class QFileDialog;
class QGroupBox;
class QMenu;
class QSplitter;
class QString;
class QWidget;

namespace acrostica
{
  struct Acrostic;
  class ClueModel;
  class MessageWidget;
  class MissingLettersModel;
  namespace ui
  {
    class downmsg;
  }
}

class Q_DECL_EXPORT MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

protected:
  void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
  void newAcrostic();
  void open();
  bool save(bool forceNewName = false);
  bool saveAs();
  void print();

private:
  void createActions();
  void createMenus();
  void createWidgets();
  void layoutWidgets();

  void saveSettings();
  void restoreSettings();

  bool maybeSave();
  QString filename(bool forceNewName);
  void setFilename(const QString &fname);

  QMenu *fileMenu;

  QAction *newAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *mSaveAsAction;
  QAction *printAction;
  QAction *exitAction;
  QAction *addClueAction;
  QAction *removeClueAction;

  QFileDialog *mSaveDialog;

  QWidget *mCentralWidget;

  acrostica::MessageWidget *mMessage;
  QGroupBox *messageLetters;
  MissingLettersUI *messageLettersView;

  QSplitter *mClueSplitter;
  QSplitter *mMessageSplitter;

  acrostica::ui::downmsg *mDownMessage;
  acrostica::MissingLettersModel *missingMessageLetters_;
  acrostica::MissingLettersModel *missingClueLetters_;
  acrostica::ClueModel *clues_;
  std::shared_ptr<acrostica::Acrostic> mAcrostic;

  QGroupBox *clueBox_;

  QGroupBox *clueLetters;
  MissingLettersUI *clueLettersView;

  QString filename_;
};

#endif // ACROSTICA_H

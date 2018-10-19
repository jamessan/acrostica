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

#include "acrostica/mainwindow.h"

#include <memory>

#include <QtWidgets>

#include "acrostica/acrostic.h"
#include "acrostica/ui/DownMsg.h"
#include "acrostica/MessageWidget.h"
#include "acrostica/MissingLettersModel.h"
#include "acrostica/MissingLettersUI.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , mCentralWidget(new QWidget)
  , missingMessageLetters_(nullptr)
  , missingClueLetters_(nullptr)
  , clues_(nullptr)
  , mAcrostic(std::make_shared<acrostica::Acrostic>())
{
  setCentralWidget(mCentralWidget);
  setFilename("");

  statusBar();
  createActions();
  createMenus();
  createWidgets();
  layoutWidgets();
}

void MainWindow::createActions()
{
  newAction = new QAction(tr("&New"), this);
  newAction->setShortcut(QKeySequence::New);
  newAction->setStatusTip(tr("Create a new acrostic"));
  connect(newAction, SIGNAL(triggered()), this, SLOT(newAcrostic()));

  openAction = new QAction(tr("&Open…"), this);
  openAction->setShortcut(QKeySequence::Open);
  openAction->setStatusTip(tr("Open existing acrostic"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction(tr("&Save"), this);
  saveAction->setShortcut(QKeySequence::Save);
  saveAction->setStatusTip(tr("Save current acrostic"));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  mSaveAsAction = new QAction(tr("Save As…"), this);
  mSaveAsAction->setShortcut(QKeySequence::SaveAs);
  mSaveAsAction->setStatusTip(tr("Save current acrostic to a new file"));
  connect(mSaveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

  printAction = new QAction(tr("&Print…"), this);
  printAction->setShortcut(QKeySequence::Print);
  printAction->setStatusTip(tr("Print"));
  printAction->setEnabled(false);
  connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

  exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(QKeySequence::Quit);
  exitAction->setMenuRole(QAction::QuitRole);
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

  addClueAction = new QAction(tr("&Add Clue"), this);
  addClueAction->setStatusTip(tr("Add a new, empty clue at the end of the clues"));

  removeClueAction = new QAction(tr("&Remove Clue"), this);
  removeClueAction->setStatusTip(tr("Remove the selected clue"));
  removeClueAction->setEnabled(false);
}

void MainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newAction);
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(mSaveAsAction);
  fileMenu->addAction(printAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  auto editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(addClueAction);
  editMenu->addAction(removeClueAction);
}

void MainWindow::createWidgets()
{
  mMessage = new acrostica::MessageWidget(this);

  messageLetters = new QGroupBox(tr("Letters Missing from Message"), this);
  messageLettersView = new MissingLettersUI(messageLetters);
  missingMessageLetters_ = new acrostica::MissingLettersModel(mAcrostic, Clues, messageLettersView);
  messageLettersView->setModel(missingMessageLetters_);

  mDownMessage = new acrostica::ui::downmsg(this);

  clues_ = new acrostica::ClueModel(mAcrostic, this);

  clueBox_ = new QGroupBox(tr("Clues"), this);
  auto clueView = new QTableView(clueBox_);
  auto policy = clueView->sizePolicy();
  policy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
  clueView->setSizePolicy(policy);
  clueView->setSortingEnabled(false);
  clueView->setCornerButtonEnabled(false);
  clueView->setModel(clues_);
  clueView->setTabKeyNavigation(false);
  clueView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  QVBoxLayout *clueLayout = new QVBoxLayout(clueBox_);
  clueLayout->addWidget(clueView);

  clueLetters = new QGroupBox(tr("Letters Missing from Clues"), this);
  clueLettersView = new MissingLettersUI(clueLetters);
  missingClueLetters_ = new acrostica::MissingLettersModel(mAcrostic, Message, clueLettersView);
  clueLettersView->setModel(missingClueLetters_);

  connect(addClueAction, &QAction::triggered,
          [=](){ clues_->insertRow(clues_->rowCount() + 1); });

  connect(mMessage, &acrostica::MessageWidget::textChanged,
          [=](const QString& msg){
            mAcrostic->message = msg;
            missingClueLetters_->update();
            missingMessageLetters_->update();
            setWindowModified(true);
          });

  connect(mDownMessage, SIGNAL(textEdited(const QString&)),
          clues_, SLOT(propagateDownMsg(const QString&)));

  connect(clues_, &acrostica::ClueModel::dataChanged,
          [=](){
            missingClueLetters_->update();
            missingMessageLetters_->update();
            setWindowModified(true);
          });
  connect(clues_, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)),
          mDownMessage, SLOT(mergeMsg(const QModelIndex&, const QModelIndex&, const QVector<int>&)));

  connect(clues_, &acrostica::ClueModel::rowsRemoved,
          [=](){ missingMessageLetters_->update(); });
  connect(clues_, &acrostica::ClueModel::rowsRemoved,
          [=](){ missingClueLetters_->update(); });
}

void MainWindow::layoutWidgets()
{
  QVBoxLayout *messageLettersLayout = new QVBoxLayout(messageLetters);
  messageLettersLayout->addWidget(messageLettersView);

  QVBoxLayout *clueLettersLayout = new QVBoxLayout(clueLetters);
  clueLettersLayout->addWidget(clueLettersView);

  QGridLayout *centralLayout = new QGridLayout(mCentralWidget);
  centralLayout->addWidget(mMessage, 0, 0);
  centralLayout->addWidget(messageLetters, 0, 1);
  centralLayout->addWidget(mDownMessage, 1, 0, 1, 2);
  centralLayout->addWidget(clueBox_, 2, 0);
  centralLayout->addWidget(clueLetters, 2, 1);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (maybeSave())
  {
    event->accept();
  }
  else
  {
    event->ignore();
  }
}

void MainWindow::newAcrostic()
{
  if (!maybeSave())
  {
    return;
  }

  mAcrostic->message.clear();
  mAcrostic->clues.clear();
  mMessage->setText("");
  mDownMessage->reset("");
  clues_->reset();

  setFilename("");
}

void MainWindow::open()
{
  if (!maybeSave())
  {
    return;
  }

  QString filename = QFileDialog::getOpenFileName(this,
                                                  tr("Open Acrostic"),
                                                  "",
                                                  tr("Acrostic (*.json)"));
  if (filename.isEmpty()) {
    return;
  }

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(this, tr("Unable to open file %1").arg(filename), file.errorString());
    return;
  }

  QByteArray bytes = file.readAll();
  QJsonDocument doc(QJsonDocument::fromJson(bytes));
  mAcrostic->read(doc.object());

  mMessage->setText(mAcrostic->message);

  QString downmsg;
  for (const auto &clue : mAcrostic->clues)
  {
    if (!clue.answer.isEmpty())
    {
      downmsg.append(clue.answer[0]);
    }
  }
  mDownMessage->reset(downmsg);
  clues_->reset();

  setFilename(filename);
}

QString MainWindow::filename(bool forceNewName)
{
  QString filename;
  if (forceNewName || filename_.isEmpty())
  {
    filename = QFileDialog::getSaveFileName(this,
                                            tr("Save Acrostic"),
                                            "",
                                            tr("Acrostic (*.json)"));
  }
  else {
    filename = filename_;
  }

  return filename;
}

bool MainWindow::maybeSave()
{
  if (!isWindowModified())
  {
    return true;
  }

  const QMessageBox::StandardButton ret = QMessageBox::warning(this,
                                                               "Acrostica",
                                                               "Do you want to save your changes?",
                                                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                                               QMessageBox::Save);
  switch (ret)
  {
    case QMessageBox::Save: {
      return save();
    }
    case QMessageBox::Discard:
      return true;
    case QMessageBox::Cancel:
    default:
      return false;
  }
}

bool MainWindow::save(bool forceNewName)
{
  QString fname = filename(forceNewName);

  if (fname.isEmpty())
  {
    return false;
  }

  QFile file(fname);
  if (!file.open(QIODevice::WriteOnly)) {
    QMessageBox::information(this, tr("Unable to open file %1").arg(fname), file.errorString());
    return false;
  }

  QJsonObject obj;
  mAcrostic->write(obj);
  QJsonDocument doc(obj);
  file.write(doc.toJson());

  setFilename(fname);

  return true;
}

bool MainWindow::saveAs()
{
  bool forceNewName = true;
  return save(forceNewName);
}

void MainWindow::setFilename(const QString &fname)
{
  filename_ = fname;

  if (filename_.isEmpty())
  {
    setWindowTitle("Acrostica[*]");
  }
  else
  {
    setWindowTitle(QString("Acrostica - %1[*]")
                   .arg(QFileInfo(filename_).fileName()));
  }
  setWindowModified(false);
}

void MainWindow::print()
{
}

#include "acrostica/moc_mainwindow.cpp"

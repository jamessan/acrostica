/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2014-2018 James McCoy <jamessan@jamessan.com>
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

#include <QtWidgets>
#include "mainwindow.h"

#include <memory>

#include <QPalette>
#include <QSizePolicy>
#include <QTableView>

#include "acrostic.h"
#include "ui/DownMsg.h"
#include "MessageBox.h"
#include "MissingLettersModel.h"
#include "MissingLettersUI.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , mCentralWidget(new QWidget)
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
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("Create a new acrostic"));
  newAction->setEnabled(false);
  connect(newAction, SIGNAL(triggered()), this, SLOT(newAcrostic()));

  openAction = new QAction(tr("&Open…"), this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Open existing acrostic"));
  openAction->setEnabled(false);
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction(tr("&Save"), this);
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Save current acrostic"));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  printAction = new QAction(tr("&Print…"), this);
  printAction->setShortcut(tr("Ctrl+P"));
  printAction->setStatusTip(tr("Print"));
  printAction->setEnabled(false);
  connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

  exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(tr("Ctrl+Q"));
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
  fileMenu->addAction(printAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  auto editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(addClueAction);
  editMenu->addAction(removeClueAction);
}

void MainWindow::createWidgets()
{
  message = new acrostica::MessageBox(this);

  messageLetters = new QGroupBox(tr("Letters Missing from Message"), this);
  messageLettersView = new MissingLettersUI(messageLetters);
  auto missingMessageLetters = new MissingLettersModel(mAcrostic, Clues, messageLettersView);
  messageLettersView->setModel(missingMessageLetters);

  downMessage = new acrostica::ui::downmsg(this);

  acrostica::ClueModel *clues = new acrostica::ClueModel(mAcrostic, this);

  clueBox_ = new QGroupBox(tr("Clues"), this);
  auto clueView = new QTableView(clueBox_);
  auto policy = clueView->sizePolicy();
  policy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
  clueView->setSizePolicy(policy);
  clueView->setSortingEnabled(false);
  clueView->setCornerButtonEnabled(false);
  clueView->setModel(clues);
  clueView->setTabKeyNavigation(false);
  clueView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  QVBoxLayout *clueLayout = new QVBoxLayout(clueBox_);
  clueLayout->addWidget(clueView);

  clueLetters = new QGroupBox(tr("Letters Missing from Clues"), this);
  clueLettersView = new MissingLettersUI(clueLetters);
  auto missingClueLetters = new MissingLettersModel(mAcrostic, Message, clueLettersView);
  clueLettersView->setModel(missingClueLetters);

  connect(addClueAction, &QAction::triggered,
          [=](){ clues->insertRow(clues->rowCount() + 1); });

  connect(message, &acrostica::MessageBox::textChanged,
          [=](const QString& msg){
            mAcrostic->message = msg;
            missingClueLetters->update();
            missingMessageLetters->update();
            setWindowModified(true);
          });

  connect(downMessage, SIGNAL(textEdited(const QString&)),
          clues, SLOT(propagateDownMsg(const QString&)));

  connect(clues, &acrostica::ClueModel::dataChanged,
          [=](){
            missingClueLetters->update();
            missingMessageLetters->update();
            setWindowModified(true);
          });
  connect(clues, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)),
          downMessage, SLOT(mergeMsg(const QModelIndex&, const QModelIndex&, const QVector<int>&)));

  connect(clues, &acrostica::ClueModel::rowsRemoved,
          [=](){ missingMessageLetters->update(); });
  connect(clues, &acrostica::ClueModel::rowsRemoved,
          [=](){ missingClueLetters->update(); });
}

void MainWindow::layoutWidgets()
{
  QVBoxLayout *messageLettersLayout = new QVBoxLayout(messageLetters);
  messageLettersLayout->addWidget(messageLettersView);

  QVBoxLayout *clueLettersLayout = new QVBoxLayout(clueLetters);
  clueLettersLayout->addWidget(clueLettersView);

  QGridLayout *centralLayout = new QGridLayout(mCentralWidget);
  centralLayout->addWidget(message, 0, 0);
  centralLayout->addWidget(messageLetters, 0, 1);
  centralLayout->addWidget(downMessage, 1, 0, 1, 2);
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
}

void MainWindow::open()
{
}

QString MainWindow::filename()
{
  QString filename;
  if (filename_.isEmpty())
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

bool MainWindow::save()
{
  QString fname = filename();

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

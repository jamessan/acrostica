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
#include "ClueWidget.h"
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

  createActions();
  createMenus();
  createWidgets();
  layoutWidgets();
}

MainWindow::~MainWindow()
{
  delete missingMessageLetters;
  delete missingClueLetters;
}

void MainWindow::createActions()
{
  newAction = new QAction(tr("&New"), this);
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("Create a new acrostic"));
  connect(newAction, SIGNAL(triggered()), this, SLOT(newAcrostic()));

  openAction = new QAction(tr("&Open…"), this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Open existing acrostic"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction(tr("&Save"), this);
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Save current acrostic"));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  printAction = new QAction(tr("&Print…"), this);
  printAction->setShortcut(tr("Ctrl+P"));
  printAction->setStatusTip(tr("Print"));
  connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

  exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
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
}

void MainWindow::createWidgets()
{
  message = new acrostica::MessageBox(this);

  messageLetters = new QGroupBox(tr("Letters Missing from Message"), this);
  missingMessageLetters = new MissingLettersModel(mAcrostic, Clues, this);
  messageLettersView = new MissingLettersUI(messageLetters);
  messageLettersView->setModel(missingMessageLetters);

  downMessage = new acrostica::ui::downmsg(this);

  acrostica::ClueModel *clues = new acrostica::ClueModel(mAcrostic, this);

  clueBox_ = new QGroupBox(tr("Clues"), this);
  auto clueView = new QTableView(clueBox_);
  clueView->setSortingEnabled(false);
  clueView->setModel(clues);

  QVBoxLayout *clueLayout = new QVBoxLayout(clueBox_);
  clueLayout->addWidget(clueView);

  clueLetters = new QGroupBox(tr("Letters Missing from Clues"), this);
  missingClueLetters = new MissingLettersModel(mAcrostic, Message, this);
  clueLettersView = new MissingLettersUI(clueLetters);
  clueLettersView->setModel(missingClueLetters);

  connect(message, &acrostica::MessageBox::textChanged,
          [=](const QString& msg){ mAcrostic->message = msg; });
  connect(message, &acrostica::MessageBox::textChanged,
          [=](const QString&){ missingClueLetters->update(); });
  connect(message, &acrostica::MessageBox::textChanged,
          [=](const QString&){ missingMessageLetters->update(); });

  connect(downMessage, SIGNAL(textEdited(const QString&)),
          clues, SLOT(propagateDownMsg(const QString&)));

  connect(clues, &acrostica::ClueModel::dataChanged,
          [=](){ missingMessageLetters->update(); });
  connect(clues, &acrostica::ClueModel::dataChanged,
          [=](){ missingClueLetters->update(); });

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
  event->accept();
}

void MainWindow::newAcrostic()
{
}

void MainWindow::open()
{
}

bool MainWindow::save()
{
  return true;
}

void MainWindow::print()
{
}

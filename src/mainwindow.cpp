/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2014-2015 James McCoy <jamessan@jamessan.com>
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

#include <QPalette>
#include <QRegExp>
#include <QRegExpValidator>
#include <QSizePolicy>

#include "ClueWidget.h"
#include "MissingLettersModel.h"
#include "MissingLettersUI.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  centralWidget = new QWidget;
  setCentralWidget(centralWidget);

  createActions();
  createMenus();
  createWidgets();
  layoutWidgets();

  downText->setFocus();
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
  message = new QGroupBox(tr("Message"));
  messageText = new QPlainTextEdit;
  messageText->setTabChangesFocus(true);

  messageLetters = new QGroupBox(tr("Letters Missing from Message"));
  missingMessageLetters = new MissingLettersModel("message");
  messageLettersView = new MissingLettersUI(messageLetters);
  messageLettersView->setModel(missingMessageLetters);

  downMessage = new QGroupBox(tr("Down Message"));

  downText = new QLineEdit(downMessage);
  QValidator *alpha = new QRegExpValidator(QRegExp("[A-Za-z ]+"));
  downText->setValidator(alpha);

  connect(downText, SIGNAL(editingFinished()),
          this, SLOT(createClues()));

  scroller = new QScrollArea();
  clueBox = new QGroupBox(tr("Clues"), scroller);
  clueBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
  scroller->setWidget(clueBox);
  scroller->setWidgetResizable(true);

  clueLetters = new QGroupBox(tr("Letters Missing from Clues"));
  missingClueLetters = new MissingLettersModel("clue");
  clueLettersView = new MissingLettersUI(clueLetters);
  clueLettersView->setModel(missingClueLetters);

  connect(messageText, SIGNAL(textChanged()),
          missingMessageLetters, SLOT(removeLetters()));
  connect(messageText, SIGNAL(textChanged()),
          missingClueLetters, SLOT(addLetters()));
}

void MainWindow::createClues()
{
  QLineEdit *widget = qobject_cast<QLineEdit*>(sender());
  int n = 0;

  for (auto c : widget->text().toUpper().toLatin1())
  {
    if (::isalpha(c))
    {
      clueList.push_back(new ClueWidget(QString('A' + n), clueBox));
      clueBox->layout()->addWidget(clueList[n]);
      n++;
    }
  }
  widget->setReadOnly(true);
  QPalette newPalette = widget->palette();
  newPalette.setCurrentColorGroup(QPalette::Inactive);
  newPalette.setColor(QPalette::Base, Qt::lightGray);
  newPalette.setColor(QPalette::Text, Qt::black);
  widget->setPalette(newPalette);
  messageText->setFocus();
}

void MainWindow::layoutWidgets()
{
  QVBoxLayout *messageLayout = new QVBoxLayout;
  messageLayout->addWidget(messageText);
  message->setLayout(messageLayout);

  QVBoxLayout *messageLettersLayout = new QVBoxLayout;
  messageLettersLayout->addWidget(messageLettersView);
  messageLetters->setLayout(messageLettersLayout);

  QVBoxLayout *clueLettersLayout = new QVBoxLayout;
  clueLettersLayout->addWidget(clueLettersView);
  clueLetters->setLayout(clueLettersLayout);

  QVBoxLayout *down = new QVBoxLayout;
  down->addWidget(downText);
  downMessage->setLayout(down);

  QVBoxLayout *clueLayout = new QVBoxLayout;
  clueBox->setLayout(clueLayout);

  QGridLayout *centralLayout = new QGridLayout;
  centralLayout->addWidget(message, 0, 0);
  centralLayout->addWidget(messageLetters, 0, 1);
  centralLayout->addWidget(downMessage, 1, 0, 1, 2);
  centralLayout->addWidget(scroller, 2, 0);
  centralLayout->addWidget(clueLetters, 2, 1);
  centralWidget->setLayout(centralLayout);
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

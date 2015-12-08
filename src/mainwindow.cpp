#include <QtWidgets>
#include "mainwindow.h"
#include "MissingLettersModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

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
    connect(messageText, SIGNAL(textChanged()), this, SLOT(messageTextChanged()));

    messageLetters = new QGroupBox(tr("Letters Missing from Message"));
    QStringList llist;
    llist << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I" << "J" << "K"
        << "L" << "M" << "N" << "O" << "P" << "Q" << "R" << "S" << "T" << "U"
        << "V" << "W" << "X" << "Y" << "Z";
    MissingLettersModel *missingMessage = new MissingLettersModel(llist);
    messageLettersView = new QTableView(messageLetters);
    messageLettersView->setModel(missingMessage);
    messageLettersView->setShowGrid(false);
    messageLettersView->horizontalHeader()->setVisible(false);
    messageLettersView->horizontalHeader()->setStretchLastSection(true);
    messageLettersView->verticalHeader()->setVisible(false);

    downMessage = new QGroupBox(tr("Down Message"));

    downText = new QLabel;
    downText->setTextFormat(Qt::PlainText);
    downText->setTextInteractionFlags(Qt::NoTextInteraction);

    clueList = new QGroupBox(tr("Clues"));
    clueLetters = new QGroupBox(tr("Letters Missing from Clues"));
    clueLettersView = new QTableView(clueLetters);
}

void MainWindow::messageTextChanged()
{
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(sender());

}

void MainWindow::layoutWidgets()
{
    QVBoxLayout *messageLayout = new QVBoxLayout;
    messageLayout->addWidget(messageText);
    message->setLayout(messageLayout);

    QVBoxLayout *messageLettersLayout = new QVBoxLayout;
    messageLettersLayout->addWidget(messageLettersView);
    messageLetters->setLayout(messageLettersLayout);

    QGridLayout *centralLayout = new QGridLayout;
    centralLayout->addWidget(message, 0, 0);
    centralLayout->addWidget(messageLetters, 0, 1);
    centralLayout->addWidget(downMessage, 1, 0, 1, 2);
    centralLayout->addWidget(clueList, 2, 0);
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

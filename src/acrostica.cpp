#include <QtWidgets>
#include "acrostica.h"

Acrostica::Acrostica(QWidget *parent) :
    QMainWindow(parent)
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    createActions();
    createMenus();
    createWidgets();
    layoutWidgets();
}

void Acrostica::createActions()
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

void Acrostica::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void Acrostica::createWidgets()
{
    message = new QGroupBox(tr("Message"));

    messageText = new QPlainTextEdit;
    messageText->setTabChangesFocus(true);

    downMessage = new QGroupBox(tr("Down Message"));

    downText = new QLabel;
    downText->setTextFormat(Qt::PlainText);
    downText->setTextInteractionFlags(Qt::NoTextInteraction);

    clues = new QGroupBox(tr("Clues"));

    letters = new QGroupBox(tr("Letters"));
}

void Acrostica::layoutWidgets()
{
    QVBoxLayout *messageLayout = new QVBoxLayout;
    messageLayout->addWidget(messageText);
    message->setLayout(messageLayout);

    QVBoxLayout *downMessageLayout = new QVBoxLayout;
    downMessageLayout->addWidget(downText);
    downMessage->setLayout(downMessageLayout);

    QVBoxLayout *clueLayout = new QVBoxLayout;
    clues->setLayout(clueLayout);

    QVBoxLayout *lettersLayout = new QVBoxLayout;
    letters->setLayout(lettersLayout);

    QVBoxLayout *leftColumn = new QVBoxLayout;
    leftColumn->addWidget(message);
    leftColumn->addWidget(downMessage);
    leftColumn->addWidget(clues);

    QVBoxLayout *rightColumn = new QVBoxLayout;
    rightColumn->addWidget(letters);

    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->addLayout(leftColumn);
    centralLayout->addLayout(rightColumn);

    centralWidget->setLayout(centralLayout);
}

void Acrostica::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void Acrostica::newAcrostic()
{
}

void Acrostica::open()
{
}

bool Acrostica::save()
{
    return true;
}

void Acrostica::print()
{
}

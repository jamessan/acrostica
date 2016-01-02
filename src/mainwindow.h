#ifndef ACROSTICA_MAINWINDOW_H
#define ACROSTICA_MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class ClueWidget;
class MissingLettersModel;
class MissingLettersUI;
class QAction;
class QGroupBox;
class QLineEdit;
class QMenu;
class QPlainTextEdit;
class QScrollArea;
class QWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

protected:
  void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
  void newAcrostic();
  void open();
  bool save();
  void print();

  void createClues();

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

  QGroupBox *downMessage;
  QLineEdit *downText;

  QScrollArea *scroller;
  QGroupBox *clueBox;
  QList<ClueWidget*> clueList;

  QGroupBox *clueLetters;
  MissingLettersUI *clueLettersView;
  MissingLettersModel *missingClueLetters;
};

#endif // ACROSTICA_H

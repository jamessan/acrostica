#ifndef ACROSTICA_MAINWINDOW_H
#define ACROSTICA_MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QGroupBox;
class QLabel;
class QMenu;
class QPlainTextEdit;
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

    QGroupBox *downMessage;
    QLabel *downText;

    QGroupBox *clues;

    QGroupBox *letters;
};

#endif // ACROSTICA_H

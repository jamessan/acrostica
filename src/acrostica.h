#ifndef ACROSTICA_H
#define ACROSTICA_H

#include <QMainWindow>

namespace Ui {
class Acrostica;
}

class Acrostica : public QMainWindow
{
    Q_OBJECT

public:
    explicit Acrostica(QWidget *parent = 0);
    ~Acrostica();

private:
    Ui::Acrostica *ui;
};

#endif // ACROSTICA_H

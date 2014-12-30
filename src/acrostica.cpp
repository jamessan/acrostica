#include "acrostica.h"
#include "ui_acrostica.h"

Acrostica::Acrostica(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Acrostica)
{
    ui->setupUi(this);
}

Acrostica::~Acrostica()
{
    delete ui;
}

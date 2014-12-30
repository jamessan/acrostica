#include "acrostica.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Acrostica w;
    w.show();

    return a.exec();
}

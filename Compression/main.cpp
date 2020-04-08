#include "compression.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    compression w;

    w.show();

    return a.exec();
}

#include "GloSConfig.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GloSConfig w;
    w.show();
    return a.exec();
}

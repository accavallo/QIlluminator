#include "QIlluminator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIlluminator w;
    w.show();
    return a.exec();
}

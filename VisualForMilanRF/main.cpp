#include "VisualForMilanRF.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisualForMilanRF w;
    w.show();
    return a.exec();
}

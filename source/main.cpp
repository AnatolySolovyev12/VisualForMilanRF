#include "VisualForMilanRF.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisualForMilanRF w;
    w.setWindowIcon(QIcon("icon.png"));
    w.setWindowTitle("VisualForMilanRF by Solovev");
    w.show();

    return a.exec();
}

//Ad-Soyad: Sema Nur EKMEKCİ
//Numara: 21100011050

#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}

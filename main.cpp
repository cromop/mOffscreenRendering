#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
//    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(4,3);

    MainWindow w;
    w.show();

    return a.exec();
}

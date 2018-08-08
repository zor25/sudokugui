#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/new/fonts/DejaVuSans.ttf");

    qApp->setFont(QFont(QFontDatabase::applicationFontFamilies(id).at(0)));

//    qDebug() << QFontDatabase::applicationFontFamilies(id).at(0);
    MainWindow w;
    w.show();
    return a.exec();
}

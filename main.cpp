#include "registration.h"
#include <QApplication>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <QFontDatabase>
#include <QDebug>
#include <QScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();
    qreal dpi = screen->logicalDotsPerInch();
    qDebug() << "DPI:" << dpi;
    qDebug() << "Device Pixel Ratio:" << screen->devicePixelRatio();
    qDebug() << "Geometry:" << screen->geometry();

    registration window;
    window.show();
    return a.exec();
}

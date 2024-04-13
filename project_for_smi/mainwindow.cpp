#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QColor>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    // Создаем объект QColor для определения цвета с помощью шестнадцатеричного значения
    QString hexColor = "#222338"; // это шестнадцатеричное представление синего цвета
    QColor backgroundColor(hexColor);

    // Создаем объект QPalette для установки цвета фона
    QPalette palette;
    palette.setColor(QPalette::Background, backgroundColor);

    // Устанавливаем палитру для главного окна
    setPalette(palette);

    // Устанавливаем размеры окна
    setGeometry(400,400,800, 600);

    QPainterPath painPath;
    painPath.addRoundedRect(rect(), 8, 8, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());
}

MainWindow::~MainWindow()
{
    delete ui;
}

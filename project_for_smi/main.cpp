#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <QFontDatabase>
#include <QDebug>

class CloseButton : public QPushButton {
public:
    CloseButton(QWidget *parent = nullptr) : QPushButton(parent) {
        // Устанавливаем размеры и текст кнопки
        setFixedSize(24, 24);


        // Стилизируем кнопку, чтобы сделать ее круглой
        setStyleSheet(
            "QPushButton {"
            "  border-radius: 12px;"  // Радиус равен половине высоты кнопки
            "  background-color: #E11010;"
            "}"
            "QPushButton:hover {"
            "  background-color: #FF0000;"  // Цвет при наведении
            "}"
        );
    }
protected:
    // Переопределяем событие нажатия мыши
    void mousePressEvent(QMouseEvent *event) override {
        // Вызываем метод закрытия окна при нажатии на кнопку
        if (event->button() == Qt::LeftButton) {
            window()->close();
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    CloseButton *closeButton = new CloseButton(&window);
    closeButton->move(window.width() - closeButton->width() - 20, 18);
    window.show();

    return a.exec();
}

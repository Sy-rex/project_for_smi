#include "stream_window.h"
#include "ui_stream_window.h"
#include <QPalette>
#include <QColor>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QFont>
#include <QLabel>

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

Stream_window::Stream_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Stream_window)
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
    painPath.addRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());

    // Создаем объект QFont с установленным шрифтом
    QFont font("Poppins ExtraBold", 20); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label = new QLabel("APPLICATION FOR SMI", this);
    label->setStyleSheet("color: #FFFFFF;");
    label->setFixedSize(370,40);
    label->move(25,90);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label->setFont(font);

    // Добавляем виджет на окно приложения
    label->show();

    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 20, 18);
}

Stream_window::~Stream_window()
{
    delete ui;
}

void Stream_window::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    // Создаем объект QPainter
    QPainter painter(this);

    // Устанавливаем цвет заливки прямоугольника
    painter.setBrush(QColor("#373752"));

    // Рисуем прямоугольник в верхней части окна
    QRect topRect(0, 0, width(), 60);
    painter.drawRect(topRect);

    QFont customFont("Poppins-Bold"); // Укажите имя вашего шрифта
    painter.setFont(customFont);
}

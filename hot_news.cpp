#include "hot_news.h"
#include "ui_hot_news.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
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

hot_news::hot_news(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hot_news)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    // Устанавливаем размеры окна
    setGeometry(600,200,800, 600);

    QPainterPath painPath;
    painPath.addRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());

    // Создаем объект QFont с установленным шрифтом
    QFont font("Poppins SemiBold", 20); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label1 = new QLabel("HOT NEWS", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(230,40);
    label1->move(300,100);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label1->setFont(font);

    // Добавляем виджет на окно приложения
    label1->show();

    // Добавляем кнопку "menu"
    QPushButton *menuButton = new QPushButton("MENU", this);
    menuButton->setStyleSheet(
        "QPushButton {"
        "  color: #FFFFFF;"
        "  border: none;"
        "  background-color: transparent;"  // Прозрачный фон
        "}"
        );

    QFont font2("Poppins SemiBold", 11); // Предполагается, что шрифт Poppins уже установлен
    menuButton->setFont(font2);
    menuButton->setFixedSize(50, 30);
    menuButton->move(24, 18);

    // Соединяем нажатие кнопки "menu" с открытием главного окна
    connect(menuButton, &QPushButton::clicked, this, &hot_news::openMainWindow);

    // Добавляем кнопку закрытия
    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 20, 18);

    QLabel *imageLabel = new QLabel(this);

    QPixmap pixmap(":/text_polygon_right.png");

    // Устанавливаем изображение в QLabel
    imageLabel->setPixmap(pixmap);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel->setFixedSize(pixmap.size());

    // Размещаем QLabel в нужном месте
    imageLabel->move(416, 170);

    // Показываем QLabel на форме
    imageLabel->show();


    QLabel *imageLabel2 = new QLabel(this);

    // Устанавливаем изображение в QLabel
    imageLabel2->setPixmap(pixmap);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel2->setFixedSize(pixmap.size());

    // Размещаем QLabel в нужном месте
    imageLabel2->move(416, 400);

    // Показываем QLabel на форме
    imageLabel2->show();


    QLabel *imageLabel3 = new QLabel(this);

    QPixmap pixmap2(":/text_polygon_left.png");

    // Устанавливаем изображение в QLabel
    imageLabel3->setPixmap(pixmap2);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel3->setFixedSize(pixmap2.size());

    // Размещаем QLabel в нужном месте
    imageLabel3->move(40, 230);

    // Показываем QLabel на форме
    imageLabel3->show();


    QLabel *imageLabel4 = new QLabel(this);

    // Устанавливаем изображение в QLabel
    imageLabel4->setPixmap(pixmap2);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel4->setFixedSize(pixmap2.size());

    // Размещаем QLabel в нужном месте
    imageLabel4->move(40, 460);

    // Показываем QLabel на форме
    imageLabel4->show();


    QLabel *imageLabel5 = new QLabel(this);

    QPixmap pixmap3(":/bottle.png");

    // Устанавливаем изображение в QLabel
    imageLabel5->setPixmap(pixmap3);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel5->setFixedSize(pixmap3.size());

    // Размещаем QLabel в нужном месте
    imageLabel5->move(654, 214);

    // Показываем QLabel на форме
    imageLabel5->show();


    QLabel *imageLabel6 = new QLabel(this);

    QPixmap pixmap4(":/fire.png");

    // Устанавливаем изображение в QLabel
    imageLabel6->setPixmap(pixmap4);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel6->setFixedSize(pixmap4.size());

    // Размещаем QLabel в нужном месте
    imageLabel6->move(-2, 274);

    // Показываем QLabel на форме
    imageLabel6->show();


    QLabel *imageLabel7 = new QLabel(this);

    QPixmap pixmap5(":/gift.png");

    // Устанавливаем изображение в QLabel
    imageLabel7->setPixmap(pixmap5);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel7->setFixedSize(pixmap5.size());

    // Размещаем QLabel в нужном месте
    imageLabel7->move(274, 400);

    // Показываем QLabel на форме
    imageLabel7->show();


    QLabel *imageLabel8 = new QLabel(this);

    QPixmap pixmap6(":/smile.png");

    // Устанавливаем изображение в QLabel
    imageLabel8->setPixmap(pixmap6);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel8->setFixedSize(pixmap6.size());

    // Размещаем QLabel в нужном месте
    imageLabel8->move(644, 460);

    // Показываем QLabel на форме
    imageLabel8->show();
}

hot_news::~hot_news()
{
    delete ui;
}

void hot_news::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setBrush(QColor("#222338"));  // Устанавливаем цвет фона
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    painter.setBrush(QColor("#373752"));
    QRect topRect(0, 0, width(), 60);
    painter.drawRect(topRect);

    QFont customFont("Poppins-Bold");
    painter.setFont(customFont);
}

// Слот для открытия главного окна
void hot_news::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}

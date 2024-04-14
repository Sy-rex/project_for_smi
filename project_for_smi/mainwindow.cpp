#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stream_window.h"
#include <QPalette>
#include <QColor>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QFont>
#include <QLabel>
#include <QPixmap>

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
    painPath.addRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());

    // Создаем объект APPLICATION FOR SMI с установленным шрифтом
    QFont font("Poppins SemiBold", 20); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label1 = new QLabel("APPLICATION FOR SMI", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(370,40);
    label1->move(25,90);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label1->setFont(font);

    // Добавляем виджет на окно приложения
    label1->show();

    QFont font2("Poppins Medium", 10);
    QLabel *label2 = new QLabel("The perfect program for your experience ", this);
    label2->setStyleSheet("color: #FFFFFF;");
    label2->setFixedSize(380,40);
    label2->move(25,116);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label2->setFont(font2);

    // Добавляем виджет на окно приложения
    label2->show();

    QLabel *imageLabel = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap(":/images/Rocket_icon.jpg");

    // Устанавливаем изображение в QLabel
    imageLabel->setPixmap(pixmap);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel->setFixedSize(pixmap.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel->move(10, 150);

    // Показываем QLabel на форме
    imageLabel->show();

    //menu
    QFont font3("Poppins SemiBold", 16); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label3 = new QLabel("MENU", this);
    label3->setStyleSheet("color: #FFFFFF;");
    label3->setFixedSize(80,40);
    label3->move(560,150);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label3->setFont(font3);

    // Добавляем виджет на окно приложения
    label3->show();


    //line menu
    QLabel *imageLabel7 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap7(":/images/line.jpg");

    // Устанавливаем изображение в QLabel
    imageLabel7->setPixmap(pixmap7);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel7->setFixedSize(pixmap7.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel7->move(477, 220);

    // Показываем QLabel на форме
    imageLabel7->show();


    //first_button_menu
    QLabel *imageLabel2 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap2(":/images/first_button_menu.jpg");

    // Устанавливаем изображение в QLabel
    imageLabel2->setPixmap(pixmap2);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel2->setFixedSize(pixmap2.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel2->move(460, 212);

    // Показываем QLabel на форме
    imageLabel2->show();


    //stream_window
    QFont font4("Poppins Medium", 12); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label4 = new QLabel("STREAM WINDOW", this);
    label4->setStyleSheet("color: #FFFFFF;");
    label4->setFixedSize(180,40);
    label4->move(520,212);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label4->setFont(font4);

    // Добавляем виджет на окно приложения
    label4->show();


    //second_button_menu
    QLabel *imageLabel3 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap3(":/images/second_button_menu.jpg");

    // Устанавливаем изображение в QLabel
    imageLabel3->setPixmap(pixmap3);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel3->setFixedSize(pixmap3.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel3->move(460, 272);

    // Показываем QLabel на форме
    imageLabel3->show();


    //author search
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label5 = new QLabel("AUTHOR SEARCH", this);
    label5->setStyleSheet("color: #FFFFFF;");
    label5->setFixedSize(180,40);
    label5->move(520,272);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label5->setFont(font4);

    // Добавляем виджет на окно приложения
    label5->show();


    //third_button_menu
    QLabel *imageLabel4 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap4(":/images/third_button_menu.jpg");

    // Устанавливаем изображение в QLabel
    imageLabel4->setPixmap(pixmap4);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel4->setFixedSize(pixmap4.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel4->move(460, 332);

    // Показываем QLabel на форме
    imageLabel4->show();


    //update data
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label6 = new QLabel("UPDATE DATA", this);
    label6->setStyleSheet("color: #FFFFFF;");
    label6->setFixedSize(180,40);
    label6->move(520,332);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label6->setFont(font4);

    // Добавляем виджет на окно приложения
    label6->show();


    //fourth_button_menu
    QLabel *imageLabel5 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap5(":/images/fourth_button_menu.jpg");

    // Устанавливаем изображение в QLabel
    imageLabel5->setPixmap(pixmap5);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel5->setFixedSize(pixmap5.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel5->move(460, 392);

    // Показываем QLabel на форме
    imageLabel5->show();


    //something
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label7 = new QLabel("SOMETHING", this);
    label7->setStyleSheet("color: #FFFFFF;");
    label7->setFixedSize(180,40);
    label7->move(520,392);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label7->setFont(font4);

    // Добавляем виджет на окно приложения
    label7->show();


    //fifth_button_menu
    QLabel *imageLabel6 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap6(":/images/fifth_button_menu.jpg");

    // Устанавливаем изображение в QLabel
    imageLabel6->setPixmap(pixmap6);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel6->setFixedSize(pixmap6.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel6->move(460, 452);

    // Показываем QLabel на форме
    imageLabel6->show();


    //hot news
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label8 = new QLabel("HOT NEWS", this);
    label8->setStyleSheet("color: #FFFFFF;");
    label8->setFixedSize(180,40);
    label8->move(520,452);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label8->setFont(font4);

    // Добавляем виджет на окно приложения
    label8->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

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



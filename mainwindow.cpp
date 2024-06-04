#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "author_search.h"
#include "update_data.h"
#include "adding_records.h"
#include "deleting_records.h"
#include "updating_records.h"
#include "hot_news.h"
#include <QPalette>
#include <QColor>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QFont>
#include <QLabel>
#include <QPixmap>

class CloseButton : public QPushButton {
public:
    CloseButton(QWidget *parent = nullptr) : QPushButton(parent) {
        // Устанавливаем размеры и текст кнопки
        setFixedSize(18, 18);


        // Стилизируем кнопку, чтобы сделать ее круглой
        setStyleSheet(
            "QPushButton {"
            "  border-radius: 9px;"  // Радиус равен половине высоты кнопки
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);
    // Устанавливаем размеры окна
    setGeometry(600,200,800/1.25, 600/1.25);

    QPainterPath painPath;
    painPath.addRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());

    // Создаем объект APPLICATION FOR SMI с установленным шрифтом
    QFont font("Poppins SemiBold", 20); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label1 = new QLabel("APPLICATION FOR SMI", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(370,40);
    label1->move(20,72);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label1->setFont(font);

    // Добавляем виджет на окно приложения
    label1->show();

    QFont font2("Poppins Medium", 10);
    QLabel *label2 = new QLabel("The perfect program for your experience ", this);
    label2->setStyleSheet("color: #FFFFFF;");
    label2->setFixedSize(380,40);
    label2->move(20,92.8);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label2->setFont(font2);

    // Добавляем виджет на окно приложения
    label2->show();
    QLabel *imageLabel = new QLabel(this);
    // Загружаем изображение из файла ресурсов
    QPixmap pixmap(":/Rocket_icon.jpg");
    pixmap.setDevicePixelRatio(devicePixelRatio());
    imageLabel->setPixmap(pixmap);
    imageLabel->setFixedSize(pixmap.size() / pixmap.devicePixelRatio());
    imageLabel->move(8, 120);
    // Показываем QLabel на форме
    imageLabel->show();

    //menu
    QFont font3("Poppins SemiBold", 16); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label3 = new QLabel("MENU", this);
    label3->setStyleSheet("color: #FFFFFF;");
    label3->setFixedSize(80,40);
    label3->move(448,120);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label3->setFont(font3);

    // Добавляем виджет на окно приложения
    label3->show();


    //line menu
    QLabel *imageLabel7 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap7(":/line.jpg"); 
    pixmap7.setDevicePixelRatio(devicePixelRatio());
    imageLabel7->setPixmap(pixmap7);
    imageLabel7->setFixedSize(pixmap7.size() / pixmap7.devicePixelRatio());
    imageLabel7->move(381, 176);
    // Показываем QLabel на форме
    imageLabel7->show();


    //first_button_menu
    QPushButton *imageButton2 = new QPushButton(this);
    imageButton2->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap2(":/first_button_menu.jpg");
    pixmap2.setDevicePixelRatio(devicePixelRatio());
    // Устанавливаем изображение в QPushButton
    imageButton2->setIcon(QIcon(pixmap2));

    imageButton2->setIconSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton2->setFixedSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton2->move(368, 174);

    // Показываем QPushButton на форме
    imageButton2->show();

    //stream_window
    QFont font4("Poppins Medium", 12); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label4 = new QLabel("STREAM WINDOW", this);
    label4->setStyleSheet("color: #FFFFFF;");
    label4->setFixedSize(180,40);
    label4->move(416,169);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label4->setFont(font4);

    // Добавляем виджет на окно приложения
    label4->show();


    //second_button_menu
    QPushButton *imageButton3 = new QPushButton(this);
    imageButton3->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap3(":/second_button_menu.jpg");
    pixmap3.setDevicePixelRatio(devicePixelRatio());
    // Устанавливаем изображение в QPushButton
    imageButton3->setIcon(QIcon(pixmap3));

    imageButton3->setIconSize(pixmap3.size() / pixmap3.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton3->setFixedSize(pixmap3.size() / pixmap3.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton3->move(368, 222);

    // Показываем QPushButton на форме
    imageButton3->show();

    //author search
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label5 = new QLabel("DELETING RECORDS", this);
    label5->setStyleSheet("color: #FFFFFF;");
    label5->setFixedSize(180,40);
    label5->move(416,217);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label5->setFont(font4);

    // Добавляем виджет на окно приложения
    label5->show();


    //third_button_menu
    QPushButton *imageButton4 = new QPushButton(this);
    imageButton4->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap4(":/third_button_menu.jpg");
    pixmap4.setDevicePixelRatio(devicePixelRatio());

    // Устанавливаем изображение в QPushButton
    imageButton4->setIcon(QIcon(pixmap4));

    imageButton4->setIconSize(pixmap4.size() / pixmap4.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton4->setFixedSize(pixmap4.size() / pixmap4.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton4->move(368, 270);

    // Показываем QPushButton на форме
    imageButton4->show();


    //update data
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label6 = new QLabel("ADDING RECORDS", this);
    label6->setStyleSheet("color: #FFFFFF;");
    label6->setFixedSize(180,40);
    label6->move(416,265);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label6->setFont(font4);

    // Добавляем виджет на окно приложения
    label6->show();


    //fourth_button_menu
    QPushButton *imageButton5 = new QPushButton(this);
    imageButton5->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap5(":/fourth_button_menu.jpg");
    pixmap5.setDevicePixelRatio(devicePixelRatio());

    // Устанавливаем изображение в QPushButton
    imageButton5->setIcon(QIcon(pixmap5));

    imageButton5->setIconSize(pixmap5.size() / pixmap5.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton5->setFixedSize(pixmap5.size() / pixmap5.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton5->move(368, 318);

    // Показываем QPushButton на форме
    imageButton5->show();


    //something
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label7 = new QLabel("UPDATING RECORDS", this);
    label7->setStyleSheet("color: #FFFFFF;");
    label7->setFixedSize(180,40);
    label7->move(416,313);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label7->setFont(font4);

    // Добавляем виджет на окно приложения
    label7->show();


    //fifth_button_menu
    QPushButton *imageButton6 = new QPushButton(this);
    imageButton6->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap6(":/fifth_button_menu.jpg");
    pixmap6.setDevicePixelRatio(devicePixelRatio());
    // Устанавливаем изображение в QPushButton
    imageButton6->setIcon(QIcon(pixmap6));

    imageButton6->setIconSize(pixmap6.size() / pixmap6.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton6->setFixedSize(pixmap6.size() / pixmap6.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton6->move(368, 366);

    // Показываем QPushButton на форме
    imageButton6->show();


    //hot news
    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label8 = new QLabel("HOT NEWS", this);
    label8->setStyleSheet("color: #FFFFFF;");
    label8->setFixedSize(180,40);
    label8->move(416,361);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label8->setFont(font4);

    // Добавляем виджет на окно приложения
    label8->show();

    // Подключаем событие нажатия на кнопку

    connect(imageButton3, &QPushButton::clicked, this, &MainWindow::onSecondButtonClicked);

    connect(imageButton4, &QPushButton::clicked, this, &MainWindow::onThirdButtonClicked);

    connect(imageButton6, &QPushButton::clicked, this, &MainWindow::onFifthButtonClicked);

    connect(imageButton5, &QPushButton::clicked, this, &MainWindow::onFourthButtonClicked);

    // Добавляем кнопку закрытия
    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 16, 16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setBrush(QColor("#222338"));  // Устанавливаем цвет фона
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    painter.setBrush(QColor("#373752"));
    QRect topRect(0, 0, width(), 48);
    painter.drawRect(topRect);

    QFont customFont("Poppins-Bold");
    painter.setFont(customFont);
}


void MainWindow::onSecondButtonClicked()
{
    // Создание и отображение окна Stream_window
    deleting_records *deleting_records2 = new deleting_records();
    deleting_records2->show();
    this->close();
}

void MainWindow::onThirdButtonClicked()
{
    // Создание и отображение окна Stream_window
    adding_records *adding_records2 = new adding_records();
    adding_records2->show();
    this->close();
}

void MainWindow::onFifthButtonClicked()
{
    // Создание и отображение окна Stream_window
    hot_news *hot_news2 = new hot_news();
    hot_news2->show();
    this->close();
}

void MainWindow::onFourthButtonClicked()
{
    // Создание и отображение окна Stream_window
    updating_records *updating_records2 = new updating_records();
    updating_records2->show();
    this->close();
}

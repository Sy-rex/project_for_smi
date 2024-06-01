#include "adding_records.h"
#include "adding_into_journal.h"
#include "adding_into_author.h"
#include "adding_into_edition.h"
#include "adding_into_article.h"
#include "ui_adding_records.h"
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

adding_records::adding_records(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::adding_records)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    // Устанавливаем размеры окна
    setGeometry(600,200,800/1.25, 600/1.25);

    QPainterPath painPath;
    painPath.addRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());

    // Создаем объект QFont с установленным шрифтом
    QFont font("Poppins SemiBold", 20); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label1 = new QLabel("ADDING RECORDS", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(300,40);
    label1->move(200,80);

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
    menuButton->move(16, 12);

    // Соединяем нажатие кнопки "menu" с открытием главного окна
    connect(menuButton, &QPushButton::clicked, this, &adding_records::openMainWindow);

    // Добавляем кнопку закрытия
    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 16, 16);

    QFont font3("Poppins SemiBold", 16);

    QLabel *label2 = new QLabel("SELECTING A TABLE", this);
    label2->setStyleSheet("color: #FFFFFF;");
    label2->setFixedSize(250,40);
    label2->move(216,128);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label2->setFont(font3);

    // Добавляем виджет на окно приложения
    label2->show();


    QPushButton *imageButton2 = new QPushButton(this);
    imageButton2->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap2(":/journal.png");
    pixmap2.setDevicePixelRatio(devicePixelRatio());

    // Устанавливаем изображение в QPushButton
    imageButton2->setIcon(QIcon(pixmap2));

    imageButton2->setIconSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton2->setFixedSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton2->move(40, 176);

    // Показываем QPushButton на форме
    imageButton2->show();


    QPushButton *imageButton3 = new QPushButton(this);
    imageButton3->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap3(":/author.png");
    pixmap3.setDevicePixelRatio(devicePixelRatio());

    // Устанавливаем изображение в QPushButton
    imageButton3->setIcon(QIcon(pixmap3));

    imageButton3->setIconSize(pixmap3.size() / pixmap3.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton3->setFixedSize(pixmap3.size() / pixmap3.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton3->move(240, 176);

    // Показываем QPushButton на форме
    imageButton3->show();

    QPushButton *imageButton4 = new QPushButton(this);
    imageButton4->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap4(":/edition.png");
    pixmap4.setDevicePixelRatio(devicePixelRatio());

    // Устанавливаем изображение в QPushButton
    imageButton4->setIcon(QIcon(pixmap4));

    imageButton4->setIconSize(pixmap4.size() / pixmap4.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton4->setFixedSize(pixmap4.size() / pixmap4.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton4->move(440, 176);

    // Показываем QPushButton на форме
    imageButton4->show();


    QLabel *imageLabel5 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap5(":/description_journal.png");
    pixmap5.setDevicePixelRatio(devicePixelRatio());
    imageLabel5->setPixmap(pixmap5);
    imageLabel5->setFixedSize(pixmap5.size() / pixmap5.devicePixelRatio());
    // Размещаем QLabel в нужном месте
    imageLabel5->move(40, 220);

    imageLabel5->show();

    QLabel *imageLabel6 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap6(":/description_author.png");
    pixmap6.setDevicePixelRatio(devicePixelRatio());
    imageLabel6->setPixmap(pixmap6);
    imageLabel6->setFixedSize(pixmap6.size() / pixmap6.devicePixelRatio());
    // Размещаем QLabel в нужном месте
    imageLabel6->move(240, 220);

    imageLabel6->show();

    QLabel *imageLabel7 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap7(":/description_edition.png");
    pixmap7.setDevicePixelRatio(devicePixelRatio());
    imageLabel7->setPixmap(pixmap7);
    imageLabel7->setFixedSize(pixmap7.size() / pixmap7.devicePixelRatio());
    // Размещаем QLabel в нужном месте
    imageLabel7->move(440, 220);

    imageLabel7->show();

    QPushButton *imageButton8 = new QPushButton(this);
    imageButton8->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap8(":/article.png");
    pixmap8.setDevicePixelRatio(devicePixelRatio());

    // Устанавливаем изображение в QPushButton
    imageButton8->setIcon(QIcon(pixmap8));

    imageButton8->setIconSize(pixmap8.size() / pixmap8.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton8->setFixedSize(pixmap8.size() / pixmap8.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton8->move(140, 324);

    // Показываем QPushButton на форме
    imageButton8->show();


    QLabel *imageLabel9 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap9(":/works.png");
    pixmap9.setDevicePixelRatio(devicePixelRatio());

    // Устанавливаем изображение в QLabel
    imageLabel9->setPixmap(pixmap9);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel9->setFixedSize(pixmap9.size() / pixmap9.devicePixelRatio());

    // Размещаем QLabel в нужном месте
    imageLabel9->move(340, 324);

    imageLabel9->show();

    QLabel *imageLabel10 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap10(":/description_article.png");
    pixmap10.setDevicePixelRatio(devicePixelRatio());
    imageLabel10->setPixmap(pixmap10);
    imageLabel10->setFixedSize(pixmap10.size() / pixmap10.devicePixelRatio());
    // Размещаем QLabel в нужном месте
    imageLabel10->move(140, 368);

    imageLabel10->show();

    QLabel *imageLabel11 = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap11(":/description_works.png");
    pixmap11.setDevicePixelRatio(devicePixelRatio());
    imageLabel11->setPixmap(pixmap11);
    imageLabel11->setFixedSize(pixmap11.size() / pixmap11.devicePixelRatio());
    // Размещаем QLabel в нужном месте
    imageLabel11->move(340, 368);

    imageLabel11->show();

    connect(imageButton2, &QPushButton::clicked, this, &adding_records::onFirstButtonClicked);

    connect(imageButton3, &QPushButton::clicked, this, &adding_records::onSecondButtonClicked);

    connect(imageButton4, &QPushButton::clicked, this, &adding_records::onThirdButtonClicked);

    connect(imageButton8, &QPushButton::clicked, this, &adding_records::onFourthButtonClicked);
}

adding_records::~adding_records()
{
    delete ui;
}

void adding_records::paintEvent(QPaintEvent *event)
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

// Слот для открытия главного окна
void adding_records::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}

void adding_records::onFirstButtonClicked()
{
    // Создание и отображение окна Stream_window
    adding_into_journal *adding_journal = new adding_into_journal();
    adding_journal->show();
    this->close();
}

void adding_records::onSecondButtonClicked()
{
    // Создание и отображение окна Stream_window
    adding_into_author *adding_author = new adding_into_author();
    adding_author->show();
    this->close();
}

void adding_records::onThirdButtonClicked()
{
    // Создание и отображение окна Stream_window
    adding_into_edition *adding_edition = new adding_into_edition();
    adding_edition->show();
    this->close();
}

void adding_records::onFourthButtonClicked()
{
    // Создание и отображение окна Stream_window
    adding_into_article *adding_article = new adding_into_article();
    adding_article->show();
    this->close();
}

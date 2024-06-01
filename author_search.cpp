#include "author_search.h"
#include "ui_author_search.h"
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

author_search::author_search(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::author_search)
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
    QLabel *label1 = new QLabel("AUTHOR SEARCH", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(300,40);
    label1->move(250,100);

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
    connect(menuButton, &QPushButton::clicked, this, &author_search::openMainWindow);

    //canals
    // Создаем виджет для отображения текста (например, QLabel)
    QFont font3("Poppins SemiBold", 16);

    QLabel *label2 = new QLabel("SETTINGS", this);
    label2->setStyleSheet("color: #FFFFFF;");
    label2->setFixedSize(130,40);
    label2->move(594,180);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label2->setFont(font3);

    // Добавляем виджет на окно приложения
    label2->show();

    QLabel *imageLabel = new QLabel(this);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap(":/stream_line.png");

    // Устанавливаем изображение в QLabel
    imageLabel->setPixmap(pixmap);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel->setFixedSize(pixmap.size());

    // Размещаем QLabel в нужном месте
    //imageLabel->move(100, 200);
    imageLabel->move(20, 170);

    // Показываем QLabel на форме
    imageLabel->show();

    // Добавляем кнопку закрытия
    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 20, 18);

    QFont font4("Poppins Medium", 12);

    QLabel *label3 = new QLabel("ИМЯ", this);
    label3->setStyleSheet("color: #FFFFFF;");
    label3->setFixedSize(100, 30);
    label3->move(634, 234);
    label3->setFont(font4);
    label3->installEventFilter(this);


    QLabel *imageLabel2 = new QLabel(this);
    // Загружаем изображение из файла ресурсов
    QPixmap pixmap2(":/list_data.png");

    // Устанавливаем изображение в QLabel
    imageLabel2->setPixmap(pixmap2);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel2->setFixedSize(pixmap2.size());

    // Размещаем QLabel в нужном месте
    imageLabel2->move(560, 270);

    // Показываем QLabel на форме
    imageLabel2->show();


    QLabel *label4 = new QLabel("НАЗВАНИЕ СТАТЬИ", this);
    label4->setStyleSheet("color: #FFFFFF;");
    label4->setFixedSize(180, 30);
    label4->move(572, 320);
    label4->setFont(font4);
    label4->installEventFilter(this);


    QLabel *imageLabel3 = new QLabel(this);

    // Устанавливаем изображение в QLabel
    imageLabel3->setPixmap(pixmap2);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel3->setFixedSize(pixmap2.size());

    // Размещаем QLabel в нужном месте
    imageLabel3->move(560, 356);

    // Показываем QLabel на форме
    imageLabel3->show();


    QLabel *label5 = new QLabel("ДАТА ВЫПУСКА", this);
    label5->setStyleSheet("color: #FFFFFF;");
    label5->setFixedSize(150, 30);
    label5->move(587, 406);
    label5->setFont(font4);
    label5->installEventFilter(this);


    QLabel *imageLabel4 = new QLabel(this);

    // Устанавливаем изображение в QLabel
    imageLabel4->setPixmap(pixmap2);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel4->setFixedSize(pixmap2.size());

    // Размещаем QLabel в нужном месте
    imageLabel4->move(560, 442);

    // Показываем QLabel на форме
    imageLabel4->show();


    QLabel *imageLabel5 = new QLabel(this);
    // Загружаем изображение из файла ресурсов
    QPixmap pixmap3(":/search_button.png");

    // Устанавливаем изображение в QLabel
    imageLabel5->setPixmap(pixmap3);

    // Устанавливаем размер QLabel, равный размеру изображения
    imageLabel5->setFixedSize(pixmap3.size());

    // Размещаем QLabel в нужном месте
    imageLabel5->move(570, 510);

    // Показываем QLabel на форме
    imageLabel5->show();
}

author_search::~author_search()
{
    delete ui;
}

void author_search::paintEvent(QPaintEvent *event)
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
void author_search::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}

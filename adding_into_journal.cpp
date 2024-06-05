#include "adding_into_journal.h"
#include "ui_adding_into_journal.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanger.h"
#include <QPalette>
#include <QColor>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QMenu>
#include <QStandardItemModel>


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

adding_into_journal::adding_into_journal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::adding_into_journal)
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
    QLabel *label1 = new QLabel("ADDING INTO JOURNAL", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(400,40);
    label1->move(176,80);

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
    connect(menuButton, &QPushButton::clicked, this, &adding_into_journal::openMainWindow);

    // Добавляем кнопку закрытия
    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 16, 16);

    QFont font3("Poppins SemiBold", 16);

    QLabel *label2 = new QLabel("SETTINGS", this);
    label2->setStyleSheet("color: #FFFFFF;");
    label2->setFixedSize(250,40);
    label2->move(268,128);

    // Устанавливаем установленный шрифт для виджета, отображающего текст
    label2->setFont(font3);

    // Добавляем виджет на окно приложения
    label2->show();


    QFont font4("Poppins Medium", 12);

    QLabel *label3 = new QLabel("НАЗВАНИЕ", this);
    label3->setStyleSheet("color: #FFFFFF;");
    label3->setFixedSize(100, 30);
    label3->move(80, 184);
    label3->setFont(font4);
    label3->installEventFilter(this);

    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setStyleSheet(
        "QLineEdit {"
        "  border-radius: 10px;"
        "  padding: 5px;"
        "  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #48DCB7, stop:1 #8599F3);"
        "  color: #FFFFFF;"
        "  font-family: 'Poppins';"
        "  selection-background-color: #555575;"
        "  selection-color: #FFFFFF;"
        "}"
        );
    lineEdit->setFixedSize(160, 30);
    lineEdit->move(40, 230);

    QLabel *label4 = new QLabel("ДАТА ОСНОВАНИЯ", this);
    label4->setStyleSheet("color: #FFFFFF;");
    label4->setFixedSize(180, 30);
    label4->move(250, 184);
    label4->setFont(font4);
    label4->installEventFilter(this);

    QLineEdit *lineEdit2 = new QLineEdit(this);
    lineEdit2->setStyleSheet(
        "QLineEdit {"
        "  border-radius: 10px;"
        "  padding: 5px;"
        "  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #48DCB7, stop:1 #8599F3);"
        "  color: #FFFFFF;"
        "  font-family: 'Poppins';"
        "  selection-background-color: #555575;"
        "  selection-color: #FFFFFF;"
        "}"
        );
    lineEdit2->setFixedSize(160, 30);
    lineEdit2->move(238, 230);

    QLabel *label5 = new QLabel("РЕЙТИНГ", this);
    label5->setStyleSheet("color: #FFFFFF;");
    label5->setFixedSize(100, 30);
    label5->move(480, 184);
    label5->setFont(font4);
    label5  ->installEventFilter(this);

    QLineEdit *lineEdit3 = new QLineEdit(this);
    lineEdit3->setStyleSheet(
        "QLineEdit {"
        "  border-radius: 10px;"
        "  padding: 5px;"
        "  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #48DCB7, stop:1 #8599F3);"
        "  color: #FFFFFF;"
        "  font-family: 'Poppins';"
        "  selection-background-color: #555575;"
        "  selection-color: #FFFFFF;"
        "}"
        );
    lineEdit3->setFixedSize(160, 30);
    lineEdit3->move(436, 230);

    QPushButton *imageButton2 = new QPushButton(this);
    imageButton2->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap2(":/add_button.png");
    pixmap2.setDevicePixelRatio(devicePixelRatio());
    // Устанавливаем изображение в QPushButton
    imageButton2->setIcon(QIcon(pixmap2));

    imageButton2->setIconSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton2->setFixedSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton2->move(244, 400);

    connect(imageButton2, &QPushButton::clicked, this, [this, lineEdit, lineEdit2, lineEdit3]() {
        addJournalEntry(lineEdit, lineEdit2, lineEdit3);
    });



    // Показываем QPushButton на форме
    imageButton2->show();

}

adding_into_journal::~adding_into_journal()
{
    delete ui;
}

void adding_into_journal::paintEvent(QPaintEvent *event)
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
void adding_into_journal::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}

void adding_into_journal::addJournalEntry(QLineEdit *lineEdit, QLineEdit *lineEdit2, QLineEdit *lineEdit3) {
    databasemanger& dbManager = databasemanger::instance(false);
    if (!dbManager.openDatabase()) {
        QMessageBox::critical(this, "Database Error", "Unable to open the database.");
        return;
    }

    QString name = lineEdit->text();
    QString yearOfFoundation = lineEdit2->text();
    QString rating = lineEdit3->text();
    // Проверка, что все поля заполнены
    if (name.isEmpty() || yearOfFoundation.isEmpty() || rating.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO journal (name, year_of_foundation, rating) VALUES (:name, :year_of_foundation, :rating)");
    query.bindValue(":name", name);
    query.bindValue(":year_of_foundation", yearOfFoundation);
    query.bindValue(":rating", rating);

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setStyleSheet(
            "QMessageBox {"
            "  background-color: #222338;"
            "  color: #FFFFFF;"
            "}"
            "QMessageBox QLabel {"
            "  color: #FFFFFF;"
            "}"
            "QMessageBox QPushButton {"
            "  background-color: #48DCB7;"
            "  color: #FFFFFF;"
            "  border-radius: 5px;"
            "  padding: 5px 10px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "  background-color: #8599F3;"
            "}"
            );
        msgBox.setText("Запись успешно добавлена.");
        msgBox.exec();

        // Очищаем поля после успешного добавления
        lineEdit->clear();
        lineEdit2->clear();
        lineEdit3->clear();

        // Здесь можно обновить представление таблицы, если необходимо
        // Например, если у вас есть представление таблицы в другом виджете
    } else {
        QMessageBox msgBox;
        msgBox.setStyleSheet(
            "QMessageBox {"
            "  background-color: #222338;"
            "  color: #FFFFFF;"
            "}"
            "QMessageBox QLabel {"
            "  color: #FFFFFF;"
            "}"
            "QMessageBox QPushButton {"
            "  background-color: #E11010;"
            "  color: #FFFFFF;"
            "  border-radius: 5px;"
            "  padding: 5px 10px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "  background-color: #FF0000;"
            "}"
            );
        msgBox.setText("Ошибка при добавлении записи: " + query.lastError().text());
        msgBox.exec();
    }
}

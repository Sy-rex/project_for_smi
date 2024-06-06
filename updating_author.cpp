#include "updating_author.h"
#include "ui_updating_author.h"
#include "updating_into_author.h"
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
#include <QComboBox>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlDatabase>
#include <QValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>


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

updating_author::updating_author(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updating_author)
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
    QLabel *label1 = new QLabel("UPDATING INTO AUTHORS", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(400,40);
    label1->move(150,80);

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
    connect(menuButton, &QPushButton::clicked, this, &updating_author::openMainWindow);

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

    QLabel *label3 = new QLabel("АВТОР", this);
    label3->setStyleSheet("color: #FFFFFF;");
    label3->setFixedSize(100, 30);
    label3->move(92,184);
    label3->setFont(font4);
    label3->installEventFilter(this);

    lineEdit = new QLineEdit(this);
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

    QLabel *label4 = new QLabel("РЕДАКЦИЯ", this);
    label4->setStyleSheet("color: #FFFFFF;");
    label4->setFixedSize(180, 30);
    label4->move(278,184);
    label4->setFont(font4);
    label4->installEventFilter(this);

    comboBox = new QComboBox(this);
    comboBox->setMaxVisibleItems(5);
    comboBox->setStyleSheet(
        "QComboBox {"
        "  border-radius: 10px;"
        "  padding: 5px;"
        "  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #48DCB7, stop:1 #8599F3);"
        "  color: #FFFFFF;"
        "  font-family: 'Poppins';"
        "}"
        "QComboBox QAbstractItemView {"
        "  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #48DCB7, stop:1 #8599F3);"
        "  color: #FFFFFF;"
        "  selection-background-color: #555575;"
        "  selection-color: #FFFFFF;"
        "  border: none;"
        "}"
        "QComboBox::drop-down {"
        "  border: none;"
        "}"
        "QScrollBar:vertical {"
        "  border: none;"
        "  background: transparent;"
        "  width: 10px;"
        "  margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "  background: #F23878;"  // Устанавливаем цвет ползунка на красный
        "  min-height: 20px;"
        "  border-radius: 5px;"
        "}"
        "QComboBox QScrollBar::add-line:vertical,"
        "QComboBox QScrollBar::sub-line:vertical {"
        "  border: none;"
        "  background: none;"
        "}"
        "QComboBox QScrollBar::add-page:vertical,"
        "QComboBox QScrollBar::sub-page:vertical {"
        "  background: none;"
        "}"
        );
    comboBox->setFixedSize(160, 30);
    comboBox->move(238, 230);

    comboBox->setPlaceholderText("Выберите издание");
    comboBox->setFocus();
    loadComboBoxData(comboBox);

    QLabel *label5 = new QLabel("РЕЙТИНГ", this);
    label5->setStyleSheet("color: #FFFFFF;");
    label5->setFixedSize(100, 30);
    label5->move(480, 184);
    label5->setFont(font4);
    label5  ->installEventFilter(this);

    lineEdit2 = new QLineEdit(this);
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
    lineEdit2->move(436, 230);

    QPushButton *imageButton2 = new QPushButton(this);
    imageButton2->setFlat(true);

    // Загружаем изображение из файла ресурсов
    QPixmap pixmap2(":/update_button.png");
    pixmap2.setDevicePixelRatio(devicePixelRatio());
    // Устанавливаем изображение в QPushButton
    imageButton2->setIcon(QIcon(pixmap2));

    imageButton2->setIconSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Устанавливаем размер QPushButton, равный размеру изображения
    imageButton2->setFixedSize(pixmap2.size() / pixmap2.devicePixelRatio());

    // Размещаем QPushButton в нужном месте
    imageButton2->move(244, 400);


    connect(imageButton2, &QPushButton::clicked, this, [this]() {
        updateAuthorEntry(Idauthor, comboBox, lineEdit, lineEdit2);
    });

    // Показываем QPushButton на форме
    imageButton2->show();

}

updating_author::~updating_author()
{
    delete ui;
}

void updating_author::paintEvent(QPaintEvent *event)
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
void updating_author::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}



void updating_author::loadComboBoxData(QComboBox *comboBox) {
    databasemanger& dbManager = databasemanger::instance(false);
    if (dbManager.openDatabase()) {
        QSqlQuery query(dbManager.database());
        query.prepare("SELECT id, name FROM edition ORDER BY name;");

        if (!query.exec()) {
            qDebug() << "SQL Query:" << query.lastQuery();
            qDebug() << "Error:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка базы данных", "Не удалось выполнить запрос: " + query.lastError().text());
            return;
        }
        comboBox->clear();

        while (query.next()) {
            int edition_id = query.value(0).toInt();
            QString name_edition = query.value(1).toString();
            comboBox->addItem(name_edition, edition_id);
        }
        comboBox->setCurrentIndex(-1); // Устанавливаем пустое значение по умолчанию

    } else {
        qDebug() << "Failed to open database";
    }
}

void updating_author::updateAuthorEntry(int Idauthor, QComboBox *comboBox, QLineEdit *lineEdit, QLineEdit *lineEdit2) {
    // Получаем значения из полей ввода
    QString editionName = comboBox->currentText();
    QString authorName = lineEdit->text();
    QString rating = lineEdit2->text();

    // Проверяем, что все поля заполнены
    if (editionName.isEmpty() || authorName.isEmpty() || rating.isEmpty()) {
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
        msgBox.setText("Пожалуйста, заполните все поля.");
        msgBox.exec();
        return;
    }

    QRegularExpression regex("[а-яА-Яa-zA-Z0-9- ]+");
    QRegularExpressionValidator validator(regex, nullptr);
    int pos = 0;
    if (validator.validate(authorName, pos) != QValidator::Acceptable) {
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
        msgBox.setText("поле Автор может содержать только буквы русского и английского алфавита, цифры, пробелы и знак тире.");
        msgBox.exec();
        return;
    }

    QRegularExpression ratingRegex("^([0-9]|10)(\\.[0-9])?$");
    if (!ratingRegex.match(rating).hasMatch()) {
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
        msgBox.setText("Рейтинг должен быть числом от 0 до 10.");
        msgBox.exec();
        return;
    }

    // Открываем базу данных
    databasemanger& dbManager = databasemanger::instance(false);
    if (!dbManager.openDatabase()) {
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
        msgBox.setText("Не удалось подключиться к базе данных.");
        msgBox.exec();
        return;
    }

    // Получаем ID издания по его названию
    QSqlQuery query(dbManager.database());
    query.prepare("SELECT id FROM edition WHERE name = :name");
    query.bindValue(":name", editionName);
    if (!query.exec() || !query.next()) {
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
        msgBox.setText("Не удалось найти издание с указанным названием.");
        msgBox.exec();
        return;
    }
    int editionId = query.value(0).toInt();

    // Обновляем данные в таблице authors
    query.prepare("UPDATE authors SET edition_id = :edition_id, fullname = :name, rating = :rating WHERE id = :id");
    query.bindValue(":edition_id", editionId);
    query.bindValue(":name", authorName);
    query.bindValue(":rating", rating);
    query.bindValue(":id", Idauthor);

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
        msgBox.setText("Автор успешно обновлен.");
        msgBox.exec();

        // Очищаем поля после успешного обновления
        comboBox->setCurrentIndex(-1);
        lineEdit->clear();
        lineEdit2->clear();
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
        msgBox.setText("Ошибка при обновлении автора: " + query.lastError().text());
        msgBox.exec();
    }
}


void updating_author::setFields(const int id_author, const QString &author, const QString &edition, const QString &rating)
{
    Idauthor = id_author;
    comboBox->setCurrentText(edition);
    lineEdit->setText(author);
    lineEdit2->setText(rating);;
}
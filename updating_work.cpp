#include "updating_work.h"
#include "ui_updating_work.h"
#include "updating_into_work.h"
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
#include <QComboBox>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlDatabase>


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

updating_work::updating_work(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updating_work)
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
    QLabel *label1 = new QLabel("ADDING INTO WORK", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(400,40);
    label1->move(190,80);

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
    connect(menuButton, &QPushButton::clicked, this, &updating_work::openMainWindow);

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

    QLabel *label3 = new QLabel("СТАТЬЯ", this);
    label3->setStyleSheet("color: #FFFFFF;");
    label3->setFixedSize(100, 30);
    label3->move(150, 184);
    label3->setFont(font4);
    label3->installEventFilter(this);

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
    comboBox->move(102, 230);
    comboBox->setFocus();
    loadComboBoxData(comboBox);

    QLabel *label4 = new QLabel("АВТОР", this);
    label4->setStyleSheet("color: #FFFFFF;");
    label4->setFixedSize(100, 30);
    label4->move(420, 184);
    label4->setFont(font4);
    label4->installEventFilter(this);

    comboBox2 = new QComboBox(this);
    comboBox2->setMaxVisibleItems(5);
    comboBox2->setStyleSheet(
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
    comboBox2->setFixedSize(160, 30);
    comboBox2->move(366, 230);
    comboBox2->setFocus();
    loadComboBoxData2(comboBox2);

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
        updateWorkEntry(comboBox, comboBox2);
    });

    // Показываем QPushButton на форме
    imageButton2->show();

}

updating_work::~updating_work()
{
    delete ui;
}

void updating_work::paintEvent(QPaintEvent *event)
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
void updating_work::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}

void updating_work::loadComboBoxData(QComboBox *comboBox) {
    databasemanger& dbManager = databasemanger::instance(false);
    if (dbManager.openDatabase()) {
        QSqlQuery query(dbManager.database());
        query.prepare("SELECT id, name FROM article ORDER BY name;");

        if (!query.exec()) {
            qDebug() << "SQL Query:" << query.lastQuery();
            qDebug() << "Error:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка базы данных", "Не удалось выполнить запрос: " + query.lastError().text());
            return;
        }
        comboBox->clear();

        while (query.next()) {
            int journal_id = query.value(0).toInt();
            QString name_journal = query.value(1).toString();
            comboBox->addItem(name_journal, journal_id);
        }
        comboBox->setCurrentIndex(-1); // Устанавливаем пустое значение по умолчанию

    } else {
        qDebug() << "Failed to open database";
    }
}

void updating_work::loadComboBoxData2(QComboBox *comboBox2) {
    databasemanger& dbManager = databasemanger::instance(false);
    if (dbManager.openDatabase()) {
        QSqlQuery query(dbManager.database());
        query.prepare("SELECT id, fullname FROM authors ORDER BY fullname;");

        if (!query.exec()) {
            qDebug() << "SQL Query:" << query.lastQuery();
            qDebug() << "Error:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка базы данных", "Не удалось выполнить запрос: " + query.lastError().text());
            return;
        }
        comboBox2->clear();

        while (query.next()) {
            int journal_id = query.value(0).toInt();
            QString name_journal = query.value(1).toString();
            comboBox2->addItem(name_journal, journal_id);
        }
        comboBox2->setCurrentIndex(-1); // Устанавливаем пустое значение по умолчанию

    } else {
        qDebug() << "Failed to open database";
    }
}

void updating_work::updateWorkEntry(QComboBox *comboBox, QComboBox *comboBox2) {
    // Получаем значения из comboboxes
    QString articleTitle = comboBox->currentText();
    QString authorName = comboBox2->currentText();

    // Проверяем, что все поля заполнены
    if (articleTitle.isEmpty() || authorName.isEmpty()) {
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

    // Получаем ID статьи по ее названию
    QSqlQuery queryArticle(dbManager.database());
    queryArticle.prepare("SELECT id FROM article WHERE name = :title");
    queryArticle.bindValue(":title", articleTitle);
    if (!queryArticle.exec() || !queryArticle.next()) {
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
        msgBox.setText("Не удалось найти статью с указанным названием.");
        msgBox.exec();
        return;
    }
    int articleId = queryArticle.value(0).toInt();

    // Получаем ID автора по его имени
    QSqlQuery queryAuthor(dbManager.database());
    queryAuthor.prepare("SELECT id FROM authors WHERE fullname = :name");
    queryAuthor.bindValue(":name", authorName);
    if (!queryAuthor.exec() || !queryAuthor.next()) {
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
        msgBox.setText("Не удалось найти автора с указанным именем.");
        msgBox.exec();
        return;
    }
    int authorId = queryAuthor.value(0).toInt();

    // Получаем ID записи в таблице article_authors по названию статьи и имени автора
    QSqlQuery queryGetOldId(dbManager.database());
    queryGetOldId.prepare("SELECT id FROM article_authors WHERE article_id = (SELECT id FROM article WHERE name = :title) AND author_id = (SELECT id FROM authors WHERE fullname = :name)");
    queryGetOldId.bindValue(":title", articleTitle);
    queryGetOldId.bindValue(":name", authorName);
    if (!queryGetOldId.exec() || !queryGetOldId.next()) {
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
        msgBox.setText("Не удалось найти старую запись в таблице.");
        msgBox.exec();
        return;
    }
    int oldId = queryGetOldId.value(0).toInt();

    // Обновляем данные в таблице article_authors
    QSqlQuery queryUpdate(dbManager.database());
    queryUpdate.prepare("UPDATE article_authors SET article_id = :article_id, author_id = :author_id WHERE id = :id");
    queryUpdate.bindValue(":article_id", articleId);
    queryUpdate.bindValue(":author_id", authorId);
    queryUpdate.bindValue(":id", oldId);

    if (queryUpdate.exec()) {
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
        msgBox.setText("Запись успешно обновлена.");
        msgBox.exec();

        // Очищаем поля после успешного обновления
        comboBox->setCurrentIndex(-1);
        comboBox2->setCurrentIndex(-1);
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
        msgBox.setText("Ошибка при обновлении записи: " + queryUpdate.lastError().text());
        msgBox.exec();
    }
}



void updating_work::setFields(const QString &article, const QString &author)
{
    comboBox->setCurrentText(article);
    comboBox2->setCurrentText(author);
}

#include "deleting_into_work.h"
#include "ui_deleting_into_work.h"
#include "databasemanger.h"
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
#include <QLineEdit>
#include <QComboBox>
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

deleting_into_work::deleting_into_work(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::deleting_into_work)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    // Устанавливаем размеры окна
    setGeometry(600,200,800/1.25, 600/1.25);

    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(customMenuRequested(QPoint)));

    QPainterPath painPath;
    painPath.addRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());

    // Создаем объект QFont с установленным шрифтом
    QFont font("Poppins SemiBold", 20); // Предполагается, что шрифт Poppins уже установлен

    // Создаем виджет для отображения текста (например, QLabel)
    QLabel *label1 = new QLabel("DELETING FROM WORKS", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(400,40);
    label1->move(164,80);

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
    connect(menuButton, &QPushButton::clicked, this, &deleting_into_work::openMainWindow);

    // Добавляем кнопку закрытия
    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 16, 16);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Получаем экземпляр databasemanger и открываем базу данных
    databasemanger& dbManager = databasemanger::instance(false);
    if (dbManager.openDatabase())
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        QSqlQuery query(dbManager.database());
        query.prepare(
                "SELECT article_authors.article_id, article_authors.author_id, article.name AS \"Статья\", authors.fullname AS \"Автор\" "
                "FROM article_authors "
                "LEFT JOIN article ON article_authors.article_id = article.id "
                "LEFT JOIN authors ON article_authors.author_id = authors.id"
            );
        query.exec();
        model->setQuery(query);

        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->hideColumn(0);
        ui->tableView->hideColumn(1);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        ui->tableView->horizontalHeader()->setStretchLastSection(true);

        int columnCount = ui->tableView->horizontalHeader()->count();
        int tableWidth = ui->tableView->viewport()->width();
        int columnWidth = tableWidth / columnCount;
        for (int i = 0; i < columnCount; ++i) {
            ui->tableView->setColumnWidth(i, columnWidth);
        }
    }
    else
    {
        qDebug() << "Failed to open database";
    }
}

deleting_into_work::~deleting_into_work()
{
    delete ui;
}

void deleting_into_work::paintEvent(QPaintEvent *event)
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
void deleting_into_work::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}

void deleting_into_work::deleteRecord(QModelIndex index) {
    if (!index.isValid()) return;

    QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tableView->model());
    if (!model) return;

    int row = index.row();
    QVariant articleId = model->data(model->index(row, 0));
    QVariant authorId = model->data(model->index(row, 1));

    qDebug() << "Attempting to delete record with article_id:" << articleId << "and author_id:" << authorId;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Удаление записи");
    msgBox.setText("Вы уверены, что хотите удалить эту запись?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: #222338;"
        "    color: #FFFFFF;"
        "}"
        "QMessageBox QLabel {"
        "    color: #FFFFFF;"
        "    font: 14px 'Poppins SemiBold';"
        "}"
        "QMessageBox QPushButton {"
        "    background-color: #373752;"
        "    color: #FFFFFF;"
        "    font: 12px 'Poppins SemiBold';"
        "    padding: 5px 10px;"
        "    border-radius: 5px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "    background-color: #4E4E6D;"
        "}"
        );

    if (msgBox.exec() == QMessageBox::Yes) {
        QSqlQuery query;

        // Удаление записи из article_authors
        query.prepare("DELETE FROM article_authors WHERE article_id = :article_id AND author_id = :author_id");
        query.bindValue(":article_id", articleId);
        query.bindValue(":author_id", authorId);
        if (query.exec()) {
            QMessageBox successBox;
            successBox.setWindowTitle("Успех");
            successBox.setText("Запись успешно удалена.");
            successBox.setStyleSheet(
                "QMessageBox {"
                "    background-color: #222338;"
                "    color: #FFFFFF;"
                "}"
                "QMessageBox QLabel {"
                "    color: #FFFFFF;"
                "    font: 14px 'Poppins SemiBold';"
                "}"
                "QMessageBox QPushButton {"
                "    background-color: #373752;"
                "    color: #FFFFFF;"
                "    font: 12px 'Poppins SemiBold';"
                "    padding: 5px 10px;"
                "    border-radius: 5px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "    background-color: #4E4E6D;"
                "}"
                );
            successBox.exec();

            // Обновляем модель с JOIN
            QSqlQuery refreshQuery(databasemanger::instance(false).database());
            refreshQuery.prepare(
                "SELECT article_authors.article_id, article_authors.author_id, article.name AS \"Статья\", authors.fullname AS \"Автор\" "
                "FROM article_authors "
                "LEFT JOIN article ON article_authors.article_id = article.id "
                "LEFT JOIN authors ON article_authors.author_id = authors.id"
                );
            refreshQuery.exec();
            model->setQuery(refreshQuery);
        } else {
            qDebug() << "Error deleting from article_authors:" << query.lastError();
            showErrorMessageBox("Не удалось удалить запись из таблицы article_authors.");
        }
    }
}

void deleting_into_work::showErrorMessageBox(const QString &message) {
    QMessageBox errorBox;
    errorBox.setWindowTitle("Ошибка");
    errorBox.setText(message);
    errorBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: #222338;"
        "    color: #FFFFFF;"
        "}"
        "QMessageBox QLabel {"
        "    color: #FFFFFF;"
        "    font: 14px 'Poppins SemiBold';"
        "}"
        "QMessageBox QPushButton {"
        "    background-color: #373752;"
        "    color: #FFFFFF;"
        "    font: 12px 'Poppins SemiBold';"
        "    padding: 5px 10px;"
        "    border-radius: 5px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "    background-color: #4E4E6D;"
        "}"
        );
    errorBox.exec();
}

void deleting_into_work::customMenuRequested(QPoint pos) {
    QModelIndex index = ui->tableView->indexAt(pos);
    if (!index.isValid())
        return;

    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(
        "QMenu {"
        "    border: 2px solid #373752; /* Фиолетовая рамка */"
        "    background-color: #FFFFFF; /* Белый фон */"
        "    color: #000000; /* Чёрный текст */"
        "}"
        "QMenu::item:selected {"
        "    background-color: #373752; /* Фиолетовый фон при наведении */"
        "    color: #FFFFFF; /* Белый текст */"
        "}"
        );
    menu->addAction(new QAction("Удалить", this));
    connect(menu->actions()[0], &QAction::triggered, [this, index]() { deleteRecord(index); });
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

#include "updating_into_author.h"
#include "ui_updating_into_author.h"
#include "updating_author.h"
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

updating_into_author::updating_into_author(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updating_into_author)
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
    QLabel *label1 = new QLabel("UPDATING INTO AUTHOR", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(400,40);
    label1->move(155,80);

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
    connect(menuButton, &QPushButton::clicked, this, &updating_into_author::openMainWindow);

    // Добавляем кнопку закрытия
    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 16, 16);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    // Получаем экземпляр databasemanger и открываем базу данных
    databasemanger& dbManager = databasemanger::instance(false);
    if (dbManager.openDatabase())
    {
        // Создаем модель для отображения данных
        QSqlQueryModel *model = new QSqlQueryModel(this);

        // Выполняем запрос для получения данных из article с именем журнала
        model->setQuery("SELECT authors.id, authors.fullname AS \"Автор\", edition.name AS \"Издание\", authors.rating AS \"Рейтинг\" "
                        "FROM authors "
                        "LEFT JOIN edition ON authors.edition_id = edition.id");

        // Устанавливаем режим растягивания столбцов
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // Устанавливаем модель в tableView
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Скрываем столбец id
        ui->tableView->hideColumn(0);

        // Устанавливаем режим растягивания столбцов
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        ui->tableView->horizontalHeader()->setStretchLastSection(true);


        // Устанавливаем равномерное начальное распределение ширины столбцов
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

updating_into_author::~updating_into_author()
{
    delete ui;
}

void updating_into_author::paintEvent(QPaintEvent *event)
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
void updating_into_author::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}
void updating_into_author::updateRecord(QModelIndex index) {
    if (!index.isValid())
        return;

    int id_author = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    QString author = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
    QString edition = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toString();
    QString rating = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 3)).toString();

    updating_author *authorWindow = new updating_author();
    authorWindow->setFields(id_author, author, edition, rating);
    authorWindow->show();

    this->close();
}

void updating_into_author::showErrorMessageBox(const QString &message) {
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

void updating_into_author::customMenuRequested(QPoint pos) {
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
    menu->addAction(new QAction("Изменить", this));
    connect(menu->actions()[0], &QAction::triggered, [this, index]() { updateRecord(index); });
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

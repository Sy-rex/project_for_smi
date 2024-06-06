#include "updating_into_edition.h"
#include "ui_updating_into_edition.h"
#include "updating_edition.h"
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

updating_into_edition::updating_into_edition(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updating_into_edition)
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
    QLabel *label1 = new QLabel("UPDATING INTO EDITION", this);
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
    connect(menuButton, &QPushButton::clicked, this, &updating_into_edition::openMainWindow);

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
        QSqlQuery query(dbManager.database());
        query.prepare("SELECT id, name AS \"Название\", main_editor AS \"Редактор\", year_of_creation AS \"Дата основания\", rating AS \"Рейтинг\" FROM edition");
        query.exec();
        model->setQuery(query);

        // Устанавливаем режим растягивания столбцов
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // Устанавливаем модель в tableView
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Скрываем столбец tariff_id
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

updating_into_edition::~updating_into_edition()
{
    delete ui;
}

void updating_into_edition::paintEvent(QPaintEvent *event)
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
void updating_into_edition::openMainWindow()
{
    // Создаем объект главного окна
    MainWindow *mainWindow = new MainWindow;
    // Показываем главное окно
    mainWindow->show();

    this->close();
}


void updating_into_edition::updateRecord(QModelIndex index) {
    if (!index.isValid())
        return;

    int id_edition = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
    QString yearOfFoundation = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 3)).toString();
    QString rating = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 4)).toString();
    QString editor = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toString();

    updating_edition *editionWindow = new updating_edition();
    editionWindow->setFields(id_edition, name, yearOfFoundation, rating, editor);
    editionWindow->show();

    this->close();
}



void updating_into_edition::customMenuRequested(QPoint pos) {
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

#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanger.h"
#include <QPalette>
#include <QColor>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QPixmap>
#include <QPainterPath>


ToggleLabel::ToggleLabel(QWidget *parent)
    : QLabel(parent), toggled(false) {
    move(254, 401);
}

void ToggleLabel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (toggled) {
            move(254, 401);
        } else {
            move(368, 401);
        }
        toggled = !toggled;
        emit toggledChanged(toggled);
    }
}

class CloseButton : public QPushButton {
public:
    CloseButton(QWidget *parent = nullptr) : QPushButton(parent) {
        setFixedSize(18, 18);
        setStyleSheet(
            "QPushButton {"
            "  border-radius: 9px;"
            "  background-color: #E11010;"
            "}"
            "QPushButton:hover {"
            "  background-color: #FF0000;"
            "}"
            );
    }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            window()->close();
        }
    }
};

registration::registration(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registration)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);
    setGeometry(600, 200, 800/1.25, 600/1.25);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
    this->setMask(path.toFillPolygon().toPolygon());

    QFont font("Poppins SemiBold", 20);

    QLabel *label1 = new QLabel("CHOOSING ROLE", this);
    label1->setStyleSheet("color: #FFFFFF;");
    label1->setFixedSize(270, 40);
    label1->move(216, 80);
    label1->setFont(font);
    label1->show();

    QPushButton *menuButton = new QPushButton("APPLY", this);
    menuButton->setStyleSheet(
        "QPushButton {"
        "  color: #FFFFFF;"
        "  border: none;"
        "  background-color: transparent;"
        "}"
        );
    QFont font2("Poppins SemiBold", 11);
    menuButton->setFont(font2);
    menuButton->setFixedSize(60, 30);
    menuButton->move(16, 12);
    connect(menuButton, &QPushButton::clicked, this, [=]() {openMainWindow(m_toggled);});



    CloseButton *closeButton = new CloseButton(this);
    closeButton->move(width() - closeButton->width() - 16, 16);

    QLabel *imageLabel3 = new QLabel(this);
    QPixmap pixmap3(":/register_line.png");
    pixmap3.setDevicePixelRatio(devicePixelRatio());
    imageLabel3->setPixmap(pixmap3);
    imageLabel3->setFixedSize(pixmap3.size() / pixmap3.devicePixelRatio());
    imageLabel3->move(96, 272);
    imageLabel3->show();

    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":/editor.png");
    pixmap.setDevicePixelRatio(devicePixelRatio());
    imageLabel->setPixmap(pixmap);
    imageLabel->setFixedSize(pixmap.size() / pixmap.devicePixelRatio());
    imageLabel->move(80, 136);
    imageLabel->show();

    QLabel *imageLabel2 = new QLabel(this);
    QPixmap pixmap2(":/reader.png");
    pixmap2.setDevicePixelRatio(devicePixelRatio());
    imageLabel2->setPixmap(pixmap2);
    imageLabel2->setFixedSize(pixmap2.size() / pixmap2.devicePixelRatio());
    imageLabel2->move(368, 136);
    imageLabel2->show();

    // Используем новый класс ToggleLabel для imageLabel4
    ToggleLabel *imageLabel4 = new ToggleLabel(this);
    connect(imageLabel4, &ToggleLabel::toggledChanged, this, &registration::onToggleLabelToggled);

    QPixmap pixmap4(":/register_pill.png");
    pixmap4.setDevicePixelRatio(devicePixelRatio());
    imageLabel4->setPixmap(pixmap4);
    imageLabel4->setFixedSize(pixmap4.size() / pixmap4.devicePixelRatio());
    imageLabel4->show();
}

registration::~registration() {
    delete ui;
}

void registration::paintEvent(QPaintEvent *event) {
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

void registration::openMainWindow(bool m_toggled) {
    databasemanger::instance(m_toggled).setToggled(m_toggled);
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
    this->close();
}
void registration::onToggleLabelToggled(bool toggled) {
    m_toggled = toggled;
}

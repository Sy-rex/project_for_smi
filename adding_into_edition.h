#ifndef ADDING_INTO_EDITION_H
#define ADDING_INTO_EDITION_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QLineEdit>

namespace Ui {
class adding_into_edition;
}

class adding_into_edition : public QWidget
{
    Q_OBJECT

public:
    explicit adding_into_edition(QWidget *parent = nullptr);
    ~adding_into_edition();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        // Запомнить начальную позицию при нажатии на кнопку мыши
        if (event->button() == Qt::LeftButton) {
            m_dragging = true;
            m_dragPosition = (event->globalPosition() - frameGeometry().topLeft()).toPoint();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        // Перемещать окно при зажатой левой кнопке мыши
        if (event->buttons() & Qt::LeftButton && m_dragging) {
            move((event->globalPosition() - m_dragPosition).toPoint());
            event->accept();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        // Остановить перемещение окна при отпускании кнопки мыши
        if (event->button() == Qt::LeftButton) {
            m_dragging = false;
            event->accept();
        }
    }

    void paintEvent(QPaintEvent *event) override;

private slots:
    void openMainWindow();
    void addEditionEntry(QLineEdit *lineEdit, QLineEdit *lineEdit2, QLineEdit *lineEdit3, QLineEdit *lineEdit4);

private:
    Ui::adding_into_edition *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;
    QLineEdit *lineEdit4;
};

#endif // ADDING_INTO_EDITION_H

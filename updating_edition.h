#ifndef updating_edition_H
#define updating_edition_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QLineEdit>
#include "databasemanger.h"

namespace Ui {
class updating_edition;
}

class updating_edition : public QWidget
{
    Q_OBJECT

public:
    explicit updating_edition(QWidget *parent = nullptr);
    ~updating_edition();

    void setFields(const int id_edition, const QString &name, const QString &yearOfFoundation, const QString &rating, const QString &editor);

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
    void updateEditionEntry(int edition,QLineEdit *lineEdit, QLineEdit *lineEdit2, QLineEdit *lineEdit3, QLineEdit *lineEdit4);

private:
    Ui::updating_edition *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;
    QLineEdit *lineEdit4;
    int edition;
};

#endif // updating_edition_H

#ifndef updating_into_work_H
#define updating_into_work_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include "updating_work.h"

namespace Ui {
class updating_into_work;
}

class updating_into_work : public QWidget
{
    Q_OBJECT

public:
    explicit updating_into_work(QWidget *parent = nullptr);
    ~updating_into_work();

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

public slots:
    void customMenuRequested(QPoint pos);
    void updateRecord(QModelIndex index);
    void showErrorMessageBox(const QString &message);

private:
    Ui::updating_into_work *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    updating_work *workWindow;
};

#endif // updating_into_work_H

#ifndef deleting_records_H
#define deleting_records_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

namespace Ui {
class deleting_records;
}

class deleting_records : public QWidget
{
    Q_OBJECT

public:
    explicit deleting_records(QWidget *parent = nullptr);
    ~deleting_records();

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
    void onFirstButtonClicked();
    void onSecondButtonClicked();
    void onThirdButtonClicked();
    void onFourthButtonClicked();
    void onFifthButtonClicked();

private:
    Ui::deleting_records *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
};

#endif // deleting_records_H

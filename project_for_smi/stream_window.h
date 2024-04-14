#ifndef STREAM_WINDOW_H
#define STREAM_WINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

namespace Ui {
class Stream_window;
}

class Stream_window : public QWidget
{
    Q_OBJECT

public:
    explicit Stream_window(QWidget *parent = nullptr);
    ~Stream_window();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        // Запомнить начальную позицию при нажатии на кнопку мыши
        if (event->button() == Qt::LeftButton) {
            m_dragging = true;
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        // Перемещать окно при зажатой левой кнопке мыши
        if (event->buttons() & Qt::LeftButton && m_dragging) {
            move(event->globalPos() - m_dragPosition);
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

private:
    Ui::Stream_window *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
};

#endif // STREAM_WINDOW_H

#ifndef AUTHOR_SEARCH_H
#define AUTHOR_SEARCH_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

namespace Ui {
class author_search;
}

class author_search : public QWidget
{
    Q_OBJECT

public:
    explicit author_search(QWidget *parent = nullptr);
    ~author_search();

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

private:
    Ui::author_search *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

};

#endif // AUTHOR_SEARCH_H

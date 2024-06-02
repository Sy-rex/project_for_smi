#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QLabel>

class ToggleLabel : public QLabel {
    Q_OBJECT

public:
    ToggleLabel(QWidget *parent = nullptr);

signals:
    void toggledChanged(bool toggled);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool toggled;
};

namespace Ui {
class registration;
}

class registration : public QWidget
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration();

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
    void openMainWindow(bool m_toggled);
    void onToggleLabelToggled(bool toggled);

private:
    Ui::registration *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    bool m_toggled = false;
};

#endif // REGISTRATION_H

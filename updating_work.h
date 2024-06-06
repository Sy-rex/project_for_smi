#ifndef updating_work_H
#define updating_work_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QComboBox>

namespace Ui {
class updating_work;
}

class updating_work : public QWidget
{
    Q_OBJECT

public:
    explicit updating_work(QWidget *parent = nullptr);
    ~updating_work();

    void setFields(const QString &article, const QString &author);

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
    void loadComboBoxData(QComboBox *comboBox);
    void loadComboBoxData2(QComboBox *comboBox2);
    void updateWorkEntry(QComboBox *comboBox, QComboBox *comboBox2);

private:
    Ui::updating_work *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    QComboBox *comboBox;
    QComboBox *comboBox2;
};

#endif // updating_work_H

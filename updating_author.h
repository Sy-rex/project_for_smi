#ifndef updating_author_H
#define updating_author_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class updating_author;
}

class updating_author : public QWidget
{
    Q_OBJECT

public:
    explicit updating_author(QWidget *parent = nullptr);
    ~updating_author();

    void setFields(const int id_author, const QString &author, const QString &edition, const QString &rating);

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
    void updateAuthorEntry(int Idauthor, QComboBox *comboBox, QLineEdit *lineEdit, QLineEdit *lineEdit2);

private:
    Ui::updating_author *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit2;
    int Idauthor;
};

#endif // updating_author_H

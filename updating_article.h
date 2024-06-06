#ifndef updating_article_H
#define updating_article_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class updating_article;
}

class updating_article : public QWidget
{
    Q_OBJECT

public:
    explicit updating_article(QWidget *parent = nullptr);
    ~updating_article();

    void setFields(const int id_article, const QString &journal, const QString &name, const QString &rating, const QString &description, const QString &price, const QString yearOfFoundation);

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
    void updateArticleEntry(int article, QComboBox *comboBox, QLineEdit *lineEdit, QLineEdit *lineEdit2, QLineEdit *lineEdit3, QLineEdit *lineEdit4, QLineEdit *lineEdit5);

private:
    Ui::updating_article *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;
    QLineEdit *lineEdit4;
    QLineEdit *lineEdit5;
    int article;
};

#endif // updating_article_H

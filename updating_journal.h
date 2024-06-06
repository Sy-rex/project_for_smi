#ifndef updating_journal_H
#define updating_journal_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QLineEdit>
#include "databasemanger.h"

namespace Ui {
class updating_journal;
}

class updating_journal : public QWidget
{
    Q_OBJECT

public:
    explicit updating_journal(QWidget *parent = nullptr);
    ~updating_journal();

    void setFields(const int id_journal, const QString &name, const QString &yearOfFoundation, const QString &rating);

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
    void updateJournalEntry(int journal,QLineEdit *lineEditName, QLineEdit *lineEditYearOfFoundation, QLineEdit *lineEditRating);

private:
    Ui::updating_journal *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    QLineEdit *lineEditName;
    QLineEdit *lineEditYearOfFoundation;
    QLineEdit *lineEditRating;
    int journal;
};

#endif // updating_journal_H

#ifndef tariffuserwindow_H
#define tariffuserwindow_H

#include <QWidget>
#include <QEvent>
#include <QPushButton>
#include <QIcon>

namespace Ui {
class tariffuserwindow;
}

class tariffuserwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tariffuserwindow(QWidget *parent = nullptr);
    ~tariffuserwindow();

private slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::tariffuserwindow *ui;

    QPoint m_lastPoint; // Добавляем переменную для хранения последней позиции курсора

    void updateButtonIcon(QPushButton *button, const QString &iconPath);

};

#endif // tariffuserwindow_H

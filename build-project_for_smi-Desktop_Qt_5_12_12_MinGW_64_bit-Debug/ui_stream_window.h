/********************************************************************************
** Form generated from reading UI file 'stream_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAM_WINDOW_H
#define UI_STREAM_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Stream_window
{
public:

    void setupUi(QWidget *Stream_window)
    {
        if (Stream_window->objectName().isEmpty())
            Stream_window->setObjectName(QString::fromUtf8("Stream_window"));
        Stream_window->resize(400, 300);

        retranslateUi(Stream_window);

        QMetaObject::connectSlotsByName(Stream_window);
    } // setupUi

    void retranslateUi(QWidget *Stream_window)
    {
        Stream_window->setWindowTitle(QApplication::translate("Stream_window", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Stream_window: public Ui_Stream_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAM_WINDOW_H

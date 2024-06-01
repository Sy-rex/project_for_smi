/********************************************************************************
** Form generated from reading UI file 'stream_window.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAM_WINDOW_H
#define UI_STREAM_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stream_window
{
public:

    void setupUi(QWidget *stream_window)
    {
        if (stream_window->objectName().isEmpty())
            stream_window->setObjectName("stream_window");
        stream_window->resize(400, 300);

        retranslateUi(stream_window);

        QMetaObject::connectSlotsByName(stream_window);
    } // setupUi

    void retranslateUi(QWidget *stream_window)
    {
        stream_window->setWindowTitle(QCoreApplication::translate("stream_window", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stream_window: public Ui_stream_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAM_WINDOW_H

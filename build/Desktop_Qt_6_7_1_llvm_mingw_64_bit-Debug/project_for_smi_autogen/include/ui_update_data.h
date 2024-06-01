/********************************************************************************
** Form generated from reading UI file 'update_data.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATE_DATA_H
#define UI_UPDATE_DATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_update_data
{
public:

    void setupUi(QWidget *update_data)
    {
        if (update_data->objectName().isEmpty())
            update_data->setObjectName("update_data");
        update_data->resize(400, 300);

        retranslateUi(update_data);

        QMetaObject::connectSlotsByName(update_data);
    } // setupUi

    void retranslateUi(QWidget *update_data)
    {
        update_data->setWindowTitle(QCoreApplication::translate("update_data", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class update_data: public Ui_update_data {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATE_DATA_H

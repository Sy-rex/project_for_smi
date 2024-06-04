/********************************************************************************
** Form generated from reading UI file 'updating_records.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATING_RECORDS_H
#define UI_UPDATING_RECORDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updating_records
{
public:

    void setupUi(QWidget *updating_records)
    {
        if (updating_records->objectName().isEmpty())
            updating_records->setObjectName("updating_records");
        updating_records->resize(400, 300);

        retranslateUi(updating_records);

        QMetaObject::connectSlotsByName(updating_records);
    } // setupUi

    void retranslateUi(QWidget *updating_records)
    {
        updating_records->setWindowTitle(QCoreApplication::translate("updating_records", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updating_records: public Ui_updating_records {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATING_RECORDS_H

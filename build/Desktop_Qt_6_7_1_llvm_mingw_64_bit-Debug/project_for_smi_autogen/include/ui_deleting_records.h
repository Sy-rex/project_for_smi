/********************************************************************************
** Form generated from reading UI file 'deleting_records.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETING_RECORDS_H
#define UI_DELETING_RECORDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deleting_records
{
public:

    void setupUi(QWidget *deleting_records)
    {
        if (deleting_records->objectName().isEmpty())
            deleting_records->setObjectName("deleting_records");
        deleting_records->resize(400, 300);

        retranslateUi(deleting_records);

        QMetaObject::connectSlotsByName(deleting_records);
    } // setupUi

    void retranslateUi(QWidget *deleting_records)
    {
        deleting_records->setWindowTitle(QCoreApplication::translate("deleting_records", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deleting_records: public Ui_deleting_records {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETING_RECORDS_H

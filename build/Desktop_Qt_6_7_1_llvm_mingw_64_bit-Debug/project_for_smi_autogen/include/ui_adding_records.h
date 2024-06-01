/********************************************************************************
** Form generated from reading UI file 'adding_records.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDING_RECORDS_H
#define UI_ADDING_RECORDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adding_records
{
public:

    void setupUi(QWidget *adding_records)
    {
        if (adding_records->objectName().isEmpty())
            adding_records->setObjectName("adding_records");
        adding_records->resize(400, 300);

        retranslateUi(adding_records);

        QMetaObject::connectSlotsByName(adding_records);
    } // setupUi

    void retranslateUi(QWidget *adding_records)
    {
        adding_records->setWindowTitle(QCoreApplication::translate("adding_records", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adding_records: public Ui_adding_records {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDING_RECORDS_H

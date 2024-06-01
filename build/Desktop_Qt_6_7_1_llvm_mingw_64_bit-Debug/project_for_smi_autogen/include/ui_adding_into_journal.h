/********************************************************************************
** Form generated from reading UI file 'adding_into_journal.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDING_INTO_JOURNAL_H
#define UI_ADDING_INTO_JOURNAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adding_into_journal
{
public:

    void setupUi(QWidget *adding_into_journal)
    {
        if (adding_into_journal->objectName().isEmpty())
            adding_into_journal->setObjectName("adding_into_journal");
        adding_into_journal->resize(400, 300);

        retranslateUi(adding_into_journal);

        QMetaObject::connectSlotsByName(adding_into_journal);
    } // setupUi

    void retranslateUi(QWidget *adding_into_journal)
    {
        adding_into_journal->setWindowTitle(QCoreApplication::translate("adding_into_journal", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adding_into_journal: public Ui_adding_into_journal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDING_INTO_JOURNAL_H

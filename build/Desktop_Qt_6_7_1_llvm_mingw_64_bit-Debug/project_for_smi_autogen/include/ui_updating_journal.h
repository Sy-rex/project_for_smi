/********************************************************************************
** Form generated from reading UI file 'updating_journal.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATING_JOURNAL_H
#define UI_UPDATING_JOURNAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updating_journal
{
public:

    void setupUi(QWidget *updating_journal)
    {
        if (updating_journal->objectName().isEmpty())
            updating_journal->setObjectName("updating_journal");
        updating_journal->resize(400, 300);

        retranslateUi(updating_journal);

        QMetaObject::connectSlotsByName(updating_journal);
    } // setupUi

    void retranslateUi(QWidget *updating_journal)
    {
        updating_journal->setWindowTitle(QCoreApplication::translate("updating_journal", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updating_journal: public Ui_updating_journal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATING_JOURNAL_H

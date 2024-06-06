/********************************************************************************
** Form generated from reading UI file 'updating_author.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATING_AUTHOR_H
#define UI_UPDATING_AUTHOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updating_author
{
public:

    void setupUi(QWidget *updating_author)
    {
        if (updating_author->objectName().isEmpty())
            updating_author->setObjectName("updating_author");
        updating_author->resize(400, 300);

        retranslateUi(updating_author);

        QMetaObject::connectSlotsByName(updating_author);
    } // setupUi

    void retranslateUi(QWidget *updating_author)
    {
        updating_author->setWindowTitle(QCoreApplication::translate("updating_author", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updating_author: public Ui_updating_author {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATING_AUTHOR_H

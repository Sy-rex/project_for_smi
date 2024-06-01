/********************************************************************************
** Form generated from reading UI file 'adding_into_author.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDING_INTO_AUTHOR_H
#define UI_ADDING_INTO_AUTHOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adding_into_author
{
public:

    void setupUi(QWidget *adding_into_author)
    {
        if (adding_into_author->objectName().isEmpty())
            adding_into_author->setObjectName("adding_into_author");
        adding_into_author->resize(400, 300);

        retranslateUi(adding_into_author);

        QMetaObject::connectSlotsByName(adding_into_author);
    } // setupUi

    void retranslateUi(QWidget *adding_into_author)
    {
        adding_into_author->setWindowTitle(QCoreApplication::translate("adding_into_author", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adding_into_author: public Ui_adding_into_author {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDING_INTO_AUTHOR_H

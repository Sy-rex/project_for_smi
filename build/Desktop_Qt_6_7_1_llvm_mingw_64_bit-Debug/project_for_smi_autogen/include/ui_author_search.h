/********************************************************************************
** Form generated from reading UI file 'author_search.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHOR_SEARCH_H
#define UI_AUTHOR_SEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_author_search
{
public:

    void setupUi(QWidget *author_search)
    {
        if (author_search->objectName().isEmpty())
            author_search->setObjectName("author_search");
        author_search->resize(400, 300);

        retranslateUi(author_search);

        QMetaObject::connectSlotsByName(author_search);
    } // setupUi

    void retranslateUi(QWidget *author_search)
    {
        author_search->setWindowTitle(QCoreApplication::translate("author_search", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class author_search: public Ui_author_search {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHOR_SEARCH_H

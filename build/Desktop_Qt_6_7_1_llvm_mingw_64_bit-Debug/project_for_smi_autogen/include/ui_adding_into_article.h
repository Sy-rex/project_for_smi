/********************************************************************************
** Form generated from reading UI file 'adding_into_article.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDING_INTO_ARTICLE_H
#define UI_ADDING_INTO_ARTICLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adding_into_article
{
public:

    void setupUi(QWidget *adding_into_article)
    {
        if (adding_into_article->objectName().isEmpty())
            adding_into_article->setObjectName("adding_into_article");
        adding_into_article->resize(400, 300);

        retranslateUi(adding_into_article);

        QMetaObject::connectSlotsByName(adding_into_article);
    } // setupUi

    void retranslateUi(QWidget *adding_into_article)
    {
        adding_into_article->setWindowTitle(QCoreApplication::translate("adding_into_article", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adding_into_article: public Ui_adding_into_article {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDING_INTO_ARTICLE_H

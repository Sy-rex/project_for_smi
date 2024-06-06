/********************************************************************************
** Form generated from reading UI file 'updating_article.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATING_ARTICLE_H
#define UI_UPDATING_ARTICLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updating_article
{
public:

    void setupUi(QWidget *updating_article)
    {
        if (updating_article->objectName().isEmpty())
            updating_article->setObjectName("updating_article");
        updating_article->resize(400, 300);

        retranslateUi(updating_article);

        QMetaObject::connectSlotsByName(updating_article);
    } // setupUi

    void retranslateUi(QWidget *updating_article)
    {
        updating_article->setWindowTitle(QCoreApplication::translate("updating_article", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updating_article: public Ui_updating_article {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATING_ARTICLE_H

/********************************************************************************
** Form generated from reading UI file 'hot_news.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOT_NEWS_H
#define UI_HOT_NEWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hot_news
{
public:

    void setupUi(QWidget *hot_news)
    {
        if (hot_news->objectName().isEmpty())
            hot_news->setObjectName("hot_news");
        hot_news->resize(400, 300);

        retranslateUi(hot_news);

        QMetaObject::connectSlotsByName(hot_news);
    } // setupUi

    void retranslateUi(QWidget *hot_news)
    {
        hot_news->setWindowTitle(QCoreApplication::translate("hot_news", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hot_news: public Ui_hot_news {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOT_NEWS_H

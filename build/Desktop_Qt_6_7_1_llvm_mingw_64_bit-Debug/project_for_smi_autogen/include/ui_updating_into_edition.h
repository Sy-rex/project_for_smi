/********************************************************************************
** Form generated from reading UI file 'updating_into_edition.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATING_INTO_EDITION_H
#define UI_UPDATING_INTO_EDITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updating_into_edition
{
public:
    QTableView *tableView;

    void setupUi(QWidget *updating_into_edition)
    {
        if (updating_into_edition->objectName().isEmpty())
            updating_into_edition->setObjectName("updating_into_edition");
        updating_into_edition->resize(649, 535);
        tableView = new QTableView(updating_into_edition);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(30, 140, 581, 321));
        tableView->setStyleSheet(QString::fromUtf8("QTableView {\n"
"border: 4px solid #373752;\n"
"border-radius: 10px;\n"
"gridline-color: #FFFFFF; /* #6D55FF */\n"
"background-color: #373752;\n"
"}\n"
"\n"
"QTableView::item {\n"
"background-color: #222338;\n"
"font-family: Poppins; /* \320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\210\321\200\320\270\321\204\321\202\320\260 */\n"
"font-size: 15pt; /* \320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\200\320\260\320\267\320\274\320\265\321\200\320\260 \321\210\321\200\320\270\321\204\321\202\320\260 */\n"
"color: white;\n"
"}\n"
"\n"
"QTableView::item:selected {\n"
"background-color: #A0A1A8; /* #6D55FF */\n"
"color: white;\n"
"}\n"
"\n"
"QTableView::item:focus {\n"
"background-color: #373752; /* #6D55FF */\n"
"color: white;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"background-color: #373752; /* #6D55FF */\n"
"color: white;\n"
"font-family: Poppins;\n"
"font-size: 14pt;\n"
"}\n"
"\n"
"QHeaderView::section:horizontal {\n"
"border: none; /* \321\203\320"
                        "\261\320\270\321\200\320\260\320\265\320\274 \320\263\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214\320\275\321\213\320\265 \320\273\320\270\320\275\320\270\320\270 \321\200\320\260\320\267\320\264\320\265\320\273\320\270\321\202\320\265\320\273\321\217 */\n"
"}\n"
"\n"
"QHeaderView::section:vertical {\n"
"border: none; /* \321\203\320\261\320\270\321\200\320\260\320\265\320\274 \320\262\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\321\213\320\265 \320\273\320\270\320\275\320\270\320\270 \321\200\320\260\320\267\320\264\320\265\320\273\320\270\321\202\320\265\320\273\321\217 */\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"border: none;\n"
"background: white; /* \320\234\320\276\320\266\320\275\320\276 \320\270\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\275\320\260 \321\206\320\262\320\265\321\202 \321\204\320\276\320\275\320\260 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 \320\270\320\273\320\270 \320\276\320\272\320\275\320"
                        "\260 */\n"
"width: 7px; /* \320\243\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\275\320\260\321\217 \321\210\320\270\321\200\320\270\320\275\320\260 */\n"
"margin: 0px; /* \320\225\321\201\320\273\320\270 \320\275\320\265 \320\275\321\203\320\266\320\275\320\276 \320\276\321\202\321\201\321\202\321\203\320\277\320\273\320\265\320\275\320\270\320\265 \320\276\321\202 \320\272\321\200\320\260\320\265\320\262 */\n"
"border-radius: 2px; /* \320\243\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\275\320\276\320\265 \320\267\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\270\320\265 */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"background: #F23878;\n"
"min-height: 7px; /* \320\243\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\275\320\260\321\217 \320\274\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \320\264\320\273\320\270\320\275\320\260 */\n"
"border-radius: 2px; /* \320\243\320\274\320\265\320\275\321\214\321\210"
                        "\320\265\320\275\320\275\320\276\320\265 \320\267\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\270\320\265 */\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"background: #373752; /* \320\255\321\202\320\276 \320\270\320\267\320\274\320\265\320\275\320\270\321\202 \321\206\320\262\320\265\321\202 \321\204\320\276\320\275\320\260 \320\275\320\265\320\260\320\272\321\202\320\270\320\262\320\275\321\213\321\205 \321\207\320\260\321\201\321\202\320\265\320\271 \320\277\320\276\320\273\320\267\321\203\320\275\320\272\320\260 */\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"border: none;\n"
"background: none;\n"
"width: 0px;\n"
"height: 0px;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"border: none;\n"
"background: white; /* \320\234\320\276\320\266\320\275\320\276 \320\270\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\275\320\260 \321\206\320\262\320\265\321\202 \321\204\320\276\320\275\320\260 \321\202\320\260\320"
                        "\261\320\273\320\270\321\206\321\213 \320\270\320\273\320\270 \320\276\320\272\320\275\320\260 */\n"
"height: 7px; /* \320\243\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\275\320\260\321\217 \320\262\321\213\321\201\320\276\321\202\320\260 */\n"
"margin: 0px; /* \320\225\321\201\320\273\320\270 \320\275\320\265 \320\275\321\203\320\266\320\275\320\276 \320\276\321\202\321\201\321\202\321\203\320\277\320\273\320\265\320\275\320\270\320\265 \320\276\321\202 \320\272\321\200\320\260\320\265\320\262 */\n"
"/*border-radius: 5px; /* \320\243\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\275\320\276\320\265 \320\267\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\270\320\265 */\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"background: #373752;\n"
"min-width: 10px; /* \320\243\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\275\320\260\321\217 \320\274\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \320\264\320\273\320\270"
                        "\320\275\320\260 */\n"
"border-radius: 5px; /* \320\243\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\275\320\276\320\265 \320\267\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\270\320\265 */\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\n"
"background: #373752; /* \320\255\321\202\320\276 \320\270\320\267\320\274\320\265\320\275\320\270\321\202 \321\206\320\262\320\265\321\202 \321\204\320\276\320\275\320\260 \320\275\320\265\320\260\320\272\321\202\320\270\320\262\320\275\321\213\321\205 \321\207\320\260\321\201\321\202\320\265\320\271 \320\277\320\276\320\273\320\267\321\203\320\275\320\272\320\260 */\n"
"}"));

        retranslateUi(updating_into_edition);

        QMetaObject::connectSlotsByName(updating_into_edition);
    } // setupUi

    void retranslateUi(QWidget *updating_into_edition)
    {
        updating_into_edition->setWindowTitle(QCoreApplication::translate("updating_into_edition", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updating_into_edition: public Ui_updating_into_edition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATING_INTO_EDITION_H

/****************************************************************************
** Meta object code from reading C++ file 'adding_into_article.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../b2ad0b3bee70096f7320af22d346fac4/adding_into_article.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adding_into_article.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSadding_into_articleENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSadding_into_articleENDCLASS = QtMocHelpers::stringData(
    "adding_into_article",
    "openMainWindow",
    "",
    "loadComboBoxData",
    "QComboBox*",
    "comboBox",
    "addArticleEntry",
    "QLineEdit*",
    "lineEdit",
    "lineEdit2",
    "lineEdit3",
    "lineEdit4",
    "lineEdit5"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSadding_into_articleENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x08,    1 /* Private */,
       3,    1,   33,    2, 0x08,    2 /* Private */,
       6,    6,   36,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 7,    5,    8,    9,   10,   11,   12,

       0        // eod
};

Q_CONSTINIT const QMetaObject adding_into_article::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSadding_into_articleENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSadding_into_articleENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSadding_into_articleENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<adding_into_article, std::true_type>,
        // method 'openMainWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadComboBoxData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QComboBox *, std::false_type>,
        // method 'addArticleEntry'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QComboBox *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>
    >,
    nullptr
} };

void adding_into_article::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<adding_into_article *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openMainWindow(); break;
        case 1: _t->loadComboBoxData((*reinterpret_cast< std::add_pointer_t<QComboBox*>>(_a[1]))); break;
        case 2: _t->addArticleEntry((*reinterpret_cast< std::add_pointer_t<QComboBox*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[6]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QComboBox* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QComboBox* >(); break;
            case 5:
            case 4:
            case 3:
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *adding_into_article::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *adding_into_article::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSadding_into_articleENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int adding_into_article::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP

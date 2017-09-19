/****************************************************************************
** Meta object code from reading C++ file 'prefsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../linssid-app/prefsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'prefsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_prefsDialog_t {
    QByteArrayData data[7];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_prefsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_prefsDialog_t qt_meta_stringdata_prefsDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "prefsDialog"
QT_MOC_LITERAL(1, 12, 16), // "plotPrefsChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "bailOut"
QT_MOC_LITERAL(4, 38, 12), // "minSbChanged"
QT_MOC_LITERAL(5, 51, 12), // "maxSbChanged"
QT_MOC_LITERAL(6, 64, 11) // "gridChanged"

    },
    "prefsDialog\0plotPrefsChanged\0\0bailOut\0"
    "minSbChanged\0maxSbChanged\0gridChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_prefsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   46,    2, 0x0a /* Public */,
       4,    1,   49,    2, 0x0a /* Public */,
       5,    1,   52,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void prefsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        prefsDialog *_t = static_cast<prefsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->plotPrefsChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->bailOut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->minSbChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->maxSbChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->gridChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (prefsDialog::*_t)(int , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&prefsDialog::plotPrefsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject prefsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_prefsDialog.data,
      qt_meta_data_prefsDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *prefsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *prefsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_prefsDialog.stringdata0))
        return static_cast<void*>(const_cast< prefsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int prefsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void prefsDialog::plotPrefsChanged(int _t1, int _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

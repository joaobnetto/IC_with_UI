/****************************************************************************
** Meta object code from reading C++ file 'data.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../IC_with_UI/data.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSet>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Data_t {
    QByteArrayData data[10];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Data_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Data_t qt_meta_stringdata_Data = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Data"
QT_MOC_LITERAL(1, 5, 16), // "notifyImportSala"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 19), // "notifyImportPedidos"
QT_MOC_LITERAL(4, 43, 13), // "numberOfSteps"
QT_MOC_LITERAL(5, 57, 6), // "number"
QT_MOC_LITERAL(6, 64, 12), // "incrProgress"
QT_MOC_LITERAL(7, 77, 16), // "paintNaoAlocados"
QT_MOC_LITERAL(8, 94, 9), // "QSet<int>"
QT_MOC_LITERAL(9, 104, 12) // "nao_alocados"

    },
    "Data\0notifyImportSala\0\0notifyImportPedidos\0"
    "numberOfSteps\0number\0incrProgress\0"
    "paintNaoAlocados\0QSet<int>\0nao_alocados"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Data[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    1,   41,    2, 0x06 /* Public */,
       6,    0,   44,    2, 0x06 /* Public */,
       7,    1,   45,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void Data::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Data *_t = static_cast<Data *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notifyImportSala(); break;
        case 1: _t->notifyImportPedidos(); break;
        case 2: _t->numberOfSteps((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->incrProgress(); break;
        case 4: _t->paintNaoAlocados((*reinterpret_cast< QSet<int>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSet<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Data::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::notifyImportSala)) {
                *result = 0;
            }
        }
        {
            typedef void (Data::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::notifyImportPedidos)) {
                *result = 1;
            }
        }
        {
            typedef void (Data::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::numberOfSteps)) {
                *result = 2;
            }
        }
        {
            typedef void (Data::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::incrProgress)) {
                *result = 3;
            }
        }
        {
            typedef void (Data::*_t)(QSet<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::paintNaoAlocados)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Data::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Data.data,
      qt_meta_data_Data,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Data::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Data::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Data.stringdata0))
        return static_cast<void*>(const_cast< Data*>(this));
    return QObject::qt_metacast(_clname);
}

int Data::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Data::notifyImportSala()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Data::notifyImportPedidos()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Data::numberOfSteps(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Data::incrProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Data::paintNaoAlocados(QSet<int> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

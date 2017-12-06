/****************************************************************************
** Meta object code from reading C++ file 'PaintedWidget.h'
**
** Created: Mon Nov 6 17:49:00 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "PaintedWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PaintedWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PaintedWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      36,   30,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PaintedWidget[] = {
    "PaintedWidget\0\0pointClicked()\0index\0"
    "itemClicked(QModelIndex)\0"
};

const QMetaObject PaintedWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PaintedWidget,
      qt_meta_data_PaintedWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PaintedWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PaintedWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PaintedWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PaintedWidget))
        return static_cast<void*>(const_cast< PaintedWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PaintedWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pointClicked(); break;
        case 1: itemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

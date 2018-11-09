/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../omo-x-server/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "changeCamera"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 16), // "runningOnNetwork"
QT_MOC_LITERAL(4, 42, 23), // "downsampleFactorChanged"
QT_MOC_LITERAL(5, 66, 6), // "factor"
QT_MOC_LITERAL(6, 73, 12), // "isRGBChanged"
QT_MOC_LITERAL(7, 86, 5), // "isRgb"
QT_MOC_LITERAL(8, 92, 22), // "initiateRemoteShutdown"
QT_MOC_LITERAL(9, 115, 24), // "on_btn_trainFace_clicked"
QT_MOC_LITERAL(10, 140, 17), // "updateStatusLabel"
QT_MOC_LITERAL(11, 158, 3), // "str"
QT_MOC_LITERAL(12, 162, 25), // "on_switchCamViews_clicked"
QT_MOC_LITERAL(13, 188, 32), // "on_slider_resolution_sliderMoved"
QT_MOC_LITERAL(14, 221, 8), // "position"
QT_MOC_LITERAL(15, 230, 26), // "on_radio_btn_isRGB_clicked"
QT_MOC_LITERAL(16, 257, 7), // "checked"
QT_MOC_LITERAL(17, 265, 30) // "on_remote_shutdown_btn_clicked"

    },
    "MainWindow\0changeCamera\0\0runningOnNetwork\0"
    "downsampleFactorChanged\0factor\0"
    "isRGBChanged\0isRgb\0initiateRemoteShutdown\0"
    "on_btn_trainFace_clicked\0updateStatusLabel\0"
    "str\0on_switchCamViews_clicked\0"
    "on_slider_resolution_sliderMoved\0"
    "position\0on_radio_btn_isRGB_clicked\0"
    "checked\0on_remote_shutdown_btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    1,   70,    2, 0x06 /* Public */,
       8,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   74,    2, 0x08 /* Private */,
      10,    1,   75,    2, 0x08 /* Private */,
      12,    0,   78,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,
      15,    1,   82,    2, 0x08 /* Private */,
      17,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeCamera((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->downsampleFactorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->isRGBChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->initiateRemoteShutdown(); break;
        case 4: _t->on_btn_trainFace_clicked(); break;
        case 5: _t->updateStatusLabel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->on_switchCamViews_clicked(); break;
        case 7: _t->on_slider_resolution_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_radio_btn_isRGB_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_remote_shutdown_btn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::changeCamera)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::downsampleFactorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::isRGBChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::initiateRemoteShutdown)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::changeCamera(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::downsampleFactorChanged(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::isRGBChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::initiateRemoteShutdown()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

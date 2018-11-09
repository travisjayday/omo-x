/****************************************************************************
** Meta object code from reading C++ file 'socketserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../socketserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socketserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SocketServer_t {
    QByteArrayData data[16];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SocketServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SocketServer_t qt_meta_stringdata_SocketServer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SocketServer"
QT_MOC_LITERAL(1, 13, 15), // "onNewConnection"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "processTextMessage"
QT_MOC_LITERAL(4, 49, 7), // "message"
QT_MOC_LITERAL(5, 57, 20), // "processBinaryMessage"
QT_MOC_LITERAL(6, 78, 4), // "data"
QT_MOC_LITERAL(7, 83, 18), // "socketDisconnected"
QT_MOC_LITERAL(8, 102, 25), // "onRunningOnNetworkChanged"
QT_MOC_LITERAL(9, 128, 5), // "state"
QT_MOC_LITERAL(10, 134, 12), // "sendFaceData"
QT_MOC_LITERAL(11, 147, 25), // "onDownsampleFactorChanged"
QT_MOC_LITERAL(12, 173, 6), // "factor"
QT_MOC_LITERAL(13, 180, 12), // "onRGBChanged"
QT_MOC_LITERAL(14, 193, 5), // "isRgb"
QT_MOC_LITERAL(15, 199, 24) // "onInitiateRemoteShutdown"

    },
    "SocketServer\0onNewConnection\0\0"
    "processTextMessage\0message\0"
    "processBinaryMessage\0data\0socketDisconnected\0"
    "onRunningOnNetworkChanged\0state\0"
    "sendFaceData\0onDownsampleFactorChanged\0"
    "factor\0onRGBChanged\0isRgb\0"
    "onInitiateRemoteShutdown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SocketServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    1,   60,    2, 0x0a /* Public */,
       5,    1,   63,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    1,   67,    2, 0x0a /* Public */,
      10,    1,   70,    2, 0x0a /* Public */,
      11,    1,   73,    2, 0x0a /* Public */,
      13,    1,   76,    2, 0x0a /* Public */,
      15,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void SocketServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SocketServer *_t = static_cast<SocketServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewConnection(); break;
        case 1: _t->processTextMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->processBinaryMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->socketDisconnected(); break;
        case 4: _t->onRunningOnNetworkChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->sendFaceData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->onDownsampleFactorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->onRGBChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->onInitiateRemoteShutdown(); break;
        default: ;
        }
    }
}

const QMetaObject SocketServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SocketServer.data,
      qt_meta_data_SocketServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SocketServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SocketServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SocketServer.stringdata0))
        return static_cast<void*>(const_cast< SocketServer*>(this));
    return QObject::qt_metacast(_clname);
}

int SocketServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

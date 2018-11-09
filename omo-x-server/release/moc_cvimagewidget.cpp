/****************************************************************************
** Meta object code from reading C++ file 'cvimagewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cvimagewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cvimagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CVImageWidget_t {
    QByteArrayData data[17];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVImageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVImageWidget_t qt_meta_stringdata_CVImageWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CVImageWidget"
QT_MOC_LITERAL(1, 14, 23), // "runningOnNetworkChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 14), // "runningNetwork"
QT_MOC_LITERAL(4, 54, 9), // "faceFound"
QT_MOC_LITERAL(5, 64, 8), // "faceData"
QT_MOC_LITERAL(6, 73, 9), // "showImage"
QT_MOC_LITERAL(7, 83, 7), // "cv::Mat"
QT_MOC_LITERAL(8, 91, 3), // "mat"
QT_MOC_LITERAL(9, 95, 5), // "isRGB"
QT_MOC_LITERAL(10, 101, 16), // "runningOnNetwork"
QT_MOC_LITERAL(11, 118, 19), // "setRunningOnNetwork"
QT_MOC_LITERAL(12, 138, 5), // "param"
QT_MOC_LITERAL(13, 144, 15), // "setFaceDetector"
QT_MOC_LITERAL(14, 160, 13), // "FaceDetector*"
QT_MOC_LITERAL(15, 174, 7), // "facedet"
QT_MOC_LITERAL(16, 182, 11) // "flushCanvas"

    },
    "CVImageWidget\0runningOnNetworkChanged\0"
    "\0runningNetwork\0faceFound\0faceData\0"
    "showImage\0cv::Mat\0mat\0isRGB\0"
    "runningOnNetwork\0setRunningOnNetwork\0"
    "param\0setFaceDetector\0FaceDetector*\0"
    "facedet\0flushCanvas"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVImageWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   55,    2, 0x0a /* Public */,
      10,    0,   60,    2, 0x0a /* Public */,
      11,    1,   61,    2, 0x0a /* Public */,
      13,    1,   64,    2, 0x0a /* Public */,
      16,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    8,    9,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,

       0        // eod
};

void CVImageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CVImageWidget *_t = static_cast<CVImageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->runningOnNetworkChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->faceFound((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->showImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: { bool _r = _t->runningOnNetwork();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->setRunningOnNetwork((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setFaceDetector((*reinterpret_cast< FaceDetector*(*)>(_a[1]))); break;
        case 6: _t->flushCanvas(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FaceDetector* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CVImageWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVImageWidget::runningOnNetworkChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CVImageWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVImageWidget::faceFound)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CVImageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CVImageWidget.data,
      qt_meta_data_CVImageWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CVImageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CVImageWidget.stringdata0))
        return static_cast<void*>(const_cast< CVImageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CVImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CVImageWidget::runningOnNetworkChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CVImageWidget::faceFound(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

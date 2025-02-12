/****************************************************************************
** Meta object code from reading C++ file 'sprite.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sprite.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sprite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
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
struct qt_meta_stringdata_CLASSSpriteENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSpriteENDCLASS = QtMocHelpers::stringData(
    "Sprite",
    "animationFinished",
    "",
    "opacityChanged",
    "visibleChanged",
    "enabledChanged",
    "xChanged",
    "yChanged",
    "zChanged",
    "rotationChanged",
    "scaleChanged",
    "spriteDestroyed",
    "Sprite*",
    "onNextAnimationFrame",
    "opacity",
    "enabled",
    "visible",
    "pos",
    "x",
    "y",
    "z",
    "rotation",
    "scale",
    "transformOriginPoint",
    "currentAnimationFrame"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSpriteENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
      11,   93, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,   12 /* Public */,
       3,    0,   81,    2, 0x06,   13 /* Public */,
       4,    0,   82,    2, 0x06,   14 /* Public */,
       5,    0,   83,    2, 0x06,   15 /* Public */,
       6,    0,   84,    2, 0x06,   16 /* Public */,
       7,    0,   85,    2, 0x06,   17 /* Public */,
       8,    0,   86,    2, 0x06,   18 /* Public */,
       9,    0,   87,    2, 0x06,   19 /* Public */,
      10,    0,   88,    2, 0x06,   20 /* Public */,
      11,    1,   89,    2, 0x06,   21 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,   92,    2, 0x08,   23 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      14, QMetaType::QReal, 0x00015903, uint(1), 0,
      15, QMetaType::Bool, 0x00015103, uint(3), 0,
      16, QMetaType::Bool, 0x00015903, uint(2), 0,
      17, QMetaType::QPointF, 0x00015903, uint(-1), 0,
      18, QMetaType::QReal, 0x00015903, uint(4), 0,
      19, QMetaType::QReal, 0x00015903, uint(5), 0,
      20, QMetaType::QReal, 0x00015803, uint(6), 0,
      21, QMetaType::QReal, 0x00015103, uint(7), 0,
      22, QMetaType::QReal, 0x00015103, uint(8), 0,
      23, QMetaType::QPointF, 0x00015103, uint(-1), 0,
      24, QMetaType::Int, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject Sprite::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSpriteENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSpriteENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSpriteENDCLASS_t,
        // property 'opacity'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'enabled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'visible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'pos'
        QtPrivate::TypeAndForceComplete<QPointF, std::true_type>,
        // property 'x'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'y'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'z'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'rotation'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'scale'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'transformOriginPoint'
        QtPrivate::TypeAndForceComplete<QPointF, std::true_type>,
        // property 'currentAnimationFrame'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Sprite, std::true_type>,
        // method 'animationFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'opacityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'visibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enabledChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'xChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'yChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'zChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rotationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scaleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'spriteDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Sprite *, std::false_type>,
        // method 'onNextAnimationFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Sprite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Sprite *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->animationFinished(); break;
        case 1: _t->opacityChanged(); break;
        case 2: _t->visibleChanged(); break;
        case 3: _t->enabledChanged(); break;
        case 4: _t->xChanged(); break;
        case 5: _t->yChanged(); break;
        case 6: _t->zChanged(); break;
        case 7: _t->rotationChanged(); break;
        case 8: _t->scaleChanged(); break;
        case 9: _t->spriteDestroyed((*reinterpret_cast< std::add_pointer_t<Sprite*>>(_a[1]))); break;
        case 10: _t->onNextAnimationFrame(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Sprite* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::animationFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::opacityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::visibleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::enabledChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::xChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::yChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::zChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::rotationChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Sprite::*)();
            if (_t _q_method = &Sprite::scaleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Sprite::*)(Sprite * );
            if (_t _q_method = &Sprite::spriteDestroyed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Sprite *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->opacity(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isEnabled(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isVisible(); break;
        case 3: *reinterpret_cast< QPointF*>(_v) = _t->pos(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = _t->x(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = _t->y(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->zValue(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = _t->rotation(); break;
        case 8: *reinterpret_cast< qreal*>(_v) = _t->scale(); break;
        case 9: *reinterpret_cast< QPointF*>(_v) = _t->transformOriginPoint(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->currentAnimationFrame(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Sprite *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOpacity(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setPos(*reinterpret_cast< QPointF*>(_v)); break;
        case 4: _t->setX(*reinterpret_cast< qreal*>(_v)); break;
        case 5: _t->setY(*reinterpret_cast< qreal*>(_v)); break;
        case 6: _t->setZValue(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setRotation(*reinterpret_cast< qreal*>(_v)); break;
        case 8: _t->setScale(*reinterpret_cast< qreal*>(_v)); break;
        case 9: _t->setTransformOriginPoint(*reinterpret_cast< QPointF*>(_v)); break;
        case 10: _t->setCurrentAnimationFrame(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *Sprite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Sprite::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSpriteENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPixmapItem"))
        return static_cast< QGraphicsPixmapItem*>(this);
    return QObject::qt_metacast(_clname);
}

int Sprite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Sprite::animationFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Sprite::opacityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Sprite::visibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Sprite::enabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Sprite::xChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Sprite::yChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Sprite::zChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Sprite::rotationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Sprite::scaleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Sprite::spriteDestroyed(Sprite * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP

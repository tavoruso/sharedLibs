/****************************************************************************
** CincoHuevitosGUI meta object code from reading C++ file 'CincoHuevitosGUI.h'
**
** Created: Wed Sep 24 09:05:20 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "CincoHuevitosGUI.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CincoHuevitosGUI::className() const
{
    return "CincoHuevitosGUI";
}

QMetaObject *CincoHuevitosGUI::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CincoHuevitosGUI( "CincoHuevitosGUI", &CincoHuevitosGUI::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CincoHuevitosGUI::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CincoHuevitosGUI", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CincoHuevitosGUI::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CincoHuevitosGUI", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CincoHuevitosGUI::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"abrirJuego", 0, 0 };
    static const QUMethod slot_1 = {"acercaDe", 0, 0 };
    static const QUMethod slot_2 = {"botonPresionado", 0, 0 };
    static const QUMethod slot_3 = {"borrar", 0, 0 };
    static const QUMethod slot_4 = {"comoJugar", 0, 0 };
    static const QUMethod slot_5 = {"guardarJuego", 0, 0 };
    static const QUMethod slot_6 = {"moverFicha", 0, 0 };
    static const QUMethod slot_7 = {"nuevoJuego", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "abrirJuego()", &slot_0, QMetaData::Public },
	{ "acercaDe()", &slot_1, QMetaData::Public },
	{ "botonPresionado()", &slot_2, QMetaData::Public },
	{ "borrar()", &slot_3, QMetaData::Public },
	{ "comoJugar()", &slot_4, QMetaData::Public },
	{ "guardarJuego()", &slot_5, QMetaData::Public },
	{ "moverFicha()", &slot_6, QMetaData::Public },
	{ "nuevoJuego()", &slot_7, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"CincoHuevitosGUI", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CincoHuevitosGUI.setMetaObject( metaObj );
    return metaObj;
}

void* CincoHuevitosGUI::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CincoHuevitosGUI" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool CincoHuevitosGUI::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: abrirJuego(); break;
    case 1: acercaDe(); break;
    case 2: botonPresionado(); break;
    case 3: borrar(); break;
    case 4: comoJugar(); break;
    case 5: guardarJuego(); break;
    case 6: moverFicha(); break;
    case 7: nuevoJuego(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CincoHuevitosGUI::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool CincoHuevitosGUI::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool CincoHuevitosGUI::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

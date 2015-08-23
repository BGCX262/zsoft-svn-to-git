/****************************************************************************
** ZGui meta object code from reading C++ file 'zgui.h'
**
** Created: Sat May 2 10:52:33 2009
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "zgui.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *ZGui::className() const
{
    return "ZGui";
}

QMetaObject *ZGui::metaObj = 0;

#ifdef QWS
static class ZGui_metaObj_Unloader {
public:
    ~ZGui_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "ZGui" );
    }
} ZGui_metaObj_unloader;
#endif

void ZGui::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZKbMainWidget::className(), "ZKbMainWidget") != 0 )
	badSuperclassWarning("ZGui","ZKbMainWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZGui::tr(const char* s)
{
    return qApp->translate( "ZGui", s, 0 );
}

QString ZGui::tr(const char* s, const char * c)
{
    return qApp->translate( "ZGui", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZGui::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZKbMainWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (ZGui::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (ZGui::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (ZGui::*m1_t2)(QKeyEvent*);
    typedef void (QObject::*om1_t2)(QKeyEvent*);
    m1_t0 v1_0 = &ZGui::guardar;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &ZGui::MenuClick;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &ZGui::keyPressEvent;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "guardar()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "MenuClick()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "keyPressEvent(QKeyEvent*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"ZGui", "ZKbMainWidget",
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}

/****************************************************************************
** ZGui meta object code from reading C++ file 'zgui.h'
**
** Created: Tue Dec 16 16:55:51 2008
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
    typedef void (ZGui::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (ZGui::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (ZGui::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (ZGui::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (ZGui::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    m1_t0 v1_0 = &ZGui::about;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &ZGui::ejecutar;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &ZGui::agregarTipoASK;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &ZGui::agregarTipoDELETE;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &ZGui::eliminarTipoASK;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &ZGui::eliminarTipoDELETE;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &ZGui::verEliminados;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    QMetaData *slot_tbl = QMetaObject::new_metadata(7);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(7);
    slot_tbl[0].name = "about()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "ejecutar()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "agregarTipoASK()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "agregarTipoDELETE()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "eliminarTipoASK()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "eliminarTipoDELETE()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "verEliminados()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"ZGui", "ZKbMainWidget",
	slot_tbl, 7,
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

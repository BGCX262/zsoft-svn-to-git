/****************************************************************************
** TestWidget meta object code from reading C++ file 'TestWidget.h'
**
** Created: Tue Dec 23 12:37:14 2008
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "TestWidget.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *TestWidget::className() const
{
    return "TestWidget";
}

QMetaObject *TestWidget::metaObj = 0;

#ifdef QWS
static class TestWidget_metaObj_Unloader {
public:
    ~TestWidget_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "TestWidget" );
    }
} TestWidget_metaObj_unloader;
#endif

void TestWidget::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZKbMainWidget::className(), "ZKbMainWidget") != 0 )
	badSuperclassWarning("TestWidget","ZKbMainWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString TestWidget::tr(const char* s)
{
    return qApp->translate( "TestWidget", s, 0 );
}

QString TestWidget::tr(const char* s, const char * c)
{
    return qApp->translate( "TestWidget", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* TestWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZKbMainWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (TestWidget::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (TestWidget::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (TestWidget::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (TestWidget::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (TestWidget::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (TestWidget::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (TestWidget::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    m1_t0 v1_0 = &TestWidget::about;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &TestWidget::crono;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &TestWidget::para;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &TestWidget::texto;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &TestWidget::crearTimer;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &TestWidget::changecolor;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &TestWidget::changesize;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    QMetaData *slot_tbl = QMetaObject::new_metadata(7);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(7);
    slot_tbl[0].name = "about()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "crono()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "para()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "texto()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "crearTimer()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "changecolor()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "changesize()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"TestWidget", "ZKbMainWidget",
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

/****************************************************************************
** MyBaseDlg meta object code from reading C++ file 'BaseDlg.h'
**
** Created: Tue Dec 9 13:44:50 2008
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "BaseDlg.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *MyBaseDlg::className() const
{
    return "MyBaseDlg";
}

QMetaObject *MyBaseDlg::metaObj = 0;

#ifdef QWS
static class MyBaseDlg_metaObj_Unloader {
public:
    ~MyBaseDlg_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "MyBaseDlg" );
    }
} MyBaseDlg_metaObj_unloader;
#endif

void MyBaseDlg::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZKbMainWidget::className(), "ZKbMainWidget") != 0 )
	badSuperclassWarning("MyBaseDlg","ZKbMainWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MyBaseDlg::tr(const char* s)
{
    return qApp->translate( "MyBaseDlg", s, 0 );
}

QString MyBaseDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "MyBaseDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MyBaseDlg::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZKbMainWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (MyBaseDlg::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    typedef void (MyBaseDlg::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (MyBaseDlg::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    m1_t0 v1_0 = &MyBaseDlg::done;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &MyBaseDlg::accept;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &MyBaseDlg::reject;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "done(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Protected;
    slot_tbl[1].name = "accept()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Protected;
    slot_tbl[2].name = "reject()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Protected;
    metaObj = QMetaObject::new_metaobject(
	"MyBaseDlg", "ZKbMainWidget",
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

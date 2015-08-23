/****************************************************************************
** ZAboutDialog meta object code from reading C++ file 'ZAboutDlg.h'
**
** Created: Tue Dec 9 13:44:52 2008
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "ZAboutDlg.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *ZAboutDialog::className() const
{
    return "ZAboutDialog";
}

QMetaObject *ZAboutDialog::metaObj = 0;

#ifdef QWS
static class ZAboutDialog_metaObj_Unloader {
public:
    ~ZAboutDialog_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "ZAboutDialog" );
    }
} ZAboutDialog_metaObj_unloader;
#endif

void ZAboutDialog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(MyBaseDlg::className(), "MyBaseDlg") != 0 )
	badSuperclassWarning("ZAboutDialog","MyBaseDlg");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZAboutDialog::tr(const char* s)
{
    return qApp->translate( "ZAboutDialog", s, 0 );
}

QString ZAboutDialog::tr(const char* s, const char * c)
{
    return qApp->translate( "ZAboutDialog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZAboutDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) MyBaseDlg::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"ZAboutDialog", "MyBaseDlg",
	0, 0,
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

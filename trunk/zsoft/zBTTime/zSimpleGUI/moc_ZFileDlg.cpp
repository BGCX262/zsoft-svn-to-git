/****************************************************************************
** ZFileOpenDialog meta object code from reading C++ file 'ZFileDlg.h'
**
** Created: Tue Dec 9 13:44:53 2008
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "ZFileDlg.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *ZFileOpenDialog::className() const
{
    return "ZFileOpenDialog";
}

QMetaObject *ZFileOpenDialog::metaObj = 0;

#ifdef QWS
static class ZFileOpenDialog_metaObj_Unloader {
public:
    ~ZFileOpenDialog_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "ZFileOpenDialog" );
    }
} ZFileOpenDialog_metaObj_unloader;
#endif

void ZFileOpenDialog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(MyBaseDlg::className(), "MyBaseDlg") != 0 )
	badSuperclassWarning("ZFileOpenDialog","MyBaseDlg");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZFileOpenDialog::tr(const char* s)
{
    return qApp->translate( "ZFileOpenDialog", s, 0 );
}

QString ZFileOpenDialog::tr(const char* s, const char * c)
{
    return qApp->translate( "ZFileOpenDialog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZFileOpenDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) MyBaseDlg::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"ZFileOpenDialog", "MyBaseDlg",
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


const char *ZFileSaveDialog::className() const
{
    return "ZFileSaveDialog";
}

QMetaObject *ZFileSaveDialog::metaObj = 0;

#ifdef QWS
static class ZFileSaveDialog_metaObj_Unloader {
public:
    ~ZFileSaveDialog_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "ZFileSaveDialog" );
    }
} ZFileSaveDialog_metaObj_unloader;
#endif

void ZFileSaveDialog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(MyBaseDlg::className(), "MyBaseDlg") != 0 )
	badSuperclassWarning("ZFileSaveDialog","MyBaseDlg");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZFileSaveDialog::tr(const char* s)
{
    return qApp->translate( "ZFileSaveDialog", s, 0 );
}

QString ZFileSaveDialog::tr(const char* s, const char * c)
{
    return qApp->translate( "ZFileSaveDialog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZFileSaveDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) MyBaseDlg::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"ZFileSaveDialog", "MyBaseDlg",
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

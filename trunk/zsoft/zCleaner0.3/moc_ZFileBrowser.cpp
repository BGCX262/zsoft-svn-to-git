/****************************************************************************
** FileBrowser meta object code from reading C++ file 'ZFileBrowser.h'
**
** Created: Tue Dec 16 16:55:53 2008
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "ZFileBrowser.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *FileBrowser::className() const
{
    return "FileBrowser";
}

QMetaObject *FileBrowser::metaObj = 0;

#ifdef QWS
static class FileBrowser_metaObj_Unloader {
public:
    ~FileBrowser_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "FileBrowser" );
    }
} FileBrowser_metaObj_unloader;
#endif

void FileBrowser::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZListBox::className(), "ZListBox") != 0 )
	badSuperclassWarning("FileBrowser","ZListBox");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString FileBrowser::tr(const char* s)
{
    return qApp->translate( "FileBrowser", s, 0 );
}

QString FileBrowser::tr(const char* s, const char * c)
{
    return qApp->translate( "FileBrowser", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* FileBrowser::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZListBox::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (FileBrowser::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    typedef void (FileBrowser::*m1_t1)(int);
    typedef void (QObject::*om1_t1)(int);
    typedef void (FileBrowser::*m1_t2)(ZListBoxItem*);
    typedef void (QObject::*om1_t2)(ZListBoxItem*);
    m1_t0 v1_0 = &FileBrowser::itemHighlighted;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &FileBrowser::itemSelected;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &FileBrowser::itemClicked;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "itemHighlighted(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "itemSelected(int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "itemClicked(ZListBoxItem*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    typedef void (FileBrowser::*m2_t0)(const QString&);
    typedef void (QObject::*om2_t0)(const QString&);
    typedef void (FileBrowser::*m2_t1)(bool);
    typedef void (QObject::*om2_t1)(bool);
    m2_t0 v2_0 = &FileBrowser::picked;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &FileBrowser::isFilePicked;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "picked(const QString&)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "isFilePicked(bool)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"FileBrowser", "ZListBox",
	slot_tbl, 3,
	signal_tbl, 2,
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

// SIGNAL picked
void FileBrowser::picked( const QString& t0 )
{
    activate_signal_strref( "picked(const QString&)", t0 );
}

// SIGNAL isFilePicked
void FileBrowser::isFilePicked( bool t0 )
{
    activate_signal_bool( "isFilePicked(bool)", t0 );
}

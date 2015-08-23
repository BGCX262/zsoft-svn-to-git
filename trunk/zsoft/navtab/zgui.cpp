#include "zgui.h"
#include <ZConfig.h>
//#include "GUI_Define.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <qpixmap.h>
#include <string.h>
#include <ZOptionsMenu.h>
#include <ZApplication.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <qtextcodec.h>
#include <ezxres.h>

//#define Z6KEY_RED               0x1030


//using namespace std;

QTextCodec* txtcodec = QTextCodec::codecForName("UTF-8");
RES_ICON_Reader iconReader;
QString unicode;

ZGui::ZGui ( const QString &argument, QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{
	
	ProgDir = getProgramDir();
	QString folder = argument;
	if ( folder != "" ) { ProgDir = folder; }

	CreateWindow ( parent );
	( ( ZApplication* ) qApp )->showMainWidget ( this );
	
}

ZGui::~ZGui()
{
}


void ZGui::CreateWindow ( QWidget* parent )
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	int tabs = ini.readNumEntry(QString("MAIN"), QString("Tabs"), 2);
	unicode = ini.readEntry(QString("SETTINGS"), QString("Unicode"), "");
	QString val;

	if ( tabs > 0 ) { tabWidget = new ZNavTabWidget(ZNavTabWidget::SEPARATE, false, false, this); }


	zllb1 = new ZListBox ( QString ( "%I%M" ), this, 0); zllb1->setFixedWidth ( 240 ); CargarMenu1();
	connect(zllb1, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked1()));
	if ( tabs > 1 ) {
		zllb2 = new ZListBox ( QString ( "%I%M" ), this, 0); zllb2->setFixedWidth ( 240 ); CargarMenu2();
		connect(zllb2, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked2()));
	}
	if ( tabs > 2 ) {
		zllb3 = new ZListBox ( QString ( "%I%M" ), this, 0); zllb3->setFixedWidth ( 240 ); CargarMenu3();
		connect(zllb3, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked3()));
	}
	if ( tabs > 3 ) {
		zllb4 = new ZListBox ( QString ( "%I%M" ), this, 0); zllb4->setFixedWidth ( 240 ); CargarMenu4();
		connect(zllb4, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked4()));
	}
	if ( tabs > 4 ) {
		zllb5 = new ZListBox ( QString ( "%I%M" ), this, 0); zllb5->setFixedWidth ( 240 ); CargarMenu5();
		connect(zllb5, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked5()));
	}

	QPixmap p1; 
	if ( tabs > 0 ) { val = ini.readEntry(QString("NAVTAB"), QString("Tab1"), "");
		p1.load(ProgDir + "/" + val); tabWidget->addTab(zllb1, QIconSet(p1), ""); }
	if ( tabs > 1 ) { val = ini.readEntry(QString("NAVTAB"), QString("Tab2"), "");
		p1.load(ProgDir + "/" + val); tabWidget->addTab(zllb2, QIconSet(p1), ""); }
	if ( tabs > 2 ) { val = ini.readEntry(QString("NAVTAB"), QString("Tab3"), "");
		p1.load(ProgDir + "/" + val); tabWidget->addTab(zllb3, QIconSet(p1), ""); }
	if ( tabs > 3 ) { val = ini.readEntry(QString("NAVTAB"), QString("Tab4"), "");
		p1.load(ProgDir + "/" + val); tabWidget->addTab(zllb4, QIconSet(p1), ""); }
	if ( tabs > 4 ) { val = ini.readEntry(QString("NAVTAB"), QString("Tab5"), "");
		p1.load(ProgDir + "/" + val); tabWidget->addTab(zllb5, QIconSet(p1), ""); }

	val = ini.readEntry(QString("MAIN"), QString("Title"), "");
    setMainWidgetTitle ( texto(val) );

	if ( tabs < 1 ) { setContentWidget ( zllb1 ); }
	else { setContentWidget ( tabWidget ); }

	softKey = new ZSoftKey ( NULL , this , this );
	Create_MenuApp();
	Create_SoftKey();
	setSoftKey ( softKey );

	zllb1->setFocus();

}

QString ZGui::getProgramDir()
{
  ProgDir = QString ( qApp->argv() [0] ) ;
  int i = ProgDir.findRev ( "/" );
  ProgDir.remove ( i+1, ProgDir.length() - i );
  return ProgDir;
}

QString ZGui::texto(const char*xString)
{
	if ( unicode == "1" ) { return txtcodec->toUnicode(xString); }
	else { return xString; }
}

void ZGui::CargarMenu1()
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);

	int num=1;
	int cant = ini.readNumEntry(QString("LIST1"), QString("Items"), 2);
	for ( int j=0; j<cant; ++j )
	{
		QPixmap p1;
		ZListBoxItem* listitem1 = new ZListBoxItem ( zllb1, QString ( "%I%M" ) );
		QString val = ini.readEntry(QString("LIST1"), QString("Icon%1").arg(num), "");
		if ( val[0] == QChar('!') ) { val.remove(0,1); 
			p1=QPixmap(iconReader.getIcon(val, false)); }
		else { if ( val[0] == QChar('/') ) { p1.load(val); }
			else { p1.load(ProgDir + "/" + val); } }
		int xi = ini.readNumEntry(QString("SETTINGS"), QString("SysIconSize"), 5);
		if ( xi > 0 ) { 
		  if ( p1.height() > xi ) { QImage image; image = p1.convertToImage(); 
		  image = image.smoothScale(xi, xi); p1.convertFromImage(image); } 
		}
		listitem1->setPixmap ( 0, p1 );
		val = ini.readEntry(QString("LIST1"), QString("Option%1").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		val = ini.readEntry(QString("LIST1"), QString("Option%1b").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		zllb1->insertItem ( listitem1,-1,true );
		++num;
	} 	
}

void ZGui::CargarMenu2()
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);

	int num=1;
	int cant = ini.readNumEntry(QString("LIST2"), QString("Items"), 2);
	for ( int j=0; j<cant; ++j )
	{
		QPixmap p1;
		ZListBoxItem* listitem1 = new ZListBoxItem ( zllb2, QString ( "%I%M" ) );
		QString val = ini.readEntry(QString("LIST2"), QString("Icon%1").arg(num), "");
		if ( val[0] == QChar('!') ) { val.remove(0,1); 
			p1=QPixmap(iconReader.getIcon(val, false)); }
		else { if ( val[0] == QChar('/') ) { p1.load(val); }
			else { p1.load(ProgDir + "/" + val); } }
		int xi = ini.readNumEntry(QString("SETTINGS"), QString("SysIconSize"), 5);
		if ( xi > 0 ) { 
		  if ( p1.height() > xi ) { QImage image; image = p1.convertToImage(); 
		  image = image.smoothScale(xi, xi); p1.convertFromImage(image); } 
		}
		listitem1->setPixmap ( 0, p1 );
		val = ini.readEntry(QString("LIST2"), QString("Option%1").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		val = ini.readEntry(QString("LIST2"), QString("Option%1b").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		zllb2->insertItem ( listitem1,-1,true );
		++num;
 	}
}

void ZGui::CargarMenu3()
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);

	int num=1;
	int cant = ini.readNumEntry(QString("LIST3"), QString("Items"), 2);
	for ( int j=0; j<cant; ++j )
	{
		QPixmap p1;
		ZListBoxItem* listitem1 = new ZListBoxItem ( zllb3, QString ( "%I%M" ) );
		QString val = ini.readEntry(QString("LIST3"), QString("Icon%1").arg(num), "");
		if ( val[0] == QChar('!') ) { val.remove(0,1); 
			p1=QPixmap(iconReader.getIcon(val, false)); }
		else { if ( val[0] == QChar('/') ) { p1.load(val); }
			else { p1.load(ProgDir + "/" + val); } }
		int xi = ini.readNumEntry(QString("SETTINGS"), QString("SysIconSize"), 5);
		if ( xi > 0 ) { 
		  if ( p1.height() > xi ) { QImage image; image = p1.convertToImage(); 
		  image = image.smoothScale(xi, xi); p1.convertFromImage(image); } 
		}
		listitem1->setPixmap ( 0, p1 );
		val = ini.readEntry(QString("LIST3"), QString("Option%1").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		val = ini.readEntry(QString("LIST3"), QString("Option%1b").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		zllb3->insertItem ( listitem1,-1,true );
		++num;
 	}
}

void ZGui::CargarMenu4()
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);

	int num=1;
	int cant = ini.readNumEntry(QString("LIST4"), QString("Items"), 2);
	for ( int j=0; j<cant; ++j )
	{
		QPixmap p1;
		ZListBoxItem* listitem1 = new ZListBoxItem ( zllb4, QString ( "%I%M" ) );
		QString val = ini.readEntry(QString("LIST4"), QString("Icon%1").arg(num), "");
		if ( val[0] == QChar('!') ) { val.remove(0,1); 
			p1=QPixmap(iconReader.getIcon(val, false)); }
		else { if ( val[0] == QChar('/') ) { p1.load(val); }
			else { p1.load(ProgDir + "/" + val); } }
		int xi = ini.readNumEntry(QString("SETTINGS"), QString("SysIconSize"), 5);
		if ( xi > 0 ) { 
		  if ( p1.height() > xi ) { QImage image; image = p1.convertToImage(); 
		  image = image.smoothScale(xi, xi); p1.convertFromImage(image); } 
		}
		listitem1->setPixmap ( 0, p1 );
		val = ini.readEntry(QString("LIST4"), QString("Option%1").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		val = ini.readEntry(QString("LIST4"), QString("Option%1b").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		zllb4->insertItem ( listitem1,-1,true );
		++num;
 	}
}

void ZGui::CargarMenu5()
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);

	int num=1;
	int cant = ini.readNumEntry(QString("LIST5"), QString("Items"), 2);
	for ( int j=0; j<cant; ++j )
	{
		QPixmap p1;
		ZListBoxItem* listitem1 = new ZListBoxItem ( zllb5, QString ( "%I%M" ) );
		QString val = ini.readEntry(QString("LIST5"), QString("Icon%1").arg(num), "");
		if ( val[0] == QChar('!') ) { val.remove(0,1); 
			p1=QPixmap(iconReader.getIcon(val, false)); }
		else { if ( val[0] == QChar('/') ) { p1.load(val); }
			else { p1.load(ProgDir + "/" + val); } }
		int xi = ini.readNumEntry(QString("SETTINGS"), QString("SysIconSize"), 5);
		if ( xi > 0 ) { 
		  if ( p1.height() > xi ) { QImage image; image = p1.convertToImage(); 
		  image = image.smoothScale(xi, xi); p1.convertFromImage(image); } 
		}
		listitem1->setPixmap ( 0, p1 );
		val = ini.readEntry(QString("LIST5"), QString("Option%1").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		val = ini.readEntry(QString("LIST5"), QString("Option%1b").arg(num), "");
		listitem1->appendSubItem ( 1, texto(val), true, NULL );
		zllb5->insertItem ( listitem1,-1,true );
		++num;
 	}
}

void ZGui::Create_MenuApp()
{

	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	QString IDval;QRect rect;

	QPixmap* pm  = new QPixmap();
	int idx = 0;
	menu = new ZOptionsMenu ( rect, softKey, NULL, 0);
	menu->setItemSpacing(10);  

	int num = 1; QString fin = "NO";
	QString val = ini.readEntry(QString("MENU"), QString("Item%1").arg(num), "");
	while ( fin != "SI" )
	{
		QString val = ini.readEntry(QString("MENU"), QString("Icon%1").arg(num), "");
		pm->load(ProgDir + "/" + val);
		val = ini.readEntry(QString("MENU"), QString("Item%1").arg(num), "");
		menu->insertItem ( texto(val), NULL, pm, true, idx, idx );
		menu->connectItem ( idx, this, SLOT ( MenuClick() ) );
		++idx; num++;
		val = ini.readEntry(QString("MENU"), QString("Item%1").arg(num), "");
		if ( val == "" ) { fin = "SI"; }
	}

}

void ZGui::Create_SoftKey()
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	QString val = ini.readEntry(QString("MAIN"), QString("Soft1"), "");
	softKey->setOptMenu ( ZSoftKey::LEFT, menu ); 
	softKey->setText ( ZSoftKey::LEFT, texto(val), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	val = ini.readEntry(QString("MAIN"), QString("Soft1"), "");
	softKey->setTextForOptMenuHide(texto(val));
	val = ini.readEntry(QString("MAIN"), QString("Soft1s"), "");
	QString val2 = ini.readEntry(QString("MAIN"), QString("Soft2s"), "");
	softKey->setTextForOptMenuShow(texto(val), texto(val2));
	val = ini.readEntry(QString("MAIN"), QString("Soft2"), "");
	softKey->setText ( ZSoftKey::RIGHT, texto(val), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, qApp, SLOT ( quit() ) );
}

void ZGui::MenuClick()
{
	qApp->processEvents();
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	QString val = ini.readEntry(QString("MENU"), QString("Exec%1").arg(menu->getActiveItemId()+1), "");
	if ( val == "quit" ) { qApp->quit(); }
	system(QString("%1/%2").arg(ProgDir).arg(val));

}

void ZGui::appClicked1()
{
  qApp->processEvents();
  int index = zllb1->currentItem();
  if (index == -1) {return;}
  int result = index+1;

  ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
  QString val = ini.readEntry(QString("LIST1"), QString("Exec%1").arg(result), "");
  if ( val == "quit" ) { qApp->quit(); }
  if ( val[0] == QChar('!') ) { val.remove(0,1); system(QString("%1").arg(val)); }
  else { system(QString("%1/%2").arg(ProgDir).arg(val)); }
  val = ini.readEntry(QString("SETTINGS"), QString("Refresh"), "");
  if ( val = "YES" ) { zllb1->clear(); CargarMenu1(); zllb1->setCurrentItem(index,true); }

}

void ZGui::appClicked2()
{
  qApp->processEvents();
  int index = zllb2->currentItem();
  if (index == -1) {return;}
  int result = index+1;

  ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
  QString val = ini.readEntry(QString("LIST2"), QString("Exec%1").arg(result), "");
  if ( val == "quit" ) { qApp->quit(); }
  if ( val[0] == QChar('!') ) { val.remove(0,1); system(QString("%1").arg(val)); }
  else { system(QString("%1/%2").arg(ProgDir).arg(val)); }
  val = ini.readEntry(QString("SETTINGS"), QString("Refresh"), "");
  if ( val = "YES" ) { zllb2->clear(); CargarMenu2(); zllb2->setCurrentItem(index,true); }

}

void ZGui::appClicked3()
{
  qApp->processEvents();
  int index = zllb3->currentItem();
  if (index == -1) {return;}
  int result = index+1;

  ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
  QString val = ini.readEntry(QString("LIST3"), QString("Exec%1").arg(result), "");
  if ( val == "quit" ) { qApp->quit(); }
  if ( val[0] == QChar('!') ) { val.remove(0,1); system(QString("%1").arg(val)); }
  else { system(QString("%1/%2").arg(ProgDir).arg(val)); }
  val = ini.readEntry(QString("SETTINGS"), QString("Refresh"), "");
  if ( val = "YES" ) { zllb3->clear(); CargarMenu3(); zllb3->setCurrentItem(index,true); }

}

void ZGui::appClicked4()
{
  qApp->processEvents();
  int index = zllb4->currentItem();
  if (index == -1) {return;}
  int result = index+1;

  ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
  QString val = ini.readEntry(QString("LIST4"), QString("Exec%1").arg(result), "");
  if ( val == "quit" ) { qApp->quit(); }
  if ( val[0] == QChar('!') ) { val.remove(0,1); system(QString("%1").arg(val)); }
  else { system(QString("%1/%2").arg(ProgDir).arg(val)); }
  val = ini.readEntry(QString("SETTINGS"), QString("Refresh"), "");
  if ( val = "YES" ) { zllb4->clear(); CargarMenu4(); zllb4->setCurrentItem(index,true); }

}

void ZGui::appClicked5()
{
  qApp->processEvents();
  int index = zllb5->currentItem();
  if (index == -1) {return;}
  int result = index+1;

  ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
  QString val = ini.readEntry(QString("LIST5"), QString("Exec%1").arg(result), "");
  if ( val == "quit" ) { qApp->quit(); }
  if ( val[0] == QChar('!') ) { val.remove(0,1); system(QString("%1").arg(val)); }
  else { system(QString("%1/%2").arg(ProgDir).arg(val)); }
  val = ini.readEntry(QString("SETTINGS"), QString("Refresh"), "");
  if ( val = "YES" ) { zllb5->clear(); CargarMenu5(); zllb5->setCurrentItem(index,true); }

}



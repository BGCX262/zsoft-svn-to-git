#include "zgui.h"
#include "GUI_Define.h"
#include "BaseDlg.h"
#include "ZAboutDlg.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qfile.h>
#include <qdir.h>
#include <string.h>
#include <qtextstream.h>
#include <qvector.h>

#include <ZApplication.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>
#include <ZMessageDlg.h>
#include <ZMultiSelectDlg.h>
#include <ZSingleSelectDlg.h>

#include "ZConfig.h"
#include <qtextcodec.h>
#include <ezxres.h>

#define APPTITLE "zPhoneFirewall"


//using namespace std;

ZGui::ZGui ( const QString &Impkg, QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{

  ProgDir = getProgramDir();
  QString val; ZConfig ini(QString("%1/zPhoneFirewall.cfg").arg(ProgDir), false);
  val = ini.readEntry(QString("zPhoneFirewall"), QString("Language"), "");
  Idioma = ProgDir + "/languages/" + val;

  system(QString("rm /ezxlocal/download/mystuff/blacklist"));
  system(QString("rm /ezxlocal/download/mystuff/zPhoneFirewall.cfg"));
  system(QString("cp %1blacklist /ezxlocal/download/mystuff/.blacklist").arg(ProgDir));
  system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));

  CreateWindow ( parent );
  ( ( ZApplication* ) qApp )->showMainWidget ( this );

}

ZGui::~ZGui()
{
}


void ZGui::CreateWindow ( QWidget* parent )
{
  setMainWidgetTitle ( APPTITLE );

  tabWidget = new ZNavTabWidget(ZNavTabWidget::SEPARATE, false, false, this);

  mainList = new ZListBox ( QString ( "%I%M%I" ), this, 0);
  mainList->setFixedWidth ( 240 );

  blackList = new ZListBox ( QString ( "%I%M" ), this, 0);
  blackList->setFixedWidth ( 240 );  

  whiteList = new ZListBox ( QString ( "%I%M" ), this, 0);
  whiteList->setFixedWidth ( 240 );  

  regCalls = new ZListBox ( QString ( "%I%M" ), this, 0);
  regCalls->setFixedWidth ( 240 );  

  QPixmap p1, p2, p3, p4;
  p1.load(ProgDir + "/images/settings.png");
  p2.load(ProgDir + "/images/black.png");
  p3.load(ProgDir + "/images/white.png");
  p3.load(ProgDir + "/images/white.png");
  p4.load(ProgDir + "/images/reg.png");
  
  tabWidget->addTab(mainList, QIconSet(p1), "");
  tabWidget->addTab(blackList, QIconSet(p2), "");
  tabWidget->addTab(whiteList, QIconSet(p3), "");
  tabWidget->addTab(regCalls, QIconSet(p4), "");

  CargarMain();
  connect(mainList, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked(ZListBoxItem *)));

  CargarBlacklist();
  connect(blackList, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked(ZListBoxItem *))); 

  CargarWhitelist();
  connect(whiteList, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked(ZListBoxItem *)));

  CargarLlamadas();
  connect(regCalls, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked(ZListBoxItem *)));

  setContentWidget ( tabWidget );
  softKey = new ZSoftKey ( NULL , this , this );

  Create_MenuApp();

  connect(tabWidget,SIGNAL(currentChanged(QWidget* )),this,SLOT(slotCurrentChanged(QWidget* )));
  
  Create_SoftKey();
  setSoftKey ( softKey );

}

QString ZGui::getProgramDir()
{
  ProgDir = QString ( qApp->argv() [0] ) ;
  int i = ProgDir.findRev ( "/" );
  ProgDir.remove ( i+1, ProgDir.length() - i );
  return ProgDir;
}


void ZGui::about()
{
  ZAboutDialog* aboutDlg = new ZAboutDialog();
  aboutDlg->exec();
  delete aboutDlg;
  aboutDlg = NULL;
}


void ZGui::slotCurrentChanged(QWidget* AWidget)
{
  softKey->setOptMenu ( ZSoftKey::LEFT, NULL );
  int i = tabWidget->currentPageIndex();
  switch (i)
  {
    case 0:
    {
      Create_MenuApp();
      softKey->setOptMenu ( ZSoftKey::LEFT, menu );
      break; 
    }
    case 1:
    {
      Create_MenuBlack();
      softKey->setOptMenu ( ZSoftKey::LEFT, menu );
      break; 
    }
    case 2:
    {
      Create_MenuWhite();
      softKey->setOptMenu ( ZSoftKey::LEFT, menu );
      break; 
    }     
    case 3:
    {
      Create_MenuCalls();
      softKey->setOptMenu ( ZSoftKey::LEFT, menu );
      break; 
    }     
  }
}
    
void ZGui::Create_SoftKey()
{
  QString IDval; QString IDval2; ZConfig IDini(Idioma, false);
  softKey->setOptMenu ( ZSoftKey::LEFT, menu ); 
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_MENU"), "");
  softKey->setText ( ZSoftKey::LEFT, IDval, ( ZSoftKey::TEXT_PRIORITY ) 0 );
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_MENU"), "");
  softKey->setTextForOptMenuHide(IDval);
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_SELECT"), "");
  IDval2 = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_CANCEL"), "");
  softKey->setTextForOptMenuShow(IDval, IDval2);
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_EXIT"), "");
  softKey->setText ( ZSoftKey::RIGHT, IDval, ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot ( ZSoftKey::RIGHT, qApp, SLOT ( quit() ) );      
}

void ZGui::Create_MenuApp()
{
  QString IDval; ZConfig IDini(Idioma, false);
  QRect rect;
  QPixmap* pm  = new QPixmap();
  int idx = 0;
  menu = new ZOptionsMenu ( rect, softKey, NULL, 0);
  menu->setItemSpacing(10);  
  pm->load(ProgDir + "images/lang.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_LANG"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( language() ) );
  ++idx;
  menu->insertSeparator(idx, idx); 
  ++idx;  pm->load(ProgDir + "images/about.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_ABOUT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( about() ) );      
  ++idx;
  pm->load(ProgDir + "images/exit.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_EXIT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, qApp, SLOT ( quit() ) );
}

void ZGui::Create_MenuBlack()
{
  QRect rect; QString IDval; ZConfig IDini(Idioma, false);
  QPixmap* pm  = new QPixmap();
  int idx = 0;
  menu = new ZOptionsMenu ( rect, softKey, NULL, 0);
  menu->setItemSpacing(10);  
  pm->load(ProgDir + "images/add.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_ADD"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( addNumber1() ) );
  ++idx;
  pm->load(ProgDir + "images/remove.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_DELETE"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( removeNumber1() ) );
  ++idx;
  menu->insertSeparator(idx, idx); 
  ++idx;
  pm->load(ProgDir + "images/about.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_ABOUT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( about() ) );      
  ++idx;
  pm->load(ProgDir + "images/exit.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_EXIT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, qApp, SLOT ( quit() ) );
}

void ZGui::Create_MenuWhite()
{
  QRect rect; QString IDval; ZConfig IDini(Idioma, false);
  QPixmap* pm  = new QPixmap();
  int idx = 0;
  menu = new ZOptionsMenu ( rect, softKey, NULL, 0);
  menu->setItemSpacing(10);  
  pm->load(ProgDir + "images/add.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_ADD"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( addNumber2() ) );
  ++idx;
  pm->load(ProgDir + "images/remove.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_DELETE"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( removeNumber2() ) );
  ++idx;
  menu->insertSeparator(idx, idx); 
  ++idx;
  pm->load(ProgDir + "images/about.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_ABOUT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( about() ) );      
  ++idx;
  pm->load(ProgDir + "images/exit.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_EXIT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, qApp, SLOT ( quit() ) );
}

void ZGui::Create_MenuCalls()
{
  QRect rect; QString IDval; ZConfig IDini(Idioma, false);
  QPixmap* pm  = new QPixmap();
  int idx = 0;
  menu = new ZOptionsMenu ( rect, softKey, NULL, 0);
  menu->setItemSpacing(10);  
  pm->load(ProgDir + "images/remove.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_DELETE"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( removeCall() ) );
  ++idx;
  menu->insertSeparator(idx, idx); 
  ++idx;
  pm->load(ProgDir + "images/about.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_ABOUT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( about() ) );      
  ++idx;
  pm->load(ProgDir + "images/exit.png");
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_EXIT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, qApp, SLOT ( quit() ) );
}

void ZGui::CargarMain()
{
  QPixmap p1; ZConfig IDini(Idioma, false);
  QString s1 = "";
  QString IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("OPTIONS_ENABLED"), ""); QString IDena=IDval;
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("OPTIONS_DISABLED"), ""); QString IDdis=IDval;

  ZListBoxItem* listitem1 = new ZListBoxItem ( mainList, QString ( "%I%M" ) );
  p1.load(ProgDir + "/images/power.png");
  listitem1->setPixmap ( 0, p1 );
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_STATE"), "");
  listitem1->appendSubItem ( 1, IDval, true, NULL );
  system(QString("rm %1/state").arg(ProgDir));
  system(QString("touch %1/state").arg(ProgDir));
  system(QString("ps | awk '{print $5}' | sed -n -e '/.blacklist/p' >> %1/state").arg(ProgDir));
  QString card2 = QString("%1/state").arg(ProgDir);
  QString line2=""; int encontro = -1;
  QFile entrada2(card2);
  QTextStream stentrada2(&entrada2);
  if ( entrada2.open(IO_ReadOnly | IO_Translate) )
  {
	line2 = stentrada2.readLine();
	encontro=line2.find(QString("/ezxlocal/download/mystuff/.blacklist"),0);
	if ( encontro >= 0 )
	{
	  listitem1->appendSubItem ( 1, IDena, true, NULL ); 
	  Potencia = "ON";
	}
	else
	{
	  listitem1->appendSubItem ( 1, IDdis, true, NULL ); 
	  Potencia = "OFF";
	}
  }
  entrada2.close();
  system(QString("rm %1/state").arg(ProgDir));
  mainList->insertItem ( listitem1,-1,true );

  ZListBoxItem* listitem2 = new ZListBoxItem ( mainList, QString ( "%I%M" ) );
  p1.load(ProgDir + "/images/list.png");
  listitem2->setPixmap ( 0, p1 );
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_LIST"), "");
  listitem2->appendSubItem ( 1, IDval, true, NULL );
  QString file2 = QString("%1/zPhoneFirewall.cfg").arg(ProgDir); ZConfig IDini3(file2, false);
  QString IDval3 = IDini3.readEntry(QString("zPhoneFirewall"), QString("Firewall"), "");
  if ( IDval3 == "Blacklist" )
  {
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_BLACK"), "");
	listitem2->appendSubItem ( 1, IDval, true, NULL );
  }
  else
  {
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_WHITE"), "");
	listitem2->appendSubItem ( 1, IDval, true, NULL );
  }
  mainList->insertItem ( listitem2,-1,true );

  ZListBoxItem* listitem3 = new ZListBoxItem ( mainList, QString ( "%I%M" ) );
  p1.load(ProgDir + "/images/number.png");
  listitem3->setPixmap ( 0, p1 );
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_UNKNOWN"), "");
  listitem3->appendSubItem ( 1, IDval, true, NULL );
  QString file1 = QString("%1/zPhoneFirewall.cfg").arg(ProgDir); ZConfig IDini2(file1, false);
  QString IDval2 = IDini2.readEntry(QString("zPhoneFirewall"), QString("BlockUnknown"), "");
  if ( IDval2 == "Yes" ) { listitem3->appendSubItem ( 1, IDena, true, NULL ); }
  else { listitem3->appendSubItem ( 1, IDdis, true, NULL ); }
  mainList->insertItem ( listitem3,-1,true );



}

void ZGui::CargarBlacklist()
{

	ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), false );
	QStringList list = blacklist.readListEntry ( QString("Blacklist"), QString("Num"), QChar(';') );
	QPixmap p1;
	for (int j=0;j<list.count();++j)
	{
	  ZListBoxItem* eitem = new ZListBoxItem ( blackList, QString ( "%I%M" ) );
	  p1.load(ProgDir + "/images/number.png");
	  eitem->setPixmap ( 0, p1 );
	  eitem->appendSubItem ( 1, list[j], true, NULL );
	  blackList->insertItem ( eitem, -1, true );
	}

}

void ZGui::CargarWhitelist()
{

	ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), false );
	QStringList list = blacklist.readListEntry ( QString("Whitelist"), QString("Num"), QChar(';') );
	QPixmap p1;
	for (int j=0;j<list.count();++j)
	{
	  ZListBoxItem* eitem = new ZListBoxItem ( whiteList, QString ( "%I%M" ) );
	  p1.load(ProgDir + "/images/number.png");
	  eitem->setPixmap ( 0, p1 );
	  eitem->appendSubItem ( 1, list[j], true, NULL );
	  whiteList->insertItem ( eitem, -1, true );
	}

}

void ZGui::CargarLlamadas()
{
  QPixmap p1;
  QString Uval; ZConfig Uini(Idioma, false);
  Uval = Uini.readEntry(QString("ZPHONEFIREWALL"), QString("UNKNOWN_NUMBER"), "");
  QString autorun = QString("/ezxlocal/download/mystuff/.blockedcalls");
  QString line="";
  QFile entrada(autorun);
  QTextStream stentrada(&entrada);
  if ( entrada.open(IO_ReadOnly | IO_Translate) )
  {
	while ( !stentrada.eof() )
	{
	  line = stentrada.readLine();
	  if ( line != "" )
	  {
		ZListBoxItem* eitem = new ZListBoxItem ( whiteList, QString ( "%I%M" ) );
		p1.load(ProgDir + "/images/number.png");
		eitem->setPixmap ( 0, p1 );
		if ( line == "unknown" ) { eitem->appendSubItem ( 1, Uval, true, NULL ); }
		else { eitem->appendSubItem ( 1, line, true, NULL ); }
		line = stentrada.readLine();
		eitem->appendSubItem ( 1, line, true, NULL );
		regCalls->insertItem ( eitem, -1, true );
	  }
	}
  }

}

void ZGui::salir()
{

 	ZMessageDlg* msg =  new ZMessageDlg ( QString::fromUtf8(APPTITLE),
	QString::fromUtf8("Desea salir?\nRecuerde que algunos cambios no tendran efecto hasta reiniciar."),
        ZMessageDlg::yes_no, 0, NULL, "ZMessageDlg", true, 0 );
	int i = msg->exec();
	delete msg;
	msg = NULL;
	if (i)
	{
	  qApp->quit();
	}
		
}

void ZGui::appClicked(ZListBoxItem *item)
{
  QString a = "";
  a = item->getSubItemText(1, 0, false);
  
  QString IDval; ZConfig IDini(Idioma, false);
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_STATE"), "");
  if ( a == IDval ) { ChangeState(); }
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_LIST"), "");
  if ( a == IDval ) { ChangeList(); }
  IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_UNKNOWN"), "");
  if ( a == IDval ) { blockUnk(); }


}


void ZGui::language()
{

  QString val; ZConfig ini(Idioma, false);
  val = ini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_LANGUAGE"), "");

  ZSingleSelectDlg* eq1 =  new ZSingleSelectDlg(val, QString(""), NULL, "ZSingleSelectDlg", true, 0, 0);
  system(QString("ls %1/languages/ > %2/ltemp").arg(ProgDir).arg(ProgDir));	

  QString card = QString("%1/ltemp").arg(ProgDir);
  QString line="";
  int cantl=0;  
  QStringList list;
  QFile entrada(card);
  QTextStream stentrada(&entrada);
  QString aux="";
  cantl=0;
  if ( entrada.open(IO_ReadOnly | IO_Translate) )
  {
	while ( !stentrada.eof() )
    {           
          line = stentrada.readLine();
		  ZConfig IDini(QString("%1/languages/%2").arg(ProgDir).arg(line), false);
		  QString val = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("LANG_NAME"), "");
          cantl++;
          aux=val;
		  list +=val;
    }
  }
  entrada.close();

  eq1->addItemsList(list);
  ZListBox* listboxx = eq1->getListBox();
  int checked = -1;
  if (checked >= 0)
 	listboxx->checkItem(checked, true);
	eq1->exec();
	int result = eq1->result();
	if (result != 1) {
		result = 0;
	} else {
		result = eq1->getCheckedItemIndex();

		QString card2 = QString("%1/ltemp").arg(ProgDir);
		QString line2="";
		int cantl2=0;  
		QStringList list2;
		QFile entrada2(card2);
		QTextStream stentrada2(&entrada2);
		QString aux2="";
		cantl2=0;
		if ( entrada2.open(IO_ReadOnly | IO_Translate) )
		{
		while ( !stentrada2.eof() )
		{           
		  line2 = stentrada2.readLine();
		  if ( result == cantl2 )
		  {
			Idioma = ProgDir + "/languages/" + line2;
			
			ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
			blacklist.writeEntry(QString("zPhoneFirewall"), QString("Language"), line2);
			qApp->processEvents();

		  Create_MenuApp();
		  Create_SoftKey();
		  while (mainList->count() != 0) { mainList->removeItem(0); } CargarMain();
		  while (blackList->count() != 0) { blackList->removeItem(0); } CargarBlacklist();
		  while (whiteList->count() != 0) { whiteList->removeItem(0); } CargarWhitelist();

		  }
		  cantl2++;
		  aux2=line2;
		  list2 +=aux2;
		}
		entrada.close();		
	}
  }
  system(QString("rm %1/ltemp").arg(ProgDir));
}

QString ZGui::getFileName(const QString &AFileName)
{
  QString str = AFileName;
  int i = str.findRev ( "/" );
  str.remove ( 0, i);
  if (str.left(1) = "/") str.remove ( 0, 1);
  return str;    
}

void ZGui::ChangeState()
{
    ZConfig IDini(Idioma, false);
	QString IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_STATE"), "");
	ZSingleSelectDlg* eq =  new ZSingleSelectDlg(IDval, QString(""), NULL, "ZSingleSelectDlg", true, 0, 0);
	QStringList list2;
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("OPTIONS_ENABLE"), "");
	list2 = IDval;
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("OPTIONS_DISABLE"), "");
	list2 += IDval;
	eq->addItemsList(list2);
	ZListBox* listboxx2 = eq->getListBox();
	int checked = -1;
	if (checked >= 0)
	    listboxx2->checkItem(checked, true);
	eq->exec();
	int result = eq->result();
	if (result != 1) {
		result = 0;
	} else {
	  result = eq->getCheckedItemIndex();
	  if (listboxx2->itemChecked(1))
	  {
		system("busybox killall .blacklist");
		//system("rm /ezxlocal/download/mystuff/blacklist");
		//system(QString("rm /ezxlocal/download/mystuff/zPhoneFirewall.cfg").arg(ProgDir));
		while (mainList->count() != 0) { mainList->removeItem(0); } CargarMain();
	  }
	  if (listboxx2->itemChecked(0))
	  {		
		system(QString("cp %1blacklist /ezxlocal/download/mystuff/.blacklist").arg(ProgDir));
		system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
		system("exec /ezxlocal/download/mystuff/.blacklist&");
		while (mainList->count() != 0) { mainList->removeItem(0); } CargarMain();
	  }
	}
}

void ZGui::ChangeList()
{
    ZConfig IDini(Idioma, false);
	QString IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_LIST"), "");
	ZSingleSelectDlg* eq =  new ZSingleSelectDlg(IDval, QString(""), NULL, "ZSingleSelectDlg", true, 0, 0);
	QStringList list2;
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_BLACK"), "");
	list2 = IDval;
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_WHITE"), "");
	list2 += IDval;
	eq->addItemsList(list2);
	ZListBox* listboxx2 = eq->getListBox();
	int checked = -1;
	if (checked >= 0)
	    listboxx2->checkItem(checked, true);
	eq->exec();
	int result = eq->result();
	if (result != 1) {
		result = 0;
	} else {
	  result = eq->getCheckedItemIndex();
	  if (listboxx2->itemChecked(1))
	  {
		ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
		blacklist.writeEntry(QString("zPhoneFirewall"), QString("Firewall"),  QString("Whitelist"));
		qApp->processEvents();
		if ( Potencia == "ON" )
		{
			system("busybox killall .blacklist");
 			system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
			system("exec /ezxlocal/download/mystuff/.blacklist&");
		}
		while (mainList->count() != 0) { mainList->removeItem(0); } CargarMain();

	  }
	  if (listboxx2->itemChecked(0))
	  {		
		ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
		blacklist.writeEntry(QString("zPhoneFirewall"), QString("Firewall"),  QString("Blacklist"));
		qApp->processEvents();
		if ( Potencia == "ON" )
		{
			system("busybox killall .blacklist");
 			system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
			system("exec /ezxlocal/download/mystuff/.blacklist&");
		}
		while (mainList->count() != 0) { mainList->removeItem(0); } CargarMain();
	  }
	}
}

void ZGui::addNumber1()
{

  ZConfig IDini(Idioma, false);
  QString IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_ADD"), "");
  QString fName; QString lista2;

  ZSingleCaptureDlg* zscd = new ZSingleCaptureDlg(QString::fromUtf8(IDval), 
      QString::fromUtf8(IDval), ZSingleCaptureDlg::normal, NULL, "ZSingleCaptureDlg", true, 0, 0);
  ZLineEdit* zle = (ZLineEdit*)zscd->getLineEdit();  
  zle->setText(fName);
  zle->setEdited(true);  
  
  if (zscd->exec() == 1)
  {
    fName = zle->text();
	ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
	QStringList list = blacklist.readListEntry ( QString("Blacklist"), QString("Num"), QChar(';') );
	for (int j=0;j<list.count();++j)
	{
		lista2 += QString("%1").arg(list[j]) + QChar(';');
	}
	lista2 += fName;
	blacklist.writeEntry(QString("Blacklist"), QString("Num"), lista2);
	qApp->processEvents();

	if ( Potencia == "ON" )
	{
		system("busybox killall .blacklist");
 		system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
		system("exec /ezxlocal/download/mystuff/.blacklist&");
	}

	while (blackList->count() != 0) { blackList->removeItem(0); } CargarBlacklist();
  }

}

void ZGui::addNumber2()
{

  ZConfig IDini(Idioma, false);
  QString IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MAIN_ADD"), "");
  QString fName; QString lista2;

  ZSingleCaptureDlg* zscd = new ZSingleCaptureDlg(QString::fromUtf8(IDval), 
      QString::fromUtf8(IDval), ZSingleCaptureDlg::normal, NULL, "ZSingleCaptureDlg", true, 0, 0);
  ZLineEdit* zle = (ZLineEdit*)zscd->getLineEdit();  
  zle->setText(fName);
  zle->setEdited(true);  
  
  if (zscd->exec() == 1)
  {
    fName = zle->text();
	ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
	QStringList list = blacklist.readListEntry ( QString("Whitelist"), QString("Num"), QChar(';') );
	for (int j=0;j<list.count();++j)
	{
		lista2 += QString("%1").arg(list[j]) + QChar(';');
	}
	lista2 += fName;
	blacklist.writeEntry(QString("Whitelist"), QString("Num"), lista2);
	qApp->processEvents();

	if ( Potencia == "ON" )
	{
		system("busybox killall .blacklist");
 		system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
		system("exec /ezxlocal/download/mystuff/.blacklist&");
	}

	while (whiteList->count() != 0) { whiteList->removeItem(0); } CargarWhitelist();
  }

}

void ZGui::removeNumber1()
{
	int index = blackList->currentItem();
	if (index == -1) {return;}
	ZListBoxItem* listitem = blackList->item ( index );
	QString app = listitem->getSubItemText ( 1, 0, true );

	ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
	QStringList list = blacklist.readListEntry ( QString("Blacklist"), QString("Num"), QChar(';') );

	QString lista2;

	for (int j=0;j<list.count();++j)
	{
	  if ( list[j] != app )
	  {
		lista2 += QString("%1").arg(list[j]) + QChar(';');
	  }
	}
	blacklist.writeEntry(QString("Blacklist"), QString("Num"), lista2);
	qApp->processEvents();

	if ( Potencia == "ON" )
	{
		system("busybox killall .blacklist");
 		system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
		system("exec /ezxlocal/download/mystuff/.blacklist&");
	}

	while (blackList->count() != 0) { blackList->removeItem(0); } CargarBlacklist();

}

void ZGui::removeNumber2()
{

	int index = whiteList->currentItem();
	if (index == -1) {return;}
	ZListBoxItem* listitem = whiteList->item ( index );
	QString app = listitem->getSubItemText ( 1, 0, true );

	ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
	QStringList list = blacklist.readListEntry ( QString("Whitelist"), QString("Num"), QChar(';') );

	QString lista2;

	for (int j=0;j<list.count();++j)
	{
	  if ( list[j] != app )
	  {
		lista2 += QString("%1").arg(list[j]) + QChar(';');
	  }
	}
	blacklist.writeEntry(QString("Whitelist"), QString("Num"), lista2);
	qApp->processEvents();

	if ( Potencia == "ON" )
	{
		system("busybox killall .blacklist");
 		system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
		system("exec /ezxlocal/download/mystuff/.blacklist&");
	}

	while (whiteList->count() != 0) { whiteList->removeItem(0); } CargarWhitelist();


}

void ZGui::removeCall()
{

	int index = regCalls->currentItem();
	regCalls->removeItem(index);

	QString Valores;
	for (int j=0;j<regCalls->count();++j)
	{
		ZListBoxItem* listitem = regCalls->item (j);
		Valores += listitem->getSubItemText ( 1, 0, true );
		Valores += "\n";
		Valores += listitem->getSubItemText ( 1, 1, true );
		Valores += "\n";

	}
	system(QString("echo \"%1\" > /ezxlocal/download/mystuff/.blockedcalls").arg(Valores));

}

void ZGui::blockUnk()
{

    ZConfig IDini(Idioma, false);
	QString IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("MENU_UNKNOWN"), "");

	ZSingleSelectDlg* eq =  new ZSingleSelectDlg(IDval, QString(""), NULL, "ZSingleSelectDlg", true, 0, 0);
	QStringList list2;
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("OPTIONS_ENABLED"), "");
	list2 = IDval;
	IDval = IDini.readEntry(QString("ZPHONEFIREWALL"), QString("OPTIONS_DISABLED"), "");
	list2 += IDval;
	eq->addItemsList(list2);
	ZListBox* listboxx2 = eq->getListBox();
	int checked = -1;
	if (checked >= 0)
	    listboxx2->checkItem(checked, true);
	eq->exec();
	int result = eq->result();
	if (result != 1) {
		result = 0;
	} else {
	  result = eq->getCheckedItemIndex();
	  if (listboxx2->itemChecked(0))
	  {
		ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
		blacklist.writeEntry(QString("zPhoneFirewall"), QString("BlockUnknown"),  QString("Yes"));
		qApp->processEvents();
		if ( Potencia == "ON" )
		{
			system("busybox killall .blacklist");
 			system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
			system("exec /ezxlocal/download/mystuff/.blacklist&");
		}
		while (mainList->count() != 0) { mainList->removeItem(0); } CargarMain();
	  }
	  if (listboxx2->itemChecked(1))
	  {
		ZConfig blacklist ( QString("%1/zPhoneFirewall.cfg").arg(ProgDir), true );
		blacklist.writeEntry(QString("zPhoneFirewall"), QString("BlockUnknown"),  QString("No"));
		qApp->processEvents();
		if ( Potencia == "ON" )
		{
			system("busybox killall .blacklist");
 			system(QString("cp %1zPhoneFirewall.cfg /ezxlocal/download/mystuff/.zPhoneFirewall.cfg").arg(ProgDir));
			system("exec /ezxlocal/download/mystuff/.blacklist&");
		}
		while (mainList->count() != 0) { mainList->removeItem(0); } CargarMain();
	  }
	}


}

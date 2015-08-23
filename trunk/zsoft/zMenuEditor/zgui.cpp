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



#define APPTITLE "zMenuEditor"


//using namespace std;

ZGui::ZGui ( const QString &Impkg, QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{

  ProgDir = getProgramDir();
  QString val; ZConfig ini(QString("%1/zMenuEditor.cfg").arg(ProgDir), false);
  val = ini.readEntry(QString("zMenuEditor"), QString("Language"), "");
  Idioma = ProgDir + "/languages/" + val;


  CreateWindow ( parent );
  ( ( ZApplication* ) qApp )->showMainWidget ( this );

}

ZGui::~ZGui()
{
}


void ZGui::CreateWindow ( QWidget* parent )
{
  setMainWidgetTitle ( APPTITLE );

  zllb = new ZListBox ( QString ( "%I%M%I" ), this, 0);
  zllb->setFixedWidth ( 240 );

  modificado="NO";
  ZConfig ini(Idioma, false);
  QString val1 = ini.readEntry(QString("ZMENUEDITOR"), QString("INI_SEARCH"), "");
  QString val2 = ini.readEntry(QString("ZMENUEDITOR"), QString("INI_WAIT"), "");
  ZMessageDlg* msg =  new ZMessageDlg ( QString::fromUtf8(APPTITLE),
  QString::fromUtf8("%1\n%2").arg(val1).arg(val2), ZMessageDlg::NONE, 200, NULL, "ZMessageDlg", true, 0 );
  msg->exec();

  CargarListaApps();
  CargarMenu( QString("Principal") );

  delete msg;
  msg = NULL;

  connect(zllb, SIGNAL(returnPressed(ZListBoxItem *)), SLOT(appClicked(ZListBoxItem *)));
  //zllb->sort(true);

  //*****************************
  setContentWidget ( zllb );
  //************** softkeys and menus **************************
  softKey = new ZSoftKey ( NULL , this , this );

  Create_MenuApp();

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

    
void ZGui::Create_SoftKey()
{
  QString IDval; QString IDval2; ZConfig IDini(Idioma, false);
  softKey->setOptMenu ( ZSoftKey::LEFT, menu ); 
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_MENU"), "");
  softKey->setText ( ZSoftKey::LEFT, IDval, ( ZSoftKey::TEXT_PRIORITY ) 0 );
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_MENU"), "");
  softKey->setTextForOptMenuHide(IDval);
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_SELECT"), "");
  IDval2 = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_CANCEL"), "");
  softKey->setTextForOptMenuShow(IDval, IDval2);
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_EXIT"), "");
  softKey->setText ( ZSoftKey::RIGHT, IDval, ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( salir() ) );
}

void ZGui::Create_SoftKey2()
{
  QString IDval; QString IDval2; ZConfig IDini(Idioma, false);
  softKey->setOptMenu ( ZSoftKey::LEFT, menu ); 
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_MENU"), "");
  softKey->setText ( ZSoftKey::LEFT, IDval, ( ZSoftKey::TEXT_PRIORITY ) 0 );
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_MENU"), "");
  softKey->setTextForOptMenuHide(IDval);
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_SELECT"), "");
  IDval2 = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_CANCEL"), "");
  softKey->setTextForOptMenuShow(IDval, IDval2);
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_BACK"), "");
  softKey->setText ( ZSoftKey::RIGHT, IDval, ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( volver() ) );
 
}

void ZGui::volver()
{
  CargarMenu(QString("Principal"));
}

void ZGui::Create_MenuApp()
{
  QString IDval; ZConfig IDini(Idioma, false);
  QRect rect;
  QPixmap* pm  = new QPixmap();
  int idx = 0;
  menu = new ZOptionsMenu ( rect, softKey, NULL, 0);
  menu->setItemSpacing(10);  
  pm->load(ProgDir + "/images/add.png");
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_ADD"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( agregarEntrada() ) );
  ++idx;
  pm->load(ProgDir + "/images/remove.png");
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_DELETE"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( borrarEntrada() ) );
  ++idx;
  menu->insertSeparator(idx, idx); 
  ++idx;
  pm->load(ProgDir + "/images/lang.png");
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("LANG_CHANGE"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( language() ) );
  ++idx;
  menu->insertSeparator(idx, idx); 
  ++idx;
  pm->load(ProgDir + "/images/about.png");
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_ABOUT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( about() ) );      
  ++idx;
  pm->load(ProgDir + "/images/exit.png");
  IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("MENU_EXIT"), "");
  menu->insertItem ( IDval, NULL, pm, true, idx, idx );
  menu->connectItem ( idx, this, SLOT ( salir() ) );
}


void ZGui::CargarMenu(QString Carpeta)
{
	while (zllb->count() != 0) { zllb->removeItem(0); }

	QString carp;
	if ( Carpeta == "Principal" ) { carp = "2a58c0d6-05c6-45aa-8938-63059d41a4e9"; }
	else { carp = Carpeta; }

	currentMenu = carp;

	ZConfig userMenuTree ( "/ezxlocal/download/appwrite/am/UserMenuTree", false );
    QStringList list = userMenuTree.readListEntry ( carp, QString("Items"), QChar(';') );

	QString IDval, IDval2;
	ZConfig IDini( ProgDir + "/Aplicaciones", false );

	for (int j=0;j<list.count();++j)
	{
		QPixmap p1;
		ZListBoxItem* listitem1 = new ZListBoxItem ( zllb, QString ( "%I%M" ) );

		IDval = IDini.readEntry( QString("%1").arg(list[j]), QString("Name"), "" );
		if ( IDval == "" ) 
		{
		    //system(QString("sed -i \"N;s/%1;//g\" $EZX_APP_WRITE_PATH/am/UserMenuTree").arg(list[j]));

			//Esta linea de arriba en teoria borra los registros basura del UserMenuTree
			//Pero por las dudas de que haya olvidado algo prefiero deshabilitarlo hasta hacer mas pruebas
		}
		else
		{
		  IDval2 = IDini.readEntry( QString("%1").arg(list[j]), QString("Type"), "" );
		  if ( IDval2 == "1" ) { p1.load(ProgDir + "/images/folder.png"); }
		  else { p1.load(ProgDir + "/images/run.png"); }
		  listitem1->setPixmap ( 0, p1 );
		  listitem1->appendSubItem ( 1, IDval, true, NULL );
		  zllb->insertItem ( listitem1,-1,true );
		}
	}

	softKey = new ZSoftKey ( NULL , this , this );

	Create_MenuApp();

	if ( Carpeta == "Principal" ) { Create_SoftKey(); }
	else { Create_SoftKey2(); }
	setSoftKey ( softKey );

}


void ZGui::CargarListaApps()
{

  QString file2 = ProgDir + "/SysRegistry";
  if (QFileInfo(file2).isFile())
  { } else {
	  QString s1 = "";
	  QString card = "/usr/data_resource/preloadapps/SysRegistry";
	  QString appid1 ="AppID =";
	  QString name1 ="Name =";
	  QString type1 ="Type =";
	  QString icon1 ="BigIcon =";
	  int elegido=0;
	  QString line="";
	  int cantl=0;  
	  QStringList list="";
	  QFile entrada(card);
	  QTextStream stentrada(&entrada);
	  cantl=0;
	  int numerodelinea=0;
	  int encontro=-1;
	  unsigned int cantidadapps=0;
	  int tam=0;
	  QString aux=""; QString appid=""; QString name=""; QString type=""; QString icon="";
	  QString appid0="NO"; QString name0="NO"; QString type0="NO"; QString icon0="NO";
	  QVector <int> apps;
	  QVector <QString> nombresapps;
	  if ( entrada.open(IO_ReadOnly | IO_Translate) )
	  {
		while ( !stentrada.eof() )
		{           
		  line = stentrada.readLine();
		  aux=line;
		  if ( line[0] == QChar( '[' ) ) 
		  {
		    tam=aux.length()-1; int j=0; appid=""; appid0="SI";           
		    for(int i=1;i<tam;i++) { appid[j]=aux[i]; j++; }
		  }
		  encontro=aux.find(name1,0);
		  if(encontro==0)
		  {
		    tam=aux.length(); int j=0; name=""; name0="SI";           
		    for(int i=7;i<tam;i++) { name[j]=aux[i]; j++; }
		  }
		  encontro=aux.find(type1,0);
		  if(encontro==0)
		  {
		    tam=aux.length(); int j=0; type=""; type0="SI";         
		    for(int i=7;i<tam;i++) { type[j]=aux[i]; j++; }
		  }
		  encontro=aux.find(icon1,0);
		  if(encontro==0)
		  {
		    tam=aux.length(); int j=0; icon=""; icon0="SI";         
		    for(int i=10;i<tam;i++) { icon[j]=aux[i]; j++; }
		  }
		  if ( appid0 == "SI" )
		  {
			if ( name0 == "SI" )
			{
			  if ( type0 == "SI" )
			  {
				if ( icon0 == "SI" )
				{
				  if ( icon0 != "" )
				  {
					  system(QString("touch %1/SysRegistry").arg(ProgDir));
					  system(QString("echo [%1] >> %2/SysRegistry").arg(appid).arg(ProgDir));
					  system(QString("echo Name = %1 >> %2/SysRegistry").arg(name).arg(ProgDir));
					  system(QString("echo Type = %1 >> %2/SysRegistry").arg(type).arg(ProgDir));
					  system(QString("touch %1/SysRegistry2").arg(ProgDir));
					  system(QString("echo [%1] >> %2/SysRegistry2").arg(name).arg(ProgDir));
					  system(QString("echo AppID = %1 >> %2/SysRegistry2").arg(appid).arg(ProgDir));
					  system(QString("echo Type = %1 >> %2/SysRegistry2").arg(type).arg(ProgDir));
				  }
				  name0="NO";appid0="NO";type0="NO";icon0="NO";
				}
			  }
			}
		  }
		}
	  }
	  entrada.close();
  }

  system(QString("rm %1/Temp1").arg(ProgDir));
  system(QString("touch %1/Temp1").arg(ProgDir));
  system(QString("cat /ezxlocal/download/appwrite/am/UserRegistry >> %1/Temp1").arg(ProgDir));
  system(QString("cat /ezxlocal/download/appwrite/am/InstalledDB >> %1/Temp1").arg(ProgDir));
  system(QString("cat /mmc/mmca1/.system/java/CardRegistry >> %1/Temp1").arg(ProgDir));

  system(QString("rm %1/SysTemp2").arg(ProgDir));
  system(QString("rm %1/SysTemp3").arg(ProgDir));

  QString s1 = "";
  QString card = ProgDir + "/Temp1";
  QString appid1 ="AppID =";
  QString name1 ="Name =";
  QString type1 ="Type =";
  QString icon1 ="BigIcon =";
  int elegido=0;
  QString line="";
  int cantl=0;  
  QStringList list="";
  QFile entrada(card);
  QTextStream stentrada(&entrada);
  cantl=0;
  int numerodelinea=0;
  int encontro=-1;
  unsigned int cantidadapps=0;
  int tam=0;
  QString aux=""; QString appid=""; QString name=""; QString type=""; QString icon="";
  QString appid0="NO"; QString name0="NO"; QString type0="NO"; QString icon0="NO";
  QVector <int> apps;
  QVector <QString> nombresapps;
  if ( entrada.open(IO_ReadOnly | IO_Translate) )
  {
	while ( !stentrada.eof() )
	{           
	  line = stentrada.readLine();
	  aux=line;
	  if ( line[0] == QChar( '[' ) ) 
	  {
	    tam=aux.length()-1; int j=0; appid=""; appid0="SI";           
	    for(int i=1;i<tam;i++) { appid[j]=aux[i]; j++; }
	  }
	  encontro=aux.find(name1,0);
	  if(encontro==0)
	  {
	    tam=aux.length(); int j=0; name=""; name0="SI";           
	    for(int i=7;i<tam;i++) { name[j]=aux[i]; j++; }
	  }
	  encontro=aux.find(type1,0);
	  if(encontro==0)
	  {
	    tam=aux.length(); int j=0; type=""; type0="SI";         
	    for(int i=7;i<tam;i++) { type[j]=aux[i]; j++; }
	  }
	  encontro=aux.find(icon1,0);
	  if(encontro==0)
	  {
	    tam=aux.length(); int j=0; icon=""; icon0="SI";         
	    for(int i=10;i<tam;i++) { icon[j]=aux[i]; j++; }
	  }
	  if ( appid0 == "SI" )
	  {
		if ( name0 == "SI" )
		{
		  if ( type0 == "SI" )
		  {
			if ( icon0 == "SI" )
			{
			  if ( icon0 != "" )
			  {
				  system(QString("touch %1/SysTemp2").arg(ProgDir));
				  system(QString("echo [%1] >> %2/SysTemp2").arg(appid).arg(ProgDir));
				  system(QString("echo Name = %1 >> %2/SysTemp2").arg(name).arg(ProgDir));
				  system(QString("echo Type = %1 >> %2/SysTemp2").arg(type).arg(ProgDir));
				  system(QString("touch %1/SysTemp3").arg(ProgDir));
				  system(QString("echo [%1] >> %2/SysTemp3").arg(name).arg(ProgDir));
				  system(QString("echo AppID = %1 >> %2/SysTemp3").arg(appid).arg(ProgDir));
				  system(QString("echo Type = %1 >> %2/SysTemp3").arg(type).arg(ProgDir));
			  }
			  name0="NO";appid0="NO";type0="NO";icon0="NO";
			}
		  }
		}
	  }
	}
  }
  entrada.close();

  system(QString("rm %1/Aplicaciones").arg(ProgDir)); 
  system(QString("touch %1/Aplicaciones").arg(ProgDir)); 
  system(QString("cat %1/SysTemp2 >> %2/Aplicaciones").arg(ProgDir).arg(ProgDir));  
  system(QString("cat %1/SysRegistry >> %2/Aplicaciones").arg(ProgDir).arg(ProgDir));  
  system(QString("rm %1/Aplicaciones2").arg(ProgDir)); 
  system(QString("touch %1/Aplicaciones2").arg(ProgDir)); 
  system(QString("cat %1/SysTemp3 >> %2/Aplicaciones2").arg(ProgDir).arg(ProgDir));  
  system(QString("cat %1/SysRegistry2 >> %2/Aplicaciones2").arg(ProgDir).arg(ProgDir));  
  system(QString("rm %1/SysTemp2").arg(ProgDir));  
  system(QString("rm %1/SysTemp3").arg(ProgDir));  
  system(QString("rm %1/Temp1").arg(ProgDir));  


  zllb->sort(true);


}

void ZGui::salir()
{

  if ( modificado == "SI" )
  {
	ZConfig IDini( Idioma, false);
	QString IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("EXIT_ASK"), "");
 	ZMessageDlg* msg =  new ZMessageDlg ( QString::fromUtf8(APPTITLE),
	  QString::fromUtf8("%1").arg(IDval), ZMessageDlg::yes_no, 0, NULL, "ZMessageDlg", true, 0 );
	int i = msg->exec();
	delete msg;
	msg = NULL;
	if (i)
	{
	  system("busybox killall am");
	}
  }
  qApp->quit();

}

void ZGui::appClicked(ZListBoxItem *item)
{
  menu->close();
  qApp->processEvents();
  int index = zllb->currentItem();
  if (index == -1) {return;}
  ZListBoxItem* listitem = zllb->item ( index );
  QString app = listitem->getSubItemText ( 1, 0, true );
  ZConfig IDini( QString("%1/Aplicaciones2").arg(ProgDir), false );
  QString IDval = IDini.readEntry( QString("%1").arg(app), QString("Type"), "" );

  if ( IDval == "1" )
  {
	IDval = IDini.readEntry( QString("%1").arg(app), QString("AppID"), "" );
	CargarMenu ( IDval );
  }

}


void ZGui::language()
{

  QString val; ZConfig ini(Idioma, false);
  val = ini.readEntry(QString("ZMENUEDITOR"), QString("MENU_LANGUAGE"), "");


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
		  QString val = IDini.readEntry(QString("ZMENUEDITOR"), QString("LANG_NAME"), "");
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
			system( QString("/ezxlocal/download/mystuff/.system/LinXtend/usr/bin/setconfig %1/zMenuEditor.cfg Language %2").arg(ProgDir).arg(line2) );

			  softKey = new ZSoftKey ( NULL , this , this );

			  Create_MenuApp();

			  Create_SoftKey();
			  setSoftKey ( softKey );

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

void ZGui::borrarEntrada()
{
  QString IDval; ZConfig IDini( ProgDir + "/Aplicaciones2", false);

  menu->close();
  qApp->processEvents();
  int index = zllb->currentItem();
  if (index == -1) {return;}
  ZListBoxItem* listitem = zllb->item ( index );
  QString app = listitem->getSubItemText ( 1, 0, true );

  QString val; ZConfig ini1(Idioma, false);
  val = ini1.readEntry(QString("ZMENUEDITOR"), QString("DELETE_MSG"), "");
  ZMessageDlg* msg =  new ZMessageDlg ( QString::fromUtf8(APPTITLE),
	QString::fromUtf8("%1 %2?").arg(val).arg(app), ZMessageDlg::yes_no, 0, NULL, "ZMessageDlg", true, 0 );
  int i = msg->exec(); delete msg; msg = NULL;
  if (i)
  {
	  
	  IDval = IDini.readEntry(QString(app), QString("AppID"), "");

	  ZConfig userMenuTree ( "/ezxlocal/download/appwrite/am/UserMenuTree", false );
	  QStringList list = userMenuTree.readListEntry ( currentMenu, QString("Items"), QChar(';') );

	  QString NuevoValor;
	  for (int j=0;j<list.count();++j)
	  {
		if ( list[j] != IDval )
		{
		  NuevoValor += QString("%1;").arg(list[j]);
		}
	  }

	  ZConfig UMT("/ezxlocal/download/appwrite/am/UserMenuTree", false);
	  QString UMTval = UMT.readEntry(QString("%1").arg(currentMenu), QString("Items"), "");
	  QString valor2 = NuevoValor;
	  UMT.writeEntry(currentMenu, QString("Items"), valor2);

	  ZConfig ini2( Idioma, false);
	  QString IDval2 = ini2.readEntry(QString("ZMENUEDITOR"), QString("DELETE_MSG2"), "");
	  znd = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString(""), QString("%1 %2").arg(app).arg(IDval2), this, "z", true, 0);
	  znd->show(); znd = NULL;

	  zllb->removeItem(zllb->currentItem());
	  modificado="SI";

  }
}


void ZGui::agregarEntrada()
{


  QString s1 = "";
  QString card = ProgDir + "/Aplicaciones";
  QString name1 ="Name =";
  int elegido=0;
  QString line="";
  int cantl=0;  
  listaApps="";
  QFile entrada(card);
  QTextStream stentrada(&entrada);
  cantl=0;
  int numerodelinea=0;
  int encontro=-1;
  unsigned int cantidadapps=0;
  int tam=0;
  QString aux=""; QString appid=""; QString name=""; QString type=""; 
  QString appid0="NO"; QString name0="NO"; QString type0="NO"; 
  QVector <int> apps;
  QVector <QString> nombresapps;
  if ( entrada.open(IO_ReadOnly | IO_Translate) )
  {
	while ( !stentrada.eof() )
	{           
	  line = stentrada.readLine();
	  aux=line;
	  encontro=aux.find(name1,0);
	  if(encontro==0)
	  {
	    tam=aux.length(); int j=0; name=""; name0="SI";           
	    for(int i=7;i<tam;i++) { name[j]=aux[i]; j++; }
	  }
	  if ( name0 == "SI" )
	  {
		  listaApps += name;
		  name0="NO";appid0="NO";type0="NO";
	  }
	}
  }
  entrada.close();


	ZConfig IDini( Idioma, false);
	QString IDval = IDini.readEntry(QString("ZMENUEDITOR"), QString("APP_SELECT"), "");
	ZSingleSelectDlg* eq =  new ZSingleSelectDlg(APPTITLE, IDval, NULL, "ZSingleSelectDlg", true, 0, 0);
	QStringList list2;

	for (int j=0;j<listaApps.count();++j)
	{
	  if ( listaApps[j].length() != 0 )
	  { 
	  	list2 += QString("%1").arg(listaApps[j]);
	  }
	}

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

	  ZConfig ini0( ProgDir + "/Aplicaciones2", false);
	  QString valor0 = ini0.readEntry(listaApps[result+1], QString("AppID"), "");

	  ZConfig UMT("/ezxlocal/download/appwrite/am/UserMenuTree", false);
	  QString UMTval = UMT.readEntry(QString("%1").arg(currentMenu), QString("Items"), "");
	  QString NuevoValor = UMTval + QChar(';') + valor0;
	  QString valor2 = QString("%1").arg(NuevoValor);
	  UMT.writeEntry(QString("%1").arg(currentMenu), QString("Items"), valor2);

	  ZConfig ini2( Idioma, false);
	  QString IDval2 = ini2.readEntry(QString("ZMENUEDITOR"), QString("ADD_MSG"), "");
	  znd = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString(""), QString("%1 %2").arg(listaApps[result+1]).arg(IDval2), this, "z", true, 0);
	  znd->show(); znd = NULL;

 	  //qApp->processEvents();
	  //CargarMenu("Principal");

	  QPixmap p1;
	  ZListBoxItem* listitem1 = new ZListBoxItem ( zllb, QString ( "%I%M" ) );
	  QString IDval; ZConfig IDini( ProgDir + "/Aplicaciones2", false);
	  IDval = IDini.readEntry( QString("%1").arg(listaApps[result+1]), QString("Type"), "" );
	  if ( IDval == "1" ) { p1.load(ProgDir + "/images/folder.png"); }
	  else { p1.load(ProgDir + "/images/run.png"); }
	  listitem1->setPixmap ( 0, p1 );
	  listitem1->appendSubItem ( 1, QString("%1").arg(listaApps[result+1]), true, NULL );
	  zllb->insertItem ( listitem1,-1,true );
	  modificado="SI";

	}
}


#include "zgui.h"
#include "GUI_Define.h"
#include "BaseDlg.h"
#include "ZAboutDlg.h"
#include "ZFileDlg.h"

#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <qpixmap.h>
#include <qlabel.h>

#include <ZApplication.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>
#include <ZMessageDlg.h>
#include <ZConfig.h>
#include <ZComboBox.h>
#include <qfile.h>
#include <qtextstream.h>
//using namespace std;


ZGui::ZGui ( QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{ znd=NULL;
  leerini();
  CreateWindow ( parent );
  ( ( ZApplication* ) qApp )->showMainWidget ( this );
}

ZGui::~ZGui()
{
if(znd!=NULL) znd=NULL;
}

void ZGui::CreateWindow ( QWidget* parent )
{
  
  setMainWidgetTitle ( "zAlarm" );
  ZWidget *myWidget = new ZWidget ( this, NULL, 0, ( ZSkinService::WidgetClsID ) 40 );
  QFont f ( qApp->font() );
  f.setPointSize ( 10 );
  myWidget->setFont ( f );

  QVBoxLayout *myVBoxLayout = new QVBoxLayout ( myWidget, 0 );
  //*****************************
  //*** add elements here
  QLabel *myLabel = new QLabel ( QString ( "<qt><font size=\"+1\">zAlarm 0.2</font><br>"
                                 "<font size=\"-1\">Alarm time changer</font></qt>" ), myWidget );
  myVBoxLayout->addWidget ( myLabel, 0 );
  myLabel->setIndent ( 5 );
  myLabel->setAutoResize ( true );


  scrollPanel = new ZScrollPanel ( myWidget, NULL, 0, ( ZSkinService::WidgetClsID ) 0 );
  scrollPanel->resize ( 240, 320 );
  myVBoxLayout->addWidget ( scrollPanel, 0 );
  ///***********
  //idioma=new ZComboBox(this,"ZComboBox",true);
  
  ///***********
  if(idiomastring=="español")
{
 QRect rect,rect2;
        ZOptionsMenu* subMenu_BT = new ZOptionsMenu(rect2, this, NULL, 0, (ZSkinService::WidgetClsID)2);
	subMenu_BT->insertItem(QString("Espanol") , NULL , NULL , true , 0 , 0 );
	subMenu_BT->insertItem(QString("Ingles") , NULL , NULL , true , 1 , -1 );

  idioma=new ZComboBox(this,"ZComboBox",true);
  idioma->insertItem("1 minuto",0);
  idioma->insertItem("2 minutos",1);
  idioma->insertItem("3 minutos",2);
  idioma->insertItem("4 minutos",3);
  idioma->insertItem("5 minutos",4);
  idioma->insertItem("6 minutos",5);

  scrollPanel->addChild(idioma , 10 , 55);//agrego el combobox de las apps al escritorio

  infoLabel = new ZLabel("Tiempo" , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
  infoLabel->setPreferredWidth(240);
  infoLabel->setAutoResize(true );
  
  scrollPanel->addChild(infoLabel , 10 , 5);//agrego el label al menu
  //*****************************
  setContentWidget ( myWidget );
  //************** softkeys and menus **************************
  ZSoftKey *softKey = new ZSoftKey ( NULL , this , this );

 QPixmap* pm  = new QPixmap(getProgramDir() + "img/about.png");
 
  ZOptionsMenu* menu = new ZOptionsMenu ( rect, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  menu->insertItem ( QString ( "Acerca de" ), NULL, pm, true, 0, 0 );
pm->load(getProgramDir() + "img/idioma.png");
  menu->insertItem ( QString ( "Idioma" ), subMenu_BT, pm, true, 1, 1 );
pm->load(getProgramDir() + "img/alarma.png");
  menu->insertItem ( QString ( "Cambiar" ), NULL, pm, true, 2, 2 );
pm->load(getProgramDir() + "img/exit.png");
  menu->insertItem ( QString ( "Salir" ), NULL, pm, true, 3, 3 );

  menu->connectItem ( 3, qApp, SLOT ( quit() ) );
  //menu->connectItem ( 1, this, SLOT ( cambiaridioma() ) );
  menu->connectItem ( 2, this, SLOT ( tiempo() ) );
  menu->connectItem ( 0, this, SLOT ( about() ) );
  subMenu_BT->connectItem ( 0, this, SLOT ( espanol() ) );
  subMenu_BT->connectItem ( 1, this, SLOT ( ingles() ) );
  softKey->setOptMenu ( ZSoftKey::LEFT, menu );
  softKey->setText ( ZSoftKey::LEFT, "Menu", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, "Salir", ( ZSoftKey::TEXT_PRIORITY ) 0 );
softKey->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit()));
  setSoftKey ( softKey );
}
else
{    QRect rect,rect2;
ZOptionsMenu* subMenu_BT = new ZOptionsMenu(rect2, this, NULL, 0, (ZSkinService::WidgetClsID)2);
	subMenu_BT->insertItem(QString("Spanish") , NULL , NULL , true , 0 , 0 );
	subMenu_BT->insertItem(QString("English") , NULL , NULL , true , 1 , -1 );
  idioma=new ZComboBox(this,"ZComboBox",true);
  idioma->insertItem("1 minute",0);
  idioma->insertItem("2 minutes",1);
  idioma->insertItem("3 minutes",2);
  idioma->insertItem("4 minutes",3);
  idioma->insertItem("5 minutes",4);
  idioma->insertItem("6 minutes",5);

  scrollPanel->addChild(idioma , 10 , 55);//agrego el combobox de las apps al escritorio

  infoLabel = new ZLabel("Time" , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
  infoLabel->setPreferredWidth(240);
  infoLabel->setAutoResize(true );
  
  scrollPanel->addChild(infoLabel , 10 , 5);//agrego el label al menu
//*****************************
  setContentWidget ( myWidget );
  //************** softkeys and menus **************************
  ZSoftKey *softKey = new ZSoftKey ( NULL , this , this );

QPixmap* pm  = new QPixmap(getProgramDir() + "img/about.png");
  ZOptionsMenu* menu = new ZOptionsMenu ( rect, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  menu->insertItem ( QString ( "About" ), NULL, pm, true, 0, 0 );
pm->load(getProgramDir() + "img/idioma.png");
  menu->insertItem ( QString ( "Language" ), subMenu_BT, pm, true, 1, 1 );
pm->load(getProgramDir() + "img/alarma.png");
  menu->insertItem ( QString ( "Apply" ), NULL, pm, true, 2, 2 );
pm->load(getProgramDir() + "img/exit.png");
  menu->insertItem ( QString ( "Exit" ), NULL, pm, true, 3, 3 );

  menu->connectItem ( 3, qApp, SLOT ( quit() ) );
  menu->connectItem ( 1, this, SLOT ( cambiaridioma() ) );
  menu->connectItem ( 2, this, SLOT ( tiempo() ) );
  menu->connectItem ( 0, this, SLOT ( about() ) );
  subMenu_BT->connectItem ( 0, this, SLOT ( espanol() ) );
  subMenu_BT->connectItem ( 1, this, SLOT ( ingles() ) );
  softKey->setOptMenu ( ZSoftKey::LEFT, menu );
  softKey->setText ( ZSoftKey::LEFT, "Menu", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, "Exit", ( ZSoftKey::TEXT_PRIORITY ) 0 );
 softKey->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit()));
  setSoftKey ( softKey );
}

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
  /*
  ZMessageDlg *dlg = new ZMessageDlg ( "Title", "Instruction", ZMessageDlg::just_ok, 0, this, "About", true, 0 );
  dlg->exec();
  delete dlg;
  dlg = NULL;
  */
  ZAboutDialog* aboutDlg = new ZAboutDialog();
  aboutDlg->exec();
/*
  if ( aboutDlg->result() == 0 )
  {
    ZMessageDlg *dlg = new ZMessageDlg ( "Title", "Instruction: Rejected", ZMessageDlg::just_ok, 0, this, "About", true, 0 );
    dlg->exec();
    delete dlg;
    dlg = NULL;
  }
  else
  {
    ZMessageDlg *dlg = new ZMessageDlg ( "Title", "Instruction: Accepted", ZMessageDlg::just_ok, 0, this, "About", true, 0 );
    dlg->exec();
    delete dlg;
    dlg = NULL;
  }*/
  delete aboutDlg;
  aboutDlg = NULL;
}

/*
void ZGui::slot_fileOpenDlg()
{
  ZFileOpenDialog *zfod  = new ZFileOpenDialog();
  zfod->exec();
  if ( zfod->result() == 1 )
  {
    ZMessageDlg *dlg = new ZMessageDlg ( "Title", zfod->getFilePath() + "\n" + zfod->getFileName(), ZMessageDlg::just_ok, 0, this, "About", true, 0 );
    dlg->exec();
    delete dlg;
    dlg = NULL; 
  }
  delete zfod;
  zfod = NULL;
}*/
/*
void ZGui::slot_fileSaveDlg()
{
  ZFileSaveDialog *zfsd  = new ZFileSaveDialog();
  zfsd->exec();
  
  if ( zfsd->result() == 1 )
  {
    ZMessageDlg *dlg = new ZMessageDlg ( "Title", zfsd->getFilePath() + "\n" + zfsd->getFileName(), ZMessageDlg::just_ok, 0, this, "About", true, 0 );
  dlg->exec();
  delete dlg;
  dlg = NULL;
  }
  else
  {
    ZMessageDlg *dlg = new ZMessageDlg ( "Title", "Instruction: Rejected", ZMessageDlg::just_ok, 0, this, "About", true, 0 );
    dlg->exec();
    delete dlg;
    dlg = NULL;
  }  
  delete zfsd;
  zfsd = NULL;
}*/
void ZGui::tiempo()
{
if(idiomastring=="ingles")
{
QString s1 = QString("/ezx_user/download/appwrite/setup/ezx_system.cfg");
	int val;
	ZConfig ini(s1, false);
			int r = idioma->currentItem()+1;
			ini.writeEntry(QString("ALARMCLOCK"), QString("AlertTime"), r);
			QString sr;
			sr = QString(" to %1 minutes").arg(r);
			
			if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::Information, 1000, QString("Alarm time changed"), sr, this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
		}
else
{
QString s1 = QString("/ezx_user/download/appwrite/setup/ezx_system.cfg");
	int val;
	ZConfig ini(s1, false);
			int r = idioma->currentItem()+1;
			ini.writeEntry(QString("ALARMCLOCK"), QString("AlertTime"), r);
			QString sr;
			sr = QString(" a %1 minutos").arg(r);
			
			if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::Information, 1000, QString("Tiempo de la alarma cambiado"), sr, this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
		}

}

void ZGui::leerini()
{
idiomastring="";
QFile entrada(getProgramDir() + "config.ini" );
  QTextStream en( &entrada ); 
  if ( entrada.open(IO_ReadOnly | IO_Translate) )
{
idiomastring=en.readLine();
}
}

void ZGui::espanol()
{

QFile salida(getProgramDir() + "config.ini" );
  QTextStream sal( &salida ); 
  if ( salida.open(IO_WriteOnly | IO_Translate) )
{
sal << "español" <<endl;
}
ZGui();
}

void ZGui::ingles()
{

QFile salida(getProgramDir() + "config.ini" );
  QTextStream sal( &salida ); 
  if ( salida.open(IO_WriteOnly | IO_Translate) )
{
sal << "ingles" <<endl;
}
ZGui();
}



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
#include <qdir.h>
#include <ZConfig.h>
#include <qfile.h>
#include <qtextstream.h>

#include <ZMultiSelectDlg.h>
#include <ZSingleCaptureDlg.h>
#include "recursos.h"
//using namespace std;

ZGui::ZGui ( const QString &ejecuta, QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{
  QString eje = ejecuta;
  if ( eje == "cleannow" )
  {infos=NULL;
  dlg=NULL;
  ZConfig conf ( getProgramDir() + "av_db.cfg", true );
  QStringList list = conf.readListEntry ( QString("DATABASE"), QString("DELETE"), QChar(';') );
  QStringList a="";
  for(int i=0;i< list.count();i++) {
  a=limpiar(SD,list[i]); borrar(a); a="";
  a=limpiar(phone,list[i]); borrar(a); a="";}
  qApp->quit();  
  }
  else
  {infos=NULL;
  dlg=NULL; 
  eliminados="";
  CreateWindow ( parent );
  ( ( ZApplication* ) qApp )->showMainWidget ( this );}
}

ZGui::~ZGui()
{
 if(infos!=NULL) infos=NULL;
 if(dlg!=NULL) dlg=NULL;
}

void ZGui::CreateWindow ( QWidget* parent )
{
  setMainWidgetTitle ( "zCleaner" );
  ZWidget *myWidget = new ZWidget ( this, NULL, 0, ( ZSkinService::WidgetClsID ) 40 );
  QFont f ( qApp->font() );
  f.setPointSize ( 10 );
  myWidget->setFont ( f );

  QVBoxLayout *myVBoxLayout = new QVBoxLayout ( myWidget, 0 );
  //*****************************
  //*** add elements here
  QLabel *myLabel = new QLabel ( QString ( "<qt><font size=\"+1\">zCleaner</font><br>"
                                 "<font size=\"-1\">Simple antivirus for Z6</font></qt>" ), myWidget );
  myVBoxLayout->addWidget ( myLabel, 0 );
  myLabel->setIndent ( 5 );
  myLabel->setAutoResize ( true );


  scrollPanel = new ZScrollPanel ( myWidget, NULL, 0, ( ZSkinService::WidgetClsID ) 0 );
  scrollPanel->resize ( 240, 320 );
   //-----------------------------------------------------------------------------------
  modo=new ZComboBox(this,"ZComboBox",true);//declaro los combobox
  lugar=new ZComboBox(this,"ZComboBox",true);
  modo->insertItem("Clean", 0 );
  modo->insertItem("AV", 1 );	
  //modo->insertItem("Picture/Video", 2 );  
  scrollPanel->addChild(modo , 100 , 5);//agrego el combobox de las apps al escritorio

  lab1 = new ZLabel("Mode" , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
  lab1->setPreferredWidth(240);
  lab1->setAutoResize(true );
  
  scrollPanel->addChild(lab1 , 10 , 8);//agrego el label al menu
  
  lugar->insertItem("SD",0);
  lugar->insertItem("Phone",1);
  lugar->insertItem("SD/Phone",2);

  scrollPanel->addChild(lugar , 100 , 55);//agrego el propiestario al escritorio
  lab2  = new ZLabel("Location" , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
  lab2->setPreferredWidth(240);
  lab2->setAutoResize(true );
  
  scrollPanel->addChild(lab2 , 10 , 58);//agrego el label al menu
  myVBoxLayout->addWidget ( scrollPanel, 0 );


  //*****************************
  setContentWidget ( myWidget );
  //************** softkeys and menus **************************
  ZSoftKey *softKey = new ZSoftKey ( NULL , this , this );
  QPixmap* pm  = new QPixmap();
  
  QRect rect, rect2, rect3, rect4;

  ZOptionsMenu* agre = new ZOptionsMenu ( rect3, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  //pm->load(getProgramDir() + "img/about.png");
  agre->insertItem ( QString ( " ASK" ), NULL, NULL, true, 0, 0 );
  agre->insertItem ( QString ( " DELETE" ), NULL, NULL, true, 1, 1 );
  agre->connectItem ( 0, this, SLOT ( agregarTipoASK() ) );
  agre->connectItem ( 1, this, SLOT ( agregarTipoDELETE() ) );

  ZOptionsMenu* borr = new ZOptionsMenu ( rect4, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  borr->insertItem ( QString ( " ASK" ), NULL, NULL, true, 0, 0 );
  borr->insertItem ( QString ( " DELETE" ), NULL, NULL, true, 1, 1 );
  borr->connectItem ( 0, this, SLOT ( eliminarTipoASK() ) );

  ZOptionsMenu* data = new ZOptionsMenu ( rect2, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  pm->load(getProgramDir() + "img/add.png");
  data->insertItem ( QString ( " Add type" ), agre, pm, true, 0, 0 );
  pm->load(getProgramDir() + "img/remove.png");
  data->insertItem ( QString ( " Remove type" ), borr, pm, true, 1, 1 );

  
  ZOptionsMenu* menu = new ZOptionsMenu ( rect, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  pm->load(getProgramDir() + "img/about.png");
  menu->insertItem ( QString ( " About" ), NULL, pm, true, 0, 0 );
  menu->insertSeparator(1, 1); 
  pm->load(getProgramDir() + "img/white.png");
  menu->insertItem ( QString ( " Clean" ), NULL, pm, true, 2, 2 );
  pm->load(getProgramDir() + "img/properties.png");
  menu->insertItem ( QString ( " Database" ), data, pm, true, 3, 3 );
  pm->load(getProgramDir() + "img/edit.png");
  menu->insertItem ( QString ( " Save delete files list" ), NULL, pm, true, 4, 4 );
  menu->insertSeparator(5, 5); 
  pm->load(getProgramDir() + "img/exit.png");
  menu->insertItem ( QString ( " Exit" ), NULL, pm, true, 6, 6 );

  menu->connectItem ( 6, qApp, SLOT ( quit() ) );
  menu->connectItem ( 2, this, SLOT ( ejecutar() ) );
  menu->connectItem ( 0, this, SLOT ( about() ) );
  menu->connectItem ( 4, this, SLOT ( verEliminados() ) );

  softKey->setOptMenu ( ZSoftKey::LEFT, menu );
  softKey->setText ( ZSoftKey::LEFT, "Menu", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, "Exit", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot ( ZSoftKey::RIGHT, qApp, SLOT ( quit() ) ); 
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
QStringList ZGui::limpiar(const QString &path, const QString &filter)
{
 if(path != "/mmc/mmca1/.system")
 {
 QDir dir ( path );
	  QStringList::Iterator it;
	  QStringList fullFiles="";
	  int size = 0;
	  QStringList files = dir.entryList ( filter, QDir::Files );
	  it = files.begin();
	  while ( it != files.end() ) 
	  {
	    fullFiles += QFileInfo ( path, *it ).filePath();
	    ++it;
	  }
	  QStringList dirs = dir.entryList ( QDir::Dirs );
	  it = dirs.begin();
	  while ( it != dirs.end() ) {
	    if ( *it != "." && *it != ".." )
	      fullFiles += limpiar ( path + "/" + *it , filter);
	    ++it;
	  }
          return fullFiles;
 }
}

void ZGui::borrar(QStringList lista)
{
 QDir q;
 for(int i=0;i < lista.count(); i++)
 {   q.remove(lista[i]); eliminados+=lista[i];}

 QString cmd = "rm -rf /mmc/mmca1/RECYCLER";
 system(cmd);
 /*QFile salida(getProgramDir() + "autorun.ini"); 
 QTextStream sal(&salida);
 salida.open(IO_WriteOnly | IO_Translate);
 QFile salida2(getProgramDir() + "autorun.inf"); 
 QTextStream sal2(&salida2);
 salida2.open(IO_WriteOnly | IO_Translate);*/
}

void ZGui::borrarcuidado(QStringList lista2)
{
 int b=0;
 QDir q;
 QString pas="";
 for(int i=0;i < lista2.count(); i++)
 {  
   pas=lista2[i];
   b=confirmacion(pas);
   if(b==0){q.remove(lista2[i]);eliminados+=lista2[i];}
 }
 QString cmd = "rm -rf /mmc/mmca1/RECYCLER";
 system(cmd); 
/* QFile salida(getProgramDir() + "autorun.ini"); 
 QTextStream sal(&salida);
 salida.open(IO_WriteOnly | IO_Translate);
 QFile salida2(getProgramDir() + "autorun.inf"); 
 QTextStream sal2(&salida2);
 salida2.open(IO_WriteOnly | IO_Translate);
*/ 
}

void ZGui::ejecutar()
{
 QStringList a="";
 int lug=0;
 int mod=0;
 mod=modo->currentItem();
 if(mod==1)//MODO AV
  {
   ZConfig conf ( getProgramDir() + "av_db.cfg", true );
   QStringList list = conf.readListEntry ( QString("DATABASE"), QString("ASK"), QChar(';') );
   lug=lugar->currentItem();
   if(lug==0)
   {
    for(int i=0;i<list.count();i++)
     {
      a=limpiar(SD,list[i]); borrarcuidado(a); a="";
     }
   }
   else if(lug==1)
   {
    for(int i=0;i<list.count();i++)
     {
      a=limpiar(phone,list[i]); borrarcuidado(a); a="";
     }
   }
   else if(lug==2)
   {
    for(int i=0;i<list.count();i++)
     {
      a=limpiar(SD,list[i]); borrarcuidado(a); a="";
      a=limpiar(phone,list[i]); borrarcuidado(a); a="";
     }
   }
  }
  
  else if(mod==0)
  {
   ZConfig conf ( getProgramDir() + "av_db.cfg", true );
   QStringList list = conf.readListEntry ( QString("DATABASE"), QString("DELETE"), QChar(';') );
  //for(int j=0;j<list.count();j++) sal << list[j] << endl;
   lug=lugar->currentItem();
   if(lug==0)
   {
    for(int i=0;i<list.count();i++)
     {
      a=limpiar(SD,list[i]); borrar(a); a="";
     }
   }
   else if(lug==1)
   {
    for(int i=0;i<list.count();i++)
     {
      a=limpiar(phone,list[i]); borrar(a); a="";
     }
   }
   else if(lug==2)
   {
    for(int i=0;i<list.count();i++)
     {
      a=limpiar(SD,list[i]); borrar(a); a="";
      a=limpiar(phone,list[i]); borrar(a); a="";
     }
   }
   }//Fin modo clean
 

 if(infos==NULL)
  {
  infos = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString("Your Z6 is clean now"), QString("!!"), this, "z", true, 0);
   infos->show();
 
  } infos=NULL;
}

int ZGui::confirmacion(QString aux)
{
    int elegido=-1;
    QStringList lista;
    lista += "Yes";//0
    lista += "No";//1
    if(aux!="")
    {
    if( dlg == NULL )
	        {
	                dlg  = new ZSingleSelectDlg("Delete??" , aux, this, "ZSingleSelectDlg", true, 0, 0);
	                dlg->addItemsList(lista);
	        
	        }
	        if(dlg->exec())
	        {
	         elegido=dlg->getCheckedItemIndex();
                }
    dlg=NULL;             
    return elegido;
    }
    else { return -1;}
}

void ZGui::agregarTipoASK()
{
  QString aux="";
ZSingleCaptureDlg* dialogo = new ZSingleCaptureDlg ( "Add type", "Enter new file type", ZSingleCaptureDlg::normal, NULL, "dlg", true, 0, 0 );
     if ( dialogo->exec() )
      {
        aux = dialogo->getResultText();
      }dialogo=NULL;
 if(aux!="") {
 ZConfig conf ( getProgramDir() + "av_db.cfg", true );
 QStringList list = conf.readListEntry ( QString("DATABASE"), QString("ASK"), QChar(';') );
 list +=  aux;
 conf.writeEntry(QString("DATABASE"), QString("ASK"), list, ';');}
 if(infos==NULL)
  {
  infos = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString("OK"), QString("Type " + aux +" added"), this, "z", true, 0);
   infos->show();
 
  } infos=NULL;
}

void ZGui::agregarTipoDELETE()
{
  QString aux="";
ZSingleCaptureDlg*  dialogo = new ZSingleCaptureDlg ( "Add type", "Enter new file type", ZSingleCaptureDlg::normal, NULL, "dlg", true, 0, 0 );
     if ( dialogo->exec() )
      {
        aux = dialogo->getResultText();
      }dialogo=NULL;
 if(aux!="") {
 ZConfig conf ( getProgramDir() + "av_db.cfg", true );
 QStringList list = conf.readListEntry ( QString("DATABASE"), QString("DELETE"), QChar(';') );
 list += aux;
 conf.writeEntry(QString("DATABASE"), QString("DELETE"), list, ';');}
  if(infos==NULL)
  {
  infos = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString("OK"), QString("Type " + aux +" added"), this, "z", true, 0);
   infos->show();
 
  } infos=NULL;
 
}


void ZGui::eliminarTipoASK()
{
 ZConfig conf ( getProgramDir() + "av_db.cfg", true );
 QStringList list = conf.readListEntry ( QString("DATABASE"), QString("ASK"), QChar(';') );
 
 ZSingleSelectDlg * dlg = new ZSingleSelectDlg("Remove", "Select type", this, "ZSingleSelectDlg", true, 0, 0);
 dlg->addItemsList(list);
 dlg->exec();
 int elegido=dlg->getCheckedItemIndex();
 QString aux="";
 aux=list[elegido];
 list.remove(list[elegido]);
 conf.writeEntry(QString("DATABASE"), QString("ASK"), list, ';');
 dlg=NULL;
  if(infos==NULL)
  {
  infos = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString("OK"), QString("Type " + aux +" removed"), this, "z", true, 0);
   infos->show();
 
  } infos=NULL;
}


void ZGui::eliminarTipoDELETE()
{ QString aux="";
  ZConfig conf ( getProgramDir() + "av_db.cfg", true );
 QStringList list = conf.readListEntry ( QString("DATABASE"), QString("DELETE"), QChar(';') );
 
 ZSingleSelectDlg * dlg = new ZSingleSelectDlg("Remove", "Select type", this, "ZSingleSelectDlg", true, 0, 0);
 dlg->addItemsList(list);
 dlg->exec();
 int elegido=dlg->getCheckedItemIndex();
 aux=list[elegido];
 list.remove(list[elegido]);
 conf.writeEntry(QString("DATABASE"), QString("DELETE"), list, ';');
 dlg=NULL;
  if(infos==NULL)
  {
  infos = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString("OK"), QString("Type " + aux +" removed"), this, "z", true, 0);
   infos->show();
 
  } infos=NULL;
}

void ZGui::verEliminados()
{  
  QFile salida("/mmc/mmca1/zCleanerList.txt");
  QTextStream sal(&salida);
  salida.open(IO_WriteOnly | IO_Translate);
  QString aux="";
  for(int i=0;i<eliminados.count();i++)
  //      aux+=aux + eliminados[i] + '\n';     

  sal << eliminados[i] << endl;
  if(infos==NULL)
  {
  infos = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString("OK"), QString("List save in /mmc/mmca1"), this, "z", true, 0);
   infos->show();
 
  } infos=NULL;
salida.close();
}

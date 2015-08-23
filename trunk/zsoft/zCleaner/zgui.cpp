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
//using namespace std;

ZGui::ZGui ( QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{
  infos=NULL;
  CreateWindow ( parent );
  ( ( ZApplication* ) qApp )->showMainWidget ( this );
}

ZGui::~ZGui()
{
 if(infos!=NULL) infos=NULL;
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
  myVBoxLayout->addWidget ( scrollPanel, 0 );


  //*****************************
  setContentWidget ( myWidget );
  //************** softkeys and menus **************************
  ZSoftKey *softKey = new ZSoftKey ( NULL , this , this );
  QPixmap* pm  = new QPixmap();
  pm->load(getProgramDir() + "img/about.png");
  QRect rect;
  ZOptionsMenu* menu = new ZOptionsMenu ( rect, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  menu->insertItem ( QString ( " About" ), NULL, pm, true, 0, 0 );
  menu->insertSeparator(1, 1); 
  pm->load(getProgramDir() + "img/white.png");
  menu->insertItem ( QString ( " Clean" ), NULL, pm, true, 2, 2 );
  menu->insertSeparator(3, 3); 
  pm->load(getProgramDir() + "img/exit.png");
  menu->insertItem ( QString ( " Exit" ), NULL, pm, true, 4, 4 );

  menu->connectItem ( 4, qApp, SLOT ( quit() ) );
  menu->connectItem ( 2, this, SLOT ( ejecutar() ) );
  menu->connectItem ( 0, this, SLOT ( about() ) );

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
    q.remove(lista[i]);
}

void ZGui::ejecutar()
{
 QStringList a="";
 a=limpiar("/mmc/mmca1","*.exe"); borrar(a); a="";
 a=limpiar("/mmc/mmca1","*.inf"); borrar(a); a="";
 a=limpiar("/mmc/mmca1","autorun.ini"); borrar(a); a="";
 a=limpiar("/ezxlocal/download/mystuff","*.exe"); borrar(a); a="";
 a=limpiar("/ezxlocal/download/mystuff","*.inf"); borrar(a); a="";
 a=limpiar("/ezxlocal/download/mystuff","autorun.ini"); borrar(a); a="";
 if(infos==NULL)
  {
  infos = new ZNoticeDlg(ZNoticeDlg::Information, 3000, QString("Your Z6 is clean now"), QString("!!"), this, "z", true, 0);
   infos->show();
 
 } infos=NULL;
}

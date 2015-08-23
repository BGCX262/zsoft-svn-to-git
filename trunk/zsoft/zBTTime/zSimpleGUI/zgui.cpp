//
// C++ Implementation: zgui
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
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
#include <ZLabel.h>
#include "resources.h"
//#include "zutils.h"

#define FILE_BT_CONFIG "/ezxlocal/download/appwrite/setup/ezx_bluetooth.cfg"
//#define FILE_SYSTEM_CONFIG "/ezx_user/download/appwrite/setup/ezx_system.cfg"
#define INI_BT_SECTION "Bluetooth Setup"
//using namespace std;
//extern ZUtils *zUtils;

ZGui::ZGui ( QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{
        dlg_bt_discover = NULL;
	znd = NULL;
  CreateWindow ( parent );
  ( ( ZApplication* ) qApp )->showMainWidget ( this );
}

ZGui::~ZGui()
{
        if( dlg_bt_discover != NULL ) delete dlg_bt_discover;
	if( znd != NULL ) delete znd;
}

void ZGui::CreateWindow ( QWidget* parent )
{
  setMainWidgetTitle ( "zBTTime 0.2" );
  ZWidget *myWidget = new ZWidget ( this, NULL, 0, ( ZSkinService::WidgetClsID ) 40 );
  QFont f ( qApp->font() );
  f.setPointSize ( 10 );
  myWidget->setFont ( f );

  QVBoxLayout *myVBoxLayout = new QVBoxLayout ( myWidget, 0 );
  //*****************************
  //*** add elements here
  QLabel *myLabel = new QLabel ( QString ( "<qt><font size=\"+1\">zBTTime 0.2</font><br>"
                                 "<font size=\"-1\">(c) 2008</font></qt>" ), myWidget );
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

  QRect rect;
  QPixmap* pm  = new QPixmap("/mmc/mmca1/.system/QTDownLoad/zBTTime/img/about.png");
  ZOptionsMenu* menu = new ZOptionsMenu ( rect, softKey, NULL, 0, ( ZSkinService::WidgetClsID ) 2 );
  menu->insertItem ( QString ( "About" ), NULL, pm, true, 0, 0 );
  //menu->insertItem ( QString ( "FileOpenDlg" ), NULL, NULL, true, 1, 1 );
  pm->load( "/mmc/mmca1/.system/QTDownLoad/zBTTime/img/time.png");  menu->insertItem ( QString ( "Time" ), NULL, pm, true, 1, 1 );
  pm->load("/mmc/mmca1/.system/QTDownLoad/zBTTime/img/exit.png");  
  menu->insertItem ( QString ( "Exit" ), NULL, pm, true, 2, 2 );

  menu->connectItem ( 2, qApp, SLOT ( quit() ) );
  menu->connectItem ( 1, this, SLOT ( BT_time() ) );
  //menu->connectItem ( 2, this, SLOT ( slot_fileSaveDlg() ) );
  menu->connectItem ( 0, this, SLOT ( about() ) );

  softKey->setOptMenu ( ZSoftKey::LEFT, menu );
  softKey->setText ( ZSoftKey::LEFT, "Menu", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, "Exit", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit())); 
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
  /*
  ZMessageDlg *dlg = new ZMessageDlg ( "Title", "Instruction", ZMessageDlg::just_ok, 0, this, "About", true, 0 );
  dlg->exec();
  delete dlg;
  dlg = NULL;
  */
  ZAboutDialog* aboutDlg = new ZAboutDialog();
  aboutDlg->exec();

 /* if ( aboutDlg->result() == 0 )
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


/*void ZGui::slot_fileOpenDlg()
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
}

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

void ZGui::BT_time()
{
	QString s1 = QString(FILE_BT_CONFIG);
	int val;
	ZConfig ini(s1, false);

		if( dlg_bt_discover == NULL )
		{
			val = ini.readNumEntry(QString(INI_BT_SECTION), QString("DiscoverablePeriod"), 5);
			QString a = QString("BTTime");
			dlg_bt_discover  = new ZNumPickerDlg(10, this, "ZNumPickerDlg", 0);
			ZNumModule* module = dlg_bt_discover->getNumModule();
			module->setMaxValue(20);
			module->setMinValue(1);
			module->setValue(val);
			
	    		ZLabel* label = new ZLabel(QString("value: "), module, NULL,0, (ZSkinService::WidgetClsID)4);
	    		module->setLabel(label, (ZNumModule::RelativeAlignment)0);
			
			dlg_bt_discover->setTitle("DiscoverablePeriod");
			//dlg_bt_discover->setInstructText("value:");
		}

		if (dlg_bt_discover->exec())
		{	
			int r = dlg_bt_discover->getNumValue();
			ini.writeEntry(QString(INI_BT_SECTION), QString("DiscoverablePeriod"), r);
			QString sr;
			sr = QString(" to %1 minutes").arg(r);
			
			if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::Information, 1000, QString("DiscoverablePeriod changed"), sr, this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
		}
}

/*QString ZGui::getProgramDir()
{
  QString s = QString ( qApp->argv() [0] ) ;
  qDebug ( s );
  int i = s.findRev ( "/" );
  s = s.remove ( i+1, s.length() - i );
  qDebug ( s );
  return s;
}*/

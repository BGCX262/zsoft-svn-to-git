#include "TestWidget.h"
#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <qfile.h>
#include "ZConfig.h"
#include <qtextcodec.h>



#define FILE_BT_CONFIG "/ezxlocal/download/appwrite/setup/ezx_bluetooth.cfg"
#define FILE_SYSTEM_CONFIG "/ezx_user/download/appwrite/setup/ezx_system.cfg"
#define INI_BT_SECTION "Bluetooth Setup"
#define INI_JAVA_SECTION "SYS_JAVA"

TestWidget::TestWidget(QWidget* parent, char* name)
                :ZKbMainWidget((ZHeader::HEADER_TYPE)3 , parent , name , WType_TopLevel)
{
        dlg = NULL;
	dlg_bt_settings = NULL;
	dlg_bt_discover = NULL;
	znd = NULL;
        setMainWidgetTitle("zBTTime");
        softKey = new ZSoftKey(NULL , this , this);
        softKey->setText(ZSoftKey::LEFT, "Options", (ZSoftKey::TEXT_PRIORITY)0);
        softKey->setText(ZSoftKey::RIGHT, "About", (ZSoftKey::TEXT_PRIORITY)0);

        scrollPanel = new ZScrollPanel(this, NULL, 0, (ZSkinService::WidgetClsID)4);
        //*****************
        
        // create menu
        QRect rect;

	menu_Main = new ZOptionsMenu(rect, this, NULL , 0 ,(ZSkinService::WidgetClsID)2 );
        // add menu items
        menu_Main->insertItem(QString("Exit") , NULL , NULL , true , 0 , 0 );
	menu_Main->insertItem(QString("Discoverable Period") , NULL , NULL , true , 1 , -1 );
	
	// LSK assing to menu
        softKey->setOptMenu(ZSoftKey::LEFT, menu_Main);
	menu_Main->connectItem(0, qApp, SLOT(quit()));
	menu_Main->connectItem(1, this, SLOT(BT_Discover()));

	softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(about()));
        
        

        
        //*****************
        

        QVBoxLayout* layout = getVBoxLayout();

        layout->addWidget(scrollPanel);
        setSoftKey(softKey);
}

TestWidget::~TestWidget()
{
	killTimers();
	if( dlg != NULL )delete dlg;
	if( dlg_bt_discover != NULL ) delete dlg_bt_discover;
	if( znd != NULL ) delete znd;
}

void TestWidget::about()
{
		if( dlg == NULL )
		{
			QString a = QString("About");
			QString b = QString("zBTTime ver. 0.1 \nby c_ro87 \ne-mail: cristian_ro87@hotmail.com \nwww.modmotov235.com.ar \nwww.modmymoto.com \nmotow510.foroactivo.es \nwww.motomod.com.ar ");
			dlg  = new ZMessageDlg(a , b , (ZMessageDlg::MessageDlgType)2 , 0 , this , "about" , true , 0);
		}
		dlg->show();
	
}

void TestWidget::BT_Discover()
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
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("DiscoverablePeriod changed"), sr, this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
		}
}

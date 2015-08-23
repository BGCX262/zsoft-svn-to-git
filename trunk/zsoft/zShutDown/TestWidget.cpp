//
// C++ Implementation: TestWidget
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "TestWidget.h"
#include "stdio.h"
//#include "iostream.h"
#include <stdlib.h>
#include <unistd.h>
#include <qfile.h>
#include "ZConfig.h"
#include <qtextcodec.h>



#define FILE_BT_CONFIG "/ezxlocal/download/appwrite/setup/ezx_bluetooth.cfg"
#define FILE_SYSTEM_CONFIG "/ezx_user/download/appwrite/setup/ezx_system.cfg"
#define INI_BT_SECTION "Bluetooth Setup"
#define INI_JAVA_SECTION "SYS_JAVA"

//using namespace std;

TestWidget::TestWidget(QWidget* parent, char* name)
                :ZKbMainWidget((ZHeader::HEADER_TYPE)3 , parent , name , WType_TopLevel) // Looks like my bugs are found there... Have to search in WType & WStyle
{
        dlg = NULL;
	dlg_bt_settings = NULL;
	dlg_bt_discover = NULL;
	dlg_java_heap = NULL;
	dlg_java_jsr135_volume = NULL;
	znd = NULL;
        setMainWidgetTitle("Test App");
        softKey = new ZSoftKey(NULL , this , this);
        softKey->setText(ZSoftKey::LEFT, "Menu", (ZSoftKey::TEXT_PRIORITY)0);
        softKey->setTextForOptMenuHide("Menu");
        softKey->setText(ZSoftKey::RIGHT, "About", (ZSoftKey::TEXT_PRIORITY)0);
        scrollPanel = new ZScrollPanel(this, NULL, 0, (ZSkinService::WidgetClsID)4);
        //*****************
        
        // create menu
        QRect rect, rect2, rect3;

	//submenu
	subMenu_BT = new ZOptionsMenu(rect2, this, NULL, 0, (ZSkinService::WidgetClsID)2);
	subMenu_BT->insertItem(QString("Device name") , NULL , NULL , true , 0 , 0 );
	subMenu_BT->insertItem(QString("DiscoverablePeriod") , NULL , NULL , true , 1 , -1 );

	subMenu_Java = new ZOptionsMenu(rect3, this, NULL, 0, (ZSkinService::WidgetClsID)2);
	subMenu_Java->insertItem(QString("Heap size") , NULL , NULL , true , 0 , 0 );
	subMenu_Java->insertItem(QString("Jsr135 volume") , NULL , NULL , true , 1 , -1 );

        menu_Main = new ZOptionsMenu(rect, this, NULL , 0 ,(ZSkinService::WidgetClsID)2 );
        // add menu items
        menu_Main->insertItem(QString("Exit") , NULL , NULL , true , 0 , 0 );
	menu_Main->insertItem(QString("BT settings") , subMenu_BT , NULL , true , 1 , -1 );
	menu_Main->insertItem(QString("Java settings") , subMenu_Java , NULL , true , 2 , -1 );

	// LSK assing to menu
        softKey->setOptMenu(ZSoftKey::LEFT, menu_Main);
	menu_Main->connectItem(0, qApp, SLOT(quit()));
	//menu->connectItem(1, this, SLOT(BTSettings()));
  	subMenu_BT->connectItem(0, this, SLOT(BTSettings()));
	subMenu_BT->connectItem(1, this, SLOT(BT_Discover()));

	subMenu_Java->connectItem(0, this, SLOT(JavaHeap()));
	subMenu_Java->connectItem(1, this, SLOT(JavaJSR135Volume()));
        // RSK assign to show dialog
        softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(about()));
        
        //****************
	ZLabel* label = new ZLabel(QString("DateTime: "), this, "ZLabel",0, (ZSkinService::WidgetClsID)4);
        QDateTime* dt = new QDateTime();
        label->setText(QString(dt->currentDateTime().toString()));
	label->setAutoResize(true);
        label->setPreferredWidth(240);
        scrollPanel->addChild(label , 2 , 2);
        label->setScrolledInPanel(TRUE);
        ZLabel* memlabel;
        ZLabel* cpulabel;

         //*****************
        QFile f("/proc/meminfo");
        QString tmp;
        QStringList datalist;
        QStringList greplist;
        if (f.open(IO_ReadOnly))   
        {
                while (f.readLine(tmp, 256) != -1) datalist += tmp;
                //**********************
                greplist = datalist.grep("Mem", true);
                memlabel = new ZLabel(QString("Meminfo:"), this, "ZLabel",0, (ZSkinService::WidgetClsID)4);
                tmp = greplist.join( "\n" );
                memlabel->setText(tmp);
                memlabel->setAutoResize(TRUE);
                memlabel->setPreferredWidth(240);
                scrollPanel->addChild(memlabel , 2 , label->height() + 2);
                memlabel->setScrolledInPanel(TRUE);
                f.close();
        }     

        QFile f2("/proc/cpu/clocks");
        datalist.clear();
        greplist.clear();
        tmp = "";
        if (f2.open(IO_ReadOnly))   
        {
                while (f2.readLine(tmp, 256) != -1) datalist += tmp;
                greplist = datalist.grep("CPU_CLK", true);
                cpulabel = new ZLabel(QString("CPU rate:"), this, "ZLabel",0, (ZSkinService::WidgetClsID)4);
                tmp = greplist.join( "" );
                tmp = tmp.replace(QRegExp("^CPU_CLK:"), "Cur. CPU rate: ");
                cpulabel->setText(tmp);
                cpulabel->setAutoResize(TRUE);
                cpulabel->setPreferredWidth(240);
                scrollPanel->addChild(cpulabel , 2 , label->height() + memlabel->height());
                cpulabel->setScrolledInPanel(TRUE);
                f2.close();
        }     

        QVBoxLayout* layout = getVBoxLayout();
        layout->addWidget(scrollPanel);
        setSoftKey(softKey);
}

TestWidget::~TestWidget()
{
	killTimers();
	if( dlg != NULL )delete dlg;
	if( dlg_bt_settings != NULL ) delete dlg_bt_settings;
	if( dlg_bt_discover != NULL ) delete dlg_bt_discover;
	if( dlg_java_jsr135_volume != NULL ) delete dlg_java_jsr135_volume;
	if( dlg_java_heap != NULL ) delete dlg_java_heap;
	if( znd != NULL ) delete znd;
}

void TestWidget::about()
{
		if( dlg == NULL )
		{
			QString a = QString("About");
			QString b = QString("TestApp ver. 0.1 \nby BeZ \ne-mail: bezols@gmail.com");
			dlg  = new ZMessageDlg(a , b , (ZMessageDlg::MessageDlgType)2 , 0 , this , "about" , true , 0);
		}
		dlg->show();
	
}

void TestWidget::BTSettings()
{
		if( dlg_bt_settings == NULL )
		{
			QString s1 = QString(FILE_BT_CONFIG);
			ZSingleCaptureDlg::CaptureDlgType type = ZSingleCaptureDlg::normal2;
			
			ZConfig ini(s1, false);
			s1 = ini.readEntry(QString(INI_BT_SECTION), QString("defaultLocalDevName"), QString("unknown"));
			
			QString a = QString("BT Settings");
			QString b = QString("1234567890");
			dlg_bt_settings  = new ZSingleCaptureDlg(a, s1, type, this, "ZSingleCaptureDlg", false, 0, 0);
		}
		dlg_bt_settings->show();
}

void TestWidget::JavaHeap()
{
	QStringList list;
	QString s1 = QString(FILE_SYSTEM_CONFIG);
	bool ok;
	ZConfig ini(s1, false);
 	QString msg = QString("Select Heap size:");
 	QString hdr = QString("Java heap size");

	list += QString::fromUtf8("unlimit"); //0
	list += QString::fromUtf8("512 Kb"); //1
	list += QString::fromUtf8("768 Kb"); //2
	list += QString::fromUtf8("1 Mb"); //3
	list += QString::fromUtf8("2 Mb"); //4
	list += QString::fromUtf8("4 Mb"); //5

	if( dlg_java_heap == NULL )
	{
		s1 = ini.readEntry(QString(INI_JAVA_SECTION), QString("JavaHeapSize"), QString("4"));
		dlg_java_heap  = new ZSingleSelectDlg(hdr, msg, this, "ZSingleSelectDlg", true, 0, 0);
		dlg_java_heap->addItemsList(list);
		ZListBox* listbox = dlg_java_heap->getListBox();
		listbox->checkItem(s1.toInt(&ok, 10), true);
	}

	if (dlg_java_heap->exec())
	{
		QString sr;
		int r = dlg_java_heap->getCheckedItemIndex();
		sr = QString(" to %1").arg(list[r]);
		ini.writeEntry(QString(INI_JAVA_SECTION), QString("JavaHeapSize"), r);
		if ( znd == NULL)
		{
			znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("JavaHeap changed"), sr, this, "z", true, 0);
        		znd->show(); 
		}
		znd = NULL;
	}
}

void TestWidget::BT_Discover()
{
	QString s1 = QString(FILE_BT_CONFIG);
	int val;
	ZConfig ini(s1, false);

		if( dlg_bt_discover == NULL )
		{
			val = ini.readNumEntry(QString(INI_BT_SECTION), QString("DiscoverablePeriod"), 5);
			QString a = QString("BT Settings");
			dlg_bt_discover  = new ZNumPickerDlg(10, this, "ZNumPickerDlg", 0);
			ZNumModule* module = dlg_bt_discover->getNumModule();
			module->setMaxValue(20);
			module->setMinValue(1);
			module->setValue(val);
	    		ZLabel* label = new ZLabel(QString("value: "), module, NULL,0, (ZSkinService::WidgetClsID)4);
	    		module->setLabel(label, (ZNumModule::RelativeAlignment)0);
			dlg_bt_discover->setTitle("DiscoverablePeriod");
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

void TestWidget::JavaJSR135Volume()
{
	QString s1 = QString(FILE_SYSTEM_CONFIG);
	int val;
	ZConfig ini(s1, false);

		if( dlg_bt_discover == NULL )
		{
			val = ini.readNumEntry(QString(INI_JAVA_SECTION), QString("JSR135_Volume"), 7);
			QString a = QString("Java Settings");
			dlg_java_jsr135_volume  = new ZNumPickerDlg(10, this, "ZNumPickerDlg", 0);
			ZNumModule* module = dlg_java_jsr135_volume->getNumModule();
			module->setMaxValue(7);
			module->setMinValue(0);
			module->setValue(val);
			
	    		ZLabel* label = new ZLabel(QString("value: "), module, NULL,0, (ZSkinService::WidgetClsID)4);
	    		module->setLabel(label, (ZNumModule::RelativeAlignment)0);
			
			dlg_java_jsr135_volume->setTitle("JSR135 Volume");
		}

		if (dlg_java_jsr135_volume->exec())
		{	
			int r = dlg_java_jsr135_volume->getNumValue();
			ini.writeEntry(QString(INI_JAVA_SECTION), QString("JSR135_Volume"), r);
			QString sr;
			sr = QString(" to %1").arg(r);
			
			if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("JSR135 Volume changed"), sr, this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
		}
}

/*
 * VMemory port to z6 by jarg72
 * Copyright (C) 2007 Lasly
 */


//#define QT_NO_TEXTCODEC
#define QT_NO_DRAGANDDROP
#define QT_NO_PROPERTIES
#include <E2_EZX_ZApplication.h>
#include <E2_EZX_ZKbMainWidget.h>
#include <E2_EZX_ZMessageDlg.h>
#include <E2_EZX_ZLabel.h>
#include <E2_EZX_ZScrollPanel.h>
#include <E2_EZX_ZSoftKey.h>
#include <E2_EZX_ZOptionsMenu.h>
#include <E2_EZX_ZFormContainer.h>
#include <E2_EZX_ZComboBox.h>
#include <qpainter.h>
#include <qlabel.h>
#include <stdio.h>
#include <stdlib.h>
#include <qfile.h>
#include <qtextcodec.h>
#include <qlayout.h>

#define SWAPDIR "mkdir /mmc/mmca1/.memcache"
#define SWAPFILE "/mmc/mmca1/.memcache/swapfile"
#define EXEC_OFF "start-stop-daemon --start --exec /sbin/telinit swapoff /mmc/mmca1/.memcache/swapfile"
#define EXEC_ON "start-stop-daemon --start --exec /sbin/telinit swapon -p 1 -v /mmc/mmca1/.memcache/swapfile"
#define MK_SWAP "start-stop-daemon --start --exec /sbin/telinit mkswap /mmc/mmca1/.memcache/swapfile"
 
int GetVMemorySize()
{	
	int size = 0;
	QFile file(SWAPFILE);
	if( file.open(IO_ReadOnly) )
	{
		file.at(1000);
		size = file.size();
		file.close();
	}
	return size >> 20;
}

int IsVMemoryOn()
{
	int ret = 0;
	char tmp[1024];
	memset( tmp , 0 , 1024);
	FILE* file = popen("free" , "r");
	fread(tmp, 1024, 1024 , file);
	pclose(file);
	char* p = strstr(tmp , "Swap" );
	p += 5;
	ret = atoi(p);
	return ret;
}

void VMemoryOff()
{
	if( IsVMemoryOn() )
	{
		system(EXEC_OFF);
	}
}

int VMemoryOn(int size)
{
	int oldsize = GetVMemorySize();
	system(SWAPDIR);
	if( oldsize != size )
	{
		VMemoryOff();
		QFile::remove(SWAPFILE);	
		QFile file(SWAPFILE);
		if( file.open(IO_WriteOnly) )
		{
			char* cache = new char[256*1024];
			memset( cache , 0 , 256*1024 );
			for( int i = 0 ; i < ( size << 2 ) ; i++ )
			{
				file.writeBlock(cache , 256*1024);
			}
			file.close();
		}
	}
	system(MK_SWAP);
	system(EXEC_ON);
}


QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");QString ChineseAndEnglish(const char*ChineseString){	return gbk_codec->toUnicode(ChineseString);} 

class MyDialog : public ZKbMainWidget
{
	Q_OBJECT
	ZComboBox* sizeBox;
	ZComboBox* isOpenBox;
	public:
	MyDialog( ):ZKbMainWidget((ZHeader::HEADER_TYPE)3,NULL , "ZMainWidget" , 0)
	{
		setMainWidgetTitle(ChineseAndEnglish("Virtual Memory"));
		ZSoftKey* softKey = new ZSoftKey(NULL , this , this);
		QRect rect;
		ZOptionsMenu* menu = new ZOptionsMenu(rect, softKey, NULL , 0 ,(ZSkinService::WidgetClsID)2 );
		menu->insertItem(ChineseAndEnglish("Set") , NULL , NULL , true , 0 , 0 );
		menu->insertItem(ChineseAndEnglish("Exit") , NULL , NULL , true , 1 , 1 );

		softKey->setOptMenu(ZSoftKey::LEFT, menu);
		softKey->setText(ZSoftKey::LEFT, ChineseAndEnglish("Options"), (ZSoftKey::TEXT_PRIORITY)0);
		softKey->setText(ZSoftKey::RIGHT, ChineseAndEnglish("About"), (ZSoftKey::TEXT_PRIORITY)0);
		softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(about()));
		menu->connectItem(0, this, SLOT(set()));
		menu->connectItem(1, qApp, SLOT(quit()));

		sizeBox = new ZComboBox(this,"Size",true);
		sizeBox->insertItem("4M", 0);
		sizeBox->insertItem("8M", 1);
		sizeBox->insertItem("16M", 2);
		sizeBox->insertItem("32M", 3);
		sizeBox->insertItem("64M", 4);
		sizeBox->insertItem("128M", 5);
		sizeBox->setCurrentItem( (GetVMemorySize()%2) > 5 ? 5 : (GetVMemorySize()%2) );
		isOpenBox = new ZComboBox(this,"IsOpen",true);
		isOpenBox->insertItem(ChineseAndEnglish("Active Virtual Memory"), 0);
		isOpenBox->insertItem(ChineseAndEnglish("Desactive Virtual Memory"), 1);
		isOpenBox->setCurrentItem( IsVMemoryOn()?1:0 );

		QVBoxLayout* layout = getVBoxLayout();
		ZScrollPanel *zsv = new ZScrollPanel(this , NULL , 0,  (ZSkinService::WidgetClsID)4);
		QString info = ChineseAndEnglish("Virtual Memory Current State\n");
		info += ChineseAndEnglish("Virtual Memory On? ") + ( IsVMemoryOn()? ChineseAndEnglish("Yes") :ChineseAndEnglish("No") );
		info += ChineseAndEnglish("\nSize ") + QString::number(GetVMemorySize()) + "M";
		ZLabel* infolabel = new ZLabel(info, this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
		infolabel->setPreferredWidth(240);
		infolabel->setAutoResize(true );

		int height = heightForWidth(240);
		zsv->addChild(infolabel , 10 , height);
		height = infolabel->heightForWidth(240) + sizeBox->getBtnHSpacing() ;
		zsv->addChild(sizeBox, 10 , height);
		height += (sizeBox->getContentRect()).height() + sizeBox->getBtnHSpacing() * 4 ;
		zsv->addChild(isOpenBox, 10 , height);
		layout->addWidget(zsv);

		setSoftKey(softKey);
		dlg = NULL;
	}
	~MyDialog( )
	{
		if( dlg != NULL )
		{
			delete dlg;
		}
	}
	ZMessageDlg *dlg;
public slots:
	void set()
	{
		int isOpen = !(isOpenBox->currentItem());
		int size = 4 << sizeBox->currentItem();
		if( isOpen )
		{
			VMemoryOn(size);
		}
		else
		{
			VMemoryOff();
		}
		qApp->quit();
	}
	void about()
	{
		if( dlg == NULL )
		{
			QString a = ChineseAndEnglish("About");
			QString b = ChineseAndEnglish("VMemory ver1.0\nby jarg72\njhona72@gmail.com\nOriginally by Lasly for E2");
			dlg  = new ZMessageDlg(a , b , (ZMessageDlg::MessageDlgType)2 , 0 , this , "about" , true , 0);
		}
		dlg->show();
	}
};

int main( int argc, char **argv )
{
	ZApplication* a = new ZApplication( argc, argv );
	MyDialog* w = new MyDialog();
   	a->setMainWidget( w );
    	w->show();
	int ret = a->exec();
	delete w;
	delete a;
   	return ret;

}


#include "VMemory.moc"


#include "TestWidget.h"
#include "stdio.h"
//#include "iostream.h"
#include <stdlib.h>
#include <unistd.h>
#include <qfile.h>
#include "ZConfig.h"
#include <qtextcodec.h>
#include <math.h>
#include <ZSingleSelectDlg.h>
//using namespace std;

TestWidget::TestWidget(QWidget* parent, char* name)
                :ZKbMainWidget((ZHeader::HEADER_TYPE)3 , parent , name , WType_TopLevel) 
{
	color=Qt::black;
	size=20;
        dlg = NULL;
	dlg_size = NULL;
	znd = NULL;
        setMainWidgetTitle("zCronometer");
        softKey = new ZSoftKey(NULL , this , this);
        softKey->setText(ZSoftKey::LEFT, "Menu", (ZSoftKey::TEXT_PRIORITY)0);
        softKey->setTextForOptMenuHide("Menu");
        softKey->setText(ZSoftKey::RIGHT, "Stop", (ZSoftKey::TEXT_PRIORITY)0);
        scrollPanel = new ZScrollPanel(this, NULL, 0, (ZSkinService::WidgetClsID)4);
        //*****************
        QPixmap* p=new QPixmap();;
        // create menu
        QRect rect;
        menu_Main = new ZOptionsMenu(rect, this, NULL , 0 ,(ZSkinService::WidgetClsID)2 );
        // add menu items
        p->load(getProgramDir() + "img/exit.png");
        menu_Main->insertItem(QString("  Exit") , NULL , p , true , 0 , 0 );
	menu_Main->insertSeparator(1, 1);
        p->load(getProgramDir() + "img/about.png");
	menu_Main->insertItem(QString("  About") , NULL , p , true , 2 , 2 );
	menu_Main->insertSeparator(3, 3);
	p->load(getProgramDir() + "img/color.png");
	menu_Main->insertItem(QString("  Color") , NULL , p , true , 4 , 4 );
        menu_Main->insertSeparator(5, 5);
        p->load(getProgramDir() + "img/alarm.png");	
	menu_Main->insertItem(QString("  Start") , NULL , p , true , 6 , 6 );

	// LSK assing to menu
        softKey->setOptMenu(ZSoftKey::LEFT, menu_Main);
	menu_Main->connectItem(0, qApp, SLOT(quit()));
	menu_Main->connectItem(2, this, SLOT(about()));
	menu_Main->connectItem(4, this, SLOT(changecolor()));
	menu_Main->connectItem(6, this, SLOT(crearTimer()));
        //------------------
        softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(para()));
        
        //****************
	label = new ZLabel(QString("Tiempo: "), this, "ZLabel",0, (ZSkinService::WidgetClsID)4);
   
        tiempo = new QTime();
    
	label->setAutoResize(true);
        label->setPreferredWidth(240);
	label->setFontColor(color);
        scrollPanel->addChild(label , 2 , 2);
        label->setScrolledInPanel(TRUE);
   

        QVBoxLayout* layout = getVBoxLayout();
        layout->addWidget(scrollPanel);
        setSoftKey(softKey);
}

TestWidget::~TestWidget()
{
	killTimers();
	if( dlg != NULL )delete dlg;
	if( dlg_size != NULL ) delete dlg_size;
	if( znd != NULL ) delete znd;
        if( dlg != NULL ) delete dlg;
}

void TestWidget::about()
{
		if( dlg == NULL )
		{
			QString a = QString("About");
			QString b = QString("zCronometer ver. 0.2 \nby c_ro87 \ne-mail: cristian_ro87@hotmail.com");
			dlg  = new ZMessageDlg(a , b , (ZMessageDlg::MessageDlgType)2 , 0 , this , "about" , true , 0);
		}
		dlg->show();
	
}

void TestWidget::crono()
{
	tiempo->start();
	h1=tiempo->currentTime().hour();
	m1=tiempo->currentTime().minute();
	s1=tiempo->currentTime().second();
	ms1=tiempo->currentTime().msec();

}         

void TestWidget::para()
{
	timer->stop();
	texto();
}
void TestWidget::texto()
{

	h2=tiempo->currentTime().hour();
	m2=tiempo->currentTime().minute();
	s2=tiempo->currentTime().second();
	ms2=tiempo->currentTime().msec();

        //-------------------------------
	
	if(h2 >= h1) h=h2-h1; else h=(24-h1)+h2;
	if(m2 >= m1) m=m2-m1; else m=(60-m1)+m2;
	if(s2 >= s1) s=s2-s1; else s=(60-s1)+s2;
	if(ms2 >= ms1) ms=ms2-ms1; else ms=(999-ms1)+ms2;//o (1-ms1) + ms2
        //-------------------------------
	hst=hst.setNum(h);
	mst=mst.setNum(m);
	sst=sst.setNum(s);
	msst=msst.setNum(ms);
	label->setText(hst+":"+mst+":"+sst+":"+msst);
	label->setAutoResize(true);
	label->setFontColor(color);
	label->setPreferredWidth(240);
	//scrollPanel->addChild(label , 2 , 2);
	label->setScrolledInPanel(TRUE);
}

void TestWidget::crearTimer()
{
  	timer = new QTimer(this);
        crono();
	// Cuando se actualice un microsegundo se hace un refresh del texto
	connect( timer, SIGNAL(timeout()), SLOT(texto()) );
	// start timer in 00ms
	timer->start( 00 );
}

QString TestWidget::getProgramDir()
{
 	 QString ProgDir = QString ( qApp->argv() [0] ) ;
 	 int i = ProgDir.findRev ( "/" );
 	 ProgDir.remove ( i+1, ProgDir.length() - i );
 	 return ProgDir;
}

void TestWidget::changecolor()
{
	 int elegido=0;
	 ZSingleSelectDlg* dlg;
         dlg=NULL;
         QStringList lista;
	 lista +="Black";
	 lista +="Red";
	 lista +="White";
	 lista +="Green";
	 lista +="Blue";
	 if( dlg == NULL )
	        {
	                dlg  = new ZSingleSelectDlg("Color" , "Select:", this, "ZSingleSelectDlg", true, 0, 0);
	                dlg->addItemsList(lista);
	        
	        }
	        if(dlg->exec())
	        {
	        	elegido=dlg->getCheckedItemIndex();
                }
	if(elegido==0) color=Qt::black;
	else if(elegido==1) color=Qt::red;	
	else if(elegido==2) color=Qt::white;
	else if(elegido==3) color=Qt::green;
	else if(elegido==4) color=Qt::blue;

	dlg=NULL;
	if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::Information, 1000, QString("Color changed"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
}

void TestWidget::changesize()
{
/*	if( dlg_size == NULL )
		{
			dlg_size  = new ZNumPickerDlg(10, this, "ZNumPickerDlg", 0);
			ZNumModule* module = dlg_size->getNumModule();
			module->setMaxValue(70);
			module->setMinValue(10);
			module->setValue(size);
			
	    		ZLabel* label = new ZLabel(QString("Size: "), module, NULL,0, (ZSkinService::WidgetClsID)4);
	    		module->setLabel(label, (ZNumModule::RelativeAlignment)0);
			
			dlg_size->setTitle("Size");
			//dlg_size->setInstructText("value:");
		}

		if (dlg_size->exec())
		{	
			int r = dlg_size->getNumValue();
			size=r;
			if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::Information, 1000, QString("Size changed"), r, this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
		}*/
}


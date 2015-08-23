
#include "TestWidget.h"
#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <qfile.h>
#include "ZConfig.h"
#include <qtextcodec.h>
#include <qdir.h> //para crear directorios

////////// ARCHIVOS a usar
#define SDHIDE "/mmc/mmca1/.Z6HIDE"
#define SDSHOW "/mmc/mmca1/Z6HIDE"
#define PHONEHIDE "/ezxlocal/download/mystuff/.Z6HIDE"
#define PHONESHOW "/ezxlocal/download/mystuff/Z6HIDE"


//////////////////////////

TestWidget::TestWidget(QWidget* parent, char* name)
                :ZKbMainWidget((ZHeader::HEADER_TYPE)3 , parent , name , WType_TopLevel) 
{//Terminado

///Esto crea el entorno principal de la aplicacion
        elegido=0;
        dlg = NULL;//para el about
	znd = NULL;
        dlg_java_heap = NULL;
        setMainWidgetTitle("zHideFolder");
        softKey = new ZSoftKey(NULL , this , this);
        softKey->setText(ZSoftKey::LEFT, "Menu", (ZSoftKey::TEXT_PRIORITY)0);
        softKey->setText(ZSoftKey::RIGHT, "About", (ZSoftKey::TEXT_PRIORITY)0);

        scrollPanel = new ZScrollPanel(this, NULL, 0, (ZSkinService::WidgetClsID)4);
        //*****************
        
        // create menu
        QRect rect, rect2, rect3;

	//submenu
	subMenu_Folder = new ZOptionsMenu(rect2, this, NULL, 0, (ZSkinService::WidgetClsID)2);
	subMenu_Folder->insertItem(QString("SD/Phone") , NULL , NULL , true , 0 , 0 ); 
	subMenu_Folder->insertItem(QString("Create Folder") , NULL , NULL , true , 1 , -1 );

	subMenu_SH = new ZOptionsMenu(rect3, this, NULL, 0, (ZSkinService::WidgetClsID)2);
	subMenu_SH->insertItem(QString("Show Folder") , NULL , NULL , true , 0 , 0 );
	subMenu_SH->insertItem(QString("Hide Folder") , NULL , NULL , true , 1 , -1 );

        menu_Main = new ZOptionsMenu(rect, this, NULL , 0 ,(ZSkinService::WidgetClsID)2 );
        // add menu items
        menu_Main->insertItem(QString("Exit") , NULL , NULL , true , 0 , 0 );
	menu_Main->insertItem(QString("Folder") , subMenu_Folder , NULL , true , 1 , -1 );
	menu_Main->insertItem(QString("Show/Hide") , subMenu_SH , NULL , true , 2 , -1 );

	// LSK assing to menu
        softKey->setOptMenu(ZSoftKey::LEFT, menu_Main);
	menu_Main->connectItem(0, qApp, SLOT(quit()));
	//menu->connectItem(1, this, SLOT(BTSettings()));
  	subMenu_Folder->connectItem(0, this, SLOT(BTSettings()));
	subMenu_Folder->connectItem(1, this, SLOT(CreateFolder()));

	subMenu_SH->connectItem(0, this, SLOT(ShowFolder()));
	subMenu_SH->connectItem(1, this, SLOT(HideFolder()));
        // RSK assign to show dialog
        softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(about()));
        
        

        
        //*****************
        

        QVBoxLayout* layout = getVBoxLayout();

        layout->addWidget(scrollPanel);
        setSoftKey(softKey);
}

TestWidget::~TestWidget()
{//Terminado Desctructor
	elegido = 0;
	if( dlg != NULL )delete dlg;
	if( znd != NULL ) delete znd;
        if(dlg_java_heap != NULL) delete dlg_java_heap;
}

void TestWidget::about()
{//Terminado Caja Acerca de
		if( dlg == NULL )
		{
			QString a = QString("About");
			QString b = QString("zHideFolder ver. 0.2 Beta \nby c_ro87 \ne-mail: cristian_ro87@hotmail.com");
			dlg  = new ZMessageDlg(a , b , (ZMessageDlg::MessageDlgType)2 , 0 , this , "About" , true , 0);
		}
		dlg->show();
	
}

void TestWidget::BTSettings()
{
//Esta funcion es para elegir la locacion PHONE o SD, no se si anda jeje
QStringList list;
	 	QString msg = QString("Select location:");
 	QString hdr = QString("SD/Phone");
        
        
	list += QString::fromUtf8("SD"); //0
	list += QString::fromUtf8("Phone"); //1
	
	if( dlg_java_heap == NULL )
	{
		dlg_java_heap  = new ZSingleSelectDlg(hdr, msg, this, "ZSingleSelectDlg", true, 0, 0);
		dlg_java_heap->addItemsList(list);
	}

	if (dlg_java_heap->exec())
	{
		elegido = dlg_java_heap->getCheckedItemIndex();
                
	if ((elegido==0) && (znd == NULL))
		{
			znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("SD"), "SD Folder", this, "z", true, 0);
        		znd->show(); 
                        znd=NULL;
		}
		
	
         else if(znd==NULL){
			znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("Phone"), "Phone Folder", this, "z", true, 0);
        		znd->show(); 
		}

		znd = NULL;
         }
}

void TestWidget::ShowFolder()
{// Funcion para mostrar la cxarpeta
  if(elegido==0) 
    {
	if (! dir.exists(SDSHOW))
         {//si no existe la carpte
        dir.rename(SDHIDE,SDSHOW); //la creo
                        if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("SD Folder Show"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
          }
    }

else if(! dir.exists(PHONESHOW)) 
  {//si no existe la carpte
        dir.rename(PHONEHIDE,PHONESHOW); //la creo
             if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("Phone Folder Show"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
    }

else {
	if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("Folder Show"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;	
     }
}

void TestWidget::CreateFolder()
{//termindado Funcion para crear la carpeta
//if (!dir.exists(SDSHOW) && !dir.exists(SDHIDE) && !dir.exists(PHONEHIDE) && !dir.exists(PHONESHOW))
//{
  if(elegido==0)
    {
        if ((! dir.exists(SDSHOW)) && (!dir.exists(SDHIDE))) 
         {//si no existe la carpte
         dir.mkdir(SDSHOW); //la creo
         if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("SD Folder is create"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
	
          } 

    }
       
        
    
else if((!dir.exists(PHONESHOW)) && (!dir.exists(PHONEHIDE)))
   {
           dir.mkdir(PHONESHOW);
                if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("Phone Folder is create"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
  }
	
else 		         {
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("Folder already exists"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;


}
///////////Tengo dudas con esto

void TestWidget::HideFolder()
{/////////////////////////termindado Funcion para ocultar la carpeta
if(elegido==0)
   {
        if (! dir.exists(SDHIDE)) 
        {//si no existe la carpte
        dir.rename(SDSHOW,SDHIDE); //la creo
if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("SD Folder Hide"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
        }
   }
else  if ( !dir.exists(PHONEHIDE)) 
     {//si no existe la carpte
        dir.rename(PHONESHOW,PHONEHIDE); //la creo
	if ( znd == NULL)
			{
				znd = new ZNoticeDlg(ZNoticeDlg::notice, 1000, QString("Phone Folder Hide"), "", this, "z", true, 0);
        			znd->show(); 
			}
			znd = NULL;
     }

		}


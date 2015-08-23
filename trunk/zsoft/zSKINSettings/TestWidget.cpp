#include "TestWidget.h"
#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <qfile.h>
#include "ZConfig.h"
#include <qtextcodec.h>
#include <qdir.h> //para crear directorios
#include <string>
#include <fstream>
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <vector>
#include <string>
#include <qdir.h>
#include <stdio.h>
//#include <stdlib.h>

using namespace std;

QFile log("/mmc/mmca1/.log");


TestWidget::TestWidget(QWidget* parent, char* name)
                :ZKbMainWidget((ZHeader::HEADER_TYPE)3 , parent , name , WType_TopLevel) 
{//Terminado

///Esto crea el entorno principal de la aplicacion
        elegido=0;
        carpeta="";
        dlg = NULL;//para el about
	znd = NULL;
        operadorvi = NULL;
        clockcolor = NULL;
        timedialog = NULL;
        clocksize = NULL;
        smod=NULL;
        calendarcolor=NULL;
        setMainWidgetTitle("zSKINSettings");
        softKey = new ZSoftKey(NULL , this , this);
        softKey->setText(ZSoftKey::LEFT, "Menu", (ZSoftKey::TEXT_PRIORITY)0);
        softKey->setText(ZSoftKey::RIGHT, "About", (ZSoftKey::TEXT_PRIORITY)0);

        scrollPanel = new ZScrollPanel(this, NULL, 0, (ZSkinService::WidgetClsID)4);
        //*****************
        
        // create menu
        QRect rect, rect2, rect3;

	//submenu
	subMenu_Folder = new ZOptionsMenu(rect2, this, NULL, 0, (ZSkinService::WidgetClsID)2);
	subMenu_Folder->insertItem(QString("Operador") , NULL , NULL , true , 0 , 0 ); 
	subMenu_Folder->insertItem(QString("Clock Size") , NULL , NULL , true , 1 , -1 );
        subMenu_Folder->insertItem(QString("Clock Position") , NULL , NULL , true , 2 , -2 );
        subMenu_Folder->insertItem(QString("Clock Color") , NULL , NULL , true , 3 , -3 );
        subMenu_Folder->insertItem(QString("Calendar Day Color") , NULL , NULL , true , 4 , -4 );
        subMenu_Folder->insertItem(QString("SkinMod") , NULL , NULL , true , 5 , -5 );
        subMenu_Folder->insertItem(QString("Incoming Call Color Name") , NULL , NULL , true , 6 , -6 );
        subMenu_Folder->insertItem(QString("Song Color") , NULL , NULL , true , 7 , -7 );
        subMenu_Folder->insertItem(QString("Song Time Color") , NULL , NULL , true , 8 , -8 );
	
        menu_Main = new ZOptionsMenu(rect, this, NULL , 0 ,(ZSkinService::WidgetClsID)2 );
        // add menu items
        menu_Main->insertItem(QString("Exit") , NULL , NULL , true , 0 , 0 );
	menu_Main->insertItem(QString("Edit") , subMenu_Folder , NULL , true , 1 , -1 );
        

	// LSK assing to menu
        softKey->setOptMenu(ZSoftKey::LEFT, menu_Main);
	menu_Main->connectItem(0, qApp, SLOT(quit()));
  
  	subMenu_Folder->connectItem(0, this, SLOT(operadora()));
	subMenu_Folder->connectItem(1, this, SLOT(csize()));
        subMenu_Folder->connectItem(2, this, SLOT(clockpos()));
        subMenu_Folder->connectItem(3, this, SLOT(ccolor()));
        subMenu_Folder->connectItem(4, this, SLOT(calendar()));
        subMenu_Folder->connectItem(5, this, SLOT(skinmod()));
        subMenu_Folder->connectItem(6, this, SLOT(colornomllamada()));
        subMenu_Folder->connectItem(7, this, SLOT(reprocolor()));
        subMenu_Folder->connectItem(8, this, SLOT(reprotimecolor()));
	
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
        if( calendarcolor!=NULL) delete calendarcolor;
	if( dlg != NULL )delete dlg;
	if( znd != NULL ) delete znd;
        if(operadorvi != NULL) delete operadorvi;
	if(timedialog != NULL) delete timedialog;
	if(smod != NULL) delete smod;
	if(clocksize != NULL) delete clocksize;
	if(clockcolor != NULL) delete clockcolor;
}

void TestWidget::about()
{//Terminado Caja Acerca de
		if( dlg == NULL )
		{
			QString a = QString("About");
			QString b = QString("zSKINSettings ver. 0.5c Beta \nby c_ro87 \ne-mail: cristian_ro87@hotmail.com\nwww.modmymoto.com");
			dlg  = new ZMessageDlg(a , b , (ZMessageDlg::MessageDlgType)2 , 0 , this , "About" , true , 0);
		}
		dlg->show();
	
}

void TestWidget::operadora()
{
log.open(IO_WriteOnly | IO_Translate );
QTextStream logout(&log);
infotheme();
logout << "Volvi de infotheme()" << endl;
//para trabajar con la operadora, ocultarla o mostrarla
QStringList list;
QString msg = QString("Visible yes/no");
QString hdr = QString("Select");

list += QString::fromUtf8("yes");//0        list += QString::fromUtf8("no");//1
//Leo el archivo
if( operadorvi == NULL )
	{
		operadorvi  = new ZSingleSelectDlg(hdr, msg, this, "ZSingleSelectDlg", true, 0, 0);
		operadorvi->addItemsList(list);
	}

	if (operadorvi->exec())
	{
int elegido=operadorvi->getCheckedItemIndex();
/////Para que sea visible el operador
QString archi(carpeta+"/phone_p.ini");
QString archiaux(carpeta+"/temp");
QFile salida(archiaux);
QFile entrada(archi);
QTextStream en( &entrada );
QTextStream sa( &salida);
QString busca("[Idle]");
//int encontro=-1;
QString line="";
QString aux="";
salida.open(IO_WriteOnly | IO_Translate );
if(elegido==0)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
           sa << line << endl;
           logout << line << endl;
           line=en.readLine();
           sa << "Padding_Top = 0" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;logout << line << endl;}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
else
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
           sa << line << endl;
           logout << line << endl;
           line=en.readLine();
           sa << "Padding_Top = -30" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;logout << line << endl;}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
}

}

void TestWidget::infotheme()
{
carpeta="";
QString theme("/ezxlocal/download/appwrite/setup/ezx_theme.cfg");
QString istheme("CurrentSkin");
//QString nom("/mmc/mmca1/tempinfoskin");
//QFile salida(nom);
QFile entrada(theme);
QString line;
QString aux;
QTextStream t( &entrada );
//QTextStream s( &salida );
//salida.open( IO_WriteOnly | IO_Translate );
int encontro=-1;
int tam=0;
if ( entrada.open(IO_ReadOnly | IO_Translate) )
{
  while ( !t.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = t.readLine();
          //cantl++;
          aux=line;
          encontro=aux.find(istheme,0);//busco la linea que me indica la direccion del theme
          if(encontro==0)//encontre la linea
           {
            tam=aux.length();
            int j=0;
            carpeta="";              
            //vamos a guadar el nombre de la app
            for(int i=14;i<tam;i++)
             {
                carpeta[j]=aux[i];//guardo la direccion del skin
                j++;
             }
            //s << carpeta << endl;
            }
           //else
            //  numerodelinea++;
      }
}
entrada.close();


}
///////////Tengo dudas con esto

void TestWidget::time()
{	
//log.open(IO_WriteOnly | IO_Translate );
//QTextStream logout(&log);
infotheme();
//logout << "Volvi de infotheme()" << endl;
//para trabajar con la operadora, ocultarla o mostrarla
QStringList list;
QString msg = QString("Size Clock");
QString hdr = QString("Select");

list += QString::fromUtf8("20");//0        list += QString::fromUtf8("50");//1
//Leo el archivo
if( timedialog == NULL )
	{
		timedialog  = new ZSingleSelectDlg(hdr, msg, this, "ZSingleSelectDlg", true, 0, 0);
		timedialog->addItemsList(list);
	}

	if (timedialog->exec())
	{
int elegido=timedialog->getCheckedItemIndex();
/////Para que sea visible el operador
QString archi(carpeta+"/phone_p.ini");
QString archiaux(carpeta+"/temp");
QFile salida(archiaux);
QFile entrada(archi);
QTextStream en( &entrada );
QTextStream sa( &salida);
QString busca("[Font_DigitalClockStd]");
//int encontro=-1;
QString line="";
QString aux="";
salida.open(IO_WriteOnly | IO_Translate );
if(elegido==0)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
           sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << "Size = 20 " << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
else
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
           sa << line << endl;
        //   logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << "Size = 50 " << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
}
}

void TestWidget::skinmod()
{
infotheme();
QStringList list;
QString msg = QString("Skin Mod");
QString hdr = QString("Select");

list += QString::fromUtf8("4*3");//0        list += QString::fromUtf8("3*4");//1
list += QString::fromUtf8("1*1");//2

//Leo el archivo
if( smod == NULL )
	{
		smod  = new ZSingleSelectDlg(hdr, msg, this, "ZSingleSelectDlg", true, 0, 0);
		smod->addItemsList(list);
	}
if (smod->exec())
{
int elegido=smod->getCheckedItemIndex();
QString cuatrotres("/mmc/mmca1/.system/QTDownLoad/4x3.ini");
QString trescuatro("/mmc/mmca1/.system/QTDownLoad/3x4.ini");
QString unouno("/mmc/mmca1/.system/QTDownLoad/1x1.ini");
QString borrar(carpeta+"/mainmenu.ini");
QString renombrar(carpeta+"/mainmenu_p.ini");
QFile salida(renombrar);
QTextStream sa( &salida);
salida.open(IO_WriteOnly | IO_Translate );
QDir q;
if(elegido==0)
{
 if(q.exists(borrar))
      q.remove(borrar);
 
 
 sa << "[ZIconView_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Opacity_Std = 0" << endl;
sa << "Padding_Left = 2" << endl;
sa << "Padding_Right = 2" << endl;
sa << "Padding_Top = 4" << endl;
sa << "Padding_Bottom = 4" << endl;
sa << "Spacing_H1 = -22" << endl;
sa << "Spacing_V1 = 8" << endl;
 sa << endl;
sa << "[ZIconViewItem_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Type_H = 0" << endl;
sa << "Bg_Type_HS = 0" << endl;
sa << "Border_Type_Std = 0" << endl;
sa << "Border_Type_H = 0" << endl;
sa << "Border_Type_HS = 0" << endl;
sa << "Border_Left_Stretch_H = 2" << endl;
sa << "Border_Left_Stretch_HS = 2" << endl;
sa << "Border_Right_Stretch_H = 2" << endl;
sa << "Border_Right_Stretch_HS = 2" << endl;
sa << "Border_Top_Stretch_H = 1" << endl;
sa << "Border_Top_Stretch_HS = 1" << endl;
sa << "Border_Bottom_Stretch_H = 1" << endl;
sa << "Border_Bottom_Stretch_HS = 1" << endl;
sa << "Image_Container_Type = 1" << endl;
sa << "Padding_Left = 7" << endl;
sa << "Padding_Right = 7" << endl;
sa << "Padding_Top = 0" << endl;
sa << "Padding_Bottom = 0" << endl;
sa << "Spacing_V1 = 1" << endl;
sa << endl;
sa << "[ZImageContainer_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Type_H = 2" << endl;
sa << "Bg_Stretch_H = 5" << endl;
sa << "Bg_Color_H = 255" << endl;
sa << "Bg_Opacity_Std =0" << endl;
sa << "Bg_Opacity_H =100" << endl;
sa << "Border_Type_Std = 0" << endl;
sa << "Border_Type_H = 2" << endl;
sa << "Border_Color_Std = 1592405" << endl;
sa << "Border_Color_H = 5592405" << endl;
sa << "Border_Width_Std = 0" << endl;
sa << "Border_Width_H = 0" << endl;
sa << "Border_Opacity_Std =100" << endl;
sa << "Border_Opacity_H =100" << endl;
sa << "Bg_Size_Std = 49" << endl;
sa << "Bg_Size_H = 49" << endl;
sa << "Padding_Left = 4" << endl;
sa << "Padding_Right = 4" << endl;
sa << "Padding_Top = 4" << endl;
sa << "Padding_Bottom = 4" << endl;
}
if(elegido==1)
{
 if(q.exists(borrar))
      q.remove(borrar);

 
sa << "[ZIconView_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Opacity_Std = 0" << endl;
sa << "Padding_Left = 5" << endl;
sa << "Padding_Right = 5" << endl;
sa << "Padding_Top = 4" << endl;
sa << "Padding_Bottom = 4" << endl;
sa << "Spacing_H1 = 14" << endl;
sa << "Spacing_V1 = 0" << endl;
 sa << endl;
sa << "[ZIconViewItem_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Type_H = 0" << endl;
sa << "Bg_Type_HS = 0" << endl;
sa << "Border_Type_Std = 0" << endl;
sa << "Border_Type_H = 0" << endl;
sa << "Border_Type_HS = 0" << endl;
sa << "Border_Left_Stretch_H = 2" << endl;
sa << "Border_Left_Stretch_HS = 2" << endl;
sa << "Border_Right_Stretch_H = 2" << endl;
sa << "Border_Right_Stretch_HS = 2" << endl;
sa << "Border_Top_Stretch_H = 1" << endl;
sa << "Border_Top_Stretch_HS = 1" << endl;
sa << "Border_Bottom_Stretch_H = 1" << endl;
sa << "Border_Bottom_Stretch_HS = 1" << endl;
sa << "Image_Container_Type = 1" << endl;
sa << "Padding_Left = 0" << endl;
sa << "Padding_Right = 0" << endl;
sa << "Padding_Top = 0" << endl;
sa << "Padding_Bottom = 0" << endl;
sa << "Spacing_V1 = 1" << endl;
sa << endl;
sa << "[ZImageContainer_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Type_H = 2" << endl;
sa << "Bg_Stretch_H = 5" << endl;
sa << "Bg_Color_H = 255" << endl;
sa << "Bg_Opacity_Std =0" << endl;
sa << "Bg_Opacity_H =100" << endl;
sa << "Border_Type_Std = 0" << endl;
sa << "Border_Type_H = 2" << endl;
sa << "Border_Color_Std = 1592405" << endl;
sa << "Border_Color_H = 5592405" << endl;
sa << "Border_Width_Std = 0" << endl;
sa << "Border_Width_H = 0" << endl;
sa << "Border_Opacity_Std =100" << endl;
sa << "Border_Opacity_H =100" << endl;
sa << "Bg_Size_Std = 49" << endl;
sa << "Bg_Size_H = 49" << endl;
sa << "Padding_Left = 4" << endl;
sa << "Padding_Right = 4" << endl;
sa << "Padding_Top = 4" << endl;
sa << "Padding_Bottom = 4" << endl;
}
if(elegido==2)
{
 if(q.exists(borrar))
      q.remove(borrar);

sa << "[ZIconView_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Opacity_Std = 0" << endl;
sa << "Padding_Left = 6" << endl;
sa << "Padding_Right = 6" << endl;
sa << "Padding_Top = 150" << endl;
sa << "Padding_Bottom = 4" << endl;
sa << "Spacing_H1 = 100" << endl;
sa << "Spacing_V1 = 100" << endl;
 sa << endl;
sa << "[ZIconViewItem_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Type_H = 0" << endl;
sa << "Bg_Type_HS = 0" << endl;
sa << "Border_Type_Std = 0" << endl;
sa << "Border_Type_H = 0" << endl;
sa << "Border_Type_HS = 0" << endl;
sa << "Border_Left_Stretch_H = 2" << endl;
sa << "Border_Left_Stretch_HS = 2" << endl;
sa << "Border_Right_Stretch_H = 2" << endl;
sa << "Border_Right_Stretch_HS = 2" << endl;
sa << "Border_Top_Stretch_H = 1" << endl;
sa << "Border_Top_Stretch_HS = 1" << endl;
sa << "Border_Bottom_Stretch_H = 1" << endl;
sa << "Border_Bottom_Stretch_HS = 1" << endl;
sa << "Image_Container_Type = 1" << endl;
sa << "Padding_Left = 2" << endl;
sa << "Padding_Right = 2" << endl;
sa << "Padding_Top = 0" << endl;
sa << "Padding_Bottom = 0" << endl;
sa << "Spacing_V1 = 1" << endl;
sa << endl;
sa << "[ZImageContainer_1]" << endl;
sa << "Bg_Type_Std = 0" << endl;
sa << "Bg_Type_H = 2" << endl;
sa << "Bg_Stretch_H = 5" << endl;
sa << "Bg_Color_H = 255" << endl;
sa << "Bg_Opacity_Std = 0" << endl;
sa << "Bg_Opacity_H = 0" << endl;
sa << "Border_Type_Std = 0" << endl;
sa << "Border_Type_H = 2" << endl;
sa << "Border_Color_Std = 1592405" << endl;
sa << "Border_Color_H = 5592405" << endl;
sa << "Border_Width_Std = 0" << endl;
sa << "Border_Width_H = 0" << endl;
sa << "Border_Opacity_Std = 0" << endl;
sa << "Border_Opacity_H = 0" << endl;
sa << "Bg_Size_Std = 220" << endl;
sa << "Bg_Size_H = 220" << endl;
sa << "Padding_Left = 3" << endl;
sa << "Padding_Right = 3" << endl;
sa << "Padding_Top = -230" << endl;
sa << "Padding_Bottom = 240" << endl;
}
salida.close();
}//smod->exec

}//funcion

void TestWidget::csize()
{
infotheme();

	if( clocksize == NULL )
		{
			//val = ini.readNumEntry(QString(INI_BT_SECTION), QString("DiscoverablePeriod"), 5);
			QString a = QString("Clock Size");
			clocksize  = new ZNumPickerDlg(10, this, "ZNumPickerDlg", 0);
			ZNumModule* module = clocksize->getNumModule();
			module->setMaxValue(100);
			module->setMinValue(10);
			module->setValue(20);
			
	    		ZLabel* label = new ZLabel(QString("Size: "), module, NULL,0, (ZSkinService::WidgetClsID)4);
	    		module->setLabel(label, (ZNumModule::RelativeAlignment)0);
			
			clocksize->setTitle("Clock Size");
			//dlg_bt_discover->setInstructText("value:");
		}

		if (clocksize->exec())
		{	
			int r = clocksize->getNumValue();


QString archi(carpeta+"/phone_p.ini");
QString archiaux(carpeta+"/temp");
QFile salida(archiaux);
QFile entrada(archi);
QTextStream en( &entrada );
QTextStream sa( &salida);
QString busca("[Font_DigitalClockStd]");
//int encontro=-1;
QString line="";
QString aux="";
salida.open(IO_WriteOnly | IO_Translate );
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
           sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << "Size = "; sa << r ;sa << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();

}

}//funcion

void TestWidget::ccolor()
{
infotheme();
QStringList list;
QString msg = QString("Clock color");
QString hdr = QString("Select");

list += QString::fromUtf8("Red");//0        list += QString::fromUtf8("Green ");//1
list += QString::fromUtf8("Blue");//2        list += QString::fromUtf8("White");//3
list += QString::fromUtf8("Black");//4 
list += QString::fromUtf8("Orange");//5       
//Leo el archivo
if( clockcolor == NULL )
	{
		clockcolor  = new ZSingleSelectDlg(hdr, msg, this, "ZSingleSelectDlg", true, 0, 0);
		clockcolor->addItemsList(list);
	}

	if (clockcolor->exec())
	{
int elegido=clockcolor->getCheckedItemIndex();
/////Para que sea visible el operador
QString archi(carpeta+"/phone_p.ini");
QString archiaux(carpeta+"/temp");
QFile salida(archiaux);
QFile entrada(archi);
QTextStream en( &entrada );
QTextStream sa( &salida);
QString busca("[Font_DigitalClockStd]");
//int encontro=-1;
QString line="";
QString aux="";
salida.open(IO_WriteOnly | IO_Translate );
if(elegido==0)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
           sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << line  << endl;
           line = en.readLine();
           sa << "Color = 14878473" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
else if(elegido==1)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
         sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << line  << endl;
           line = en.readLine();
           sa << "Color = 65280" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
else if(elegido==2)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
         sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << line  << endl;
           line = en.readLine();
           sa << "Color = 975" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
else if(elegido==3)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
         sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << line  << endl;
           line = en.readLine();
           sa << "Color = 16777215" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
else if(elegido==4)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
         sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << line  << endl;
           line = en.readLine();
           sa << "Color = 0" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}
else if(elegido==5)
{
if(entrada.open(IO_ReadOnly | IO_Translate ))
{
while ( !en.eof() ) //leo linea a linea el ezx_theme.cfg
      {           
          line = en.readLine();
          //encontro=aux.find(busca,0);//busco la linea que me indica la direccion del theme
          if(line==busca)//encontre la
          {
         sa << line << endl;
  //         logout << line << endl;
           line=en.readLine();
           sa << line << endl;
           line=en.readLine();
           sa << line  << endl;
           line = en.readLine();
           sa << "Color = 16744448" << endl;
           /*if(elegido==0) {
           sa << "Padding_Top = 0" << endl; logout << "Padding_Top = 0" << endl;}
           else
           {sa << "Padding_Top = -30" << endl;logout << "Padding_Top = -30" << endl;}
          */}
          else{
           sa << line << endl;/*logout << line << endl;*/}
      }
 
}
entrada.close();
salida.close();
QDir q;
q.remove(carpeta+"/phone_p.ini");
q.rename(carpeta+"/temp",carpeta+"/phone_p.ini");
log.close();
}}

}
//funcion
void TestWidget::calendar()
{
infotheme();
QStringList list;
QString msg2 = QString("Day color");
QString hdr2 = QString("Select");

list += QString::fromUtf8("Red");//0        list += QString::fromUtf8("Green ");//1
list += QString::fromUtf8("Blue");//2        list += QString::fromUtf8("White");//3
list += QString::fromUtf8("Black");//4 
list += QString::fromUtf8("Orange");//5       
//Leo el archivo
if( calendarcolor == NULL )
	{
		calendarcolor  = new ZSingleSelectDlg(hdr2, msg2, this, "ZSingleSelectDlg", true, 0, 0);
		calendarcolor->addItemsList(list);
	}

	if (calendarcolor->exec())
	{
int elegido=calendarcolor->getCheckedItemIndex();

FILE_BT_CONFIG=(carpeta+"/calendar_p.ini");
INI_BT_SECTION= "Font_MonthHeaderStd";
QString s1 = QString(FILE_BT_CONFIG);
	
	ZConfig ini(s1, false);

if(elegido==0)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 14878473);
else if(elegido==1)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==2)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 975);
else if(elegido==3)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==4)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 0);
else if(elegido==5)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16744448);

}
calendarcolor=NULL;
}

void TestWidget::clockpos()
{
infotheme();
QStringList list;
QString msg = QString("Clock position");
QString hdr = QString("Select");

list += QString::fromUtf8("Right down");//0        list += QString::fromUtf8("Right up");//1
if( calendarcolor == NULL )
	{
		calendarcolor  = new ZSingleSelectDlg(hdr, msg, this, "ZSingleSelectDlg", true, 0, 0);
		calendarcolor->addItemsList(list);
	}
	if (calendarcolor->exec())
	{
int elegido=calendarcolor->getCheckedItemIndex();
FILE_BT_CONFIG=(carpeta+"/phone_p.ini");
INI_BT_SECTION= "Idle";
QString s1 = QString(FILE_BT_CONFIG);
	
	ZConfig ini(s1, false);
 if(elegido==0)
{
/*
Padding_Top = -25
Padding_Bottom = 3
Padding_Right = 5
Padding_Left = 5
*/
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Top"), -25);
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Bottom"), 3);
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Right"), 5);
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Left"), 5);

}
else if(elegido==1)
{
/*
Padding_Top = 5
Padding_Bottom = 161
Padding_Right = 5
Padding_Left = 5
*/
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Top"), 5);
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Bottom"), 161);
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Right"), 5);
ini.writeEntry(QString(INI_BT_SECTION), QString("Padding_Left"), 5);
}

}
calendarcolor=NULL;

}

void TestWidget::reprotimecolor()
{
infotheme();
QStringList list;
QString msg2 = QString("Time Song Color");
QString hdr2 = QString("Select");

list += QString::fromUtf8("Red");//0        list += QString::fromUtf8("Green ");//1
list += QString::fromUtf8("Blue");//2        list += QString::fromUtf8("White");//3
list += QString::fromUtf8("Black");//4 
list += QString::fromUtf8("Orange");//5       
//Leo el archivo
if( calendarcolor == NULL )
	{
		calendarcolor  = new ZSingleSelectDlg(hdr2, msg2, this, "ZSingleSelectDlg", true, 0, 0);
		calendarcolor->addItemsList(list);
	}

	if (calendarcolor->exec())
	{
int elegido=calendarcolor->getCheckedItemIndex();

FILE_BT_CONFIG=(carpeta+"/phone_p.ini");
INI_BT_SECTION= "Font_IdleControlerBStd";
QString s1 = QString(FILE_BT_CONFIG);
	
	ZConfig ini(s1, false);

if(elegido==0)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 14878473);
else if(elegido==1)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==2)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 975);
else if(elegido==3)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==4)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 0);
else if(elegido==5)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16744448);

}
calendarcolor=NULL;
}
void TestWidget::colornomllamada()
{
infotheme();
QStringList list;
QString msg2 = QString("Color name IC");
QString hdr2 = QString("Select");

list += QString::fromUtf8("Red");//0        list += QString::fromUtf8("Green ");//1
list += QString::fromUtf8("Blue");//2        list += QString::fromUtf8("White");//3
list += QString::fromUtf8("Black");//4 
list += QString::fromUtf8("Orange");//5       
//Leo el archivo
if( calendarcolor == NULL )
	{
		calendarcolor  = new ZSingleSelectDlg(hdr2, msg2, this, "ZSingleSelectDlg", true, 0, 0);
		calendarcolor->addItemsList(list);
	}

	if (calendarcolor->exec())
	{
int elegido=calendarcolor->getCheckedItemIndex();

FILE_BT_CONFIG=(carpeta+"/phone_p.ini");
INI_BT_SECTION= "Font_CallNameStd";
QString s1 = QString(FILE_BT_CONFIG);

	ZConfig ini(s1, false);

if(elegido==0)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 14878473);
else if(elegido==1)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==2)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 975);
else if(elegido==3)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==4)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 0);
else if(elegido==5)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16744448);

}
calendarcolor=NULL;
}

void TestWidget::reprocolor()
{
infotheme();
QStringList list;
QString msg2 = QString("Song name color");
QString hdr2 = QString("Select");

list += QString::fromUtf8("Red");//0        list += QString::fromUtf8("Green ");//1
list += QString::fromUtf8("Blue");//2        list += QString::fromUtf8("White");//3
list += QString::fromUtf8("Black");//4 
list += QString::fromUtf8("Orange");//5       
//Leo el archivo
if( calendarcolor == NULL )
	{
		calendarcolor  = new ZSingleSelectDlg(hdr2, msg2, this, "ZSingleSelectDlg", true, 0, 0);
		calendarcolor->addItemsList(list);
	}

	if (calendarcolor->exec())
	{
int elegido=calendarcolor->getCheckedItemIndex();

FILE_BT_CONFIG=(carpeta+"/phone_p.ini");
INI_BT_SECTION= "Font_IdleControlerAStd";
QString s1 = QString(FILE_BT_CONFIG);
	
	ZConfig ini(s1, false);

if(elegido==0)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 14878473);
else if(elegido==1)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==2)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 975);
else if(elegido==3)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16777215);
else if(elegido==4)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 0);
else if(elegido==5)
ini.writeEntry(QString(INI_BT_SECTION), QString("Color"), 16744448);

}
calendarcolor=NULL;
}

void TestWidget::salir()
{
//salgo de la app y reinicio los procesos
system ( QString ( "/bin/busybox killall am" ).utf8() );

}


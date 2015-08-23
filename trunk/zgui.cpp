#include "zgui.h"
#include <ZConfig.h>
//#include "GUI_Define.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <qpixmap.h>
#include <string.h>
#include <ZOptionsMenu.h>
#include <ZApplication.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <qtextcodec.h>
#include <ezxres.h>

#define Z6KEY_RED               0x1031




//using namespace std;

QTextCodec* txtcodec = QTextCodec::codecForName("UTF-8");
RES_ICON_Reader iconReader;
QString unicode;

ZGui::ZGui ( const QString &argument, QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::FULL_TYPE, NULL, "ZMainWidget", 0 )
{
	
	ProgDir = getProgramDir();
	QString folder = argument;
	if ( folder != "" ) { ProgDir = folder; }

	CreateWindow ( parent );
	( ( ZApplication* ) qApp )->showMainWidget ( this );
	
}

ZGui::~ZGui()
{
}

void ZGui::keyPressEvent (QKeyEvent* k)

{

switch (k->key())
	{

	case 0x1031: 

	int pan = getFullScreenMode();

	if ( pan == 0 ) { setFullScreenMode(false,false);update();}
	if ( pan == 1 ) { setFullScreenMode(true,true);update();}	
	

	break;

	case 0x1030:

	guardar();

	}

}


void ZGui::CreateWindow ( QWidget* parent )
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);

	/*********/
	int Combo = ini.readNumEntry(QString("MAIN"), QString("Combo"), 0);
	/*********/
	int Combop = ini.readNumEntry(QString("COMBO1"), QString("ComboOpciones"), 0);
	/*********/
	int Combop2 = ini.readNumEntry(QString("COMBO2"), QString("ComboOpciones"), 0);
	/*********/
	int Combop3 = ini.readNumEntry(QString("COMBO3"), QString("ComboOpciones"), 0);
	/*********/

	/*********/
	unicode = ini.readEntry(QString("SETTINGS"), QString("Unicode"), "");
	QString val;

	/*********/
	QString IDLab1 = ini.readEntry(QString("COMBO1"), QString("Leyenda"), "");
	QString IDCom1 = ini.readEntry(QString("COMBO1OPCIONES"), QString("Combo1"), "");
	QString IDCom2 = ini.readEntry(QString("COMBO1OPCIONES"), QString("Combo2"), "");
	QString IDCom3 = ini.readEntry(QString("COMBO1OPCIONES"), QString("Combo3"), "");
	QString IDCom4 = ini.readEntry(QString("COMBO1OPCIONES"), QString("Combo4"), "");
	QString IDCom5 = ini.readEntry(QString("COMBO1OPCIONES"), QString("Combo5"), "");
	QString IDCom6 = ini.readEntry(QString("COMBO1OPCIONES"), QString("Combo6"), "");
	/*********/
	QString IDLab2 = ini.readEntry(QString("COMBO2"), QString("Leyenda"), "");
	QString IDCom21 = ini.readEntry(QString("COMBO2OPCIONES"), QString("Combo1"), "");
	QString IDCom22 = ini.readEntry(QString("COMBO2OPCIONES"), QString("Combo2"), "");
	QString IDCom23 = ini.readEntry(QString("COMBO2OPCIONES"), QString("Combo3"), "");
	QString IDCom24 = ini.readEntry(QString("COMBO2OPCIONES"), QString("Combo4"), "");
	QString IDCom25 = ini.readEntry(QString("COMBO2OPCIONES"), QString("Combo5"), "");
	QString IDCom26 = ini.readEntry(QString("COMBO2OPCIONES"), QString("Combo6"), "");
	/*********/
	QString IDLab3 = ini.readEntry(QString("COMBO3"), QString("Leyenda"), "");
	QString IDCom31 = ini.readEntry(QString("COMBO3OPCIONES"), QString("Combo1"), "");
	QString IDCom32 = ini.readEntry(QString("COMBO3OPCIONES"), QString("Combo2"), "");
	QString IDCom33 = ini.readEntry(QString("COMBO3OPCIONES"), QString("Combo3"), "");
	QString IDCom34 = ini.readEntry(QString("COMBO3OPCIONES"), QString("Combo4"), "");
	QString IDCom35 = ini.readEntry(QString("COMBO3OPCIONES"), QString("Combo5"), "");
	QString IDCom36 = ini.readEntry(QString("COMBO3OPCIONES"), QString("Combo6"), "");
	/*********/

	scrollPanel = new ZFormContainer(this, 0, ZSkinService::clsZFormContainer);	
	scrollPanel->resize ( 240, 320 );

//***************************** CON UN SOLO COMOBOX COMIENZO *********************************//

	

	if ( Combo == 1 ) { 
	ComboBox = new ZComboBox(this,"ZComboBox",true); 
	infoLabel = new ZLabel(IDLab1 , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
	infoLabel->setPreferredWidth(240);
	infoLabel->setAutoResize(true ); 
	


	if ( Combop == 1 ) { 
	ComboBox->insertItem(IDCom1,0); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop == 2 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop == 3 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1);
	ComboBox->insertItem(IDCom3,2);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop == 4 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1);
	ComboBox->insertItem(IDCom3,2);
	ComboBox->insertItem(IDCom4,3);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop == 5 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1);
	ComboBox->insertItem(IDCom3,2);
	ComboBox->insertItem(IDCom4,3);
	ComboBox->insertItem(IDCom5,4);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop == 6 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1);
	ComboBox->insertItem(IDCom3,2);
	ComboBox->insertItem(IDCom4,3);
	ComboBox->insertItem(IDCom5,4);
	ComboBox->insertItem(IDCom6,5);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	}
//***************************** CON UN SOLO COMOBOX FINAL ************************************//


//******************************* CON DOS COMOBOX COMIENZO *********************************//

	if ( Combo == 2 ) { 
	ComboBox = new ZComboBox(this,"ZComboBox",true); 
	ComboBox2 = new ZComboBox(this,"ZComboBox",true);
	infoLabel = new ZLabel(IDLab1 , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
	infoLabel->setPreferredWidth(240);
	infoLabel->setAutoResize(true ); 
	infoLabel2 = new ZLabel(IDLab2 , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
	infoLabel2->setPreferredWidth(240);
	infoLabel2->setAutoResize(true ); 


	if ( Combop == 1 ) { 
	ComboBox->insertItem(IDCom1,0); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 1 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop == 2 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 2 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop == 3 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 3 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop == 4 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	ComboBox->insertItem(IDCom4,3); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 4 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	ComboBox2->insertItem(IDCom24,3); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop == 5 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	ComboBox->insertItem(IDCom4,3); 
	ComboBox->insertItem(IDCom5,4); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 5 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	ComboBox2->insertItem(IDCom24,3); 
	ComboBox2->insertItem(IDCom25,4); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop == 6 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	ComboBox->insertItem(IDCom4,3); 
	ComboBox->insertItem(IDCom5,4); 
	ComboBox->insertItem(IDCom6,5); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 6 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	ComboBox2->insertItem(IDCom24,3); 
	ComboBox2->insertItem(IDCom25,4); 
	ComboBox2->insertItem(IDCom26,5); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

}


//******************************** CON DOS COMOBOX FINAL ************************************//


//******************************** CON TRES COMOBOX FINAL ************************************//


	if ( Combo == 3 ) { 
	ComboBox = new ZComboBox(this,"ZComboBox",true); 
	ComboBox2 = new ZComboBox(this,"ZComboBox",true);
	ComboBox3 = new ZComboBox(this,"ZComboBox",true);
	infoLabel = new ZLabel(IDLab1 , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
	infoLabel->setPreferredWidth(240);
	infoLabel->setAutoResize(true ); 
	infoLabel2 = new ZLabel(IDLab2 , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
	infoLabel2->setPreferredWidth(240);
	infoLabel2->setAutoResize(true ); 
	infoLabel3 = new ZLabel(IDLab3 , this, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
	infoLabel3->setPreferredWidth(240);
	infoLabel3->setAutoResize(true ); 

	if ( Combop == 1 ) { 
	ComboBox->insertItem(IDCom1,0); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 1 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop3 == 1 ) { 
	ComboBox3->insertItem(IDCom31,0); 
	scrollPanel->addChild(infoLabel3);
	scrollPanel->addChild(ComboBox3);
	}

	if ( Combop == 2 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 2 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop3 == 2 ) { 
	ComboBox3->insertItem(IDCom31,0); 
	ComboBox3->insertItem(IDCom32,1); 
	scrollPanel->addChild(infoLabel3);
	scrollPanel->addChild(ComboBox3);
	}

	if ( Combop == 3 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 3 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop3 == 3 ) { 
	ComboBox3->insertItem(IDCom31,0); 
	ComboBox3->insertItem(IDCom32,1); 
	ComboBox3->insertItem(IDCom33,2); 
	scrollPanel->addChild(infoLabel3);
	scrollPanel->addChild(ComboBox3);
	}

	if ( Combop == 4 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	ComboBox->insertItem(IDCom4,3);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 4 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	ComboBox2->insertItem(IDCom24,3); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop3 == 4 ) { 
	ComboBox3->insertItem(IDCom31,0); 
	ComboBox3->insertItem(IDCom32,1); 
	ComboBox3->insertItem(IDCom33,2); 
	ComboBox3->insertItem(IDCom34,3); 
	scrollPanel->addChild(infoLabel3);
	scrollPanel->addChild(ComboBox3);
	}

	if ( Combop == 5 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	ComboBox->insertItem(IDCom4,3);
	ComboBox->insertItem(IDCom5,4);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 5 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	ComboBox2->insertItem(IDCom24,3); 
	ComboBox2->insertItem(IDCom25,4); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop3 == 5 ) { 
	ComboBox3->insertItem(IDCom31,0); 
	ComboBox3->insertItem(IDCom32,1); 
	ComboBox3->insertItem(IDCom33,2); 
	ComboBox3->insertItem(IDCom34,3); 
	ComboBox3->insertItem(IDCom35,4); 
	scrollPanel->addChild(infoLabel3);
	scrollPanel->addChild(ComboBox3);
	}

	if ( Combop == 6 ) { 
	ComboBox->insertItem(IDCom1,0); 
	ComboBox->insertItem(IDCom2,1); 
	ComboBox->insertItem(IDCom3,2); 
	ComboBox->insertItem(IDCom4,3);
	ComboBox->insertItem(IDCom5,4);
	ComboBox->insertItem(IDCom6,5);
	scrollPanel->addChild(infoLabel);
	scrollPanel->addChild(ComboBox);
	}

	if ( Combop2 == 6 ) { 
	ComboBox2->insertItem(IDCom21,0); 
	ComboBox2->insertItem(IDCom22,1); 
	ComboBox2->insertItem(IDCom23,2); 
	ComboBox2->insertItem(IDCom24,3); 
	ComboBox2->insertItem(IDCom25,4); 
	ComboBox2->insertItem(IDCom26,5); 
	scrollPanel->addChild(infoLabel2);
	scrollPanel->addChild(ComboBox2);
	}

	if ( Combop3 == 6 ) { 
	ComboBox3->insertItem(IDCom31,0); 
	ComboBox3->insertItem(IDCom32,1); 
	ComboBox3->insertItem(IDCom33,2); 
	ComboBox3->insertItem(IDCom34,3); 
	ComboBox3->insertItem(IDCom35,4); 
	ComboBox3->insertItem(IDCom36,5); 
	scrollPanel->addChild(infoLabel3);
	scrollPanel->addChild(ComboBox3);
	}


}


	val = ini.readEntry(QString("MAIN"), QString("Title"), "");
	setMainWidgetTitle ( texto(val) );


	QString PanCom = ini.readEntry(QString("MAIN"), QString("Pantalla Completa"), "NO");
	if ( PanCom == "SI" ) { setFullScreenMode(true,true); }
	else { setFullScreenMode(false,false); }


	setContentWidget ( scrollPanel );

	softKey = new ZSoftKey ( NULL , this , this );
	Create_MenuApp();
	Create_SoftKey();
	setSoftKey ( softKey );


}

QString ZGui::getProgramDir()
{
  ProgDir = QString ( qApp->argv() [0] ) ;
  int i = ProgDir.findRev ( "/" );
  ProgDir.remove ( i+1, ProgDir.length() - i );
  return ProgDir;
}

QString ZGui::texto(const char*xString)
{
	if ( unicode == "1" ) { return txtcodec->toUnicode(xString); }
	else { return xString; }
}


void ZGui::Create_MenuApp()
{

	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	QString IDval;QRect rect;

	QPixmap* pm  = new QPixmap();
	int idx = 0;
	menu = new ZOptionsMenu ( rect, softKey, NULL, 0);
	menu->setItemSpacing(10);  

	int num = 1; QString fin = "NO";
	QString val = ini.readEntry(QString("MENU"), QString("Item%1").arg(num), "");
	while ( fin != "SI" )
	{
		QString val = ini.readEntry(QString("MENU"), QString("Icon%1").arg(num), "");
		pm->load(ProgDir + "/" + val);
		val = ini.readEntry(QString("MENU"), QString("Item%1").arg(num), "");
		if ( val == "!sep" ) { menu->insertSeparator(idx, idx); }
		else {
		  menu->insertItem ( texto(val), NULL, pm, true, idx, idx );
		  menu->connectItem ( idx, this, SLOT ( MenuClick() ) );
		}
		++idx; num++;
		val = ini.readEntry(QString("MENU"), QString("Item%1").arg(num), "");
		if ( val == "" ) { fin = "SI"; }
	}

}

void ZGui::MenuClick()


{

	qApp->processEvents();
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	QString val = ini.readEntry(QString("MENU"), QString("Exec%1").arg(menu->getActiveItemId()+1), "");
	system(QString("%1/%2").arg(ProgDir).arg(val));
}

void ZGui::Create_SoftKey()
{
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	QString val = ini.readEntry(QString("MAIN"), QString("Soft1"), "");
	softKey->setOptMenu ( ZSoftKey::LEFT, menu ); 
	softKey->setText ( ZSoftKey::LEFT, texto(val), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	val = ini.readEntry(QString("MAIN"), QString("Soft1"), "");
	softKey->setTextForOptMenuHide(texto(val));
	val = ini.readEntry(QString("MAIN"), QString("Soft1s"), "");
	QString val2 = ini.readEntry(QString("MAIN"), QString("Soft2s"), "");
	softKey->setTextForOptMenuShow(texto(val), texto(val2));
	val = ini.readEntry(QString("MAIN"), QString("Soft2"), "");
	softKey->setText ( ZSoftKey::RIGHT, texto(val), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( guardar() ) );
}

void ZGui::guardar()

{
	
	ZConfig ini(QString("%1/settings.cfg").arg(ProgDir), false);
	
	QString val = ini.readEntry(QString("COMBO1OPCIONES"), QString("Exec%1").arg(ComboBox->currentItem()+1), "");
	system(QString("%1%2").arg(ProgDir).arg(val));

	QTimer * Tiempo = new QTimer (this, 0);
	Tiempo->start(2000, true);

	QString val1 = ini.readEntry(QString("COMBO2OPCIONES"), QString("Exec%1").arg(ComboBox2->currentItem()+1), "");
	system(QString("%1%2").arg(ProgDir).arg(val1));

	Tiempo->start(2000, true);

	QString val2 = ini.readEntry(QString("COMBO3OPCIONES"), QString("Exec%1").arg(ComboBox3->currentItem()+1), "");
	system(QString("%1%2").arg(ProgDir).arg(val2));

	Tiempo->start(2000, true);

	QString titulo = ini.readEntry(QString("DIALOGS"), QString("QuitTitle"), "");
	QString imagen = ini.readEntry(QString("DIALOGS"), QString("QuitPic"), "");
	QPixmap pm; pm.load(imagen);
	QString texto = ini.readEntry(QString("DIALOGS"), QString("QuitText"), "");

	QString SALIR = ini.readEntry(QString("MAIN"), QString("Guardar y Salir"), "");
	if ( SALIR == "SI" )

	{

	salir = new ZPopup (ZPopup::DIALOG, this, 0, true, 0);
	salir->setTitle (titulo);
	salir->setTitleIcon (pm);
	salir->setInstructText (texto);
	salir->setSoftkeyText ("Si", "No");
	salir->show();

	int salida = salir->exec();
	
	if ( salida == 1 ) { qApp->quit(); }

	}


}


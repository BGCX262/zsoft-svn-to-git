#define QT_NO_DRAGANDDROP
#define QT_NO_PROPERTIES
#include <ZApplication.h>
#include <ZKbMainWidget.h>
#include <ZMessageDlg.h>
#include <ZLabel.h>
#include <ZScrollPanel.h>
#include <ZSoftKey.h>
#include <ZFormContainer.h>
#include <qpainter.h>
#include <qlabel.h>
#include <stdio.h>
#include <stdlib.h>
#include <qfile.h>
#include <qtextcodec.h>
#include <qlayout.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <qimage.h>
#include <qtimer.h>

#define REFLASH_ON 0
#define SHUT_ON 1 
#define REBOOT_ON 2 
#define REFLASH_DOWN 3
#define SHUT_DOWN 4
#define REBOOT_DOWN 5


QString ChineseAndEnglish(const char*ChineseString);

class MyZKbMain : public ZKbMainWidget
{	
	Q_OBJECT
//////////////////
	public:
	int icon0_y;
	int icon1_y;
	int width0;
	int width1;
	int height0;
	int height1;

	int reflash_x;
	int shut_x;
	int reboot_x;
	int cancel_x;
		
	int start_x;
	int start_y;
	int line_color;
		int curren_stat;
		bool flag_cancel;
		bool flag_cancel_down;
		bool flag_loading;
		QImage myimg;
	public:
	MyZKbMain(char * currentpath):ZKbMainWidget((ZHeader::HEADER_TYPE)3,NULL , "ZMainWidget" , 0)
	{
		ini_soft();
		myimg.load("/mmc/mmca1/.system/QTDownLoad/zShutDown/shut_down.png");
		flag_cancel=false;
		flag_cancel_down=false;
		flag_loading=false;
		curren_stat=SHUT_ON ;
		setMainWidgetTitle("shut_down");
	//	QVBoxLayout* layout = getVBoxLayout();
	//		inifontfile();
		setFullScreenMode(true, true);
}
public :
int getintformini(FILE *fp , char * keyname);
int ini_soft();
~MyZKbMain();
 private slots:
//	virtual void timerEvent(QTimerEvent* e);
	virtual void keyPressEvent(QKeyEvent* k);
	virtual void paintEvent( QPaintEvent * pe);
	void slotTimeout();
};

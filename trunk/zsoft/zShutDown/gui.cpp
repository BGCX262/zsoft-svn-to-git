/*
仿windows关机界面 for moto e2
2008-2-1
written by letterb	@scnu_cs _05
Email:	boy.letterb@yahoo.com.cn	或 	letterb@tom.com
Thanks:lasly's sdk
*/
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
		myimg.load("shut_down.png");
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

void MyZKbMain::slotTimeout()		//调用命令
{
	static bool send_cmd_now=false;
	if(send_cmd_now)
	{
			char cmd[3][100]={"./item0.sh","./item1.sh","./item2.sh"};
//			char cmd[3][100]={"kill `pidof phone` ; kill `pidof am`","halt","reboot"};
			system(cmd[curren_stat-3]);
			qApp->quit();
	}
	if(!flag_loading)
	{
		if(flag_cancel_down)
		{
			qApp->quit();
		}
		else
		{
			flag_loading=true;
			send_cmd_now=true;
			update();
			QTimer::singleShot(100, this, SLOT(slotTimeout()));
		}
	}
	else
	{
//		if(curren_stat!=REFLASH_DOWN)
			qApp->quit();		
	}
}

MyZKbMain::~MyZKbMain()
{
/*	if(flag_cancel_down)
	{
	
	}
	else
	{
		char cmd[3][100]={"kill -9 `pidof phone`","halt","reboot"};
		system(cmd[curren_stat-3]);
	}*/
}

int MyZKbMain::ini_soft()		//初始化
{
	FILE * fp = fopen("shut.ini","r");
	if(fp==NULL)
		return 0;
	icon0_y=getintformini(fp,"icon0_y");
	icon1_y=getintformini(fp,"icon1_y");
	width0=getintformini(fp,"width0");
	width1=getintformini(fp,"width1");
	height0=getintformini(fp,"height0");
	height1=getintformini(fp,"height1");

	reflash_x=getintformini(fp,"reflash_x");
	shut_x=getintformini(fp,"shut_x");
	reboot_x=getintformini(fp,"reboot_x");
	cancel_x=getintformini(fp,"cancel_x");

	start_x=getintformini(fp,"start_x");
	start_y=getintformini(fp,"start_y");
	line_color=getintformini(fp,"line_color");
	fclose(fp);
	return 0;
}

void MyZKbMain::keyPressEvent(QKeyEvent* k)
{
	switch (k->key())
	{
		//5
		case 4100:
		case 53:
			if(flag_cancel)
				flag_cancel_down=1;
			else
				curren_stat+=3;			
			update();
			QTimer::singleShot(50, this, SLOT(slotTimeout()));
		break; 
		//		up
		case 4115:
		case 50:
			flag_cancel=false;
			update();
		break;
		//down
		case 4117:
		case 56:
			flag_cancel=true;
			update();
		break;
		//left
		case 4114:
		case 52:
			if(flag_cancel)
				break;
			curren_stat--;
			if(curren_stat==-1)
				curren_stat=2;
			update();
		break;
		//right
		case 4116:
		case 54:
			if(flag_cancel)
				break;
			curren_stat++;
			if(curren_stat==3)
				curren_stat=0;
			update();
		break;
		case 4145:
			close();
		break;		
	}
//	return QWidget::keyPressEvent(k);
}

void MyZKbMain::paintEvent(QPaintEvent * pe)
{
//		int width=20;
		int x1=0;
		int y1=0;
//		int x2=0;
	//	int y2=0;
		if(!flag_loading)
		{
//			QImage img;//( "bg.bmp" );
			QPixmap	pix;
			pix=myimg;
			QRect ur(0,0,240,320);
			ur=pe->rect();				//用户可见区域
			QPainter p(&pix);
			p.begin(&pix);
			QPen pen(QColor( ((line_color >> 16) & 0xff ), ((line_color >> 8) & 0xff) ,line_color & 0xff),1);
	//		pen.setWidth(5);
			p.setPen(pen);
			
			if(!flag_cancel)
			{
				switch (curren_stat)
				{
					case REFLASH_ON:	
					case REFLASH_DOWN:	
						x1=reflash_x;
						y1=icon0_y;
					break;
					case SHUT_ON:
					case SHUT_DOWN:	
						x1=shut_x;
						y1=icon0_y;
					break;
					case REBOOT_ON: 	
					case REBOOT_DOWN: 	
						x1=reboot_x;
						y1=icon0_y;				
					break;
				}
		//		x2=x1+width;
		//		y2=y1+width;
	//			p.drawWinFocusRect(x1,y1,width,width);	
				if(curren_stat<3)		
					p.drawWinFocusRect(x1,y1,width0,height0);		//绘制高亮选框
				else
				{
					p.drawRoundRect(x1,y1,width0,height0,50,50);	//绘制按下框
				}
			}
			else
			{
				x1=cancel_x;
				y1=icon1_y;						
	//			x2=x1+width;
		//		y2=y1+width/2;
				if(!flag_cancel_down)
					p.drawWinFocusRect(x1,y1,width1,height1);//,QColor(0,0,255));	//drawRect		
				else
					p.drawRoundRect(x1,y1,width1,height1,50,50);	//drawRect					
			}
			p.end();
//			img=pix;
			setWFlags(getWFlags() | Qt::WRepaintNoErase);
			bitBlt(   this,  start_x , start_y  ,  &pix,   0,   0,   -1,   -1   );   
		}
		else
		{
			
//			QImage img;//( "bg.bmp" );
			myimg.load("poweroff.png");		//按键按下后
			QPixmap	pix;
			pix=myimg;
			QRect ur(0,0,240,320);
			ur=pe->rect();
			QPainter p(&pix);
			p.begin(&pix);
			p.end();
//			img=pix;
			setWFlags(getWFlags() | Qt::WRepaintNoErase);
			bitBlt(   this,  0 , 0  ,  &pix,   0,   0,   -1,   -1   );   
		}
	 QWidget::paintEvent( pe);

}

int MyZKbMain::getintformini(FILE * fp, char * keyname)
{
	
	int value;
	int i;
	char buf[50];
	char tmp[20];
	char *p;
	fseek(fp,0,SEEK_SET);
	memset(tmp,0,sizeof tmp);
//    FILE *fp;
//    if((fp=fopen(filename,"r"))==NULL)
   //     printf("error\n");
    while(fgets(buf,sizeof buf,fp))
    		{ 
    		if(buf[0]=='#')
    			continue;
	      if(p=strstr(buf,keyname))
		         {	
		      p+=strlen(keyname);
				p++;
				i=0;
		      while(*p)
		      		{
		      	tmp[i++]=*p;
		      	p++;
		      		}
		     	tmp[i]='\0';
	//			printf(tmp);
				break;
			}
	    }
//    fclose (fp);
    value=atoi(tmp);
	return value;
}


int main( int argc, char **argv )
{
	ZApplication* a = new ZApplication( argc, argv );
	MyZKbMain*zmain=new MyZKbMain("/mmc/mmca1/.system/QTDownLoad/zShutdown");
	a->setMainWidget( zmain );
    	zmain->show();
	a->exec();

	delete zmain;
	delete a;
   	return argc;

}
#include"gui.moc"

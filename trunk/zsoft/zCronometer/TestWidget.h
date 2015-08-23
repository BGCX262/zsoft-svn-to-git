//
// C++ Interface: TestWidget
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#define QT_NO_DRAGANDDROP
#define QT_NO_PROPERTIES

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>
//#include <iostream.h>
#include <qfile.h>
#include <qtextcodec.h>
#include <qlayout.h>
#include <qdir.h>
#include <pthread.h>
#include <qwidget.h>
#include <qdirectpainter_qws.h>
#include <qdatetime.h>

#include <ZApplication.h>
#include <ZKbMainWidget.h>
#include <ZSoftKey.h>
#include <ZPanel.h>
#include <ZLabel.h>
#include <ZScrollPanel.h>
#include <ZOptionsMenu.h>
#include <ZMessageDlg.h>
#include <ZSingleCaptureDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZListBox.h>
#include <ZNoticeDlg.h>
#include <ZNumPickerDlg.h>
#include <qtimer.h>

//using namespace std;

class TestWidget : public ZKbMainWidget
{
        Q_OBJECT
	int status;
	pthread_t thread;
	QWidget* dlg;
	ZNumPickerDlg* dlg_size;
	ZNoticeDlg* znd;
	ZSoftKey* softKey;
	ZPanel* zpl;
        ZScrollPanel* scrollPanel;
	ZOptionsMenu* menu_Main;
	int h1,h2,m1,m2,s1,s2,ms1,ms2;
	QTime* tiempo;
	QTime* t2;
	QTimer *timer;
	QString hst,mst,sst,msst;
	int h,m,s,ms;
	QString getProgramDir();
	QColor color;
	int size;
public:
        TestWidget(QWidget* parent, char*);
        ~TestWidget();
	
public slots:
   //virtual void timerEvent(QTimerEvent* e);
   void about();
   void crono();
   void para();
   ZLabel* label;
   void texto();
   void crearTimer();
   void changecolor();	 
   void changesize();	
};


#endif

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

/**
	@author BeZ <bezols@gmail.com>
*/

//using namespace std;

class TestWidget : public ZKbMainWidget
{
        Q_OBJECT
	int status;
	pthread_t thread;
	QWidget* dlg;
	ZSingleCaptureDlg* dlg_bt_settings;
	ZSingleSelectDlg* dlg_java_heap;
        ZNumPickerDlg* dlg_bt_discover;
	ZNumPickerDlg* dlg_java_jsr135_volume;
	ZNoticeDlg* znd;
	ZSoftKey* softKey;
	ZPanel* zpl;
        ZScrollPanel* scrollPanel;
	ZOptionsMenu* menu_Main;
	ZOptionsMenu* subMenu_BT;
	ZOptionsMenu* subMenu_Java;
public:
        TestWidget(QWidget* parent, char*);
        ~TestWidget();
	
public slots:
   //virtual void timerEvent(QTimerEvent* e);
   void about();
   void BTSettings();
   void BT_Discover();
   void JavaHeap();
   void JavaJSR135Volume();
};


#endif

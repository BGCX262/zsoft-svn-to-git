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

//using namespace std;

class TestWidget : public ZKbMainWidget
{
        Q_OBJECT
	int status;
	pthread_t thread;
	QWidget* dlg;
	ZSingleCaptureDlg* dlg_bt_settings;
	ZNumPickerDlg* dlg_bt_discover;
	ZNoticeDlg* znd;
	ZSoftKey* softKey;
	ZPanel* zpl;
        ZScrollPanel* scrollPanel;
	ZOptionsMenu* menu_Main;
	ZOptionsMenu* subMenu_BT;
	
public:
        TestWidget(QWidget* parent, char*);
        ~TestWidget();
	
public slots:
   void about();
   void BT_Discover();

};


#endif

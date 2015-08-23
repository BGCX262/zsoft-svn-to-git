//
// C++ Interface: zgui
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ZGUI_H
#define ZGUI_H

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>

#include <ZMessageDlg.h>
#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZScrollPanel.h>
#include <ZNumPickerDlg.h>
#include <ZNoticeDlg.h>
#include <ZConfig.h>
/**
  @author BeZ <bezols@gmail.com>
*/

//using namespace std;

class ZGui : public ZKbMainWidget
{
    Q_OBJECT
  public:
    ZGui (QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZGui();
    QString getProgramDir();
    void CreateWindow(QWidget* parent);
    
  public slots:
    void about();
    //void slot_fileOpenDlg();
    //void slot_fileSaveDlg();
    void BT_time();
   // QString getProgramDir();

  private:
    QString ProgDir;
    ZScrollPanel *scrollPanel;
    ZNumPickerDlg* dlg_bt_discover;    ZNoticeDlg* znd;
	
};



#endif


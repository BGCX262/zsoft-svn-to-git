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
#include <qfile.h>

#include <ZMessageDlg.h>
#include <ZNavTabWidget.h>
#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZScrollPanel.h>
#include <ZNumPickerDlg.h>
#include <ZSingleCaptureDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZMultiSelectDlg.h>
#include <ZLabel.h>
#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>
#include <ZSoftKey.h>


/**
  @author BeZ <bezols@gmail.com>
*/

//using namespace std;

class ZGui : public ZKbMainWidget
{
    Q_OBJECT
  public:
    ZGui (const QString &APackageToOpen = QString::null, QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZGui();
    QString getProgramDir();
    QString getFileName(const QString &AFileName);
    QString ClaveCorrecta;
    void CreateWindow(QWidget* parent);
    QString ProgDir;
    QString Idioma;
    QWidget* dlg;
    ZNoticeDlg* znd;
    ZListBox* mainList;
    ZListBox* blackList;
    ZListBox* whiteList;
    ZListBox* regCalls;
	QString Potencia;
	
	void Create_SoftKeyMain();
    void Create_SoftKey();
    void Create_MenuApp();
    void Create_MenuBlack();
    void Create_MenuWhite();
    void Create_MenuCalls();

  signals:
    void picked(const QString &sFileName);
    void isFilePicked(bool);
    
  public slots:
    void about();
    void salir();
    void language();
    void CargarMain();
    void CargarBlacklist();
    void CargarWhitelist();
    void CargarLlamadas();
    void ChangeState();
    void ChangeList();
    void addNumber1();
    void addNumber2();
    void removeNumber1();
    void removeNumber2();
    void removeCall();
    void blockUnk();

    void slotCurrentChanged(QWidget* AWidget);    
    void appClicked(ZListBoxItem *);   

  private:
    ZScrollPanel *scrollPanel;
    ZNavTabWidget *tabWidget;
    ZSoftKey *softKey;
    ZOptionsMenu * menu;

};



#endif


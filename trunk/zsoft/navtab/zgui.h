#ifndef ZGUI_H
#define ZGUI_H

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>
#include <qfile.h>

#include <ZNavTabWidget.h>
#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZScrollPanel.h>
#include <ZNoticeDlg.h>


//using namespace std;

class ZGui : public ZKbMainWidget
{
    Q_OBJECT
  public:
    ZGui (const QString &Argument = QString::null, QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZGui();
    void CreateWindow(QWidget* parent);
    QString texto(const char*xString);
    QString getProgramDir();
    QString ProgDir;
    ZListBox* zllb1;
    ZListBox* zllb2;
    ZListBox* zllb3;
    ZListBox* zllb4;
    ZListBox* zllb5;
    void Create_SoftKey();
    void Create_MenuApp();

  public slots:
    void MenuClick();   
    void CargarMenu1();
    void CargarMenu2();
    void CargarMenu3();
    void CargarMenu4();
    void CargarMenu5();
    void appClicked1();
    void appClicked2();
    void appClicked3();
    void appClicked4();
    void appClicked5();

  private:
    ZNavTabWidget *tabWidget;
    ZSoftKey *softKey;
    ZOptionsMenu * menu;


};



#endif


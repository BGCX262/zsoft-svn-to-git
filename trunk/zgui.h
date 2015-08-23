#ifndef ZGUI_H
#define ZGUI_H

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>
#include <qfile.h>
#include <qlabel.h>

#include <ZNavTabWidget.h>
#include <ZKbMainWidget.h>
#include <ZPopup.h>
#include <ZSoftKey.h>
#include <ZScrollPanel.h>
#include <ZMessageDlg.h>
#include <ZComboBox.h>


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
    void Create_SoftKey();
    void Create_MenuApp();



  public slots:

    void guardar();
    void MenuClick();

  private slots:
	
    virtual void keyPressEvent(QKeyEvent* k);



  private:
    ZMessageDlg * reboot;
    ZFormContainer* scrollPanel;
    ZLabel* infoLabel;
    ZLabel* infoLabel2;
    ZLabel* infoLabel3;
    ZComboBox* ComboBox;
    ZComboBox* ComboBox2;
    ZComboBox* ComboBox3;
    ZSoftKey* softKey;
    ZOptionsMenu* menu;
    ZPopup* salir;

};



#endif


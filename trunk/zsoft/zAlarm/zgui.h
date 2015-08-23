
#ifndef ZGUI_H
#define ZGUI_H

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>

#include <ZMessageDlg.h>
#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZScrollPanel.h>
#include <qstring.h>
#include <ZLabel.h>
#include <ZComboBox.h>
#include <ZNoticeDlg.h>


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
    void tiempo();    
    void leerini();
    void espanol();
    void ingles();
   //void cambiaridioma();

  private:
    QString ProgDir;
    ZScrollPanel *scrollPanel;
    ZComboBox* idioma;
    QString idiomastring;
    ZLabel* infoLabel;
    ZNoticeDlg* znd;
};



#endif


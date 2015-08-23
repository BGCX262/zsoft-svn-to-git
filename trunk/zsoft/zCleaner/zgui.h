#ifndef ZGUI_H
#define ZGUI_H

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>

#include <ZMessageDlg.h>
#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZScrollPanel.h>
#include <qstringlist.h>
#include <qdir.h>
#include <ZNoticeDlg.h>


class ZGui : public ZKbMainWidget
{
    Q_OBJECT
  public:
    ZGui (QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZGui();
    QString getProgramDir();
    void CreateWindow(QWidget* parent);
    void borrar(QStringList lista);
    QStringList limpiar(const QString &path, const QString &filter);
  public slots:
    void about();
    void ejecutar();    
  private:
    QString ProgDir;
    ZScrollPanel *scrollPanel;
    ZNoticeDlg* infos;
};



#endif


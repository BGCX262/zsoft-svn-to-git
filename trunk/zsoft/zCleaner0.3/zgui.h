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
#include <ZComboBox.h>
#include <ZSingleSelectDlg.h>
#include <ZLabel.h>


class ZGui : public ZKbMainWidget
{
    Q_OBJECT
  public:
    ZGui (const QString &ejecuta = QString::null,QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZGui();
    QString getProgramDir();
    void CreateWindow(QWidget* parent);
    void borrar(QStringList lista);
    void borrarcuidado(QStringList lista2);
    QStringList limpiar(const QString &path, const QString &filter);
    int confirmacion(QString aux);
  public slots:
    void about();
    void ejecutar();    
    void agregarTipoASK();
    void agregarTipoDELETE();
    void eliminarTipoASK();
    void eliminarTipoDELETE();
    void verEliminados();
  private:
    QString ProgDir;
    ZScrollPanel *scrollPanel;
    ZNoticeDlg* infos;
    ZComboBox * lugar;
    ZComboBox * modo;
    ZLabel * lab1;
    ZLabel * lab2;
    ZSingleSelectDlg * dlg;	
    QStringList eliminados;
    QStringList todos;
    
};



#endif


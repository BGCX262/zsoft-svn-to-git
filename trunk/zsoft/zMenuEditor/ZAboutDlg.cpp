//
// C++ Implementation: ZAboutDlg
//
// Description:
//
//
// Author: root <root@andLinux>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "BaseDlg.h"
#include "ZAboutDlg.h"

#include <qlabel.h>
#include <ZApplication.h>
#include <ZSoftKey.h>


ZAboutDialog::ZAboutDialog()
    :MyBaseDlg()
{

  setMainWidgetTitle ( "zMenuEditor" );

  QString ProgDir = QString ( qApp->argv() [0] ) ;
  int i = ProgDir.findRev ( "/" );
  ProgDir.remove ( i+1, ProgDir.length() - i );

  QWidget *myWidget = new QWidget ( this );
  //myWidget->setGeometry(0,0,240,320);
  QVBoxLayout *myVBoxLayout = new QVBoxLayout ( myWidget, 0 );
  QHBoxLayout *myHBoxLayout = new QHBoxLayout;
  myHBoxLayout->setSpacing ( 4 );
  myHBoxLayout->setMargin ( 10 );

  QLabel *myLabel = new QLabel ( myWidget );
  myLabel->setPixmap ( QPixmap ( "" ) );
  myLabel->setScaledContents ( false );
  myHBoxLayout->addWidget ( myLabel );

  myLabel = new QLabel ( QString ( "<qt><img src=%1/images/icon.png><br>"
                                   "<font size=\"+1\">zMenuEditor</font><font size=\"-1\">"
                                   "  v0.1<br><br>Motorola Z6 Linuxmod<br>www.modmymoto.com<br>"
                                   "<br><br>(C) 2008. CepiPerez"
                                   "</font></qt>" ).arg(ProgDir) , myWidget );
  myHBoxLayout->addWidget ( myLabel, 1 );
  myVBoxLayout->addLayout ( myHBoxLayout );

  QSpacerItem* spacer = new QSpacerItem ( 8, 8, QSizePolicy::Minimum, QSizePolicy::Expanding );
  myVBoxLayout->addItem ( spacer );

  //myLabel = new QLabel ( "Licensed under the GNU GPL.", myWidget );
  //myVBoxLayout->addWidget ( myLabel );
  setContentWidget ( myWidget );

  ZSoftKey *softKey = new ZSoftKey ( NULL, this, this );
  softKey->setText ( ZSoftKey::LEFT, "Aceptar", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  //softKey->setText ( ZSoftKey::RIGHT, "Reject", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  //softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( reject() ) );
  softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( accept() ) );
  setCSTWidget ( softKey );
}

ZAboutDialog::~ZAboutDialog()
{

}



//int ZAboutDialog::exec()
//{}

//int ZAboutDialog::result() const
//{ }

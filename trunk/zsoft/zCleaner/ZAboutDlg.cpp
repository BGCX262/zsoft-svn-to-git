
#include "BaseDlg.h"
#include "ZAboutDlg.h"

#include <qlabel.h>
#include <ZApplication.h>
#include <ZSoftKey.h>

ZAboutDialog::ZAboutDialog()
    :MyBaseDlg()
{
  setMainWidgetTitle ( "zCleaner" );

  QString ProgDir = QString ( qApp->argv() [0] ) ;
  int i = ProgDir.findRev ( "/" );
  ProgDir.remove ( i+1, ProgDir.length() - i );
  QWidget *myWidget = new QWidget ( this );
  //myWidget->setGeometry(0,0,240,320);
  QVBoxLayout *myVBoxLayout = new QVBoxLayout ( myWidget, 0 );
  QHBoxLayout *myHBoxLayout = new QHBoxLayout;
  myHBoxLayout->setSpacing ( 4 );
  myHBoxLayout->setMargin ( 0 );

  QLabel *myLabel = new QLabel ( myWidget );
  myLabel->setPixmap ( QPixmap ( "folder.png" ) );
  myLabel->setScaledContents ( false );
  myHBoxLayout->addWidget ( myLabel );

  myLabel = new QLabel ( QString ( "<qt><img src=%1/img/zCleaner_usr.png><br>"
"<qt>zCleaner 0.1 by c_ro87<br>" "<qt>Base GUI zGui 0.7.4g by BeZ<br>"
                                   "<font size=\"-1\">zCleaner is a simple antivirus for Z6</font></qt>" ).arg(ProgDir), myWidget );
  myHBoxLayout->addWidget ( myLabel, 1 );
  myVBoxLayout->addLayout ( myHBoxLayout );

  myLabel = new QLabel ( QString ( "<qt><font size=\"-1\"><p>Copyright (C) 2008 c_ro87<br>"
                                   "<tt>&lt;cristian_ro87@hotmail.com&gt;</tt><br></font></qt>" ),
                         myWidget );
  myVBoxLayout->addWidget ( myLabel );

  QSpacerItem* spacer = new QSpacerItem ( 8, 8, QSizePolicy::Minimum, QSizePolicy::Expanding );
  myVBoxLayout->addItem ( spacer );

  myLabel = new QLabel ( "www.modmymoto.com", myWidget );
  myVBoxLayout->addWidget ( myLabel );
  setContentWidget ( myWidget );

  ZSoftKey *softKey = new ZSoftKey ( NULL, this, this );
  softKey->setText ( ZSoftKey::LEFT, "OK", ( ZSoftKey::TEXT_PRIORITY ) 0 );
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

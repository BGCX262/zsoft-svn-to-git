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

  myLabel = new QLabel ( QString ( "<qt>zBTTime 0.2<br>"
                                   "<font size=\"-1\">Change the BT discoverable period time</font></qt>" ), myWidget );
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

 /* ZSoftKey *softKey = new ZSoftKey ( NULL, this, this );
  softKey->setText ( ZSoftKey::LEFT, "Accept", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, "Reject", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( reject() ) );
  softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( accept() ) );
  setCSTWidget ( softKey );
*/
ZSoftKey *softKey = this->getSoftKey();
  softKey->setText ( ZSoftKey::LEFT, "Ok", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, "", ( ZSoftKey::TEXT_PRIORITY ) 0 );
  //softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( reject() ) );
  softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( accept() ) );
 
}

ZAboutDialog::~ZAboutDialog()
{

}

//int ZAboutDialog::exec()
//{}

//int ZAboutDialog::result() const
//{ }

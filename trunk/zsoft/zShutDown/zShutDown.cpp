//
// C++ Implementation: TestMain
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "MyZKbMain.h"
#include <ZApplication.h>

//TestWidget* testWidget;
int main( int argc, char **argv )
{
	ZApplication* a = new ZApplication( argc, argv );
//	MyZKbMain* zmain=new MyZKbMain("/mmc/mmca1/.system/QTDownLoad/zShutdown");
MyZKbMain* zmain=new MyZKbMain("/mmc/mmca1/.system/QTDownLoad/zShutDown/");
	a->setMainWidget( zmain );
    	zmain->show();
	a->exec();

	delete zmain;
	delete a;
   	return argc;

}

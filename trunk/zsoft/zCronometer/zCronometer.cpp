#include "TestWidget.h"
#include <ZApplication.h>

TestWidget* testWidget;
ZApplication* a;
int main( int argc, char **argv )
{
        ZApplication* a = new ZApplication( argc, argv );
        testWidget = new TestWidget(NULL, NULL);
        testWidget->setGeometry(0,0,240,320);
	a->setMainWidget(testWidget);
	testWidget->show();
        int ret = a->exec();
	delete testWidget;
	delete a;
	return ret;
}

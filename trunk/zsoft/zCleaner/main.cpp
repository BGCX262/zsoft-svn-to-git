
#include "zgui.h"
//#include "GUI_Define.h"
#include <ZApplication.h>

ZGui* zgui;
ZApplication* app;

int main ( int argc, char **argv )
{
  app = new ZApplication ( argc, argv );
  ZGui *zgui = new ZGui ( NULL, NULL );
  int ret = app->exec();
  delete zgui;
  zgui = NULL;
  delete app;
  app = NULL;
  return ret;
}

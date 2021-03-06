/*
  PictureFlow - animated image show widget
  http://pictureflow.googlecode.com

  Copyright (C) 2007 Ariya Hidayat (ariya@kde.org)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifdef PICTUREFLOW_EZX
#ifdef EZX_E2
#include <ZApplication.h> // different header name for same class :(
#else
#include <zapplication.h>
#endif
#include "qwallpaper.h"
#endif

#include <qapplication.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qpixmap.h>

#include "pictureflow.h"

QStringList findFiles(const QString& path = QString())
{
  QStringList files;

  QDir dir = QDir::current();
  if(!path.isEmpty())
    dir = QDir(path);

  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
#if QT_VERSION >= 0x040000
  QFileInfoList list = dir.entryInfoList();
  for (int i = 0; i < list.size(); ++i) 
  {
    QFileInfo fileInfo = list.at(i);
    files.append(dir.absoluteFilePath(fileInfo.fileName()));
  }
#else
  const QFileInfoList* list = dir.entryInfoList();
  if(list) 
  {
    QFileInfoListIterator it( *list );
    QFileInfo * fi;
    while( (fi=it.current()) != 0 ) 
    {
      ++it;
      files.append(dir.absFilePath(fi->fileName()));
    }
  }
#endif

  return files;
}

int main( int argc, char ** argv )
{
#ifdef PICTUREFLOW_EZX
  ZApplication a( argc, argv );
  QWallpaper::setAppWallpaperMode(QWallpaper::Off);
#else
  QApplication a( argc, argv );
#endif

  PictureFlow* w = new PictureFlow;

#ifdef PICTUREFLOW_EZX
#ifdef PICTUREFLOW_LANDSCAPE
  w->setSlideSize(QSize(150, 178));
#else
  w->setSlideSize(QSize(150, 240));
#endif
  w->resize(240, 320);
#else
  w->setSlideSize(QSize(150, 250));
#ifdef PICTUREFLOW_LANDSCAPE
  w->resize(350, 780);
#else
  w->resize(780, 350);
#endif
#endif

  QStringList files = (argc > 1) ? findFiles(QString(argv[1])) : findFiles();

  QPixmap pixmap;
  for(int i = 0; i < (int)files.count(); i++)
    if(pixmap.load(files[i]))
      w->addSlide(pixmap);

  w->setCenterIndex(w->slideCount()/2);
#ifdef PICTUREFLOW_EZX
  a.setMainWidget(w);
  w->showFullScreen();
#else
  w->show();
#endif
  w->setBackgroundColor(Qt::black);

  a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
  return a.exec();
}

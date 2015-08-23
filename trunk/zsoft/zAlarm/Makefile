TOOLPREFIX:=	/arm-eabi
#Remember to set your own TOOLPREFIX. A to pi3dec bydet!
QTDIR	:=	$(TOOLPREFIX)/lib/qt-2.3.8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-z6
UPLOAD_PATH :=  /mmc/mmca1/bin/
CC	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
CXX	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
LD	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
CFLAGS	=	-pipe -Wall -W -O2 -DNO_DEBUG $(INCPATH)
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG $(INCPATH)
INCPATH	=	-I$(QTDIR)/include -I$(EZXDIR)/include -I $(TOOLPREFIX)/arm-linux-gnueabi/include
LDFLAGS	=	-s
LINK	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
LFLAGS	=	
LIBS	=	$(SUBLIBS) -L$(TOOLPREFIX)/arm-linux-gnueabi/lib -L$(QTDIR)/lib -L$(EZXDIR)/lib -lm -lqte-mt -lezxpm -ljpeg -lezxappbase -lezxtapi-xscale-r -llog_util -llighting
MOC	=	$(QTDIR)/bin/moc
UIC	=	$(QTDIR)/bin/uic


####### Files
HEADERS =   zgui.h\
            GUI_Define.h\
            BaseDlg.h\
            ZAboutDlg.h\
            ZFileBrowser.h\
            ZFileDlg.h
            
SOURCES =   main.cpp\
            zgui.cpp\
            BaseDlg.cpp\
            ZAboutDlg.cpp\
            ZFileBrowser.cpp\
            ZFileDlg.cpp
	    
OBJECTS =   main.o zgui.o\
            BaseDlg.o\
            ZAboutDlg.o\
            ZFileBrowser.o\
            ZFileDlg.o
            
SRCMOC	=	moc_zgui.cpp\
          moc_BaseDlg.cpp\
          moc_ZAboutDlg.cpp\
          moc_ZFileBrowser.cpp\
          moc_ZFileDlg.cpp
                
OBJMOC	=	moc_zgui.o\
          moc_BaseDlg.o\
          moc_ZAboutDlg.o\
          moc_ZFileBrowser.o\
          moc_ZFileDlg.o
                
TARGETS = 	$(TARGET)
TARGET	=       zAlarm
INTERFACE_DECL_PATH = .



all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

moc: $(SRCMOC)

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core
	$(RM) *.o
	$(RM) moc_*.cpp

#----------- obj -----------------------------
main.o: main.cpp
zgui.o: zgui.cpp zgui.h
BaseDlg.o: BaseDlg.cpp BaseDlg.h
ZAboutDlg.o: ZAboutDlg.cpp ZAboutDlg.h
ZFileBrowser.o: ZFileBrowser.cpp ZFileBrowser.h
ZFileDlg.o: ZFileDlg.cpp ZFileDlg.h

#--------- moc's -----------------------------
moc_zgui.o: moc_zgui.cpp zgui.h
moc_zgui.cpp: zgui.h
	$(MOC) zgui.h -o moc_zgui.cpp
  
moc_BaseDlg.o: moc_BaseDlg.cpp BaseDlg.h
moc_BaseDlg.cpp: BaseDlg.h
	$(MOC) BaseDlg.h -o moc_BaseDlg.cpp

moc_ZAboutDlg.o: moc_ZAboutDlg.cpp ZAboutDlg.h
moc_ZAboutDlg.cpp: ZAboutDlg.h
	$(MOC) ZAboutDlg.h -o moc_ZAboutDlg.cpp
	
moc_ZFileBrowser.o: moc_ZFileBrowser.cpp ZFileBrowser.h
moc_ZFileBrowser.cpp: ZFileBrowser.h
	$(MOC) ZFileBrowser.h -o moc_ZFileBrowser.cpp
			
moc_ZFileDlg.o: moc_ZFileDlg.cpp ZFileDlg.h
moc_ZFileDlg.cpp: ZFileDlg.h
	$(MOC) ZFileDlg.h -o moc_ZFileDlg.cpp
				
#----------------------------------------------
install: $(TARGETS)
	ncftpput -u root -p "" 192.168.16.2 $(UPLOAD_PATH) $(TARGETS)

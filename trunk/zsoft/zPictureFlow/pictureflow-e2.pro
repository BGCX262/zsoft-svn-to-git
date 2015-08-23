TEMPLATE = app
HEADERS = pictureflow.h
SOURCES = pictureflow.cpp main.cpp
DEFINES += PICTUREFLOW_LANDSCAPE

CONFIG += qt warn_off release thread
CONFIG += ezx
TARGET = pictureflow

ezx:DEFINES += PICTUREFLOW_EZX EZX_E2
ezx:HEADERS += dropin/qtl.h dropin/qvaluevector.h
ezx:INCLUDEPATH += ${EZXDIR}/include dropin
ezx:LIBS += -Wl,-rpath-link,${EZXDIR}/lib -L${EZXDIR}/lib -lezxappbase

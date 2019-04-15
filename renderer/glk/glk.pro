######################################################################
# Automatically generated by qmake (2.01a) ?? 9? 17 20:37:54 2016
######################################################################

TEMPLATE = lib
TARGET = glk
DEPENDPATH += . ../opengl
INCLUDEPATH += . ../opengl

LIBS += -lopengl

include(../../netlizard-game.pri)
harmattan_opengl {
PKGONFIG += glut
LIBS += -lglut
DEFINES += _USE_MESAGLUT
}

CONFIG += plugin
CONFIG += x11 shared 
PRE_TARGETDEPS += $$DESTDIR/libopengl.so 

# Input
HEADERS += glk.h \
private_glk_egl.h \
private_glk_glx.h \
private_glk_xi2.h

SOURCES += glk.c

libglk.files = $$DESTDIR/libglk*
libglk.path = /usr/lib

INSTALLS += libglk
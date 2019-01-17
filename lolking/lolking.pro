######################################################################
# Automatically generated by qmake (2.01a) ?? 9? 17 20:37:54 2016
######################################################################

TEMPLATE = lib
TARGET = lolking
DEPENDPATH += . .. ../SOIL ../math3d ../opengl
INCLUDEPATH += . .. ../SOIL ../math3d ../opengl

LIBS += -lSOIL -lglk -lmath3d -lopengl
LIBS += -lz

#QMAKE_CXXFLAGS += -std=c++0x

include(../netlizard-game.pri)

QT -= core gui
CONFIG += plugin
QT -= core gui
CONFIG -= qt
CONFIG += debug_and_release x11 shared 
CONFIG(debug, debug|release) {
OBJECTS_DIR = ../.debug/.obj/lolking
DESTDIR = ../.debug
LIBS += -L../.debug
PRE_TARGETDEPS += ../.debug/libSOIL.so ../.debug/libmath3d.so ../.debug/libglk.so ../.debug/libopengl.so
} else {
OBJECTS_DIR = ../.release/.obj/lolking
DESTDIR = ../.release
LIBS += -L../.release
PRE_TARGETDEPS += ../.release/libSOIL.so ../.release/libmath3d.so ../.release/libglk.so ../.release/libopengl.so
}

# Input
HEADERS += lol.h \
lol_render.h \
lol_struct.h \
           anim_reader.h \
           mesh_reader.h

SOURCES += mesh_reader.c \
lol.c \
           anim_reader.c \
lol_struct.c \
lol_render.c

liblolking.files = ../.release/liblolking*
liblolking.path = /usr/lib

INSTALLS += liblolking

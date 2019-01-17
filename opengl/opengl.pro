######################################################################
# Automatically generated by qmake (2.01a) ?? 9? 17 20:37:54 2016
######################################################################

TEMPLATE = lib
TARGET = opengl
DEPENDPATH += .
INCLUDEPATH += .

#QMAKE_CXXFLAGS += -std=c++0x

include(../netlizard-game.pri)

CONFIG += plugin
QT -= core gui
CONFIG -= qt
CONFIG += debug_and_release x11 shared 
CONFIG(debug, debug|release) {
OBJECTS_DIR = ../.debug/.obj/opengl
DESTDIR = ../.debug
} else {
OBJECTS_DIR = ../.release/.obj/opengl
DESTDIR = ../.release
}

# Input
HEADERS += opengl.h \
openglu.h

SOURCES += opengl.c

harmattan_opengles {
HEADERS += gles1.1/opengl/opengl1.h \
gles1.1/openglu/openglu1.h

SOURCES += gles1.1/opengl/opengl1.c \
gles1.1/openglu/glu_project.c \
gles1.1/openglu/glu_error.c \
gles1.1/openglu/glu_mipmap.c
} else:harmattan_opengles2{
HEADERS += gles2.0/opengl/opengl2.h \
gles2.0/openglu/openglu2.h \
gles2.0/opengl/opengl2_math.h \
gles2.0/opengl/opengl2_port.h \
gles2.0/opengl/opengl2_def.h

SOURCES += gles2.0/opengl/opengl2.c \
gles2.0/opengl/opengl2_attrib.c \
gles2.0/opengl/opengl2_math.c \
gles2.0/opengl/opengl2_matrix.c \
gles2.0/opengl/opengl2_program.c \
gles2.0/opengl/opengl2_shaderprogram.c \
gles2.0/opengl/opengl2_transform.c \
gles2.0/openglu/glu_project.c \
gles2.0/openglu/glu_error.c \
gles2.0/openglu/glu_mipmap.c
}

libopengl.files = ../.release/libopengl*
libopengl.path = /usr/lib

INSTALLS += libopengl

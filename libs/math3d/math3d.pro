######################################################################
# Automatically generated by qmake (2.01a) ?? 9? 17 20:37:54 2016
######################################################################

TEMPLATE = lib
TARGET = math3d
DEPENDPATH += . ..
INCLUDEPATH += . ..

include(../../netlizard-game.pri)

CONFIG += plugin
CONFIG += shared 

# Input
HEADERS += graph.h \
					 algo.h \
					 matrix44.h \
					 glmatrix44.h \
					 matrix.h \
					 matrix33.h \
					 math3d_std.h \
					 quat.h \
					 base_algo.h \
					 vector2.h \
					 vector.h \
					 vector3.h

SOURCES += graph.c \
					 algo.c \
					 matrix44.c \
					 glmatrix44.c \
					 matrix33.c \
					 quat.c \
					 base_algo.c \
					 vector2.c \
					 vector3.c

libmath3d.files = $$DESTDIR/libmath3d*
libmath3d.path = /usr/lib

INSTALLS += libmath3d


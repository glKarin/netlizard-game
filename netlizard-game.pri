


DEFINES += _KARIN_APPBIN=\\\"netlizard-game\\\"
DEFINES += _KARIN_APPNAME=\\\"NETLizard-Game\\\"
DEFINES += _KARIN_RELEASE=\\\"2016\\\"
DEFINES += _KARIN_VERSION=\\\"0.8.0harmattan1\\\"
DEFINES += _KARIN_DEVELOPER=\\\"Karin\\\"
DEFINES += _KARIN_HOME=\\\".netlizard-game\\\"
DEFINES += _KARIN_DEVCODE=\\\"Natasha\\\"
DEFINES += _KARIN_EMAIL=\\\"beyondk2000@gmail.com\\\"

# compile OpenGL ES 1.1 version.
CONFIG += harmattan_opengles

# compile OpenGL ES 2.0 version.
#CONFIG += harmattan_opengles2

# compile OpenGL
#CONFIG += harmattan_opengl

harmattan_opengles {
LIBS += -lGLES_CM -lEGL
DEFINES += _HARMATTAN_OPENGLES
} else:harmattan_opengles2 {
LIBS += -lGLESv2 -lEGL
DEFINES += _HARMATTAN_OPENGLES2
} else {
PKGCONFIG += gl glu #iLmBase
DEFINES += _HARMATTAN_OPENGL
LIBS += -lGL -lGLU #-lIex
}

# compile multi touch version for MeeGo Harmattan by XInput2 extension.
DEFINES += _XI2_MULTI_TOUCH

# for local test
#CONFIG += install_release

install_release {
DEFINES += _KARIN_RESOURCE_DIR=\\\"/usr/share/netlizard-game/\\\"
DEFINES += _KARIN_GAME_DIR=\\\"/usr/share/netlizard-game/game/\\\"
} else {
DEFINES += _KARIN_RESOURCE_DIR=\\\"./\\\"
DEFINES += _KARIN_GAME_DIR=\\\"./\\\"
#DEFINES += _SPLASH_FILE=\\\"./netlizard-game_80.png\\\"
}

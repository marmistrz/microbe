TEMPLATE = app
QT += network sql opengl dbus gui
TARGET = microbe
CONFIG += link_pkgconfig

INSTALLS += target

SOURCES = $$files(src/*.cpp)
HEADERS = $$files(src/*.h)

#QTMOZEMBED
SOURCES += $$files(src/qtmozembed/*.cpp)
HEADERS += $$files(src/qtmozembed/*.h)

PKGCONFIG += QJson
LIBS +=-lX11

isEmpty(DEFAULT_COMPONENT_PATH) {
  DEFINES += DEFAULT_COMPONENTS_PATH=\"\\\"/usr/lib/mozembedlite/\\\"\"
} else {
  DEFINES += DEFAULT_COMPONENTS_PATH=\"\\\"$$DEFAULT_COMPONENT_PATH\\\"\"
}

DEFINES += Q_DEBUG_LOG

maemo5 {
#    QT += maemo5 dbus
#    CONFIG += mobility12
#    MOBILITY += multimedia
#    SOURCES += $$files(src/maemo5_gui/*.cpp)
#    HEADERS += $$files(src/maemo5_gui/*.h)
    #RESOURCES = src/maemo5_gui/resources.qrc

#    desktopfile.path = /usr/share/applications/hildon
#    desktopfile.files = desktop/maemo5/iplayer.desktop

#    icon.path = /usr/share/icons/hicolor/64x64/apps
#    icon.files = desktop/iplayer64.png

#    translations.files += $$files(src/maemo5_gui/translations/*.*)
#    translations.path += /opt/myPlayer/translations

#    dbus_service.files += dbus/com.maemo.myPlayer.service
#    dbus_service.path = /usr/share/dbus-1/services
#    dbus_interface.files += dbus/com.maemo.myPlayer.xml
#    dbus_interface.path = /usr/share/dbus-1/interfaces

    target.path = /opt/microbe/bin/

#    INSTALLS += translations desktopfile icon dbus_service dbus_interface
}

QMAKE_CXXFLAGS += -include mozilla-config.h
unix:QMAKE_CXXFLAGS += -fno-short-wchar -std=c++0x -fPIC
DEFINES += XPCOM_GLUE=1 XPCOM_GLUE_USE_NSPR=1 MOZ_GLUE_IN_PROGRAM=1

isEmpty(OBJ_PATH) {
  message(OBJ_PATH not defined)
  CONFIG += link_pkgconfig
  SDK_HOME=$$system(pkg-config --variable=sdkdir libxul-embedding)
  GECKO_LIB_DIR = $$SDK_HOME/lib
  GECKO_INCLUDE_DIR = $$SDK_HOME/include
  BIN_DIR=$$replace(SDK_HOME, -devel-, -)
  message($$BIN_DIR - binary dir)
} else {
  CONFIG += link_pkgconfig
  message(OBJ_PATH defined $$OBJ_PATH)
  GECKO_LIB_DIR = $$OBJ_PATH/dist/lib
  GECKO_INCLUDE_DIR = $$OBJ_PATH/dist/include
  BIN_DIR=$$OBJ_PATH/dist/bin
  message($$BIN_DIR - binary dir)
}

INCLUDEPATH += $$GECKO_INCLUDE_DIR $$GECKO_INCLUDE_DIR/nspr /usr/include/nspr4
LIBS += -L$$GECKO_LIB_DIR -lxpcomglue -Wl,--whole-archive -lmozglue
LIBS += -Wl,--no-whole-archive -rdynamic -ldl

DEFINES += BUILD_GRE_HOME=\"\\\"$$BIN_DIR\\\"\"

# Copy default mozilla flags to avoid some gcc warnings
*-g++*: QMAKE_CXXFLAGS += -Wno-attributes
*-g++*: QMAKE_CXXFLAGS += -Wno-ignored-qualifiers
*-g++*: QMAKE_CXXFLAGS += -pedantic
*-g++*: QMAKE_CXXFLAGS += -Wall
*-g++*: QMAKE_CXXFLAGS += -Wno-unused-parameter
*-g++*: QMAKE_CXXFLAGS += -Wpointer-arith
*-g++*: QMAKE_CXXFLAGS += -Woverloaded-virtual
*-g++*: QMAKE_CXXFLAGS += -Werror=return-type
*-g++*: QMAKE_CXXFLAGS += -Wtype-limits
*-g++*: QMAKE_CXXFLAGS += -Wempty-body
*-g++*: QMAKE_CXXFLAGS += -Wno-ctor-dtor-privacy
*-g++*: QMAKE_CXXFLAGS += -Wno-format
*-g++*: QMAKE_CXXFLAGS += -Wno-overlength-strings
*-g++*: QMAKE_CXXFLAGS += -Wno-invalid-offsetof
*-g++*: QMAKE_CXXFLAGS += -Wno-variadic-macros
*-g++*: QMAKE_CXXFLAGS += -Wno-long-long
*-g++*: QMAKE_CXXFLAGS += -Wno-psabi


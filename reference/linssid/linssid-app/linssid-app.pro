TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = linssid
VERSION = 2.9
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets svg
SOURCES += AboutBox.cpp Getter.cpp MainForm.cpp main.cpp passBox.cpp prefsDialog.cpp
HEADERS += AboutBox.h Custom.h Getter.h MainForm.h passBox.h prefsDialog.h
FORMS += AboutBox.ui MainForm.ui passBox.ui prefsDialog.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/include/boost
INCLUDEPATH += /usr/include/qt5
INCLUDEPATH += /usr/include/qwt
LIBS += -lboost_regex
LIBS += /usr/lib/libqwt-qt5.so.6
QMAKE_CXXFLAGS += -std=c++11
#
TARGET = linssid
target.path = /usr/bin
INSTALLS += target
dtop.path = /usr/share/applications
dtop.files = linssid.desktop
INSTALLS += dtop
icons.path = /usr/share/pixmaps
icons.files = *.png
INSTALLS += icons
data.path = /usr/share/linssid
data.files = oui.datb linssid-pause.png linssid-start.png
INSTALLS += data

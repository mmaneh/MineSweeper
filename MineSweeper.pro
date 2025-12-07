QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/appmanager.cpp \
    source/boardmodel.cpp \
    source/boardwidget.cpp \
    source/cellbutton.cpp \
    source/cellmodel.cpp \
    source/welcomewindow.cpp\
    source/mainwindow.cpp \
    source/statuspanel.cpp \
    source/main.cpp

# Headers
HEADERS += \
    headers/appmanager.h \
    headers/boardmodel.h \
    headers/boardwidget.h \
    headers/cellbutton.h \
    headers/cellmodel.h \
    headers/mainwindow.h \
    headers/statuspanel.h \
    headers/welcomewindow.h \
    source/appmanager.h \
    source/boardmodel.h \
    source/cellmodel.h


INCLUDEPATH += headers

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


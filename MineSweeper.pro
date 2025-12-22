QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# Sources
SOURCES += \
    source/appmanager.cpp \
    source/boardmodel.cpp \
    source/boardwidget.cpp \
    source/cellbutton.cpp \
    source/cellmodel.cpp \
    source/welcomewindow.cpp \
    source/mainwindow.cpp \
    source/statuspanel.cpp \
    source/main.cpp \
    source/gamecontroller.cpp

# Headers
HEADERS += \
    headers/gamecontroller.h \
    headers/appmanager.h \
    headers/boardmodel.h \
    headers/boardwidget.h \
    headers/cellbutton.h \
    headers/cellmodel.h \
    headers/gamestate.h \
    headers/mainwindow.h \
    headers/statuspanel.h \
    headers/welcomewindow.h

# Include paths
INCLUDEPATH += headers

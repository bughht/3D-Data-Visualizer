#QT *= xml opengl widgets gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11
#CONFIG += qt opengl warn_on thread rtti console embed_manifest_exe no_keywords

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app
TARGET   = 3D

HEADERS  = \
    mainwindow.h \
    mesh.h \
    model.h \
    pcd.h \
    pos3.h \
    viewer.h
SOURCES  = main.cpp \
    mainwindow.cpp \
    mesh.cpp \
    model.cpp \
    pcd.cpp \
    pos3.cpp \
    viewer.cpp


include( ../based.pri )

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc

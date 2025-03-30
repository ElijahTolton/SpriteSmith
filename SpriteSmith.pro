QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addframecommand.cpp \
    addlayercommand.cpp \
    frame.cpp \
    framemodel.cpp \
    frameview.cpp \
    layereditcommand.cpp \
    main.cpp \
    mainwindow.cpp \
    sizedialog.cpp \
    sprite.cpp \
    spriteeditor.cpp \
    layer.cpp \
    layermodel.cpp \
    tool.cpp

HEADERS += \
    addframecommand.h \
    addlayercommand.h \
    frame.h \
    framemodel.h \
    frameview.h \
    layerdelegate.h \
    layereditcommand.h \
    mainwindow.h \
    sizedialog.h \
    sprite.h \
    spriteeditor.h \
    layer.h \
    layermodel.h \
    tool.h \
    layerdelegate.h

FORMS += \
    mainwindow.ui \
    sizedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
     field \
     item \
     inventory \
     db

SOURCES += \
    db/database.cpp \
    field/gamefield.cpp \
    inventory/inventory.cpp \
    item/item.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    db/database.h \
    field/gamefield.h \
    inventory/inventory.h \
    item/item.h \
    mainwindow.h

FORMS += \
    field/gamefield.ui \
    mainwindow.ui

addFiles.sources = items_database.sqlite
addFiles.path = ./db
DEPLOYMENT += addFiles

TRANSLATIONS += \
    Test_redwood_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

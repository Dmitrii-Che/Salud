QT -= gui -=console

#!!! Обязательно добавить к .exe:
#sfml-graphics-2.dll
#sfml-system-2.dll
#sfml-window-2.dll
#!!!!!

greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets

CONFIG += c++14
CONFIG -= app_bundle
LIBS += -LC:/SFML-2.5.1-64/lib
#LIBS += -LC:/SFML-2.5.1-32/lib
CONFIG(release, debug|release): LIBS += -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += C:/SFML-2.5.1-64/include
DEPENDPATH += C:/SFML-2.5.1-64/include
#INCLUDEPATH += C:/SFML-2.5.1-32/include
#DEPENDPATH += C:/SFML-2.5.1-32/include

SOURCES += \
    basicelement.cpp \
    button.cpp \
    flash.cpp \
    light.cpp \
    main.cpp \
    message.cpp \
    salut.cpp \
    snow.cpp \
    snowflake.cpp

HEADERS += \
    basicelement.h \
    button.h \
    element.h \
    flash.h \
    light.h \
    message.h \
    salut.h \
    snow.h \
    snowflake.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

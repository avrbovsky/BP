QT -= gui

TEMPLATE = lib
DEFINES += HILDITCH_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hilditch.cpp

HEADERS += \
    Hilditch_global.h \
    hilditch.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/../../../../lib/ -lopencv_core
unix|win32: LIBS += -L$$PWD/../../../../lib/ -lopencv_imgproc
unix|win32: LIBS += -L$$PWD/../../../../lib/ -lopencv_imgcodecs
unix|win32: LIBS += -L$$PWD/../../../../lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../../../usr/include/opencv4
DEPENDPATH += $$PWD/../../../../usr/include/opencv4

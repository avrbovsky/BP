QT -= gui

TEMPLATE = lib
DEFINES += POSTPROCESSING_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    breaks.cpp \
    dots.cpp \
    helperClass.cpp \
    islands.cpp \
    postprocessing.cpp \
    spur.cpp

HEADERS += \
    Postprocessing_global.h \
    breaks.h \
    dots.h \
    helperClass.h \
    islands.h \
    postprocessing.h \
    spur.h

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

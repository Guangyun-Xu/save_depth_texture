TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    camera_utils.cpp

INCLUDEPATH+=/opt/PhotoneoPhoXiControl-1.2.14/API/include
INCLUDEPATH += /usr/local/include/opencv\
/usr/local/include/opencv2

LIBS+=/opt/PhotoneoPhoXiControl-1.2.14/API/lib/libPhoXi_API_gcc7.4.0_Debug.so.1.2.14\
/usr/local/lib/libopencv_*.so

HEADERS += \
    camera_utils.h

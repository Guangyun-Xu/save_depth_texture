TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH+=/opt/PhotoneoPhoXiControl-1.2.14/API/include
INCLUDEPATH += /usr/local/include/opencv\
/usr/local/include/opencv2\
/usr/local/include/pcl-1.9\
/usr/include/eigen3\
/usr/local/include/vtk-7.1

LIBS+=/usr/local/lib/libpcl_*.so\
-lboost_system\
-lrt\
/opt/PhotoneoPhoXiControl-1.2.14/API/lib/libPhoXi_API_gcc7.4.0_Debug.so.1.2.14\
/usr/local/lib/libvtk*.so\
/usr/local/lib/libopencv_*.so

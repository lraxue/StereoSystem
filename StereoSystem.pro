#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T21:10:07
#
#-------------------------------------------------
INCLUDEPATH += d:\opencv\build\include\
INCLUDEPATH += d:\opencv\build\include\opencv\
INCLUDEPATH += d:\opencv\build\include\opencv2\

CONFIG(debug,debug|release) {
LIBS += -Ld:\opencv\build\x64\vc12\lib \
    -lopencv_ml2410d \
    -lopencv_calib3d2410d \
    -lopencv_contrib2410d \
    -lopencv_core2410d \
    -lopencv_features2d2410d \
    -lopencv_flann2410d \
    -lopencv_gpu2410d \
    -lopencv_highgui2410d \
    -lopencv_imgproc2410d \
    -lopencv_legacy2410d \
    -lopencv_objdetect2410d \
    -lopencv_ts2410d \
    -lopencv_video2410d \
    -lopencv_nonfree2410d \
    -lopencv_ocl2410d \
    -lopencv_photo2410d \
    -lopencv_stitching2410d \
    -lopencv_superres2410d \
    -lopencv_videostab2410d
} else {
LIBS += -Ld:\opencv\build\x64\vc12\lib \
    -lopencv_objdetect2410 \
    -lopencv_ts2410 \
    -lopencv_video2410 \
    -lopencv_nonfree2410 \
    -lopencv_ocl2410 \
    -lopencv_photo2410 \
    -lopencv_stitching2410 \
    -lopencv_superres2410 \
    -lopencv_videostab2410 \
    -lopencv_calib3d2410 \
    -lopencv_contrib2410 \
    -lopencv_core2410 \
    -lopencv_features2d2410 \
    -lopencv_flann2410 \
    -lopencv_gpu2410 \
    -lopencv_highgui2410 \
    -lopencv_imgproc2410 \
    -lopencv_legacy2410 \
    -lopencv_ml2410
}

LIBS +=  -lglut32
LIBS += -LC:\glut

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StereoSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stereoview.cpp \
    stereoanalysis.cpp \
    pglwidget.cpp

HEADERS  += mainwindow.h \
    stereoview.h \
    stereoanalysis.h \
    pglwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    src.qrc

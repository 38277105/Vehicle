#-------------------------------------------------
#
# Project created by QtCreator 2016-08-18T13:25:15
#
#-------------------------------------------------

QT       += xml  core gui

CONFIG += uitools

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

TARGET = VehicleVideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
    ANTOfflineFileSDKAdapter.cpp \
    CommonFunc.cpp \
    CommonStruct.cpp \
    DllFunc.cpp \
    FramelessDialog.cpp \
    FullVideo.cpp \
    LanguageProcessor.cpp \
    logindialog.cpp \
    TipsBox.cpp \
    VehicleVideoPlayerPub.cpp \
    windowlisteditor.cpp \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_writer.cpp \
    Thread.cpp

HEADERS  += ANTOfflineFileSDKAdapter.h \
    CommonFunc.h \
    CommonStruct.h \
    DllFunc.h \
    FramelessDialog.h \
    FullVideo.h \
    LanguageProcessor.h \
    LoginDialog.h \
    TipsBox.h \
    VehicleVideoPlayerPub.h \
    windowlisteditor.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/json_batchallocator.h \
    json/json_tool.h \
    json/reader.h \
    json/value.h \
    json/writer.h \
    Thread.h

RESOURCES += \
    vehiclevideoplayer.qrc

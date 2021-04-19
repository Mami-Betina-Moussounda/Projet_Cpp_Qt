#-------------------------------------------------
#
# Project created by QtCreator 2020-08-17T14:41:27
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += network

TARGET = TempReceptor
TEMPLATE = app

#QT       += core gui

#TARGET = TempReceptor
#QT -= gui

#CONFIG += c++11 console
#CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    FirmWare/Application/ControllerWorker/Controller.cpp \
    FirmWare/Application/TcpIpServer/TcpIpServer.cpp \
    FirmWare/Application/ThpSupervisor/Thpsupervisor.cpp \
    FirmWare/MiddleWare/TempReceptor/TempReceptor.cpp \
    FirmWare/MiddleWare/TempReceptor/bme280_htp_sensor/bme280.c \
    FirmWare/MiddleWare/TempReceptor/bme280_htp_sensor/bme280_htp_sensor.cpp \
    main.cpp \

HEADERS += \
    Configurations/configuration.h \
    FirmWare/Application/ControllerWorker/iworker.h \
    FirmWare/Application/ControllerWorker/Controller.h \
    FirmWare/Application/TcpIpServer/TcpIpServer.h \
    FirmWare/Application/ThpSupervisor/Thpsupervisor.h \
    FirmWare/MiddleWare/TempReceptor/TempReceptor.h \
    FirmWare/MiddleWare/TempReceptor/bme280_htp_sensor/bme280.h \
    FirmWare/MiddleWare/TempReceptor/bme280_htp_sensor/bme280_defs.h \
    FirmWare/MiddleWare/TempReceptor/bme280_htp_sensor/bme280_htp_sensor.h \


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Tell Qt where to find the wiringPi library
# The wiringPi library is raspberry pi specific and allow us to use raspberry pi specific
# hardware such as I2C, SPI ...
unix:!macx: LIBS += -L/home/vincent/Documents/99_TOOLS/Qt5.12.3_Rpi3/sysroot/usr/lib/ -lwiringPi

INCLUDEPATH += /home/vincent/Documents/99_TOOLS/Qt5.12.3_Rpi3/sysroot/usr/include
DEPENDPATH += /home/vincent/Documents/99_TOOLS/Qt5.12.3_Rpi3/sysroot/usr/include


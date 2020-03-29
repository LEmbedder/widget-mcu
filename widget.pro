#-------------------------------------------------
#
# Project created by QtCreator 2019-08-28T21:40:13
#
#-------------------------------------------------

QT       += core gui sql serialport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets axcontainer
target.path = /app_qt5
INSTALLS += target

TARGET = widget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    navprogress.cpp \
    progressbar.cpp \
    formmain.cpp \
    formchannelsettings.cpp \
    formchannlesettings2.cpp \
    formargssettings.cpp \
    formargusetting.cpp \
    formsystemsetting.cpp \
    formtimesetting.cpp \
    formpasswordsetting.cpp \
    formcalibration.cpp \
    formextend.cpp \
    formviewdata.cpp \
    communicationtomcu.cpp \
    globalvariable.cpp \
    formvolumetest.cpp \
    formcalibrationtest.cpp \
    formprogress.cpp \
    formpassword.cpp

HEADERS  += widget.h \
    navprogress.h \
    progressbar.h \
    formmain.h \
    formchannelsettings.h \
    formchannlesettings2.h \
    formargssettings.h \
    formargusetting.h \
    formsystemsetting.h \
    formtimesetting.h \
    formpasswordsetting.h \
    formcalibration.h \
    formextend.h \
    formviewdata.h \
    communicationtomcu.h \
    config.h \
    globalvariable.h \
    sys_struct.h \
    formvolumetest.h \
    formcalibrationtest.h \
    formprogress.h \
    formpassword.h

FORMS    += widget.ui \
    formmain.ui \
    formchannelsettings.ui \
    formchannlesettings2.ui \
    formargssettings.ui \
    formargusetting.ui \
    formsystemsetting.ui \
    formtimesetting.ui \
    formpasswordsetting.ui \
    formcalibration.ui \
    formextend.ui \
    formviewdata.ui \
    formvolumetest.ui \
    formcalibrationtest.ui \
    formprogress.ui \
    formpassword.ui


RESOURCES += \
    image/image.qrc

DISTFILES += \
    image/factory.jpg \
    image/label.png

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    all_time.cpp \
    day.cpp \
    emotion.cpp \
    idate.cpp \
    main.cpp \
    mainwindow.cpp \
    month.cpp \
    myxml.cpp \
    week.cpp \
    year_class.cpp

HEADERS += \
    all_time.h \
    day.h \
    emotion.h \
    idate.h \
    mainwindow.h \
    month.h \
    myxml.h \
    week.h \
    year_class.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-ForM-Replacement_for_Desktop_Qt_6_1_0_MinGW_64_bit-Debug/calendar.xml

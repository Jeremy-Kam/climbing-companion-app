QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editrow.cpp \
    editwindow.cpp \
    main.cpp \
    climbingapp.cpp \
    rowdata.cpp \
    workoutdata.cpp \
    workoutrow.cpp

HEADERS += \
    climbingapp.h \
    editrow.h \
    editwindow.h \
    rowdata.h \
    workoutdata.h \
    workoutrow.h

FORMS += \
    climbingapp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

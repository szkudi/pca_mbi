SOURCES += main.cpp \
    dataimport.cpp \
    controller.cpp \
    mainwindow.cpp \
    settings.cpp \
    micromatrixpca.cpp \
    parameters.cpp \
    badfile.cpp \
    pcaresultwindow.cpp \
    aboutwindow.cpp \
    importeddatamodel.cpp

HEADERS += \
    dataimport.h \
    controller.h \
    mainwindow.h \
    settings.h \
    micromatrixpca.h \
    parameters.h \
    badfile.h \
    pcaresultwindow.h \
    aboutwindow.h \
    importeddatamodel.h

FORMS += \
    mainwindow.ui \
    parameters.ui \
    pcaresultwindow.ui \
    aboutwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    QMAKE_CXXFLAGS += -Werror
}

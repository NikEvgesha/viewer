# TEMPLATE = app
CONFIG += console c++20
# CONFIG -= app_bundle
# CONFIG -= qt

QT += widgets

include(3rdparty/qtgifimage/qtgifimage.pri)

INCLUDEPATH += $$PWD/back
INCLUDEPATH += $$PWD/front

SOURCES += \
        3rdParty/gifimage/doc/snippets/doc_src_qtgifimage.cpp \
        3rdParty/gifimage/qgifimage.cpp \
        3rdParty/giflib/dgif_lib.c \
        3rdParty/giflib/egif_lib.c \
        3rdParty/giflib/gif_err.c \
        3rdParty/giflib/gif_font.c \
        3rdParty/giflib/gif_hash.c \
        3rdParty/giflib/gifalloc.c \
        3rdParty/giflib/quantize.c \
        back/s21_model.cpp \
        back/s21_objparser.cpp \
        front/s21_desktop.cpp \
        front/s21_panelinformation.cpp \
        front/s21_toolbar.cpp \
        front/s21_transformation.cpp \
        front/s21_viewer.cpp \
        s21_main.cpp

HEADERS += \
    3rdParty/gifimage/qgifglobal.h \
    3rdParty/gifimage/qgifimage.h \
    3rdParty/gifimage/qgifimage_p.h \
    3rdParty/giflib/gif_hash.h \
    3rdParty/giflib/gif_lib.h \
    3rdParty/giflib/gif_lib_private.h \
    back/s21_model.h \
    back/s21_objparser.h \
    front/s21_desktop.h \
    front/s21_panelinformation.h \
    front/s21_toolbar.h \
    front/s21_transformation.h \
    front/s21_viewer.h

RESOURCES += \
    resources.qrc

SUBDIRS += \
    3rdParty/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    3rdParty/gifimage/gifimage.pro

DISTFILES += \
    3rdParty/gifimage/doc/qtgifimage.qdocconf \
    3rdParty/gifimage/doc/src/examples.qdoc \
    3rdParty/gifimage/doc/src/index.qdoc \
    3rdParty/gifimage/doc/src/qtgifimage.qdoc \
    3rdParty/gifimage/doc/src/usage.qdoc \
    3rdParty/gifimage/qtgifimage.pri \
    3rdParty/giflib.pri \
    3rdParty/giflib/AUTHORS \
    3rdParty/giflib/COPYING \
    3rdParty/giflib/README

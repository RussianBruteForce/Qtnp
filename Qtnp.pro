#-------------------------------------------------
#
# Project created by QtCreator 2012-12-22T21:00:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtnp
TEMPLATE = app


SOURCES += main.cpp\
        Qtnp.cpp \
    DigitalClock.cpp \
    DrawCore.cpp \
    fparser/muparser/muParserTokenReader.cpp \
    fparser/muparser/muParserTest.cpp \
    fparser/muparser/muParserInt.cpp \
    fparser/muparser/muParserError.cpp \
    fparser/muparser/muParserDLL.cpp \
    fparser/muparser/muParserCallback.cpp \
    fparser/muparser/muParserBytecode.cpp \
    fparser/muparser/muParserBase.cpp \
    fparser/muparser/muParser.cpp \
    fparser/fparser.cpp \
    ColorWidget.cpp \
    GCPWidget.cpp \
    DrawGCPDialog.cpp \
    Settings.cpp \
    NewFileDialog.cpp \
    DrawGraphicDialog.cpp \
    SettingsDialog.cpp

HEADERS  += Qtnp.h \
    DigitalClock.h \
    DrawCore.h \
    DrawTools.h \
    fparser/fparser.h \
    fparser/muparser/muParserTokenReader.h \
    fparser/muparser/muParserToken.h \
    fparser/muparser/muParserTest.h \
    fparser/muparser/muParserTemplateMagic.h \
    fparser/muparser/muParserStack.h \
    fparser/muparser/muParserInt.h \
    fparser/muparser/muParserFixes.h \
    fparser/muparser/muParserError.h \
    fparser/muparser/muParserDLL.h \
    fparser/muparser/muParserDef.h \
    fparser/muparser/muParserCallback.h \
    fparser/muparser/muParserBytecode.h \
    fparser/muparser/muParserBase.h \
    fparser/muparser/muParser.h \
    ColorWidget.h \
    GCPWidget.h \
    DrawGCPDialog.h \
    Settings.h \
    NewFileDialog.h \
    DrawGraphicDialog.h \
    SettingsDialog.h

FORMS    += Qtnp.ui \
    GCPWidget.ui \
    DrawGCPDialog.ui \
    NewFileDialog.ui \
    DrawGraphicDialog.ui \
    SettingsDialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS += \
    ru_RU.ts

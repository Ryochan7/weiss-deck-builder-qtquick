TEMPLATE = app

QT += qml quick widgets sql

SOURCES += main.cpp \
    weisscardmodel.cpp \
    weisscard.cpp \
    weisscardfullmodel.cpp \
    weissdeck.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    weisscardmodel.h \
    weisscard.h \
    weisscardfullmodel.h \
    weissdeck.h


copydata.commands = $$QMAKE_COPY -u $$PWD/CardData.sqlite $$OUT_PWD/CardData.sqlite
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

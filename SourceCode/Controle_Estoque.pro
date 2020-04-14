include(QtXlsx/src/xlsx/qtxlsx.pri)
QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS XLSX_NO_LIB

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fm_edit_produtovenda.cpp \
    fm_gcolab.cpp \
    fm_gestoque.cpp \
    fm_gvendas.cpp \
    fm_login.cpp \
    fm_venda.cpp \
    global_functions.cpp \
    main.cpp \
    fm_main.cpp

HEADERS += \
    Conexao.h \
    Global_variables.h \
    fm_edit_produtovenda.h \
    fm_gcolab.h \
    fm_gestoque.h \
    fm_gvendas.h \
    fm_login.h \
    fm_main.h \
    fm_venda.h \
    global_functions.h

FORMS += \
    fm_edit_produtovenda.ui \
    fm_gcolab.ui \
    fm_gestoque.ui \
    fm_gvendas.ui \
    fm_login.ui \
    fm_main.ui \
    fm_venda.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource_file.qrc

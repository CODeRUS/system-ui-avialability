TEMPLATE      = lib
QT += core dbus
CONFIG       += plugin gui meegotouch link_pkgconfig
PKGCONFIG += gq-gconf \
	     accounts-qt

LIBS += -ltelepathy-qt4

INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/telepathy-1.0
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/accounts-qt
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/meegotouch
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/system-ui/statusindicatormenu

TARGET        = statusindicatormenu-avialability
target.path = /usr/lib/meegotouch/applicationextensions

INSTALLS += target

HEADERS += \
    MAvialability.h \
    MAvialabilityWidget.h \
    MAExtensionController.h \
    MAExtensionPlugin.h

SOURCES += \
    MAvialability.cpp \
    MAvialabilityWidget.cpp \
    MAExtensionController.cpp \
    MAExtensionPlugin.cpp

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/prerm \
    qtc_packaging/debian_harmattan/preinst \
    qtc_packaging/debian_harmattan/postrm \
    qtc_packaging/debian_harmattan/postinst

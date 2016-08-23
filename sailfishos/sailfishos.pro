# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-gibrievida

CONFIG += sailfishapp
CONFIG += c++11

QT += sql network multimedia sensors positioning

contributors.path = /usr/share/harbour-gibrievida/icons/contributors
contributors.files = images/contributors/*.png
INSTALLS += contributors

soundfiles.path = /usr/share/harbour-gibrievida/sounds
soundfiles.files = ../common/sounds/*
INSTALLS += soundfiles

langfiles.path = /usr/share/harbour-gibrievida/l10n
langfiles.files = ../l10n/*.qm
INSTALLS += langfiles

include(../common/common.pri)

SOURCES += \
    src/main.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

DISTFILES += \
    qml/harbour-gibrievida.qml \
    harbour-gibrievida.desktop \
    rpm/harbour-gibrievida.changes.in \
    rpm/harbour-gibrievida.yaml \
    qml/pages/MainPage.qml \
    qml/common/ImageHighlight.qml \
    qml/dialogs/CategoryDialog.qml \
    qml/pages/Categories.qml \
    qml/pages/Activities.qml \
    qml/dialogs/ActivityDialog.qml \
    qml/pages/Records.qml \
    qml/dialogs/RecordDialog.qml \
    qml/pages/Record.qml \
    qml/common/IconSectionHeader.qml \
    qml/common/DateTimeButton.qml \
    qml/common/DurationButton.qml \
    qml/pages/Settings.qml \
    qml/btcomponents/AboutPage.qml \
    qml/btcomponents/Changelog.qml \
    qml/btcomponents/ChangelogDelegate.qml \
    qml/btcomponents/Contributors.qml \
    qml/btcomponents/ContributorsDelegate.qml \
    qml/pages/About.qml \
    qml/pages/ContributorsModel.qml \
    qml/pages/ChangelogModel.qml \
    qml/pages/AttachedFilters.qml \
    qml/pages/Help.qml


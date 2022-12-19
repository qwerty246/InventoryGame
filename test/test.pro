greaterThan(QT_MAJOR_VERSION, 4)

QT += widgets core gui sql multimedia

TARGET = inventory
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

HEADERS  += \
    headers/database/DatabaseManager.h \
    headers/database/SqlQueryManager.h \
    \
    headers/inventory/InventoryTable.h \
    headers/inventory/InventoryView.h \
    \
    headers/item/AppleImage.h \
    headers/item/AppleLabel.h \
    headers/item/ItemDelegate.h \
    headers/item/ItemMimeData.h \
    \
    headers/window/MainMenu.h \
    headers/window/Window.h

SOURCES += \
    src/main.cpp \
    \
    src/database/DatabaseManager.cpp \
    src/database/SqlQueryManager.cpp \
    \
    src/inventory/InventoryTable.cpp \
    src/inventory/InventoryView.cpp \
    \
    src/item/AppleImage.cpp \
    src/item/AppleLabel.cpp \
    src/item/ItemDelegate.cpp \
    src/item/ItemMimeData.cpp \
    \
    src/window/MainMenu.cpp \
    src/window/Window.cpp

RESOURCES += \
    resource.qrc

INCLUDEPATH += headers

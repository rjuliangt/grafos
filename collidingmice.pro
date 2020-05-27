QT += widgets

HEADERS += \
    people.h
SOURCES += \
	main.cpp \
	people.cpp

RESOURCES += \
	mice.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/collidingmice
INSTALLS += target

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static

SOURCES += main.cpp \
    config.cpp \
    gameloop.cpp \
    memory.cpp \
    tileset.cpp \
    tilesetconfigs.cpp

# OH YEAH!
QMAKE_CXXFLAGS += -std='c++11'

HEADERS += \
    assertions.hpp \
    config.hpp \
    common.hpp \
    gameloop.hpp \
    memory.hpp \
    tileset.hpp \
    tilesetconfigs.hpp

# Libraries!

# Windows Libraries
# Linking against supplied precompiled binaries because building
# libraries on Windows is a hassle :(
# Allegro:
win32: LIBS += -L$$PWD/../Allegro/mingw32/lib/ -lallegro-static
# Allegro Addons:
win32: LIBS += -lallegro_acodec-static
win32: LIBS += -lallegro_audio-static
win32: LIBS += -lallegro_color-static
win32: LIBS += -lallegro_dialog-static
win32: LIBS += -lallegro_font-static
win32: LIBS += -lallegro_image-static
win32: LIBS += -lallegro_main-static
win32: LIBS += -lallegro_memfile-static
win32: LIBS += -lallegro_physfs-static
win32: LIBS += -lallegro_primitives-static
win32: LIBS += -lallegro_ttf-static
win32: LIBS += -lallegro_video-static
# Allegro dependencies
win32: LIBS += -ldumb
win32: LIBS += -lFLAC
win32: LIBS += -lfreetype
win32: LIBS += -logg
win32: LIBS += -lphysfs
win32: LIBS += -ltheora
win32: LIBS += -lvorbis
win32: LIBS += -lvorbisfile
# Static linking dependencies
win32: LIBS += -lgdiplus
win32: LIBS += -luuid
win32: LIBS += -lkernel32
win32: LIBS += -lwinmm
win32: LIBS += -lpsapi
win32: LIBS += -lopengl32
win32: LIBS += -lglu32
win32: LIBS += -luser32
win32: LIBS += -lcomdlg32
win32: LIBS += -lgdi32
win32: LIBS += -lshell32
win32: LIBS += -lole32
win32: LIBS += -ladvapi32
win32: LIBS += -lws2_32
win32: LIBS += -lshlwapi
# Add Allegro to include path in windows
win32: INCLUDEPATH += $$PWD/../Allegro/mingw32/include
win32: DEPENDPATH += $$PWD/../Allegro/mingw32/include

# On Linux it is easy and fun to compile libraries, yay!
# Just link directly against them
# Allegro (built into a single monolithic binary, joy!)
unix:!macx: LIBS += -lallegro_monolith-static
# Allegro's dependencies
unix:!macx: LIBS += -lXcursor
unix:!macx: LIBS += -lX11
unix:!macx: LIBS += -lpthread
unix:!macx: LIBS += -lGL

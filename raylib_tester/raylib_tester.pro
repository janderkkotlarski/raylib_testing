CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17


# RAYLIB_PATH = C:\raylib
# High warnings levels
# -Werror
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Weffc++
QMAKE_CXXFLAGS += -static-libgcc -static-libstdc++




# Allow debug and release mode
CONFIG += debug_and_release

CONFIG += staticlib

# In release mode, turn on profiling
CONFIG(release, debug|release) {

  DEFINES += NDEBUG

# gprof
  QMAKE_CXXFLAGS += -pg
  QMAKE_LFLAGS += -pg
}

INCLUDEPATH += C:/raylib/raylib/src/externa/glfw
INCLUDEPATH += C:/raylib/raylib/src
INCLUDEPATH += C:/raylib/MinGW/bin
INCLUDEPATH += C:/raylib/raylib
INCLUDEPATH += C:/raylib

LIBS += -LC:/raylib/raylib/src/externa/glfw
LIBS += -LC:/raylib/raylib/src
LIBS += -LC:/raylib/MinGW/bin
LIBS += -LC:/raylib/raylib
LIBS += -LC:/raylib

LIBS += -lraylib -Iexternal -lopengl32 -lgdi32 -lwinmm
LIBS += -static -lpthread
#  -lglfw3 -lopenal32

SOURCES += \
        core_basic_window.cpp \
        main.cpp

HEADERS += \
  core_basic_window.h

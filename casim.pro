QT += core gui widgets opengl openglwidgets
TEMPLATE = app 
TARGET = casim
INCLUDEPATH += \
        . \
        ./src \
        ./third_party

#CONFIG += console

HEADERS += \
    src/core/automaton.hpp\
    src/core/common.hpp \
    src/core/utils.hpp \
    src/gui/common.hpp \
    src/gui/file_tree.hpp \
    src/gui/script_editor.hpp \
    src/gui/config_editor.hpp \
    src/gui/tool_bar.hpp \
    src/gui/viewer.hpp \
    src/gui/main_window.hpp \
    src/gui/logger.hpp \
    src/gui/viewer_config.hpp \
    src/gui/pattern_config.hpp \
    third_party/lua/lapi.h \
    third_party/lua/lauxlib.h \
    third_party/lua/lcode.h \
    third_party/lua/lctype.h \
    third_party/lua/ldebug.h \
    third_party/lua/ldo.h \
    third_party/lua/lfunc.h \
    third_party/lua/lgc.h \
    third_party/lua/ljumptab.h \
    third_party/lua/llex.h \
    third_party/lua/llimits.h \
    third_party/lua/lmem.h \
    third_party/lua/lobject.h \
    third_party/lua/lopcodes.h \
    third_party/lua/lopnames.h \
    third_party/lua/lparser.h \
    third_party/lua/lprefix.h \
    third_party/lua/lstate.h \
    third_party/lua/lstring.h \
    third_party/lua/ltable.h \
    third_party/lua/ltm.h \
    third_party/lua/lua.h \
    third_party/lua/lua.hpp \
    third_party/lua/luaconf.h \
    third_party/lua/lualib.h \
    third_party/lua/lundump.h \
    third_party/lua/lvm.h \
    third_party/lua/lzio.h
SOURCES += \
    src/core/automaton.cpp \
    src/core/utils.cpp \
    src/gui/file_tree.cpp \
    src/gui/main.cpp \
    src/gui/script_editor.cpp \
    src/gui/config_editor.cpp \
    src/gui/tool_bar.cpp \
    src/gui/viewer.cpp \
    src/gui/logger.cpp \
    src/gui/main_window.cpp \
    src/gui/viewer_config.cpp \
    src/gui/pattern_config.cpp \
    third_party/lua/lapi.c \
    third_party/lua/lauxlib.c \
    third_party/lua/lbaselib.c \
    third_party/lua/lcode.c \
    third_party/lua/lcorolib.c \
    third_party/lua/lctype.c \
    third_party/lua/ldblib.c \
    third_party/lua/ldebug.c \
    third_party/lua/ldo.c \
    third_party/lua/ldump.c \
    third_party/lua/lfunc.c \
    third_party/lua/lgc.c \
    third_party/lua/linit.c \
    third_party/lua/liolib.c \
    third_party/lua/llex.c \
    third_party/lua/lmathlib.c \
    third_party/lua/lmem.c \
    third_party/lua/loadlib.c \
    third_party/lua/lobject.c \
    third_party/lua/lopcodes.c \
    third_party/lua/loslib.c \
    third_party/lua/lparser.c \
    third_party/lua/lstate.c \
    third_party/lua/lstring.c \
    third_party/lua/lstrlib.c \
    third_party/lua/ltable.c \
    third_party/lua/ltablib.c \
    third_party/lua/ltm.c \
    third_party/lua/lundump.c \
    third_party/lua/lutf8lib.c \
    third_party/lua/lvm.c \
    third_party/lua/lzio.c

RESOURCES += \
    casim.qrc

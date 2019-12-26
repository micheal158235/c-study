CC := $(platform)-gcc
CPP := $(platform)-g++
C11 :=
SOURCE_DIR := .
INCLUDEFLAGS := -I../../../toolsLib/json
CFLAGS := -fpermissive $(C11)
DBGFLAG := -g   #调试模式

ifeq ("$(platform)", "i686-pc-mingw32") #注意：ifeq后要有空格
LFLAGS := -L../../../target/lib -lliblog4cpp
LLFLAGS := $(LFLAGS)
else
LFLAGS := -L../../../target/lib/ -ljson
LLFLAGS := $(LFLAGS) -shared -fpic
endif

TARGET := ../../../target/lib/libstudy_makefile.so
include ThatMakefile

ifeq ("$(platform)", "arm-hisiv400-linux")
all:
	cp $(TARGET) $(QX_INSTALL_DIR_LIB)
endif

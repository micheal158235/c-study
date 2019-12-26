#安装目录
export platform = i686-pc-mingw32
export QX_INSTALL_DIR = $(PWD)/../../target
export QX_INSTALL_DIR_LIB = $(QX_INSTALL_DIR)/lib
export QX_INSTALL_DIR_BIN = $(QX_INSTALL_DIR)/bin

OBJS = ./study_makefile/libstudy_makefile.so
$(OBJS):
	make -C $(dir $@)
.PHONY: clean
clean:
	make -C ./study_makefile clean

#all:
#	@cd ./study_makefile; make
#	@cd ..
#
#clean:
#	@cd ./study_makefile; make clean
#	@cd ..

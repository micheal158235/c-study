#安装目录
export platform = i686-pc-mingw32
export QX_INSTALL_DIR = $(PWD)/../../target
export QX_INSTALL_DIR_LIB = $(QX_INSTALL_DIR)/lib
export QX_INSTALL_DIR_BIN = $(QX_INSTALL_DIR)/bin

all:
	@cd ./testgcc; make
	@cd ..

clean:
	@cd ./testgcc; make clean
	@cd ..

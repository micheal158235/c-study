platform = i686-pc-mingw32
CC = gcc
CPP = g++
#gcc -w的意思是关闭编译时的警告，也就是编译后不显示任何warning，因为有时在编译之后编译器会显示一些例如数据转换之类的警告，这些警告是我们平时可以忽略的。
#gcc -Wall选项意思是编译后显示所有警告。
#gcc -W选项类似-Wall，会显示警告，但是只显示编译器认为会出现错误的警告。在编译一些项目的时候可以-W和-Wall选项一起使用。
CFLAGS = -Wall -g
#用法是$(subst FROM,TO,TEXT),即将TEXT中的东西从FROM变为TO 注意:不要写成:$(subst ,/,\,$(PWD))
#例如$(subst /,\,c:/user/)得到的结果是c:/user/
SOURCE_DIR := $(subst /,\,$(PWD)) 
TARGET = $(PWD)/iomanipStudy
#包含wchar2char与path1等目录,添加的头文件会去这几个目录下找
VPATH = wchar2char:path1
#vpath % wchar2char
#vpath %.c wchar2char
DOTSO := .so
DOTA := .a
CPPSRCS    := $(wildcard *.cpp)
CPPOBJS    := $(CPPSRCS:%.cpp=%.o)
CPPDEPS    := $(CPPSRCS:%.cpp=%.d)

#注意：ifeq后要有空格
ifeq ("$(platform)", "i686-pc-mingw32")
#LFLAGS := -L../../../target/lib -lliblog4cpp
LFLAGS :=
LLFLAGS := $(LFLAGS)
else
#LFLAGS := -L../../../target/lib/ -lliblog4cpp
LFLAGS :=
#
LLFLAGS := $(LFLAGS) -shared -fpic
endif

$(TARGET):$(CPPOBJS)
ifeq "$(findstring $(DOTSO), $(TARGET))" "$(DOTSO)"
	$(CPP) $(CPPOBJS) -o $(TARGET) $(LLFLAGS)
else
ifeq "$(findstring $(DOTA), $(TARGET))" "$(DOTA)"
	-$(AR) rcs $(TARGET) $(CPPOBJS)
else
	$(CPP) $(CPPOBJS) -o $(TARGET) $(LFLAGS)
endif
endif

$(CPPOBJS):%.o:%.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

#自动生成各CPP的依赖关系如：main.o main.d : main.c defs.h
#在Windows平台下不能用$(PWD)/$@.$$$$,因为windows平台下会得到类似如下结果：$(PWD)/$@.$$$$ =  C:\Users\wchar2char/wchar2char.d.$$
$(CPPDEPS):%.d:%.cpp
	set -e; rm -f $@; $(CC) -MM $< > $@.$$$$; sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -Rf $@.$$$$ 

#windows下这种换行的方式兼容的不好，make编译不过
#$(CPPDEPS):%.d:%.cpp
#	set -e; rm -f $@; $(CC) -MM $< > $@.$$$$ \
#	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ \
#	rm -Rf $@.$$$$ 

-include $(CPPOBJS:.o=.d)

#*sed echo $(SOURCE_DIR);rm -Rf *.o *.d;
.PHONY:clean
clean:
	rm -Rf *.o *.d
	

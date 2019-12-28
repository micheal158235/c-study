platform = i686-pc-mingw32
CC = gcc
CPP = g++
CFLAGS = -Wall -g
SOURCE_DIR := $(subst /,\,$(PWD)) #注意：不要写成:$(subst ,/,\,$(PWD))
TARGET = $(PWD)/wchar2char
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
	

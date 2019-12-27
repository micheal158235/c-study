CC = gcc
CPP = g++
CFLAGS = -Wall -g
TARGET = $(PWD)/wchar2char
#VPATH = wchar2char:path1
#vpath % wchar2char
#vpath %.c wchar2char

CPPSRCS    := $(wildcard *.cpp)
CPPOBJS    := $(CPPSRCS:%.cpp=%.o)
CPPDEPS    := $(CPPSRCS:%.cpp=%.d)
CPPDEPS    := $(CPPSRCS:%.cpp=%.d)

$(TARGET):$(OBJS)
	$(CPP) -o $(TARGET) $^ $(CFLAGS)
	
$(CPPOBJS):%.o:%.cpp
	$(CPP) -o $@ -c $< $(CFLAGS) $(INCLUDEFLAGS)

#自动生成各CPP的依赖关系如：main.o main.d : main.c defs.h
$(CPPDEPS):%.d:%.cpp
	@set -e; rm -f $@; $(CC) -MM $< $(INCLUDEFLAGS) > $@.$$$$ \
	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
-include $(CPPOBJS:.o=.d)


.PHONY:clean
clean:
	rm -Rf *.o
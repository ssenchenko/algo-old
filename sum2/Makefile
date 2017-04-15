# makefile for small tasks

# c compiler
CC = clang

# c++ compiler
CPP = -x c++

# standard to use
#STD = -std=c11
STD = -std=c++14 -stdlib=libc++

# c++ library for osx and freebsd
CPPLIB = -lc++

# other flags
# -ggdb3
CFLAGS = -glldb -O0 -Qunused-arguments -Wall -Werror -Wno-c++11-extensions

# include
INCLUDE = -I ../utils

# space-separated list of header files
HDRS = ../utils/myutil.h

# space-separated list of source files
SRCS = ../utils/myutil.cpp

# other libs to include
# each of which should be prefixed with -l
LIBS =

# target executable
TARGET = sum2
APP = ./obj/sum2

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS) $(HDRS) Makefile
	$(CC) $(CPP) $(STD) $(CFLAGS) $(CPPLIB) $(INCLUDE) -o $(APP) $(OBJS) $(TARGET).cpp $(LIBS) 

# dependencies 
$(OBJS): $(HDRS) Makefile

.PHONY: clean
clean:
	rm -fR ./obj/*.o ./obj/*dSYM $(APP)
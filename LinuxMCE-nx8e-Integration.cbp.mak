#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.135                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC =  -Iinclude -Isrc -I\$\(\#boost.include\)
CFLAGS =  -Wall -fexceptions
RESINC = 
LIBDIR =  -L\$\(\#boost.lib\)
LIB =  -lboost_system -lpthread
LDFLAGS = 

INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -g
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG =  $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/LinuxMCE-nx8e-Integration

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE =  $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/LinuxMCE-nx8e-Integration

OBJ_DEBUG = $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/src/Nx8eInterface.o $(OBJDIR_DEBUG)/src/writelog.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/src/Nx8eInterface.o $(OBJDIR_RELEASE)/src/writelog.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src

after_debug: 

debug: before_debug out_debug after_debug

out_debug: $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

$(OBJDIR_DEBUG)/main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/src/Nx8eInterface.o: src/Nx8eInterface.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/Nx8eInterface.cpp -o $(OBJDIR_DEBUG)/src/Nx8eInterface.o

$(OBJDIR_DEBUG)/src/writelog.o: src/writelog.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/writelog.cpp -o $(OBJDIR_DEBUG)/src/writelog.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)/src

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src

after_release: 

release: before_release out_release after_release

out_release: $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/src/Nx8eInterface.o: src/Nx8eInterface.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/Nx8eInterface.cpp -o $(OBJDIR_RELEASE)/src/Nx8eInterface.o

$(OBJDIR_RELEASE)/src/writelog.o: src/writelog.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/writelog.cpp -o $(OBJDIR_RELEASE)/src/writelog.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)/src

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release


LIBNAME = cupid

SRC_DIR = src
LIB_DIR = lib

INCLUDE = -I./include

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
SOURCES_C = $(wildcard $(SRC_DIR)/*.c)
OBJS_C = $(patsubst %.c,%.o,$(SOURCES_C))

COMMON_DEFINES = -DLINUX -D_REENTERANT

DEFINES=$(COMMON_DEFINES)
CXXFLAGS= -fPIC -g -Wall -W -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 $(DEFINES) $(INCLUDE) 

CXX = g++
CXX_C = gcc
AR  = ar

OUTPUT_LIB=lib$(LIBNAME).a

#-----------------------------------------------------------------#
# make all
#-----------------------------------------------------------------#
all: clean output

#-----------------------------------------------------------------#
# make library
#-----------------------------------------------------------------#
output: $(OBJS) $(OBJS_C)
	if [ ! -d $(LIB_DIR) ]; then mkdir $(LIB_DIR); fi
	ar -ruv $(LIB_DIR)/$(OUTPUT_LIB) $(OBJS) $(OBJS_C)

$(OBJS): %.o: %.cpp
	$(CXX) -c $< -o $@ $(INCLUDE) $(LIB) $(CXXFLAGS)
	
$(OBJS_C): %.o: %.c
	$(CXX_C) -c $< -o $@ $(INCLUDE) $(LIB) $(CXXFLAGS)

#-----------------------------------------------------------------#
# make clean
#-----------------------------------------------------------------#
clean:
	rm -f $(OBJS) $(OBJS_C) $(LIB_DIR)/$(OUTPUT_LIB)

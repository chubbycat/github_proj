CXX = g++

CXXFLAGS =	-O -g -Wall -Wno-write-strings -fmessage-length=0 

LIBS = -L../lib -lcupid -pthread

#TODO
INCLUDE := -I../include
SOURCE := $(wildcard ./*.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SOURCE))

TARGET = $(shell ls *.cpp | awk -F. '{print $$1}')

all:	$(TARGET)
%: %.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^ $(LIBS) 

$(OBJS): %.o:%.cpp	
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

clean:	
	rm -rf $(OBJS) $(TARGET) 


TARGET=cache_sample
LIBSRCS = $(wildcard *.cpp)
LIBOBJS = $(LIBSRCS:.cpp=.o)

DEPENDS = ${OBJECTS:.o=.d}

WARNING= -w

CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11

all:$(TARGET)
$(TARGET): $(LIBOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(LIBOBJS) 

-include ${DEPENDS}

.PHONY: clean
clean: 
	rm $(LIBOBJS) $(TARGET)
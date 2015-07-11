.PHONY: all clean

CXXFLAGS=-O2 -std=c++0x
LINK_FLAGS=-lglut -lGL -lGLU -lm -lIL -lILU -lGLEW
CXX=g++

all: main

%:%.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LINK_FLAGS) 

clean:
	rm main

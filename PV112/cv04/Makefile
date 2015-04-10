.PHONY: all clean

CXXFLAGS=-O2 -lm
LINK_FLAGS=-lglut -lGL -lGLU -lIL -lILU
CXX=g++

all: main

%:%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) $(LINK_FLAGS) 

clean:
	rm main

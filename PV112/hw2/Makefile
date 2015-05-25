.PHONY: all clean

CXXFLAGS=-O2
LINK_FLAGS=-lglut -lGL -lGLU -lm -lIL -lILU
CXX=g++

all: hw2

%.o:%.cpp
	$(CXX) -c $< $(CXXFLAGS)

hw2: hw2.o ObjLoader.o
	$(CXX) -o $@ $^ $(LINK_FLAGS)

clean:
	rm hw2 *.o

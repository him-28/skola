.PHONY: all clean

CXXFLAGS=-O2
LINK_FLAGS=-lglut -lGL -lGLU -lm
CXX=g++

all: hw1

%.o:%.cpp
	$(CXX) -c $< $(CXXFLAGS)

hw1: hw1.o ObjLoader.o
	$(CXX) -o $@ hw1.o ObjLoader.o $(LINK_FLAGS)

clean:
	rm hw1 *.o

# Makefile for Queue tests
PROGRAM_SRC_DIR = ../src
CXX = g++
all: my_tunes_search.o
	g++ -g -std=c++11 $^ tests.cpp -I ../src -o runtests

my_tunes_search.o: $(PROGRAM_SRC_DIR)/artist.cpp $(PROGRAM_SRC_DIR)/artist.hpp
	g++ -g -std=c++11 -c $(PROGRAM_SRC_DIR)/artist.cpp -I $(PROGRAM_SRC_DIR)/ -o $@

clean:
	rm -rf *~ runtests

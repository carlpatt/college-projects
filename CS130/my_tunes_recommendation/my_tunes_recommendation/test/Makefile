# Makefile for Recommendation tests
PROGRAM_SRC_DIR = ../src
CXX = g++
all: my_tunes_recommendation.o
	g++ -g -std=c++11 $^ tests.cpp -I ../src -o runtests

my_tunes_recommendation.o: $(PROGRAM_SRC_DIR)/graph.hpp $(PROGRAM_SRC_DIR)/graph.cpp
	g++ -std=c++11 -c $(PROGRAM_SRC_DIR)/graph.cpp -I $(PROGRAM_SRC_DIR)/ -o $@

clean:
	rm -rf *~ runtests

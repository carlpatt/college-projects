# Makefile for Queue tests
PROGRAM_SRC_DIR = ../src
CXX = g++
all: my_tunes_queue.o
	g++ -std=c++11 $^ tests.cpp -I ../src -o runtests

my_tunes_queue.o: $(PROGRAM_SRC_DIR)/queue.hpp $(PROGRAM_SRC_DIR)/queue.cpp
	g++ -std=c++11 -c $(PROGRAM_SRC_DIR)/queue.cpp -I $(PROGRAM_SRC_DIR)/ -o $@

clean:
	rm -rf *~ runtests

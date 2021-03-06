# File:   Makefile
# Author: robertomaldonado
# Created on January 22, 2019
#Define Compiler:
CC=g++ -std=c++11
CFLAG=-g -Wall
#Define the processes:
all: compile_all

compile_all: 
	$(CC) $(CFLAG) -o hypercubeRouting links.cpp checker.cpp transformations.cpp

clean:
	rm hypercubeRouting

run_links:
	make
	./hypercubeRouting 4 all
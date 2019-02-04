# File:   Makefile
# Author: robertomaldonado
# Created on January 22, 2019
#Define Compiler:
CC=g++ -std=c++11
CFLAG=-g -Wall
#Define the processes:
all: compile_all

compile_all: 
	$(CC) $(CFLAG) -o my_test test.cpp

clean:
	rm my_test

run:
	make
	./my_test
# Makefile for the TeX template generator.
#
# Author: Alexander Roth
# Date:   2014-11-20

CC = gcc

CFLAGS = -g -Wall

LDFLAGS = -g

templater: templater.o
	$(CC) $(LDFLAGS) templater.o -o templater

templater.o: templater.c templater.h
	$(CC) -c $(CFLAGS) templater.c

.PHONY: clean
clean:
	rm -f *.o *~ a.out templater *.tex

.PHONY: all
all: clean templater

# Makefile for filler tool.
# It was necessary because with Mac OS X 10.7 simply using
# gcc -o filler filler.c won't work. It says it could not find libgcc. 
# Thus, use this file.
#
# AW / 17.09.2012
#
CC=llvm-gcc-4.2  
CFLAGS=-c -Wall

filler: filler.o 
	$(CC) filler.c  -o filler

clean:
	rm *.o filler



CC = g++
CFLAGS = -Wall -g

output: matrix.o main.o
	$(CC) $(CFLAGS) matrix.o main.o -o output

matrix.o: matrix.cpp matrix.h
	$(CC) $(CFLAGS) -c matrix.cpp 

main.o: main.cpp matrix.h
	$(CC) $(CFLAGS) -c main.cpp

clean: 
	rm *.o output
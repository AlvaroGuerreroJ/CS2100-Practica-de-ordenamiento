##
# Sorting algorithms
#
# @file
# @version 0.1

CC=clang++
CFLAGS=-lrapidcheck -Wall -Werror -Wextra

main: main.o
	$(CC) -o main main.o $(CFLAGS)

main.o: main.cpp sort.hpp
	$(CC) -c -o $@ $<

# end

# Projekt: Hello world!
# Autor:   David Martinek
# Datum:   16.8.2014

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra

Maze: maze.c
	$(CC) $(CFLAGS) maze.c -o Maze

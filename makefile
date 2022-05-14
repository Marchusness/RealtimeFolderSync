CC = g++
VER = -std=c++17
CFLAGS = -c
DEBUG = -g
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: run

run : FileWatcher.cpp
	$(CC) $(VER) main.cpp FileWatcher.cpp FileManager.cpp -o run
	./run

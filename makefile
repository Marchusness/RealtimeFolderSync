CC = g++
VER = -std=c++17
CFLAGS = -c
DEBUG = -g
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: run

run : FileWatcher.cpp
	$(CC) $(VER) test_fs_watcher.cpp FIleWatcher.cpp -o run
	./run

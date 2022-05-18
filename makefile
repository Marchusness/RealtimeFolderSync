CC = g++
CFLAGS = -c
DEBUG = -g

# clean:
# 	rm server client unitTest

run : FileWatcher.cpp
	$(CC) -std=c++20 main.cpp Engine.cpp FileWatcher.cpp FileManager.cpp TCPStream.cpp TCPListener.cpp PacketTypes.cpp Packet.cpp -o run

clean:
	rm run

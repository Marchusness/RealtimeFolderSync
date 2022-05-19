CC = g++
CFLAGS = -c
DEBUG = -g

run : 
	$(CC) -std=c++2a main.cpp Engine.cpp FileWatcher.cpp FileManager.cpp TCPStream.cpp TCPListener.cpp PacketTypes.cpp Packet.cpp -o run

clean:
	rm run

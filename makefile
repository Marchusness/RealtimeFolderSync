CC = g++

TARGET = main
OBJ := Packet PacketTypes TCPListener TCPStream

all: $(TARGET)

$(OBJ).o : $(OBJ).cpp
    $(CC) -c $(OBJ).cpp -o $(OBJ).o

$(TARGET): Packet.o PacketTypes.o TCPListener.o TCPStream.o
	$(CC) Packet.o PacketTypes.o TCPListener.o TCPStream.o -o $(TARGET)

clean:
	rm main
	rm -f *.o
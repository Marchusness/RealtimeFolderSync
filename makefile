networkingTests: 
	g++ testclient.cpp TCPStream.cpp PacketTypes.cpp Packet.cpp -o client
	g++ testserver.cpp TCPStream.cpp TCPListener.cpp PacketTypes.cpp Packet.cpp -o server
	g++ unitTest.cpp Packet.cpp TCPStream.cpp PacketTypes.cpp -o unitTest
	./unitTest

clean:
	rm server client unitTest
networkingTests: testserver.cpp testclient.cpp ntestmain.cpp TCPStream.cpp TCPListener.cpp
	g++ testserver.cpp -o server
	g++ testclient.cpp -o client
	g++ ntestmain.cpp TCPStream.cpp -o nmain
	g++ ntestserver.cpp TCPStream.cpp TCPListener.cpp -o nserver

clean:
	rm server client nmain nserver
networkingTests: testserver.cpp testclient.cpp
	g++ testserver.cpp -o server
	g++ testclient.cpp -o client

clean:
	rm server client
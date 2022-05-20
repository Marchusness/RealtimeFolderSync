CC = g++
OBJFOLDER = obj
CPPVER = -std=c++2a
FILES := $(wildcard main.cpp Engine.cpp Packet.cpp PacketTypes.cpp TCPListener.cpp TCPStream.cpp FileManager.cpp FileWatcher.cpp)
objects := $(patsubst %.cpp,$(OBJFOLDER)/%.o,$(FILES))
#objects := $(patsubst %.cpp,$(OBJFOLDER)/%.o,$(wildcard *.cpp)) all cpp files in directory

foo : $(objects)
	@echo linking
	@$(CC) $(CPPVER) $(objects) -o main

$(OBJFOLDER)/main.o: main.cpp
	@echo building main
	@$(CC) $(CPPVER) -c main.cpp -o $(OBJFOLDER)/main.o

$(OBJFOLDER)/%.o: %.cpp %.h
	@echo building $<
	@$(CC) $(CPPVER) -c $< -o $@

clean:
	rm $(OBJFOLDER)/* main

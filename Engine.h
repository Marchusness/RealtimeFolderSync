#include <string>

class TCPListener;
class TCPStream;
class FileManager;
class FileWatcher;
class Packet;

class Engine
{
private:
    /* data */
public:
    TCPListener* tCPListener;
    TCPStream* tCPStream;
    FileWatcher* fileWatcher;
    FileManager* fileManager;

    Engine(std::string path, int port);
    Engine(std::string syncPath, int port, std::string address);
    ~Engine();

    void loop();

    //this will be improved version 2
    void sendPacket(Packet* p); //used to bridge listener and stream
    Packet* getPacket();
};

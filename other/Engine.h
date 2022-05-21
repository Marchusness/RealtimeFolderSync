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

    Engine(int port);
    Engine(int port, std::string adress);
    ~Engine();

    void loop();

    //this will be improved version 2
    void sendPacket(Packet* p); //used to bridge listener and stream
    Packet* getPacket();
};

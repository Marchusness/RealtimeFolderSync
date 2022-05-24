#include <string>

class TCPListener;
class TCPStream;
class FileManager;
class FileWatcher;
class Packet;

class Engine
{
public:
    static Engine* engine;
    TCPListener* tCPListener;
    TCPStream* tCPStream;
    FileWatcher* fileWatcher;
    FileManager* fileManager;
    bool running;

    Engine(std::string path, int port);
    Engine(std::string syncPath, int port, std::string address);
    ~Engine();

    void loop();
    static void escapeHandler(int s);               //catches terminal control-c to handle closing sockets cleanly 

    void sendPacket(Packet* p);                     //used to bridge listener and stream
    void sendPacket(Packet* p, TCPStream* stream);  //if server will ignore stream
    Packet* getPacket();
};

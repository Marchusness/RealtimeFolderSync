#include <iostream>
#include <chrono>
#include <thread>
#include "TCPStream.h"
#include "PacketTypes.h"
#include "Packet.h"

int main(int argc, char const *argv[])
{
    TCPStream* s = TCPStream::connectTo("localhost", 1110);
    if (s)
    {
        Packet_GetPaths* p = new Packet_GetPaths();
        s->write(p);

        Packet* r;
        while (!(r = s->tryReadPacket()))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        r->exicute();
    }
    delete s;
    
    return 0;
}

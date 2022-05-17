#include "TCPListener.h"
#include <iostream>
#include <chrono>
#include <thread>

#include "Packet.h"

int main(int argc, char const *argv[])
{
    TCPListener t(1110);
    while (true)
    {
        t.check();
        Packet* p;
        while (p = t.getPacketInQueue())
        {
            p->exicute();//may have to pass this function some pointers im not sure yet
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}

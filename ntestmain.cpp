#include "TCPStream.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    TCPStream* s = TCPStream::connectTo("localhost", 1110);
    if (s)
    {
        const char* mes = "hello\n";
        //s->write((void*)mes, 14);
        char bug[256];
        s->read(bug);
        std::cout << bug << std::endl;
    }
    
    return 0;
}

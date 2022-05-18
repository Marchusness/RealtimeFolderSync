#include "Packet.h"
#include <cstring>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    //test packet creating from data array
    {
        Packet* p1 = new Packet(254, 0);
        p1->writeHeader();

        Packet* p2 = new Packet(p1->getDataArray(), 254, p1->getDataSize());

        bool same = true;
        for (int i = 0; i < p1->getDataSize(); i++)
        {
            if (p1->getDataArray()[i] != p2->getDataArray()[i])
            {
                same = false;
                break;
            }
        }
        if (!same)
        {
            std::cout << "failed data copying test" << std::endl;
        }
        
        delete p1;
        delete p2;
    }
    //test reading and writing ints from data array
    {
        int in = 3478;
        Packet* p1 = new Packet(10, INITIALPACKETSIZE + sizeof(in));

        p1->addToByteArray(&in, sizeof(in));
        p1->writeHeader();

        char* p1data = p1->getDataArray();

        Packet* p2 = new Packet(p1data, 10, p1->getDataSize());
        int out = 0;
        p2->readFromByteArray(&out, sizeof(out));

        if (in != out)
        {
            std::cout << "failed to read and write int from data array\n";
            std::cout << "in " << in << " out " << out << std::endl;
        }

        delete p1;
        delete p2;
    }
    //test reading and writing strings from data array
    {
        std::string in = "the input";
        Packet* p1 = new Packet(10, 50);

        p1->addToByteArray(in);
        p1->writeHeader();

        char* p1data = p1->getDataArray();

        Packet* p2 = new Packet(p1data, 10, p1->getDataSize());
        std::string out;
        p2->readFromByteArray(out);

        if (in != out)
        {
            std::cout << "failed to read and write string from data array\n";
            std::cout << "in " << in << " out " << out << std::endl;
        }

        delete p1;
        delete p2;
    }
    return 0;
}

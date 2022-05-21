#ifndef H_PACKET
#define H_PACKET

#include <string>

//size of defualt packet header
#define INITIALPACKETSIZE (sizeof(char) + sizeof(unsigned int))

/* types
0 something
1 connection closed
2 write file
3 request file
4 request folder structure
5 update folder structure
*/

class TCPStream;
class Engine;

class Packet
{
protected:
    char type;
    unsigned int size = 0;
    TCPStream* stream = nullptr;
    char* data;
    unsigned int dataIndex = 0;

public:
    Packet(TCPStream* stream, char type);                      //create packet that reads data from a TCPStream
    Packet(char* byteArray, char type, unsigned int size);     //create packet from a byte array and length
    Packet(char type, unsigned int size);                      //creates a packet with no data to write to
    virtual ~Packet();

    void writeHeader();             //write type and size header
    virtual char* toByteArray();    //convert packet to byte array
    virtual void exicute(Engine*);  //do whatever the packet does
    virtual bool read();            //read the byte array to packet data

    //getters
    char getType();
    char* getDataArray();
    unsigned int getPacketSize();
    unsigned int getDataSize();

    //DOESNT WORK WITH OBJECTS THAT CONTAIN INTERNAL POINTERS, but everything else is fine ignoring significant byte order
    void addToByteArray(void* data, long unsigned length);      //write data to byte array
    void readFromByteArray(void* data, long unsigned length);   //read data from byte array

    void addToByteArray(std::string& string);                   //a special set just for strings
    void readFromByteArray(std::string& string);                //strings are just to usefull
};

#endif
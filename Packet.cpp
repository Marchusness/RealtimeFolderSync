#include <cstring>
#include <iostream>
#include "Packet.h"
#include "TCPStream.h"
#include "Engine.h"

Packet::Packet(TCPStream* stream, char type)
{
    this->type = type;
    this->stream = stream;
    this->dataIndex = INITIALPACKETSIZE;   //the header is ignored
}

Packet::Packet(char* byteArray, char type, unsigned int size)
{
    this->type = type;
    this->size = size;
    this->dataIndex = INITIALPACKETSIZE;
    data = new char[size];
    memcpy(data, byteArray, size);
}

Packet::Packet(char type, unsigned int _size)
{
    this->type = type;
    this->size = _size < INITIALPACKETSIZE ? INITIALPACKETSIZE : _size; //must atleast be large enought to hold the header
    this->dataIndex = INITIALPACKETSIZE;
    data = new char[size];
}

Packet::~Packet()
{
    delete[] data;
}

void Packet::writeHeader()
{
    dataIndex = dataIndex < INITIALPACKETSIZE ? INITIALPACKETSIZE : dataIndex;   
    data[0] = type;
    char* Cdata = reinterpret_cast<char* >(&dataIndex);
    memcpy(data + 1, Cdata, sizeof(dataIndex));
}

char* Packet::toByteArray()
{
    writeHeader();
    return data;
}

bool Packet::read()
{
    if (!stream)
    {
        return false;
    }

    //read data size from stream
    char* streamData[sizeof(unsigned int)];
    stream->read(streamData, sizeof(unsigned int));

    //convert to unsigned int
    char* Cdata = reinterpret_cast<char* >(&size);
    memcpy(Cdata, streamData, sizeof(unsigned int));
    
    //read the rest of the data but dont interprete it
    unsigned int readDataLen = INITIALPACKETSIZE;
    data = new char[size];
    while (readDataLen < size)
    {
        readDataLen += stream->read(data + readDataLen, size - readDataLen);
    }
    return true;
}

void Packet::exicute(Engine* engine)
{
}

//getters
char Packet::getType()
{
    return type;
}

char* Packet::getDataArray()
{
    return data;
}

unsigned int Packet::getPacketSize()
{
    return size;
}

unsigned int Packet::getDataSize()
{
    return dataIndex;
}

void Packet::addToByteArray(void* Tdata, long unsigned length)
{
    //convert data type char pointer and coppy bytes  
    char* Cdata = reinterpret_cast<char* >(Tdata);
    memcpy(data + dataIndex, Cdata, length);
    dataIndex += length;
}
 
void Packet::readFromByteArray(void* Tdata, long unsigned length)
{
    //convert data type to char pointer and then copy data from array to pointer
    char* Cdata = reinterpret_cast<char* >(Tdata);
    memcpy(Cdata, data + dataIndex, length);
    dataIndex += length;
}

void Packet::addToByteArray(std::string& string)
{
    unsigned int length = string.size();
    addToByteArray(&length, sizeof(length));
    char* cstring = &string[0];
    addToByteArray(cstring, length);
}

void Packet::readFromByteArray(std::string& string)
{
    unsigned int length;
    readFromByteArray(&length, sizeof(length));
    char* cstring = new char[length+1];
    readFromByteArray(cstring, length);
    cstring[length] = '\0';
    string = std::string(cstring);
    delete[] cstring;
}
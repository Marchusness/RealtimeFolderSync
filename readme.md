# Realtime Folder Sync
Syncs folders realtime

## How To Use It
- Clone the repository
- Run 'make' from your terminal
- Run './main' from your terminal

## TCPStream
- Holds a stream
- Can write data and read data from the stream
- Has a static member to perform a connection, returning a stream pointer
- Perfereably can be used as a stream with << and >>

## TCPListener
- Listens for incomming connections and creates streams for them
- Has a 'check' function that checks the states of all the streams and if a connection is waiting

## Current Version
- Either host or connect to a server
- Clients sync with server's folder
- When changes are made the client informs the server which then informs all clients.

## Future Improvements
- Utilise OS specific directory monitoring libraries for increased efficiency.
- Incrementally write data straight to files from the TPCStream (Current: reads entire packet from stream then writes to file. Won't work with extremely large files)
- More user friendly
- Secureity
- Better methods in general
- Less memory leaks


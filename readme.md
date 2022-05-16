# Realtime Folder Sync
Syncs folders realtime

## TCPStream
- holds a stream
- can write data and read data from the stream
- has a static member to perform a connection, returning a stream pointer
- perfereably can be used as a stream with << and >>

## TCPListener
- listens for incomming connections and creates streams for them
- has a 'check' function that checks the states of all the streams and if a connection is waiting
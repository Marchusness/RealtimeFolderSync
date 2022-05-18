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

## Version 1
- either host or connect to a server
- client syncs with servers folder
- when changes are made the client informs the server which then informs all clients

## Version 2
- better methods in general
- less memory leaks
- more user friendly
- secureity


client needs to ask for paths, and then ask for each file from the server
when a file is changed the client needs to send a write file to the server, and the server needs to send it to all clients
send to all needs to be abke to exclude a sttream
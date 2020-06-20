# TCPClient
A basic TCPClient designed in c++ using winsock

___________________
INSTRUCTION FOR USE

1. Create a new TCPClient object (Ex.: TCPClient client(<ip addr(std::string)>, <port(int)>))
2. Create the main loop (Ex.: if(client.Init()){ client.Run(); })
3. Open the server (Server source code available here: https://github.com/LorenzoCirillo/Multithreaded_TCPServer)

P.S. Make sure to run the server first, because the server will wait for a client connection.
___________________

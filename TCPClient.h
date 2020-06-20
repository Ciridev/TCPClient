#pragma once

#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class TCPClient
{
public:
	TCPClient(std::string ipAddress, int port);
	~TCPClient();
	
	bool Init();

	void Run();
	int Send(int socketId, std::string msg);
	void CleanUp();

private:
	
	SOCKET CreateSocket();

	std::string				m_ipAddress;
	std::string				m_userInput;
	int						m_port;

};
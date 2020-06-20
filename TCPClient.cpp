#include <iostream>
#include <string>

#include "TCPClient.h"

#define MAX_BUFFER_SIZE (4096)

TCPClient::TCPClient(std::string ipAddress, int port)
	: m_ipAddress(ipAddress), m_port(port)
{
}

TCPClient::~TCPClient()
{
	this->CleanUp();
}

bool TCPClient::Init()
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);

	int dataOk = WSAStartup(ver, &data);

	return dataOk == 0;

}

void TCPClient::Run()
{
	char buffer[MAX_BUFFER_SIZE];

	bool flag = 0;

	while(!flag)
	{
		SOCKET server = this->CreateSocket();

		if (server == INVALID_SOCKET)
		{
			flag = 1;
		}
		else
		{
			do
			{
				std::cout << "> ";
				getline(std::cin, this->m_userInput);

				if (this->m_userInput.size() > 0)
				{
					int sendOk = this->Send(server, this->m_userInput);

					if (sendOk != SOCKET_ERROR)
					{
						ZeroMemory(buffer, 4096);
						int bytesReceived = recv(server, buffer, sizeof(buffer), 0);

						if (bytesReceived > 0)
						{
							std::cout << "Server > " << std::string(buffer, 0, bytesReceived) << std::endl;
						}
					}
				}

			} while (this->m_userInput.size() > 0);

			closesocket(server);
			flag = 1;
		}

		Sleep(100);
	}
}

int TCPClient::Send(int socketId, std::string msg)
{
	return send(socketId, msg.c_str(), msg.size() + 1, 0);
}

void TCPClient::CleanUp()
{
	WSACleanup();
}


SOCKET TCPClient::CreateSocket()
{
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	if (server != INVALID_SOCKET)
	{
		sockaddr_in  hint;

		hint.sin_family = AF_INET;
		hint.sin_port = htons(this->m_port);
		inet_pton(AF_INET, this->m_ipAddress.c_str(), &hint.sin_addr);

		int connOk = connect(server, (sockaddr*)&hint, sizeof(hint));

		if (connOk == SOCKET_ERROR)
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}

	return server;
}

#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")

#include <string>
#include <thread>
#include <iostream>

#include "ErrorFormatter.hpp"

class Client
{
public:
	Client(std::string strIP, __int32 iPort );
	~Client( );

private:
	void Connect( std::string strIP, __int32 iPort );
	void InfiniteRead( void );

	SOCKET m_iSocket;
};


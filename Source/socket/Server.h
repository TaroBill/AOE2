#pragma once
#include "../StdAfx.h"
#include "ServerSocket.h"
class Server {
public:
	static Server* getInstance();
	void createServer();
	Server();
	~Server();

private:
	static Server* instance;
	CServerSocket cserversocket;
	bool ServerStatus;
};
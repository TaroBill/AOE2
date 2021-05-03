#pragma once
#pragma comment(lib,"wsock32.lib")
#include "../StdAfx.h"
#include "CConnSocket.h"
#include <list>


class CServerSocket : public CSocket {
public:
	virtual void OnAccept(int);
	void CloseAllConn();
private:
	list<CConnSocket*> ClientList;
};
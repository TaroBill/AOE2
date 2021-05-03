#include "../StdAfx.h"
#include "ServerSocket.h"


void CServerSocket::OnAccept(int nErrorCode)
{
	CSocket* client = new CSocket();
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	int addrLen = sizeof(addr);

	Accept(*client, (SOCKADDR*)&addr, &addrLen);
	/*char* ip = inet_ntoa(addr.sin_addr);
	client->SetClientAddr(CString(ip), addr.sin_port);
	ClientList.push_back(client);

	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: connect success!"), t.wHour, t.wMinute, t.wSecond, CString(ip), addr.sin_port);*/
	//TRACE(msg);

	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::CloseAllConn()
{
	list<CConnSocket*>::iterator it = ClientList.begin();
	for (; it != ClientList.end(); )
	{
		(*it)->Close();
		delete (*it);
		it = ClientList.erase(it);
	}
	this->Close();
}
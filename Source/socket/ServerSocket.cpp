#include "ServerSocket.h"
#include "NetWork.h"

ServerSocket::ServerSocket()
{
}

ServerSocket::~ServerSocket()
{
}


/////////////////////////////////////////////////////////////////////////////
// MyEchoSocket member functions

void ServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		NetWork::getInstance()->OnAccept();
	}
	CSocket::OnAccept(nErrorCode);
}

void ServerSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{

	}


	CSocket::OnClose(nErrorCode);
}

void ServerSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class


	CSocket::OnConnect(nErrorCode);
}

void ServerSocket::OnOutOfBandData(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnOutOfBandData(nErrorCode);
}

void ServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		NetWork::getInstance()->OnReceive();
	}

	CSocket::OnReceive(nErrorCode);
}

void ServerSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnSend(nErrorCode);
}


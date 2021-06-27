#include "../StdAfx.h"
#include "ClientSocket.h"
#include "NetWork.h"

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}




/////////////////////////////////////////////////////////////////////////////
// MyEchoSocket member functions

void ClientSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnAccept(nErrorCode);
}

void ClientSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnClose(nErrorCode);

}

void ClientSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class


	CSocket::OnConnect(nErrorCode);
}

void ClientSocket::OnOutOfBandData(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnOutOfBandData(nErrorCode);
}

void ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		NetWork::getInstance()->OnReceive();
	}

	CSocket::OnReceive(nErrorCode);
}

void ClientSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnSend(nErrorCode);
}


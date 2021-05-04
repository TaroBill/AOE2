#include "ClientSocket.h"
#include "NetWork.h"

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(MyEchoSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(MyEchoSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// MyEchoSocket member functions

void ClientSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnAccept(nErrorCode);
}

void ClientSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnClose(nErrorCode);
}

void ClientSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class


	CAsyncSocket::OnConnect(nErrorCode);
}

void ClientSocket::OnOutOfBandData(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		NetWork::getInstance()->OnReceive();
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void ClientSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnSend(nErrorCode);
}


#include "ServerSocket.h"
#include "NetWork.h"

ServerSocket::ServerSocket()
{
}

ServerSocket::~ServerSocket()
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

void ServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		NetWork::getInstance()->OnAccept();
	}
	CAsyncSocket::OnAccept(nErrorCode);
}

void ServerSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{

	}


	CAsyncSocket::OnClose(nErrorCode);
}

void ServerSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class


	CAsyncSocket::OnConnect(nErrorCode);
}

void ServerSocket::OnOutOfBandData(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void ServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		NetWork::getInstance()->OnReceive();
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void ServerSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnSend(nErrorCode);
}


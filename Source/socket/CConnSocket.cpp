#include "CConnSocket.h"

CConnSocket::CConnSocket()
{

}

CConnSocket::~CConnSocket()
{
}



void CConnSocket::OnSend(int nErrorCode)
{

	char buf[] = "your connect success";
	Send(buf, strlen(buf)); 
	CSocket::OnSend(nErrorCode);
}


void CConnSocket::OnReceive(int nErrorCode)
{
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: %s"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
	TRACE(msg);
	CharUpperA(recvBuf);
	this->Send(recvBuf, strlen(recvBuf));
}

void CConnSocket::OnClose(int nErrorCode)
{
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: already close!"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port);
	TRACE(msg);
	CSocket::OnClose(nErrorCode);
}

void CConnSocket::SetClientAddr(CString ip, USHORT port)
{
	m_ip = ip;
	m_port = port;
}
#pragma once
#include "../StdAfx.h"
#include <CString>

class CConnSocket : public CSocket
{
public:
	CConnSocket();
	virtual ~CConnSocket();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void SetClientAddr(CString ip, USHORT port);
private:
	CString m_ip;
	USHORT m_port;
};
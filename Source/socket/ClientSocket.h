#pragma once
#include "../StdAfx.h"

class ClientSocket : public CSocket
{
	// Attributes
public:

	// Operations
public:
	ClientSocket();
	virtual ~ClientSocket();

	// Overrides
public:
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

};

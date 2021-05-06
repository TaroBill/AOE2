#pragma once

#include "StdAfx.h"
// ServerControler 對話方塊

class ServerControler : public CDialog
{
	DECLARE_DYNAMIC(ServerControler);

public:
	ServerControler(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~ServerControler();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OLE_PROPPAGE_SMALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP();
};

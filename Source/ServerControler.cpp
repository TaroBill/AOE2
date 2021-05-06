// ServerControler.cpp: 實作檔案
//
#include "StdAfx.h"
#include "ServerControler.h"
#include "afxdialogex.h"


// ServerControler 對話方塊

IMPLEMENT_DYNAMIC(ServerControler, CDialog)

ServerControler::ServerControler(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OLE_PROPPAGE_SMALL, pParent)
{

}

ServerControler::~ServerControler()
{
}

void ServerControler::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ServerControler, CDialogEx)
END_MESSAGE_MAP()


// ServerControler 訊息處理常式

#include "NetWork.h"

NetWork* NetWork::getInstance() {
    if (instance == nullptr) {
        instance = new NetWork();
    }
    return instance;
}


NetWork::NetWork() {
    ServerStatus = false;
}

NetWork::~NetWork() {

}

void NetWork::createServer() {
    TRACE("Creating Server\n");
    if (cserversocket.Create(1234)) {
        ServerStatus = true;
        if (!cserversocket.Listen()) {
            AfxMessageBox(_T("無法listen此port"));
            cserversocket.Close();
            return;
        }
    }
    else {
        AfxMessageBox(_T("創建Socket失敗"));
    }
    TRACE("Listening for Connections!!!");
}

void NetWork::ConnectToServer() {
    clientsocket.Create();
    clientsocket.Connect("127.0.0.1", 1234);
}

void NetWork::OnAccept() {
    TRACE("OnAccept\n");
    CString strIP;
    UINT port;
    if (cserversocket.Accept(clientsocket))
    {
        clientsocket.GetSockName(strIP, port);
        //m_status = "Client Connected,IP :" + strIP;
        clientsocket.Send("Connected To Server", strlen("Connected To  Server"));
    }
    else
    {
        AfxMessageBox("Cannot Accept Connection");
    }
}

void NetWork::OnReceive() {
    TRACE("OnReceive\n");
    char* pBuf = new char[1025];
    CString strData;
    int iLen;
    iLen = clientsocket.Receive(pBuf, 1024);
    if (iLen == SOCKET_ERROR)
    {
        AfxMessageBox("Could not Receive");
    }
    else
    {
        pBuf[iLen] = NULL;
        strData = pBuf;
        AfxMessageBox(_T(strData));
        //display in server              
    }
}

NetWork* NetWork::instance;
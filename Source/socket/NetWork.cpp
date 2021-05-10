#include "NetWork.h"
#include "../World.h"
NetWork* NetWork::getInstance() {
    return &instance;
}


NetWork::NetWork() {
    isOpened = false;
    isPlaying = false;
    isConnectedToClient = false;
}

NetWork::~NetWork() {
    isOpened = false;
    TRACE("~NetWork()\n");
}

void NetWork::play() {
    isPlaying = true;
}

void NetWork::pause() {
    isPlaying = false;
}

void NetWork::createServer() {
    TRACE("Creating Server\n");
    if (cserversocket.Create(1234)) {
        if (!cserversocket.Listen()) {
            AfxMessageBox(_T("無法listen此port"));
            cserversocket.Close();
            return;
        }
    }
    else {
        AfxMessageBox(_T("創建Socket失敗"));
    }
    TRACE("Listening for Connections!!!\n");
    isOpened = true;
}

void NetWork::ConnectToServer() {
    clientsocket.Create();
    clientsocket.Connect("127.0.0.1", 1234);
    isConnectedToClient = true;
}

void NetWork::OnAccept() {
    TRACE("OnAccept\n");
    CString strIP;
    UINT port;
    if (cserversocket.Accept(clientsocket))
    {
        clientsocket.GetSockName(strIP, port);
        TRACE("isConnectedToClient %s %d\n", strIP, port);
        isConnectedToClient = true;
    }
    else
    {
        AfxMessageBox("Cannot Accept Connection");
    }
}

void NetWork::OnReceive() {
    TRACE("OnReceive\n");
    char* pBuf = new char[4096];
    CString strData;
    stringstream ss;
    string erase;
    int iLen;
    iLen = clientsocket.Receive(pBuf, 4096);
    if (iLen == SOCKET_ERROR)
    {
        AfxMessageBox("Could not Receive");
    }
    else
    {
        //pBuf[iLen] = NULL;
        strData = pBuf;
        //TRACE(pBuf);
        ss << strData;
        int size;
        ss >> erase >> size;
        World::getInstance()->LoadEnemyFromStringStream(size, ss);
        //display in server        
        if (!isOpened)
            SendData();
    }
    delete [] pBuf;


}

void NetWork::SendData() {
    if (!isConnectedToClient) {
        //TRACE("Haven't Connect to client\n");
        return;
    }
    stringstream packet;
    int size = World::getInstance()->unit.size();
    packet << "VillagersSize " << size << " ";
    for (int i = 0; i < size; i++) {
        dynamic_cast<Unit::Villager*>(World::getInstance()->unit.at(i))->Serialize(packet);
    }
    //TRACE("SENDING DATA\n");
    string str = packet.str();
    char* output = new char[str.length() + 1];
    strcpy(output, str.c_str());
    //TRACE(output);
    
    clientsocket.Send(output, 4096);
    delete [] output;
}

NetWork NetWork::instance;
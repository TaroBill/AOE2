#include "NetWork.h"
#include "../World.h"
NetWork* NetWork::getInstance() {
    if (instance == nullptr) {
        instance = new NetWork();
    }
    return instance;
}


NetWork::NetWork() {
    isOpened = false;
    isPlaying = false;
    isConnectedToClient = false;
}

NetWork::~NetWork() {
    isOpened = false;
}

/*DWORD WINAPI NetWork::ServerTickThread(LPVOID lpParam) {
    while (instance->isOpened) {
        if (instance->isPlaying == false) {
            Sleep(300);
            continue;
        }
        if (instance->isConnectedToClient == false) {
            TRACE("Haven't connected to client\n");
            Sleep(300);
            continue;
        }
        instance->SendData();
        Sleep(300);
    }
    return 0;
}*/

void NetWork::play() {
    isPlaying = true;
}

void NetWork::pause() {
    isPlaying = false;
}

void NetWork::createServer() {
    TRACE("Creating Server\n");
    if (instance->cserversocket.Create(1234)) {
        if (!instance->cserversocket.Listen()) {
            AfxMessageBox(_T("無法listen此port"));
            instance->cserversocket.Close();
            return;
        }
    }
    else {
        AfxMessageBox(_T("創建Socket失敗"));
    }
    TRACE("Listening for Connections!!!\n");
    isOpened = true;
    //hThread = CreateThread(NULL, 0, ServerTickThread, NULL, 0, &dwThreadID);  //採用多線程固定tick送data失敗，MFC CSocket類不支援多線程
    //GAME_ASSERT(hThread != NULL, "NetWork error: Create Thread failed!"); 
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
        TRACE("isConnectedToClient %s %d\n", strIP, port);
        isConnectedToClient = true;
        //m_status = "Client Connected,IP :" + strIP;
      //  clientsocket.Send("Connected To Server", strlen("Connected To  Server"));
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
        TRACE(pBuf);
        //display in server              
    }
    delete pBuf;


    /*  CArchive ar(file, CArchive::load, 4096);
      int amount;
      ar >> amount;
      World::getInstance()->LoadEnemyFromArchive(amount, ar);
      ar.Close();*/

}

void NetWork::SendData() {
    stringstream packet;
    int size = World::getInstance()->unit.size();
    packet << size;
    for (int i = 0; i < size; i++) {
        dynamic_cast<Unit::Villager*>(World::getInstance()->unit.at(i))->Serialize(packet);
    }
    TRACE("SENDING DATA\n");
    string str = packet.str();
    char* output = new char[str.length() + 1];
    strcpy(output, str.c_str());
    
    clientsocket.Send(output, 4096);
    delete[] output;
}

NetWork* NetWork::instance;
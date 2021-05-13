#include "NetWork.h"
#include "../World.h"
#include "../gamelib.h"

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
            AfxMessageBox(_T("�L�klisten��port"));
            cserversocket.Close();
            return;
        }
    }
    else {
        AfxMessageBox(_T("�Ы�Socket����"));
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
    string contain;
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
        //TRACE("%s\n", pBuf);
        ss << strData;
        ss >> contain;
        if (contain == "spawn") {// command = spawn EntityTypes x y
            //TRACE("spawn entity from data\n");
            int ET;
            ss >> ET;//Entity type
            int x, y;   //Entity Location
            ss >> x >> y;
            World::getInstance()->spawnEnemy(static_cast<EntityTypes>(ET), x, y);
        }
        else if (contain == "settarget") {// command = settarget <amount> <id id id ... id> x y
            //TRACE("settarget from data\n");
            int amount; //�N�h�ֹ���]�w�ؼ�
            ss >> amount;
            vector<UINT> entityID;
            for (int i = 0; i < amount; i++) {
                UINT id;
                ss >> id;//����ID
                entityID.push_back(id);
            }
            int x, y;//�ؼЪ���m
            ss >> x >> y;
            vector<Unit::Entity*> ListEntity = World::getInstance()->getEntityByID(entityID);
            for (unsigned int i = 0; i < ListEntity.size(); i++)
            {

                ListEntity[i]->
                    SetTarget(
                        CPoint(x,y),
                        World::getInstance()->LE);

            }
        }
        else if (contain == "killEntity") { // command = killEntity <amount> <id id id ... id>
            UINT id;
            ss >> id;//����ID
            World::getInstance()->killByID(id);
        }
        else if (contain == "EndGame") {// command = EndGame
            //TRACE("EndGame from data\n");
            game_framework::CGame::Instance()->SetGameState(GAME_STATE_OVER);
        }
    }
    delete [] pBuf;


}

void NetWork::SendData(stringstream& command) {
    if (!isConnectedToClient)
        return;
    //TRACE("SENDING DATA\n");
    string str = command.str();
    char* output = new char[str.length() + 1];
    strcpy(output, str.c_str());
    //TRACE(output);
    
    clientsocket.Send(output, 4096);
    delete [] output;
}

bool NetWork::isServer() {
    return isOpened;
}

NetWork NetWork::instance;
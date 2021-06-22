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
    isCreated = false;
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
    if (isCreated) 
        return;
    isCreated = true;
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
    AfxMessageBox("創建伺服器成功! \n正在等待連線");
    isOpened = true;
}

void NetWork::ConnectToServer(string ip) {
    if (!isCreated) {
        isCreated = true;
        clientsocket.Create();
    }
    char* output = new char[ip.length() + 1];
    strcpy(output, ip.c_str());

    if (clientsocket.Connect(output, 1234)) {
        isConnectedToClient = true;
        AfxMessageBox("連線成功");
        game_framework::CGame::Instance()->SetGameState(GAME_STATES::GAME_STATE_RUN);
        stringstream command;
        command << "StartGame";
        SendData(command);
    }
    else {
        AfxMessageBox("連線失敗");
    }
    delete[] output;
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
            int amount; //將多少實體設定目標
            ss >> amount;
            vector<UINT> entityID;
            for (int i = 0; i < amount; i++) {
                UINT id;
                ss >> id;//實體ID
                entityID.push_back(id);
            }
            int x, y;//目標的位置
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
        else if (contain == "killEntity") { // command = killEntity id
            UINT id;
            ss >> id;//實體ID
            World::getInstance()->killByID(id);
        }
        else if (contain == "EndGame") {// command = EndGame
            //TRACE("EndGame from data\n");
            World::getInstance()->isWin = true;
            game_framework::CGame::Instance()->SetGameState(GAME_STATE_OVER);
        }
        else if (contain == "StartGame") {// command = StartGame
            game_framework::CGame::Instance()->SetGameState(GAME_STATE_RUN);
        }
        else if (contain == "OnMove") {
            game_framework::CGame::Instance()->GetGameState()->NetOnMove();
        }
        else if (contain == "UpdateEntity1") {
            int amount;
            ss >> amount;
            TRACE("amount %d\n", amount);
            World::getInstance()->LoadEnemyFromStringStream(amount, ss);
        }
        else if (contain == "UpdateEntity2") {
            int amount;
            ss >> amount;
            World::getInstance()->LoadUnitFromStringStream(amount, ss);
        }
        else if (contain == "UpdateEntity3") {
            int amount;
            ss >> amount;
            World::getInstance()->LoadResourceFromStringStream(amount, ss);
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

bool &NetWork::isServer() {
    return isOpened;
}

NetWork NetWork::instance;
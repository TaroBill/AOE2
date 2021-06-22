#pragma once
#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

using namespace game_framework;

class NetWork {
public:
    static NetWork* getInstance();
    NetWork();
    ~NetWork();
    void createServer();
    void ConnectToServer(string ip);
    void OnAccept();
    void OnReceive();
    void play();
    void pause();
    void SendData(stringstream& command);
    bool &isServer();
    bool isConnectedToClient;
    ServerSocket cserversocket;
    ClientSocket clientsocket;
    bool isCreated;
private:
    static NetWork instance;
    bool isOpened;
    bool isPlaying;
};
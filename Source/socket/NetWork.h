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
    void ConnectToServer();
    void OnAccept();
    void OnReceive();
    void play();
    void pause();
    void SendData();
    ServerSocket cserversocket;
    ClientSocket clientsocket;
private:
    static NetWork instance;
    bool isOpened;
    bool isPlaying;
    bool isConnectedToClient;
};
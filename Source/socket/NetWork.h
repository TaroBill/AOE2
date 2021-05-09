#pragma once
#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <mutex>
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
    static NetWork* instance;
    static DWORD WINAPI ServerTickThread(LPVOID lpParam);
    mutex gMutex;
    bool isOpened;
    bool isPlaying;
    bool isConnectedToClient;
    HANDLE	hThread;	
    DWORD dwThreadID;
};
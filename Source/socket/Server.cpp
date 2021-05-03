#include "Server.h"

Server* Server::getInstance() {
	if (instance == nullptr) {
		instance = new Server();
	}
	return instance;
}

Server::Server() {

}

Server::~Server() {

}

void Server::createServer() {
	if (cserversocket.Create(1234)) {
		if (cserversocket.Listen()) {
			ServerStatus = true;
			cserversocket.Accept();
			cserversocket.Close();
		}
	}
	else {
		AfxMessageBox(_T("³Ð«ØSocket¥¢±Ñ"));
	}

}






Server* Server::instance;
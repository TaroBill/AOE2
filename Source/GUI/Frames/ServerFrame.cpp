#include "../../StdAfx.h"
#include "ServerFrame.h"
#include "../Buttons/StartMenu_CreateServer_Button.h"
#include "../Buttons/StartMenu_JoinServer_Button.h"

ServerFrame::ServerFrame() : Frame(600, 250, 91, 186)
{
	loadBitmap();
	LoadButtons();
}

ServerFrame::~ServerFrame()
{
	
}

void ServerFrame::loadBitmap() {
	texture.LoadBitmap(IDB_SERVERFRAME);
}

void ServerFrame::onMove() {

}

void ServerFrame::OnShow() {
	Frame::OnShow();
	for (unsigned int i = 0; i < buttons.size(); i++) {
		buttons[i]->OnShow();
	}
}

void ServerFrame::LoadButtons() {
	freeButtons();
	buttons.push_back(new CreateServerButton());
	buttons.push_back(new JoinServerButton());
}

#include "../../StdAfx.h"
#include "IPFrame.h"
#include "../Buttons/StartMenu_JoinServer2_Button.h"
#include "../GUI.h"

IPFrame::IPFrame() : Frame(845, 465, 200, 400)
{
	loadBitmap();
	LoadButtons();
	GUI::getInstance()->isTyping = true;
}

IPFrame::~IPFrame()
{
	GUI::getInstance()->isTyping = false;
	GUI::getInstance()->ip = "";
}

void IPFrame::loadBitmap() {
	texture.LoadBitmap(IDB_IP);
}

void IPFrame::onMove() {

}

void IPFrame::OnShow() {
	Frame::OnShow();
	for (unsigned int i = 0; i < buttons.size(); i++) {
		buttons[i]->OnShow();
	}
}

void IPFrame::LoadButtons() {
	freeButtons();
	buttons.push_back(new JoinServerButton2());
}

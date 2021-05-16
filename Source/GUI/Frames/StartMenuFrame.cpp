#include "StartMenuFrame.h"
#include "../Buttons/StartMenu_Leave_Button.h"
#include "../Buttons/StartMenu_MulitGame_Button.h"

StartMenuFrame::StartMenuFrame() : Frame(0, 0, 1920, 1080)
{
	loadBitmap();
	LoadButtons();
}

StartMenuFrame::~StartMenuFrame()
{
	
}

void StartMenuFrame::loadBitmap() {
	texture.LoadBitmap(IDB_MAINMENU);
}

void StartMenuFrame::onMove() {

}

void StartMenuFrame::OnShow() {
	Frame::OnShow();
	for (unsigned int i = 0; i < buttons.size(); i++) {
		buttons[i]->OnShow();
	}
}

void StartMenuFrame::LoadButtons() {
	freeButtons();
	buttons.push_back(new MultiGameButton());
	buttons.push_back(new LeaveButton());
}

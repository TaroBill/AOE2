#include "HelpFrame.h"
#include "../Buttons/StartMenu_JoinServer2_Button.h"
#include "../GUI.h"

HelpFrame::HelpFrame() : Frame(300, 200, 200, 400)
{
	loadBitmap();
	LoadButtons();
	GUI::getInstance()->isTyping = true;
}

HelpFrame::~HelpFrame()
{
}

void HelpFrame::loadBitmap() {
	texture.LoadBitmap(IDB_HELPFRAME);
}

void HelpFrame::onMove() {

}

void HelpFrame::OnShow() {
	Frame::OnShow();
}

void HelpFrame::LoadButtons() {
	freeButtons();
}

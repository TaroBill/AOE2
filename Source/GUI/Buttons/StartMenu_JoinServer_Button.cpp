#include "../../StdAfx.h"
#include "StartMenu_JoinServer_Button.h"
#include "../GUI.h"
#include "../../socket/NetWork.h"
#include "../Frames/IPFrame.h"

JoinServerButton::JoinServerButton() : Button(605, 300, 40, 180, true)
{
	loadBitmap();
}

JoinServerButton::~JoinServerButton() {

}

void JoinServerButton::loadBitmap() {
	texture.LoadBitmap(IDB_STARTMENUBUTTONSHORT, RGB(255, 255, 255));
}

void JoinServerButton::onClicked() {
	GUI::getInstance()->loadMainMenu();
	GUI::getInstance()->addFrame(new IPFrame);
}

void JoinServerButton::OnShow() {
	if (this->isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}
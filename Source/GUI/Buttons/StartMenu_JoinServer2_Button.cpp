#include "../../StdAfx.h"
#include "StartMenu_JoinServer2_Button.h"
#include "../GUI.h"
#include "../../socket/NetWork.h"

JoinServerButton2::JoinServerButton2() : Button(950, 622, 40, 180, true)
{
	loadBitmap();
}

JoinServerButton2::~JoinServerButton2() {

}

void JoinServerButton2::loadBitmap() {
	texture.LoadBitmap(IDB_STARTMENUBUTTONSHORT, RGB(255, 255, 255));
}

void JoinServerButton2::onClicked() {
	NetWork::getInstance()->ConnectToServer(GUI::getInstance()->ip);
}

void JoinServerButton2::OnShow() {
	if (this->isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}
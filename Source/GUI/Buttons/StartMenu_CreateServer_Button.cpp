#include "../../StdAfx.h"
#include "StartMenu_CreateServer_Button.h"
#include "../GUI.h"
#include "../../socket/NetWork.h"


CreateServerButton::CreateServerButton() : Button(605, 250, 40, 180, true)
{
	loadBitmap();
}

CreateServerButton::~CreateServerButton() {

}

void CreateServerButton::loadBitmap() {
	texture.LoadBitmap(IDB_STARTMENUBUTTONSHORT, RGB(255, 255, 255));
}

void CreateServerButton::onClicked() {
	NetWork::getInstance()->createServer();
}

void CreateServerButton::OnShow() {
	if (this->isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}
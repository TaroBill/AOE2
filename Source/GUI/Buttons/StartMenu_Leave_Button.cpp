#include "../../StdAfx.h"
#include "StartMenu_Leave_Button.h"
#include "../GUI.h"


LeaveButton::LeaveButton() : Button(176, 1013, 40, 380, true)
{
	loadBitmap();
}

LeaveButton::~LeaveButton() {

}

void LeaveButton::loadBitmap() {
	texture.LoadBitmap(IDB_STARTMENUBUTTONLONG, RGB(255, 255, 255));
}

void LeaveButton::onClicked() {
	PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// Ãö³¬¹CÀ¸
}

void LeaveButton::OnShow() {
	if (this->isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}
#include "StartMenu_Help_Button.h"
#include "../GUI.h"


HelpButton::HelpButton() : Button(176, 639, 40, 380, true)
{
	loadBitmap();
}

HelpButton::~HelpButton() {

}

void HelpButton::loadBitmap() {
	texture.LoadBitmap(IDB_STARTMENUBUTTONLONG, RGB(255, 255, 255));
}

void HelpButton::onClicked() {
	GUI::getInstance()->openHelp();
}

void HelpButton::OnShow() {
	if (this->isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}
#include "StartMenu_About_Button.h"
#include "../Frames/AboutFrame.h"
#include "../GUI.h"

AboutButton::AboutButton() : Button(375, 884, 40, 180, true)
{
	loadBitmap();
}

AboutButton::~AboutButton() {

}

void AboutButton::loadBitmap() {
	texture.LoadBitmap(IDB_STARTMENUBUTTONSHORT, RGB(255, 255, 255));
}

void AboutButton::onClicked() {
	GUI::getInstance()->addFrame(new AboutFrame());
}

void AboutButton::OnShow() {
	if (this->isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}
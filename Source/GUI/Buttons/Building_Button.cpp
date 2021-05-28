#include "Building_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"


Building_Button::Building_Button() : Button(40, SIZE_Y - 240 + 40, 40, 40, true)
{
	loadBitmap();
}

Building_Button::~Building_Button() {

}

void Building_Button::loadBitmap() {
	texture.LoadBitmap(IDB_BUILDING_BUTTON);
}

void Building_Button::onClicked() {
	dynamic_cast<EntityDataButtonFrame*>(GUI::getInstance()->frames.at(3))->LoadBuildingButtons();
}


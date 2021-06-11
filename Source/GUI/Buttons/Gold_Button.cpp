#include "Gold_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"
#include "../../World.h"


Gold_Button::Gold_Button() : Button(140, SIZE_Y - 240 + 40, 40, 40, true)
{
	loadBitmap();
}

Gold_Button::~Gold_Button() {

}

void Gold_Button::loadBitmap() {
	texture.LoadBitmap(IDB_GOLDICON);
}

void Gold_Button::onClicked() {
	World::getInstance()->spawningEntity(IDB_GOLD);
}


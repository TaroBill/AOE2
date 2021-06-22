#include "water_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"


Water_Button::Water_Button() : Button(90, SIZE_Y - 240 + 40, 40, 40, true)
{
	loadBitmap();
}

Water_Button::~Water_Button() {

}

void Water_Button::loadBitmap() {
	texture.LoadBitmap(IDB_WATERICON);
}

void Water_Button::onClicked() {
	World::getInstance()->spawningEntity(IDB_WaterBig);

}


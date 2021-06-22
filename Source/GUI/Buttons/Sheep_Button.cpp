#include "Sheep_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"
#include "../../World.h"


Sheep_Button::Sheep_Button() : Button(40, SIZE_Y - 240 + 90, 40, 40, true)
{
	loadBitmap();
}

Sheep_Button::~Sheep_Button() {

}

void Sheep_Button::loadBitmap() {
	texture.LoadBitmap(IDB_SHEEPICON);
}

void Sheep_Button::onClicked() {
	World::getInstance()->spawningEntity(IDB_SHEEP);
}


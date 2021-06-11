#include "Grass_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"
#include "../../World.h"


Grass_Button::Grass_Button() : Button(40, SIZE_Y - 240 + 40, 40, 40, true)
{
	loadBitmap();
}

Grass_Button::~Grass_Button() {

}

void Grass_Button::loadBitmap() {
	texture.LoadBitmap(IDB_GrassIcon);
}

void Grass_Button::onClicked() {
	World::getInstance()->spawningEntity(IDB_GRASS);
}


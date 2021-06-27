#include "../../StdAfx.h"
#include "Stone_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"
#include "../../World.h"


Stone_Button::Stone_Button() : Button(90, SIZE_Y - 240 + 90, 40, 40, true)
{
	loadBitmap();
}

Stone_Button::~Stone_Button() {

}

void Stone_Button::loadBitmap() {
	texture.LoadBitmap(IDB_STONEICON);
}

void Stone_Button::onClicked() {
	World::getInstance()->spawningEntity(IDB_STONE);
}


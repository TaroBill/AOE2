#include "../../StdAfx.h"
#include "eraser_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"


Eraser_Button::Eraser_Button() : Button(190, SIZE_Y - 240 + 40, 40, 40, true)
{
	loadBitmap();
}

Eraser_Button::~Eraser_Button() {

}

void Eraser_Button::loadBitmap() {
	texture.LoadBitmap(IDB_DESTROY_BUTTON);
}

void Eraser_Button::onClicked() {
	World::getInstance()->spawningEntity(IDB_DESTROY_BUTTON);

}


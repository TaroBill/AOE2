#include "../../StdAfx.h"
#include "Tree_Button.h"
#include "../Frames/EntityDataButtonFrame.h"
#include "../GUI.h"
#include "../../World.h"


Tree_Button::Tree_Button() : Button(140, SIZE_Y - 240 + 90, 40, 40, true)
{
	loadBitmap();
}

Tree_Button::~Tree_Button() {

}

void Tree_Button::loadBitmap() {
	texture.LoadBitmap(IDB_TREE_ICON);
}

void Tree_Button::onClicked() {
	World::getInstance()->spawningEntity(IDB_TREE);
}


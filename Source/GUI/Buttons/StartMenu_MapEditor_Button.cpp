#include "../../StdAfx.h"
#include "StartMenu_MapEditor_Button.h"
#include "../GUI.h"

MapEditorButton::MapEditorButton() : Button(177, 782, 40, 180, true)
{
	loadBitmap();
}

MapEditorButton::~MapEditorButton() {

}

void MapEditorButton::loadBitmap() {
	texture.LoadBitmap(IDB_STARTMENUBUTTONSHORT, RGB(255, 255, 255));
}

void MapEditorButton::onClicked() {
	game_framework::CGame::Instance()->SetGameState(GAME_STATES::GAME_STATE_MAP_EDITOR);
}

void MapEditorButton::OnShow() {
	if (this->isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}
#include "../../StdAfx.h"
#include "StartMenu_MulitGame_Button.h"
#include "../GUI.h"
#include "../../socket/NetWork.h"
#include "../Frames/ServerFrame.h"


MultiGameButton::MultiGameButton() : Button(400, 190, 240, 165, true)
{
	loadBitmap();
}

MultiGameButton::~MultiGameButton() {

}

void MultiGameButton::loadBitmap() {
	texture.LoadBitmap(IDB_MULTIPLAYERGAMEBUTTON, RGB(255, 255, 255));
}

void MultiGameButton::onClicked() {
	/*NetWork::getInstance()->play();
	game_framework::CGame::Instance()->SetGameState(GAME_STATE_RUN);						// ¤Á´«¦ÜGAME_STATE_RUN*/
	Frame* f = new ServerFrame();
	GUI::getInstance()->addFrame(f);
}

void MultiGameButton::OnShow() {
	if (isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}

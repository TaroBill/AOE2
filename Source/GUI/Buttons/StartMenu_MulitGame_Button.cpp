#include "StartMenu_MulitGame_Button.h"
#include "../GUI.h"
#include "../../socket/NetWork.h"


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
	NetWork::getInstance()->createServer();
	//AfxMessageBox(_T("已創建伺服器"));	//這行會觸發BUG
	NetWork::getInstance()->play();
	game_framework::CGame::Instance()->SetGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
}

void MultiGameButton::OnShow() {
	if (isInButton(World::getInstance()->mouseLocation)) {
		texture.SetTopLeft(getLocation().x, getLocation().y);
		texture.ShowBitmap();
	}
}

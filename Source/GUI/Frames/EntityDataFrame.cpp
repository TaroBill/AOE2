#include "EntityDataFrame.h"
#include "../../mygame.h"

EntityDataFrame::EntityDataFrame() : Frame(300, SIZE_Y - 240, 240, 1380)
{
	loadBitmap();
}

EntityDataFrame::~EntityDataFrame()
{

}


void EntityDataFrame::loadBitmap() {
	texture.LoadBitmap(IDB_DATABACKGROUND);
}

void EntityDataFrame::loadEntitysBitmap(vector<Unit::Entity*> en) {
	entitys.clear();
	CPoint firstLocation = CPoint(300 + 40, SIZE_Y - 240 + 40);
	for (unsigned int i = 0; i < en.size(); i++) {
		entitys.push_back(CMovingBitmap());
		if (typeid(*en[i]) == typeid(Unit::Villager)) {
			entitys[i].LoadBitmap(IDB_VILLAGERICON);
			CAudio::Instance()->Play(AUDIO_SHEEP, false);
		}
		else if (typeid(*en[i]) == typeid(Unit::Mine)) {
			entitys[i].LoadBitmap(IDB_GOLDICON);
		}
		else if (typeid(*en[i]) == typeid(Unit::TownCenter)) {
			entitys[i].LoadBitmap(IDB_TOWNCENTER_ICON);
			CAudio::Instance()->Play(AUDIO_TOWNCENTER, false);
		}
		else if (typeid(*en[i]) == typeid(Unit::Stone)) {
			entitys[i].LoadBitmap(IDB_STONE_ICON);
		}
		else if (typeid(*en[i]) == typeid(Unit::Tree)) {
			entitys[i].LoadBitmap(IDB_TREE_ICON);
		}
		entitys[i].SetTopLeft(firstLocation.x + i%20 * 40, firstLocation.y + (int)(i / 20) * 40);
	}
	if (entitys.size() == 1) {
		showDataEntity = en[0];
	}
}

void EntityDataFrame::clearEntitysBitmap() {
	entitys.clear();
}

void EntityDataFrame::onMove() {

}

void EntityDataFrame::OnShow() {
	Frame::OnShow();
	for (unsigned int i = 0; i < entitys.size(); i++) {
		entitys[i].ShowBitmap();
	}
	if (entitys.size() == 1) {
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(80, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		if (typeid(*showDataEntity) == typeid(Unit::Mine)) {
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, "剩餘資源量: %d ", dynamic_cast<Unit::Mine*>(showDataEntity)->remainAmount);
			pDC->TextOut(300 + 40, SIZE_Y - 240 + 80, str);
		}
		else if (typeid(*showDataEntity) == typeid(Unit::Stone)) {
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, "剩餘資源量: %d ", dynamic_cast<Unit::Stone*>(showDataEntity)->remainAmount);
			pDC->TextOut(300 + 40, SIZE_Y - 240 + 80, str);
		}
		else if (typeid(*showDataEntity) == typeid(Unit::Tree) ){
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, "剩餘資源量: %d ", dynamic_cast<Unit::Tree*>(showDataEntity)->remainAmount);
			pDC->TextOut(300 + 40, SIZE_Y - 240 + 80, str);
		}
		else {
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, "HP: (%d / %d)", showDataEntity->hp, showDataEntity->maxHP);
			pDC->TextOut(300 + 40, SIZE_Y - 240 + 80, str);
		}
		switch (showDataEntity->playerId) {
		case 0:
			pDC->TextOut(300 + 40, SIZE_Y - 240 + 30, "這是你的實體");
			break;
		case 1:
			pDC->TextOut(300 + 40, SIZE_Y - 240 + 30, "這是敵人的實體");
			break;
		case -1:
			pDC->TextOut(300 + 40, SIZE_Y - 240 + 30, "這是資源");
			break;
		}
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}

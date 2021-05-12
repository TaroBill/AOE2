#include "EntityDataFrame.h"

EntityDataFrame::EntityDataFrame() : Frame(300, SIZE_Y - 240, 240, 1380)
{
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
		}
		else if (typeid(*en[i]) == typeid(Unit::Mine)) {
			entitys[i].LoadBitmap(IDB_GOLDICON);
		}
		else if (typeid(*en[i]) == typeid(Unit::TownCenter)) {
			entitys[i].LoadBitmap(IDB_TOWNCENTER_ICON);
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
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "HP: (%d / %d)", showDataEntity->hp, showDataEntity->maxHP);
		pDC->TextOut(300 + 40, SIZE_Y - 240 + 80, str);
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

void EntityDataFrame::onClicked(CPoint p) {

}

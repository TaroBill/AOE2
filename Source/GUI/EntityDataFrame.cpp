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
		entitys[i].SetTopLeft(firstLocation.x + i%20 * 40, firstLocation.y + (int)(i / 20) * 40);
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
}

void EntityDataFrame::onClicked(CPoint p) {

}

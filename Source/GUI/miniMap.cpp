#include "miniMap.h"


MiniMap::MiniMap() {
	this->Name = "";
	this->CurrentLocationX = 0;
	this->CurrentLocationY = 0;
	w = 240;
	h = 240;
	x = SIZE_X - w;
	y = SIZE_Y - h;
}


MiniMap::MiniMap(int CurrentLocationX = 0, int CurrentLocationY = 0, string Name = "") {
	this->Name = Name;
	this->CurrentLocationX = CurrentLocationX;
	this->CurrentLocationY = CurrentLocationY;
	w = 240;
	h = 240;
	x = SIZE_X - w;
	y = SIZE_Y - h;
}
void MiniMap::OnShow() {
	map.SetTopLeft(x, y);
	CurrentLocation.SetTopLeft(x + CurrentLocationX*2, y + CurrentLocationY*2);
	map.ShowBitmap();
	CurrentLocation.ShowBitmap();
}
void MiniMap::LoadBitMap() {
	map.LoadBitmap(IDB_MINIMAP);
	CurrentLocation.LoadBitmap(IDB_MiniMap_CL, RGB(0, 0, 0));
}

bool MiniMap::isInMiniMap(int px, int py) {
	if (px >= (x) && px <= SIZE_X && py >= (y) && py <= SIZE_Y) {
		return true;
	}
	return false;
}
void MiniMap::setCurrentLocation(int cX, int cY) {
	CurrentLocationX = cX;
	CurrentLocationY = cY;
}
CPoint MiniMap::MiniMapLoc2GlobalLoc(CPoint point) {
	return CPoint((point.x - x)/2 * 50, (point.y - y)/2 * 50);
}
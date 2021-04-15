#include "miniMap.h"




MiniMap::MiniMap() : Frame(SIZE_X - 240, SIZE_Y - 240, 240, 240){
	this->Name = "";
	this->CurrentLocationX = 0;
	this->CurrentLocationY = 0;
}

MiniMap::~MiniMap() {

}

void MiniMap::OnShow() {
	Frame::OnShow();
	CurrentLocation.SetTopLeft(getLocation().x + CurrentLocationX, getLocation().y + CurrentLocationY);
	CurrentLocation.ShowBitmap();
}

void MiniMap::LoadBitmap() {
	texture.LoadBitmap(IDB_MINIMAP);
	CurrentLocation.LoadBitmap(IDB_MiniMap_CL, RGB(0, 0, 0));
}

bool MiniMap::isInMiniMap(int px, int py) {
	return this->isInFrame(px, py);
}
void MiniMap::setCurrentLocation(int cX, int cY) {
	CurrentLocationX = cX * 2;
	CurrentLocationY = cY * 2;
}
CPoint MiniMap::MiniMapLoc2GlobalLoc(CPoint point) {
	return CPoint(((point.x - getLocation().x)/2 * 50, (point.y - getLocation().y)/2 * 50));
}

void MiniMap::onClicked(CPoint point) {

}
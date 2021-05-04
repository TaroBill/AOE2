#include "GUI.h"

GUI* GUI::getInstance() {
	if (instance == nullptr) {
		instance = new GUI();
	}
	return instance;
}


GUI::GUI() {

}

GUI::~GUI() {
}

void GUI::loadBitmap() {
	entityDataButtonFrame.loadBitmap();
	entityDataFrame.loadBitmap();
	resourceFrame.loadBitmap();
	minimap.loadBitmap();
}
void GUI::onShow() {
	entityDataButtonFrame.OnShow();
	entityDataFrame.OnShow();
	resourceFrame.OnShow();
	minimap.OnShow();
}

bool GUI::isInGUI(int x, int y) {
	if (minimap.isInFrame(x, y) || entityDataButtonFrame.isInFrame(x, y) || entityDataFrame.isInFrame(x, y) || resourceFrame.isInFrame(x, y))
		return true;
	return false;
}

bool GUI::isInGUI(CPoint p) {
	if (minimap.isInFrame(p.x, p.y) || entityDataButtonFrame.isInFrame(p.x, p.y) || entityDataFrame.isInFrame(p.x, p.y) || resourceFrame.isInFrame(p.x, p.y))
		return true;
	return false;
}

void GUI::triggerOnClicked(CPoint p) {
	if (entityDataButtonFrame.isInFrame(p)) {
		entityDataButtonFrame.onClicked(p);
	}
	if (entityDataFrame.isInFrame(p)) {
		entityDataFrame.onClicked(p);
	}
	if (resourceFrame.isInFrame(p)) {
		resourceFrame.onClicked(p);
	}
	if (minimap.isInFrame(p)) {
		World::getInstance()->setScreenLocation(minimap.MiniMapLoc2GlobalLoc(p));
	}
}

void GUI::printTest() {
	TRACE("TEST\n");
}

GUI* GUI::instance;

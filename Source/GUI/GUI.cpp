#include "GUI.h"


GUI::GUI() {
	AllFrames.push_back(new ResourceFrame());
	AllFrames.push_back(new EntityDataFrame());
	AllFrames.push_back(new EntityDataButtonFrame());
}

GUI::~GUI() {
	
}

void GUI::LoadBitmap() {
	for (unsigned int i = 0; i < AllFrames.size(); i++)
		AllFrames[i]->LoadBitmap();
	minimap.LoadBitmap();
}
void GUI::onShow() {
	for (unsigned int i = 0; i < AllFrames.size(); i++) 
		AllFrames[i]->OnShow();
	minimap.OnShow();
}

bool GUI::isInGUI(int x,int y) {
	for (unsigned int i = 0; i < AllFrames.size(); i++) {
		if (AllFrames[i]->isInFrame(x, y))
			return true;
	}
	if (minimap.isInFrame(x, y))
		return true;
	return false;
}

void GUI::triggerOnClicked(CPoint p) {
	for (unsigned int i = 0; i < AllFrames.size(); i++) {
		if (AllFrames[i]->isInFrame(p)) {
			AllFrames[i]->onClicked(p);
		}
	}
}
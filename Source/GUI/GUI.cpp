#include "GUI.h"


GUI::GUI() {

}

void GUI::LoadBitMap() {
	minimap.LoadBitMap();
}
void GUI::onShow() {
	minimap.OnShow();
}

bool GUI::isInGUI(int x,int y) {
	return minimap.isInMiniMap(x, y);
}
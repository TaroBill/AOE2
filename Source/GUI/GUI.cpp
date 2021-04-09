#include "GUI.h"


GUI::GUI() {

}

void GUI::LoadBitMap() {
	minimap.LoadBitMap();
	resourcesBackground.LoadBitmap(IDB_RESOURCEBACKGROUND);
	entityDataBackground.LoadBitmap(IDB_DATABACKGROUND);
	buttonBackground.LoadBitmap(IDB_BUTTONBACKGROUND);
}
void GUI::onShow() {
	minimap.OnShow();
	resourcesBackground.SetTopLeft(0, 0);
	entityDataBackground.SetTopLeft(300, SIZE_Y - 240);
	buttonBackground.SetTopLeft(0, SIZE_Y - 240);
	resourcesBackground.ShowBitmap();
	entityDataBackground.ShowBitmap();
	buttonBackground.ShowBitmap();
}

bool GUI::isInGUI(int x,int y) {
	return minimap.isInMiniMap(x, y);
}
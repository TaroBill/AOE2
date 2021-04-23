#include "EntityDataButtonFrame.h"


EntityDataButtonFrame::EntityDataButtonFrame() : Frame(0, SIZE_Y - 240, 240, 300)
{
}

EntityDataButtonFrame::~EntityDataButtonFrame()
{

}

void EntityDataButtonFrame::LoadBitmap() {
	texture.LoadBitmap(IDB_BUTTONBACKGROUND);
}

void EntityDataButtonFrame::onClicked(CPoint p) {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if(buttons[i].isEnable() && buttons[i].isInButton(p))
			buttons[i].onClicked();
	}
}

void EntityDataButtonFrame::LoadVillagerButtons() {

}
#include "EntityDataButtonFrame.h"

EntityDataButtonFrame::EntityDataButtonFrame() : Frame(0, SIZE_Y - 240, 240, 300)
{
	LoadVillagerButtons();
}

EntityDataButtonFrame::~EntityDataButtonFrame()
{

}

void EntityDataButtonFrame::loadBitmap() {
	texture.LoadBitmap(IDB_BUTTONBACKGROUND);
}

void EntityDataButtonFrame::OnShow() {
	Frame::OnShow();
	for (unsigned int i = 0; i < buttons.size(); i++) {
		buttons[i]->OnShow();
	}
}

void EntityDataButtonFrame::onClicked(CPoint p) {
	//TRACE("%d\n", 0);
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->isEnable() && buttons[i]->isInButton(p)) {
			//TRACE("%d\n", 1);
			buttons[i]->onClicked();
			if (typeid(Building_Button) == typeid(*buttons[i])) {
				LoadBuildingButtons();
				//TRACE("%d\n", 2);
			}
		}
	}
}

void EntityDataButtonFrame::LoadVillagerButtons() {
	buttons.clear();
	buttons.push_back(new Building_Button());
	buttons.push_back(new Military_Button());
}

void EntityDataButtonFrame::LoadBuildingButtons() {
	buttons.clear();
	buttons.push_back(new House_Button());
}
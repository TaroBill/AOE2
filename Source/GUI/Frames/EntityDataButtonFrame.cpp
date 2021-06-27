#include "../../StdAfx.h"
#include "EntityDataButtonFrame.h"
#include "../Buttons/Building_Button.h"
#include "../Buttons/Military_Button.h"
#include "../Buttons/House_Button.h"
#include "../Buttons/Grass_Button.h"
#include "../Buttons/water_Button.h"
#include "../Buttons/Sheep_Button.h"
#include "../Buttons/Gold_Button.h"
#include "../Buttons/Stone_Button.h"
#include "../Buttons/Tree_Button.h"
#include "../Buttons/eraser_Button.h"

EntityDataButtonFrame::EntityDataButtonFrame() : Frame(0, SIZE_Y - 240, 240, 300)
{
	loadBitmap();
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

void EntityDataButtonFrame::onMove() {

}

void EntityDataButtonFrame::LoadEmpty() {
	freeButtons();
}

void EntityDataButtonFrame::LoadVillagerButtons() {
	freeButtons();
	buttons.push_back(new Building_Button());
	buttons.push_back(new Military_Button());
}

void EntityDataButtonFrame::LoadBuildingButtons() {
	freeButtons();
	buttons.push_back(new House_Button());
}

void EntityDataButtonFrame::LoadMapEditorButtons() {
	freeButtons();
	buttons.push_back(new Grass_Button());
	buttons.push_back(new Water_Button());
	buttons.push_back(new Sheep_Button());
	buttons.push_back(new Stone_Button());
	buttons.push_back(new Tree_Button());
	buttons.push_back(new Gold_Button());
	buttons.push_back(new Eraser_Button());
}

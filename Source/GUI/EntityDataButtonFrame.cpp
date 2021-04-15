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

}
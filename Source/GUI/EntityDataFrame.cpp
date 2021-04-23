#include "EntityDataFrame.h"

EntityDataFrame::EntityDataFrame() : Frame(300, SIZE_Y - 240, 240, 1380)
{
}

EntityDataFrame::~EntityDataFrame()
{

}

void EntityDataFrame::loadBitmap() {
	texture.LoadBitmap(IDB_DATABACKGROUND);
}

void EntityDataFrame::onClicked(CPoint p) {

}

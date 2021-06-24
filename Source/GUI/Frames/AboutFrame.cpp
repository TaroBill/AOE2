#include "AboutFrame.h"
#include "../GUI.h"

AboutFrame::AboutFrame() : Frame(845, 465, 200, 400)
{
	loadBitmap();
	LoadButtons();
}

AboutFrame::~AboutFrame()
{
}

void AboutFrame::loadBitmap() {
	texture.LoadBitmap(IDB_ABOUTFRAME);
}

void AboutFrame::onMove() {

}

void AboutFrame::OnShow() {
	Frame::OnShow();
}

void AboutFrame::LoadButtons() {
}

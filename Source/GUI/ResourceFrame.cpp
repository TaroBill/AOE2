#include "ResourceFrame.h"


ResourceFrame::ResourceFrame() : Frame(0, 0, 26, 1920)
{

}

ResourceFrame::~ResourceFrame()
{

}

void ResourceFrame::loadBitmap() {
	texture.LoadBitmap(IDB_RESOURCEBACKGROUND);
}

void ResourceFrame::onClicked(CPoint p) {

}

#include "GUI.h"
#include "Frames/minimap.h"
#include "Frames/ResourceFrame.h"
#include "Frames/EntityDataFrame.h"
#include "Frames/EntityDataButtonFrame.h"
#include "Frames/StartMenuFrame.h"

GUI* GUI::getInstance() {
	return &instance;
}


GUI::GUI() {

}

GUI::~GUI() {
	freeFrames();
	TRACE("~GUI\n");
}

void GUI::onMove() {
	for (unsigned int i = 0; i < frames.size(); i++) {
		frames[i]->onMove();
	}
}

void GUI::loadInGameGUI() {
	freeFrames();
	frames.push_back(new MiniMap());
	frames.push_back(new ResourceFrame());
	frames.push_back(new EntityDataFrame());
	frames.push_back(new EntityDataButtonFrame());
}

void GUI::freeFrames() {
	for (unsigned int i = 0; i < frames.size(); i++) {
		delete frames[i];
	}
	frames.clear();
}

void GUI::onShow() {
	for (unsigned int i = 0; i < frames.size(); i++) {
		frames[i]->OnShow();
	}
}

bool GUI::isInGUI(int x, int y) {
	for (unsigned int i = 0; i < frames.size(); i++) {
		if (frames[i]->isInFrame(x,y))
			return true;
	}
	return false;
}

bool GUI::isInGUI(CPoint p) {
	for (unsigned int i = 0; i < frames.size(); i++) {
		if (frames[i]->isInFrame(p))
			return true;
	}
	return false;
}

void GUI::triggerOnClicked(CPoint p) {
	for (unsigned int i = 0; i < frames.size(); i++) {
		if (frames[i]->isInFrame(p))
			frames[i]->onClicked(p);
	}
}

void GUI::loadMainMenu() {
	freeFrames();
	frames.push_back(new StartMenuFrame);
}

GUI GUI::instance;

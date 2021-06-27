#include "../StdAfx.h"
#include "GUI.h"
#include "Frames/minimap.h"
#include "Frames/ResourceFrame.h"
#include "Frames/EntityDataFrame.h"
#include "Frames/EntityDataButtonFrame.h"
#include "Frames/StartMenuFrame.h"
#include "Frames/HelpFrame.h"

GUI* GUI::getInstance() {
	return &instance;
}


GUI::GUI() {
	isTyping = false;
	ip = "";
	isHelpOpened = false;
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

void GUI::addFrame(Frame* frame) {
	frames.push_back(frame);
}

void GUI::loadMainMenu() {
	freeFrames();
	frames.push_back(new StartMenuFrame());
}

void GUI::loadMapEditorGUI() {
	freeFrames();
	EntityDataButtonFrame *f = new EntityDataButtonFrame();
	f->LoadMapEditorButtons();
	frames.push_back(f);
}

void GUI::openHelp() {
	if (!isHelpOpened) {
		addFrame(new HelpFrame());
		isHelpOpened = true;
	}
	else {
		isHelpOpened = false;
		for (unsigned int i = 0; i < frames.size(); i++) {
			if (typeid(*frames.at(i)) == typeid(HelpFrame)) {
				delete frames.at(i);
				frames.erase(frames.begin() + i);
				break;
			}
		}
	}
}

GUI GUI::instance;

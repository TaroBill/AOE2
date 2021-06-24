#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "Frames/Frame.h"
using namespace game_framework;
class GUI {
public:
	GUI();
	~GUI();
	static GUI* getInstance();
	void onShow();
	void onMove();
	bool isInGUI(int, int);
	bool isInGUI(CPoint);
	void triggerOnClicked(CPoint);
	void loadInGameGUI();
	void loadMainMenu();
	void loadMapEditorGUI();
	void freeFrames();
	void addFrame(Frame* frame);
	void openHelp();
	vector<Frame*> frames;
	bool isTyping;
	string ip;
private:
	bool isHelpOpened;
	static GUI instance;

};

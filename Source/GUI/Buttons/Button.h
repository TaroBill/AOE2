#pragma once

#include "../../stdafx.h"
#include "../../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../../audio.h"
#include "../../gamelib.h"
//#include "../GUI.h"

using namespace game_framework;
class Button {
public:
	Button(int, int, int, int, bool);
	virtual ~Button();
	int getX();
	int getY();
	void setLocation(int, int);//���s�̥��W����m(X, Y)
	void setRange(int, int);//���s�d��j�p(��, �e)
	virtual void loadBitmap() = 0;		// ���J�ϧ�
	virtual void OnShow();			// �N�ϧζK��e��
	virtual void onClicked() = 0;
	void setEnable(bool);
	CPoint getLocation();
	bool isEnable();
	bool isInButton(CPoint);
	CMovingBitmap texture;
private:
	void init(int, int, int, int, bool);//��l�ƫ��s(LocX, LocY, Height, Width, enable)
	int LocX, LocY;
	int Height, Width;
	bool enable;
};

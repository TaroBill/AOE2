#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
//#include <Vector>
//#include "AllHeader.h"

using namespace game_framework;
class Button {
public:
	Button(int, int, int, int, bool);
	int getX();
	int getY();
	void setLocation(int, int);//���s�̥��W����m(X, Y)
	void setRange(int, int);//���s�d��j�p(��, �e)
	void LoadBitmap();		// ���J�ϧ�
	void OnShow();			// �N�ϧζK��e��
	bool isEnable();
	CMovingBitmap texture;
private:
	void init(int, int, int, int, bool);//��l�ƫ��s(LocX, LocY, Height, Width, enable)
	int LocX, LocY;
	int Height, Width;
	bool enable;
};

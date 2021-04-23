#pragma once

#include "../../stdafx.h"
#include "../../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../../audio.h"
#include "../../gamelib.h"

using namespace game_framework;
class Button {
public:
	Button(int, int, int, int, bool);
	~Button();
	int getX();
	int getY();
	void setLocation(int, int);//���s�̥��W����m(X, Y)
	void setRange(int, int);//���s�d��j�p(��, �e)
	virtual void LoadBitmap() = 0;		// ���J�ϧ�
	void OnShow();			// �N�ϧζK��e��
	void onClicked();
	bool isEnable();
	bool isInButton(CPoint);
	CMovingBitmap texture;
private:
	void init(int, int, int, int, bool);//��l�ƫ��s(LocX, LocY, Height, Width, enable)
	int LocX, LocY;
	int Height, Width;
	bool enable;
};

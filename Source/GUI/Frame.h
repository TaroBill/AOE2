#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include <vector>
#include "./Buttons/Button.h"
#include "../World.h"

using namespace game_framework;
class Frame {
public:
	CMovingBitmap texture;
	Frame(int x=0, int y=0, int h=50, int w=50) {
		LocX = x;
		LocY = y;
		Height = h;
		Width = w;
	}
	~Frame() {

	}
	CPoint getLocation() const{
		return CPoint(LocX, LocY);
	}
	//�ج[�̥��W����m(X, Y)
	void setLocation(int x, int y) {
		LocX = x;
		LocY = y;
	}
	//�ج[�d��j�p(��, �e)
	void setRange(int h, int w) {
		Height = h;
		Width = w;
	}
	// ���J�ϧ�s
	virtual void LoadBitmap() = 0;		
	// �N�ϧζK��e��
	void OnShow() {
		texture.SetTopLeft(LocX, LocY);
		texture.ShowBitmap();
	}

	bool isInFrame(CPoint p) const{
		if (p.x >= LocX && p.x <= (LocX + Width) && p.y >= (LocY) && p.y <= (LocY + Height)) {
			return true;
		}
		return false;
	}

	bool isInFrame(int x, int y) const{
		if (x >= (LocX) && x <= LocX + Width && y >= (LocY) && y <= LocY + Height) {
			return true;
		}
		return false;
	}

	virtual void onClicked(CPoint p) = 0;
private:
	int LocX, LocY;
	int Height, Width;
};

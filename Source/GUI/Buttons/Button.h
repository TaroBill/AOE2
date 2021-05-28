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
	void setLocation(int, int);//按鈕最左上角位置(X, Y)
	void setRange(int, int);//按鈕範圍大小(長, 寬)
	virtual void loadBitmap() = 0;		// 載入圖形
	virtual void OnShow();			// 將圖形貼到畫面
	virtual void onClicked() = 0;
	void setEnable(bool);
	CPoint getLocation();
	bool isEnable();
	bool isInButton(CPoint);
	CMovingBitmap texture;
private:
	void init(int, int, int, int, bool);//初始化按鈕(LocX, LocY, Height, Width, enable)
	int LocX, LocY;
	int Height, Width;
	bool enable;
};

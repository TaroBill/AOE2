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
	void setLocation(int, int);//按鈕最左上角位置(X, Y)
	void setRange(int, int);//按鈕範圍大小(長, 寬)
	void LoadBitmap();		// 載入圖形
	void OnShow();			// 將圖形貼到畫面
	bool isEnable();
	CMovingBitmap texture;
private:
	void init(int, int, int, int, bool);//初始化按鈕(LocX, LocY, Height, Width, enable)
	int LocX, LocY;
	int Height, Width;
	bool enable;
};

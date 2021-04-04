#pragma once

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
//#include <Vector>
//#include "AllHeader.h"

using namespace game_framework;
enum mapItem { GRASS, RIVER };
class World {
public:
	World();
	void OnShow();									//顯示地圖
	void setScreenLocation(int, int);				//設置sx,sy，螢幕最左上點座標
	void setScreenLocation(CPoint);					//設置sx,sy，螢幕最左上點座標
	int getScreenX();								//取得sx，螢幕最左上點座標x
	int getScreenY();								//取得sy，螢幕最左上點座標y
	int ScreenX2GlobalX(int);						//將取得的螢幕座標X 轉世界座標X
	int ScreenY2GlobalY(int);						//將取得的螢幕座標Y 轉世界座標Y
	int GlobalX2ScreenX(int);						//將取得的世界座標X 轉螢幕座標X
	int GlobalY2ScreenY(int);						//將取得的世界座標Y 轉螢幕座標Y
	int getLocationItem(int, int);					//取得X, Y上的物件(障礙物)
	void LoadBitMap();
	CMovingBitmap grass;
	CMovingBitmap river;
	void moveScreenUp(bool);						//是否移動螢幕向上
	void moveScreenDown(bool);						//是否移動螢幕向下
	void moveScreenLeft(bool);						//是否移動螢幕向左
	void moveScreenRight(bool);						//是否移動螢幕向右
	void onMove();									//移動螢幕
	void UnitOnMove();								//移動單位
	void UnitOnShow();								//顯示單位
	bool isOnScreen(int, int);						//世界座標x, y 是否在現在螢幕要顯示的位子
	//vector<UnitBase> unit;							
private:
	bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
	void initMap();
	int map[120][120];
	int sx, sy;
};

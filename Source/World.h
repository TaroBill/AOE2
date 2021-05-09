#pragma once

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <Vector>
#include "Units/Villager.h"
#include "Units/Navigator.h"
#include "Player/Player.h"
#include <typeinfo>
#include "Units/EntityFactory.h"


enum mapItem { GRASS, RIVER };
class World {
public:
	static World* getInstance();
	World();
	~World();
	Player player;
	void OnShow();									//顯示地圖
	void setScreenLocation(int, int);				//設置sx,sy，螢幕最左上點座標
	void setScreenLocation(CPoint);					//設置sx,sy，螢幕最左上點座標
	int getScreenX();								//取得sx，螢幕最左上點座標x
	int getScreenY();								//取得sy，螢幕最左上點座標y
	int ScreenX2GlobalX(int);						//將取得的螢幕座標X 轉世界座標X
	int ScreenY2GlobalY(int);						//將取得的螢幕座標Y 轉世界座標Y
	CPoint Screen2Global(CPoint);
	int GlobalX2ScreenX(int);						//將取得的世界座標X 轉螢幕座標X
	int GlobalY2ScreenY(int);						//將取得的世界座標Y 轉螢幕座標Y
	int getLocationItem(int, int);					//取得X, Y上的物件(障礙物)
	void LoadBitmap();
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
	void spwan(EntityTypes, CPoint);					//生成實體在座標
	void spwan(EntityTypes, int, int);					//生成實體在座標
	void spwanEnemy(EntityTypes, CPoint);					//生成實體在座標
	void spwanEnemy(EntityTypes, int, int);					//生成實體在座標
	vector<Unit::Entity*> listAllEntityInRange(CPoint, CPoint);
	void spawningEntity(int);
	bool isSpawningEntity = false;
	CMovingBitmap spawningEntityBitmap;		// 滑鼠移動時預覽生成位置
	EntityTypes spawningEntityType;
	CPoint mouseLocation;
	void moveEntityToLocation(vector<Unit::Entity*>, CPoint);
	vector<Unit::Entity*> LE;
	vector<Unit::Entity*> EnemyUnit;
	vector<Unit::Entity*> unit;
	void LoadEnemyFromArchive(int, stringstream&);
	EntityFactory entityFactory;
private:
	static World* instance;
	bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
	void initMap();
	void calculatePopulation();
	int map[120][120];
	int sx, sy;

};
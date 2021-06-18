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
#include "Player/GameResource.h"
#include <typeinfo>
#include "Units/EntityFactory.h"
#include "Units/TownCenter.h"
#include "Units/Tree.h"
#include "Units/Stone.h"

enum mapItem { GRASS, RIVER };
class World {
public:
	static World* getInstance();
	World();
	~World();
	Player player;
	//顯示地圖
	void OnShow();							
	//設置sx,sy，螢幕最左上點座標
	void setScreenLocation(int, int);		
	//設置sx,sy，螢幕最左上點座標
	void setScreenLocation(CPoint);		
	//取得sx，螢幕最左上點座標x
	int getScreenX();		
	//取得sy，螢幕最左上點座標y
	int getScreenY();		
	//將取得的螢幕座標X 轉世界座標X
	int ScreenX2GlobalX(int);				
	//將取得的螢幕座標Y 轉世界座標Y
	int ScreenY2GlobalY(int);						
	//將取得的螢幕座標 轉世界座標
	CPoint Screen2Global(CPoint);
	//將取得的世界座標X 轉螢幕座標X
	int GlobalX2ScreenX(int);						
	//將取得的世界座標Y 轉螢幕座標Y
	int GlobalY2ScreenY(int);			
	//X, Y上是否有障礙物
	int getLocationItem(int, int);					
	void LoadBitmap();
	CMovingBitmap grass;
	CMovingBitmap river;
	//是否移動螢幕向上
	void moveScreenUp(bool);	
	//是否移動螢幕向下
	void moveScreenDown(bool);					
	//是否移動螢幕向左
	void moveScreenLeft(bool);						
	//是否移動螢幕向右
	void moveScreenRight(bool);						
	//移動螢幕
	void onMove();									
	//移動單位
	void UnitOnMove();								
	//顯示單位
	void UnitOnShow();								
	//世界座標x, y 是否在現在螢幕要顯示的位子	
	bool isOnScreen(int, int);						
	//生成實體在座標
	void spawn(EntityTypes, CPoint);
	//生成實體在座標
	void spawn(EntityTypes, int, int);
	//生成敵人實體在座標
	void spawnEnemy(EntityTypes, CPoint);
	//生成敵人實體在座標
	void spawnEnemy(EntityTypes, int, int);
	//生成資源實體在座標
	void spawnResaurce(EntityTypes, CPoint);
	//生成資源實體在座標
	void spawnResaurce(EntityTypes ET, int x, int y);
	//用ID刪除實體
	void killByID(unsigned int);						
	//取得範圍內的己方實體
	vector<Unit::Entity*> listAllEntityInRange(CPoint, CPoint);	
	//取得與滑鼠點擊最近的實體(滑鼠點擊50p*50p內)
	Unit::Entity* getNearestEntity(CPoint);				
	//生成實體的預覽圖示
	void spawningEntity(int);							
	//是否正在生成實體
	bool isSpawningEntity = false;						
	// 滑鼠移動時預覽生成位置圖示
	CMovingBitmap spawningEntityBitmap;		
	EntityTypes spawningEntityType;
	CPoint mouseLocation;
	void moveEntityToLocation(vector<Unit::Entity*>, CPoint);
	//目前所選取所有實體
	vector<Unit::Entity*> LE;							
	//敵人所有實體
	vector<Unit::Entity*> EnemyUnit;					
	//己方所有實體
	vector<Unit::Entity*> unit;							
	//系統所有資源實體
	vector<Unit::Entity*> ResaurceUnit;			
	//同步敵人
	void LoadEnemyFromStringStream(int, stringstream&);	
	//同步自己
	void LoadUnitFromStringStream(int, stringstream&);
	//同步資源
	void LoadResourceFromStringStream(int, stringstream&);
	//包裝成stringstream送出同步
	void packUnit(vector<Unit::Entity*>, int type);
	//實體工廠
	EntityFactory entityFactory;
	//取得與實體ID相符的實體
	Unit::Entity* getEntityByID(unsigned int ID);			
	//取得與實體ID相符的實體(複數)
	vector<Unit::Entity*> getEntityByID(vector<UINT> id);
	// 建築物的障礙判斷
	int buildingMap[120][120];
	//生成世界時初始化的實體
	void initWorld();
private:
	static World instance;
	bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
	void initMap();
	void calculatePopulation();
	int map[120][120];
	int sx, sy; //螢幕座標
	bool isInitingWorld = true;

};
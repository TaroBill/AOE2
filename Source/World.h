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
	void OnShow();									//��ܦa��
	void setScreenLocation(int, int);				//�]�msx,sy�A�ù��̥��W�I�y��
	void setScreenLocation(CPoint);					//�]�msx,sy�A�ù��̥��W�I�y��
	int getScreenX();								//���osx�A�ù��̥��W�I�y��x
	int getScreenY();								//���osy�A�ù��̥��W�I�y��y
	int ScreenX2GlobalX(int);						//�N���o���ù��y��X ��@�ɮy��X
	int ScreenY2GlobalY(int);						//�N���o���ù��y��Y ��@�ɮy��Y
	CPoint Screen2Global(CPoint);
	int GlobalX2ScreenX(int);						//�N���o���@�ɮy��X ��ù��y��X
	int GlobalY2ScreenY(int);						//�N���o���@�ɮy��Y ��ù��y��Y
	int getLocationItem(int, int);					//���oX, Y�W������(��ê��)
	void LoadBitmap();
	CMovingBitmap grass;
	CMovingBitmap river;
	void moveScreenUp(bool);						//�O�_���ʿù��V�W
	void moveScreenDown(bool);						//�O�_���ʿù��V�U
	void moveScreenLeft(bool);						//�O�_���ʿù��V��
	void moveScreenRight(bool);						//�O�_���ʿù��V�k
	void onMove();									//���ʿù�
	void UnitOnMove();								//���ʳ��
	void UnitOnShow();								//��ܳ��
	bool isOnScreen(int, int);						//�@�ɮy��x, y �O�_�b�{�b�ù��n��ܪ���l	
	void spwan(EntityTypes, CPoint);					//�ͦ�����b�y��
	void spwan(EntityTypes, int, int);					//�ͦ�����b�y��
	void spwanEnemy(EntityTypes, CPoint);					//�ͦ�����b�y��
	void spwanEnemy(EntityTypes, int, int);					//�ͦ�����b�y��
	vector<Unit::Entity*> listAllEntityInRange(CPoint, CPoint);
	void spawningEntity(int);
	bool isSpawningEntity = false;
	CMovingBitmap spawningEntityBitmap;		// �ƹ����ʮɹw���ͦ���m
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
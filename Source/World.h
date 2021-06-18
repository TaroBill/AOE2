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
	//��ܦa��
	void OnShow();							
	//�]�msx,sy�A�ù��̥��W�I�y��
	void setScreenLocation(int, int);		
	//�]�msx,sy�A�ù��̥��W�I�y��
	void setScreenLocation(CPoint);		
	//���osx�A�ù��̥��W�I�y��x
	int getScreenX();		
	//���osy�A�ù��̥��W�I�y��y
	int getScreenY();		
	//�N���o���ù��y��X ��@�ɮy��X
	int ScreenX2GlobalX(int);				
	//�N���o���ù��y��Y ��@�ɮy��Y
	int ScreenY2GlobalY(int);						
	//�N���o���ù��y�� ��@�ɮy��
	CPoint Screen2Global(CPoint);
	//�N���o���@�ɮy��X ��ù��y��X
	int GlobalX2ScreenX(int);						
	//�N���o���@�ɮy��Y ��ù��y��Y
	int GlobalY2ScreenY(int);			
	//X, Y�W�O�_����ê��
	int getLocationItem(int, int);					
	void LoadBitmap();
	CMovingBitmap grass;
	CMovingBitmap river;
	//�O�_���ʿù��V�W
	void moveScreenUp(bool);	
	//�O�_���ʿù��V�U
	void moveScreenDown(bool);					
	//�O�_���ʿù��V��
	void moveScreenLeft(bool);						
	//�O�_���ʿù��V�k
	void moveScreenRight(bool);						
	//���ʿù�
	void onMove();									
	//���ʳ��
	void UnitOnMove();								
	//��ܳ��
	void UnitOnShow();								
	//�@�ɮy��x, y �O�_�b�{�b�ù��n��ܪ���l	
	bool isOnScreen(int, int);						
	//�ͦ�����b�y��
	void spawn(EntityTypes, CPoint);
	//�ͦ�����b�y��
	void spawn(EntityTypes, int, int);
	//�ͦ��ĤH����b�y��
	void spawnEnemy(EntityTypes, CPoint);
	//�ͦ��ĤH����b�y��
	void spawnEnemy(EntityTypes, int, int);
	//�ͦ��귽����b�y��
	void spawnResaurce(EntityTypes, CPoint);
	//�ͦ��귽����b�y��
	void spawnResaurce(EntityTypes ET, int x, int y);
	//��ID�R������
	void killByID(unsigned int);						
	//���o�d�򤺪��v�����
	vector<Unit::Entity*> listAllEntityInRange(CPoint, CPoint);	
	//���o�P�ƹ��I���̪񪺹���(�ƹ��I��50p*50p��)
	Unit::Entity* getNearestEntity(CPoint);				
	//�ͦ����骺�w���ϥ�
	void spawningEntity(int);							
	//�O�_���b�ͦ�����
	bool isSpawningEntity = false;						
	// �ƹ����ʮɹw���ͦ���m�ϥ�
	CMovingBitmap spawningEntityBitmap;		
	EntityTypes spawningEntityType;
	CPoint mouseLocation;
	void moveEntityToLocation(vector<Unit::Entity*>, CPoint);
	//�ثe�ҿ���Ҧ�����
	vector<Unit::Entity*> LE;							
	//�ĤH�Ҧ�����
	vector<Unit::Entity*> EnemyUnit;					
	//�v��Ҧ�����
	vector<Unit::Entity*> unit;							
	//�t�ΩҦ��귽����
	vector<Unit::Entity*> ResaurceUnit;			
	//�P�B�ĤH
	void LoadEnemyFromStringStream(int, stringstream&);	
	//�P�B�ۤv
	void LoadUnitFromStringStream(int, stringstream&);
	//�P�B�귽
	void LoadResourceFromStringStream(int, stringstream&);
	//�]�˦�stringstream�e�X�P�B
	void packUnit(vector<Unit::Entity*>, int type);
	//����u�t
	EntityFactory entityFactory;
	//���o�P����ID�۲Ū�����
	Unit::Entity* getEntityByID(unsigned int ID);			
	//���o�P����ID�۲Ū�����(�Ƽ�)
	vector<Unit::Entity*> getEntityByID(vector<UINT> id);
	// �ؿv������ê�P�_
	int buildingMap[120][120];
	//�ͦ��@�ɮɪ�l�ƪ�����
	void initWorld();
private:
	static World instance;
	bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
	void initMap();
	void calculatePopulation();
	int map[120][120];
	int sx, sy; //�ù��y��
	bool isInitingWorld = true;

};
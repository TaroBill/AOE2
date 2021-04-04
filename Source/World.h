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
	void OnShow();									//��ܦa��
	void setScreenLocation(int, int);				//�]�msx,sy�A�ù��̥��W�I�y��
	void setScreenLocation(CPoint);					//�]�msx,sy�A�ù��̥��W�I�y��
	int getScreenX();								//���osx�A�ù��̥��W�I�y��x
	int getScreenY();								//���osy�A�ù��̥��W�I�y��y
	int ScreenX2GlobalX(int);						//�N���o���ù��y��X ��@�ɮy��X
	int ScreenY2GlobalY(int);						//�N���o���ù��y��Y ��@�ɮy��Y
	int GlobalX2ScreenX(int);						//�N���o���@�ɮy��X ��ù��y��X
	int GlobalY2ScreenY(int);						//�N���o���@�ɮy��Y ��ù��y��Y
	int getLocationItem(int, int);					//���oX, Y�W������(��ê��)
	void LoadBitMap();
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
	//vector<UnitBase> unit;							
private:
	bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
	void initMap();
	int map[120][120];
	int sx, sy;
};

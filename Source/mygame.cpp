/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "GUI/Frames/EntityDataButtonFrame.h"
#include "GUI/Frames/EntityDataFrame.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{

		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(2037	 );
		//_CrtSetBreakAlloc(	2025 );
		//_CrtSetBreakAlloc(	2012 );
		//_CrtSetBreakAlloc(	2000 );
		//_CrtSetBreakAlloc(	1987 );
		//_CrtSetBreakAlloc(	1975 );
		//_CrtSetBreakAlloc(	1962 );

	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		logo.LoadBitmap(IDB_BACKGROUND);
		CAudio::Instance()->Load(AUDIO_MAINTHEME, "..//Sounds//MainTheme.mp3");
		CAudio::Instance()->Load(AUDIO_SHEEP, "..//Sounds//SheepSound.mp3");
		CAudio::Instance()->Load(AUDIO_TOWNCENTER, "..//Sounds//TownCenterSound.mp3");
		CAudio::Instance()->Load(AUDIO_SOUNDTRACK, "..//Sounds//Soundtrack.mp3");
		CAudio::Instance()->Play(AUDIO_MAINTHEME, true);
		//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
		GUI::getInstance()->loadMainMenu();
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (GUI::getInstance()->isTyping) {
			if (nChar >= 96 && nChar <= 105) {
				char strInt[2];
				sprintf(strInt, "%d", nChar - 96);
				GUI::getInstance()->ip += strInt;
			}
			else if (nChar >= 48 && nChar <= 57) {
				char strInt[2];
				sprintf(strInt, "%d", nChar - 48);
				GUI::getInstance()->ip += strInt;
			}
			else if (nChar == 190 || nChar == 110) {
				GUI::getInstance()->ip += ".";
			}
			else if (nChar == 8) {
				if(!GUI::getInstance()->ip.empty())
					GUI::getInstance()->ip.pop_back();
			}
		}
		TRACE("%d\n", nChar);
		if (nChar == 80) {
			game_framework::CGame::Instance()->SetGameState(GAME_STATES::GAME_STATE_RUN);
		}
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GUI::getInstance()->triggerOnClicked(point);
	}

	void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point)
	{
		GUI::getInstance()->loadMainMenu();
	}

	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point) {
		World::getInstance()->mouseLocation = point;
	}

	void CGameStateInit::OnShow()
	{
		//
		// 貼上logo
		//
		logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
		logo.ShowBitmap();

		GUI::getInstance()->onShow();
		if (GUI::getInstance()->isTyping) {
			CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CFont f, * fp;
			f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetTextColor(RGB(0, 0, 0));
			char* output = new char[GUI::getInstance()->ip.length() + 1];
			strcpy(output, GUI::getInstance()->ip.c_str());
			pDC->TextOut(950, 560, output);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
			delete[] output;
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{

	}

	void CGameStateOver::OnMove()
	{
		if(NetWork::getInstance()->isServer()){
			stringstream cmd;
			cmd << "OnMove";
			NetWork::getInstance()->SendData(cmd);
		}
		GUI::getInstance()->onMove();
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 60 * 10; // 5 seconds
		CAudio::Instance()->Stop(AUDIO_SOUNDTRACK);
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		GUI::getInstance()->onShow();
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
	
	}

	CGameStateRun::~CGameStateRun()
	{

	}

	void CGameStateRun::OnBeginState()
	{
		sendDataCounter = 0;
		/*CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
		CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
		CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI*/
		CAudio::Instance()->Stop(AUDIO_MAINTHEME);
		CAudio::Instance()->Play(AUDIO_SOUNDTRACK, true);
		World::getInstance()->initMap();
		GUI::getInstance()->loadInGameGUI();
		World::getInstance()->initWorld();
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		if (NetWork::getInstance()->isServer()) {
			stringstream cmd;
			cmd << "OnMove";
			NetWork::getInstance()->SendData(cmd);
			sendDataCounter++;
			if (sendDataCounter == 30) {
				World::getInstance()->packUnit(World::getInstance()->unit, 1);
			}
			else if (sendDataCounter == 60) {
				World::getInstance()->packUnit(World::getInstance()->EnemyUnit, 2);
			}
			if (sendDataCounter == 90) {
				World::getInstance()->packUnit(World::getInstance()->ResaurceUnit, 3);
				sendDataCounter = 0;
			}
		}
		if (World::getInstance()->player.population == 0) {
			GotoGameState(GAME_STATE_OVER);
			stringstream ss;
			ss << "EndGame";
			NetWork::getInstance()->SendData(ss);
		}
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

		//GotoGameState(GAME_STATE_OVER);
		//
		// 移動彈跳的球
		//
		World::getInstance()->onMove();
		GUI::getInstance()->onMove();
		World::getInstance()->UnitOnMove();
		//NetWork::getInstance()->SendData();
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		World::getInstance()->LoadBitmap();
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT) {
			//eraser.SetMovingLeft(true);
			World::getInstance()->moveScreenLeft(true);
		}
		if (nChar == KEY_RIGHT) {
			//eraser.SetMovingRight(true);
			World::getInstance()->moveScreenRight(true);
		}
		if (nChar == KEY_UP) {
			//eraser.SetMovingUp(true);
			World::getInstance()->moveScreenUp(true);
		}
		if (nChar == KEY_DOWN) {
			//eraser.SetMovingDown(true);
			World::getInstance()->moveScreenDown(true);
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT) {
			World::getInstance()->moveScreenLeft(false);
		}
		if (nChar == KEY_RIGHT) {
			World::getInstance()->moveScreenRight(false);
		}
		if (nChar == KEY_UP) {
			World::getInstance()->moveScreenUp(false);
		}
		if (nChar == KEY_DOWN) {
			World::getInstance()->moveScreenDown(false);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		isLButtonDown = true;
		TRACE("Mouse monitor Location: (%d, %d)\n", point.x, point.y);
		TRACE("Mouse Global Location: (%d, %d)\n", World::getInstance()->ScreenX2GlobalX(point.x), World::getInstance()->GlobalY2ScreenY(point.y));
		LButtonDownPoint = World::getInstance()->Screen2Global(point);
		if (GUI::getInstance()->isInGUI(point)) {
			GUI::getInstance()->triggerOnClicked(point);
			return;
		}
		if (World::getInstance()->isSpawningEntity) {
			int x = (int)LButtonDownPoint.x / 50;
			int y = (int)LButtonDownPoint.y / 50;
			if (World::getInstance()->getLocationItem(x * 50,y * 50) == 1)
				return;
			switch (World::getInstance()->spawningEntityType) {
			case EntityTypes::Villager:
				World::getInstance()->spawn(EntityTypes::Villager, LButtonDownPoint);
				break;
			case EntityTypes::TownCenter:
				if (World::getInstance()->getLocationItem(x * 50, y * 50) == 1 || World::getInstance()->getLocationItem(x * 50, (y+1)*50) == 1 || World::getInstance()->getLocationItem((x+1)*50, y*50) == 1 || World::getInstance()->getLocationItem((x + 1) * 50, (y + 1) * 50) == 1) {
					break;
				}
				//TRACE("SPAWNING TOWNCENTER\n");
				CAudio::Instance()->Play(AUDIO_TOWNCENTER, false);
				World::getInstance()->spawn(EntityTypes::TownCenter, x * 50, y * 50);
				break;
			}
		}
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		isLButtonDown = false;
		if (GUI::getInstance()->isInGUI(point)) {
			return;
		}
		CPoint LButtonUpPoint = World::getInstance()->Screen2Global(point);
		//("(%d, %d), (%d, %d)\n", LButtonDownPoint.x, LButtonDownPoint.y, LButtonUpPoint.x, LButtonUpPoint.y);
		CPoint p = (LButtonDownPoint - LButtonUpPoint);
		if (abs(p.x) < 50 && abs(p.y) < 50) {
			World::getInstance()->LE.clear();
			Unit::Entity* tempEntity = World::getInstance()->getNearestEntity(LButtonUpPoint);
			if(tempEntity != NULL)
				World::getInstance()->LE.push_back(tempEntity);
		}
		else {
			World::getInstance()->LE = World::getInstance()->listAllEntityInRange(LButtonDownPoint, LButtonUpPoint);
		}

		dynamic_cast<EntityDataButtonFrame*>(GUI::getInstance()->frames.at(3))->LoadEmpty();
		if (!World::getInstance()->LE.empty()) {
			dynamic_cast<EntityDataFrame*>(GUI::getInstance()->frames.at(2))->loadEntitysBitmap(World::getInstance()->LE);
			if (typeid(Unit::Villager) == typeid(*World::getInstance()->LE[0]) && World::getInstance()->LE[0]->playerId == 0) {
				dynamic_cast<EntityDataButtonFrame*>(GUI::getInstance()->frames.at(3))->LoadVillagerButtons();
			}
		}
		else {
			dynamic_cast<EntityDataFrame*>(GUI::getInstance()->frames.at(2))->clearEntitysBitmap();
		}
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		World::getInstance()->mouseLocation = point;
		mouseLocation = point;
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

		if (World::getInstance()->isSpawningEntity) {
			World::getInstance()->isSpawningEntity = false;
			return;
		}


		World::getInstance()->
			moveEntityToLocation(World::getInstance()->LE, World::getInstance()->Screen2Global(point));

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnShow()
	{
		World::getInstance()->OnShow();
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//

		//
		//  貼上背景圖、撞擊數、球、擦子、彈跳的球
		//
		World::getInstance()->UnitOnShow();
		GUI::getInstance()->onShow();
		if (isLButtonDown) {
			CDC* myDC = CDDraw::GetBackCDC();
			myDC->SelectObject(GetStockObject(NULL_BRUSH));
			myDC->Rectangle(World::getInstance()->GlobalX2ScreenX(LButtonDownPoint.x), World::getInstance()->GlobalY2ScreenY(LButtonDownPoint.y), mouseLocation.x, mouseLocation.y);
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC		
		}
	}


	CGameStateMapEditor::CGameStateMapEditor(CGame* g)
		: CGameState(g)
	{

	}

	CGameStateMapEditor::~CGameStateMapEditor()
	{

	}

	void CGameStateMapEditor::OnBeginState()
	{
		World::getInstance()->initMap();
		GUI::getInstance()->loadMapEditorGUI();
	}

	void CGameStateMapEditor::OnMove()							// 移動遊戲元素
	{
		World::getInstance()->onMove();
		World::getInstance()->UnitOnMove();
		GUI::getInstance()->onMove();
	}

	void CGameStateMapEditor::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateMapEditor::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const UINT KEY_S = 83;
		if (nChar == KEY_LEFT) {
			//eraser.SetMovingLeft(true);
			World::getInstance()->moveScreenLeft(true);
		}
		if (nChar == KEY_RIGHT) {
			//eraser.SetMovingRight(true);
			World::getInstance()->moveScreenRight(true);
		}
		if (nChar == KEY_UP) {
			//eraser.SetMovingUp(true);
			World::getInstance()->moveScreenUp(true);
		}
		if (nChar == KEY_DOWN) {
			//eraser.SetMovingDown(true);
			World::getInstance()->moveScreenDown(true);
		}
		else if (nChar == KEY_S) {
			World::getInstance()->save();
			GotoGameState(GAME_STATES::GAME_STATE_INIT);
		}
		//TRACE("nchar %d \n", nChar);
	}

	void CGameStateMapEditor::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT) {
			World::getInstance()->moveScreenLeft(false);
		}
		if (nChar == KEY_RIGHT) {
			World::getInstance()->moveScreenRight(false);
		}
		if (nChar == KEY_UP) {
			World::getInstance()->moveScreenUp(false);
		}
		if (nChar == KEY_DOWN) {
			World::getInstance()->moveScreenDown(false);
		}
	}

	void CGameStateMapEditor::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		isLBDown = true;
		TRACE("Mouse monitor Location: (%d, %d)\n", point.x, point.y);
		TRACE("Mouse Global Location: (%d, %d)\n", World::getInstance()->ScreenX2GlobalX(point.x), World::getInstance()->ScreenY2GlobalY(point.y));
		if (GUI::getInstance()->isInGUI(point)) {
			GUI::getInstance()->triggerOnClicked(point);
			return;
		}
		CPoint LButtonDownPoint = World::getInstance()->Screen2Global(point);
		if (World::getInstance()->isSpawningEntity) {
			int isEditingMap = World::getInstance()->isEditingMap;
			if (isEditingMap == 1 || isEditingMap == 2) {
				World::getInstance()->setMap(LButtonDownPoint, isEditingMap - 1);
			}
			else if (isEditingMap == 3) {
				Unit::Entity* en = World::getInstance()->getNearestEntity(LButtonDownPoint);
				if(en != NULL)
					World::getInstance()->killByID(en->ID);
			}
			else {
				int x = (int)LButtonDownPoint.x / 50;
				int y = (int)LButtonDownPoint.y / 50;
				switch (World::getInstance()->spawningEntityType) {
				case EntityTypes::GoldMine:
					World::getInstance()->spawnResaurce(EntityTypes::GoldMine, LButtonDownPoint);
					break;
				case EntityTypes::Stone:
					World::getInstance()->spawnResaurce(EntityTypes::Stone, LButtonDownPoint);
					break;
				case EntityTypes::Tree:
					World::getInstance()->spawnResaurce(EntityTypes::Tree, LButtonDownPoint);
					break;
				case EntityTypes::Sheep:

					break;
				}
			}
		}
	}

	void CGameStateMapEditor::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		isLBDown = false;
		if (GUI::getInstance()->isInGUI(point)) {
			return;
		}
	}

	void CGameStateMapEditor::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		World::getInstance()->mouseLocation = point;
		if (isLBDown) {
			CPoint LButtonDownPoint = World::getInstance()->Screen2Global(point);
			if (World::getInstance()->isSpawningEntity) {
				int isEditingMap = World::getInstance()->isEditingMap;
				if (isEditingMap == 1 || isEditingMap == 2) {
					World::getInstance()->setMap(LButtonDownPoint, isEditingMap - 1);
				}
				else if (isEditingMap == 3) {
					Unit::Entity* en = World::getInstance()->getNearestEntity(LButtonDownPoint);
					if (en != NULL) {
						TRACE("delete %d\n", en->ID);
						World::getInstance()->killByID(en->ID);
					}else
						TRACE("ID not found\n");
				}
				else {
					int x = (int)LButtonDownPoint.x / 50;
					int y = (int)LButtonDownPoint.y / 50;
					if (World::getInstance()->getLocationItem(x*50, y*50) == 1)
						return;
					switch (World::getInstance()->spawningEntityType) {
					case EntityTypes::GoldMine:
						World::getInstance()->spawnResaurce(EntityTypes::GoldMine, LButtonDownPoint);
						break;
					case EntityTypes::Stone:
						World::getInstance()->spawnResaurce(EntityTypes::Stone, LButtonDownPoint);
						break;
					case EntityTypes::Tree:
						World::getInstance()->spawnResaurce(EntityTypes::Tree, LButtonDownPoint);
						break;
					case EntityTypes::Sheep:

						break;
					}
				}
			}
		}
	}

	void CGameStateMapEditor::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		World::getInstance()->isSpawningEntity = false;
		World::getInstance()->isEditingMap = 0;
	}

	void CGameStateMapEditor::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateMapEditor::OnShow()
	{
		World::getInstance()->OnShow();
		World::getInstance()->UnitOnShow();
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//

		//
		//  貼上背景圖、撞擊數、球、擦子、彈跳的球
		//
		GUI::getInstance()->onShow();
	}
}
#include "World.h"

void World::initMap() {
	int resource[3][3] = { {1,0,0},
							{0,1,0 },
							{0,0,1} };
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			int a = i / 40;
			int b = j / 40;
			map[i][j] = resource[a][b];
		}
	}
}
World::World() {
	initMap();
	isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	sx = sy = 50 * 50; //�ù��y��
}

int World::getLocationItem(int x, int y) {
	int GX = x / 50;
	int GY = y / 50;
	return map[GY][GX];
}

void World::OnShow() {
	for (int i = -1; i <= 26; i++) { //�ù����26��*15����ɹw���@��
		for (int j = -1; j <= 15; j++) {
			int MX = i * 50 - sx % 50;//���o�ù��I�y��
			int MY = j * 50 - sy % 50;
			int GX = i + sx / 50;//���o�a�ϤW����y��
			int GY = j + sy / 50;
			switch (map[GY][GX])
			{
			case GRASS:
				grass.SetTopLeft(MX, MY);
				grass.ShowBitmap();
				break;
			case RIVER:
				river.SetTopLeft(MX, MY);
				river.ShowBitmap();
				break;
			default:
				break;
			}
		}
	}
}
void World::onMove() {
	if (isMovingDown == true) {
		if ((sy + 5) > ((120 * 50) - (15 * 50))) {
			sy = 120 * 50 - 15 * 50;
		}
		else {
			sy += 5;
		}
	}
	if (isMovingUp == true) {
		if (sy - 5 < 50) {
			sy = 50;
		}
		else {
			sy -= 5;
		}
	}
	if (isMovingLeft == true) {
		if (sx - 5 < 50) {
			sx = 50;
		}
		else {
			sx -= 5;
		}
	}
	if (isMovingRight == true) {
		if ((sx + 5) > (120 * 50 - 26 * 50)) {
			sx = 120 * 50 - 30 * 50;
		}
		else {
			sx += 5;
		}
	}
}

void World::UnitOnMove() {
	for (int i = 0; i < unit.size(); i++) {
		unit[i].onMove();
	}
}

void World::UnitOnShow() {
	for (int i = 0; i < unit.size(); i++) {
		if (isOnScreen(unit[i].pointX, unit[i].pointY)) {
			unit[i].onShow(GlobalX2ScreenX(unit[i].pointX), GlobalY2ScreenY(unit[i].pointY));
		}
	}
}

bool World::isOnScreen(int x,int y) {
	if (x >= sx && x <= sx + 26 * 50) {
		if (y >= sy && y <= sy + 15 * 50) {
			return true;
		}
	}
	return false;
}

void World::moveScreenUp(bool state) {
	isMovingUp = state;
}

void World::moveScreenDown(bool state) {
	isMovingDown = state;
}

void World::moveScreenLeft(bool state) {
	isMovingLeft = state;
}

void World::moveScreenRight(bool state) {
	isMovingRight = state;
}

int World::ScreenX2GlobalX(int x) {
	return x + sx;
}

int World::ScreenY2GlobalY(int y) {
	return y + sy;
}

int World::getScreenX() {
	return sx;
}

int World::getScreenY() {
	return sy;
}

int World::GlobalX2ScreenX(int x) {
	return x - sx;
}

int World::GlobalY2ScreenY(int y) {
	return y - sy;
}

void World::LoadBitMap() {
	grass.LoadBitmap(IDB_GRASS);
	river.LoadBitmap(IDB_GOLD);
}

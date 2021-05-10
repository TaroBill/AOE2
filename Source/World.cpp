#include "World.h"

World* World::getInstance()
{
	if (instance==nullptr)
	{
		instance = new World();
	}
	return instance;
}



void World::initMap() {
	int resource[10][10] = { {1,1,1,0,0,0,0,1,1,1},
							 {1,1,0,0,0,0,0,0,1,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {0,0,0,0,0,0,0,0,0,0},
							 {0,0,0,0,0,0,0,0,0,0},
							 {0,0,0,0,0,1,0,0,0,0},
							 {0,0,0,0,0,0,0,0,0,0},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,1,0,0,0,0,0,0,1,1},
							 {1,1,1,0,0,0,0,1,1,1} };
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			int a = i / 12;
			int b = j / 12;
			map[i][j] = resource[a][b];
		}
	}
}
World::World() {
	initMap();
	isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	sx = sy = 50 * 50; //螢幕座標

}

World::~World() {
	for (unsigned int i = 0; i < unit.size(); i++) {
		delete unit[i];
	}
	unit.clear();

}

int World::getLocationItem(int x, int y) {
	int GX = x / 50;
	int GY = y / 50;
	return map[GY][GX];
}

void World::OnShow() {
	for (int i = -1; i <= SIZE_X / 50 + 1; i++) { //螢幕顯示40格*22格邊界預載一格
		for (int j = -1; j <= SIZE_Y / 50 + 1; j++) {
			int MX = i * 50 - sx % 50;//取得螢幕點座標
			int MY = j * 50 - sy % 50;
			int GX = i + sx / 50;//取得地圖上的格座標
			int GY = j + sy / 50;
			if (map[GY][GX] != GRASS && map[GY][GX] != RIVER)
				continue;
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
	if (World::getInstance()->isSpawningEntity) {
		//TRACE("Mouse monitor Location: (%d, %d)\n", mouseLocation.x, mouseLocation.y);
		World::getInstance()->spawningEntityBitmap.SetTopLeft(mouseLocation.x, mouseLocation.y);
		World::getInstance()->spawningEntityBitmap.ShowBitmap();
	}
}
void World::onMove() {
	if (isMovingDown == true) {
		if ((sy + 5) > ((120 * 50) - (SIZE_Y))) {
			sy = 120 * 50 - SIZE_Y;
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
		if ((sx + 5) > (120 * 50 - SIZE_X)) {
			sx = 120 * 50 - SIZE_X;
		}
		else {
			sx += 5;
		}
	}
}

void World::UnitOnMove() {
	for (unsigned int i = 0; i < unit.size(); i++) {
		unit[i]->onMove();
	}
}

void World::UnitOnShow() {
	for (unsigned int i = 0; i < unit.size(); i++) {
		if (isOnScreen(unit[i]->point.x, unit[i]->point.y)) {
			unit[i]->onShow(GlobalX2ScreenX(unit[i]->point.x), GlobalY2ScreenY(unit[i]->point.y));
		}
	}
	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		if (isOnScreen(EnemyUnit[i]->point.x, EnemyUnit[i]->point.y)) {
			EnemyUnit[i]->onShow(GlobalX2ScreenX(EnemyUnit[i]->point.x), GlobalY2ScreenY(EnemyUnit[i]->point.y));
		}
	}
}

bool World::isOnScreen(int x,int y) {
	if (x >= sx && x <= sx + SIZE_X) {
		if (y >= sy && y <= sy + SIZE_Y) {
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

CPoint World::Screen2Global(CPoint p) {
	return CPoint(p.x + sx, p.y + sy);
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

void World::LoadBitmap() {
	grass.LoadBitmap(IDB_GRASS);
	river.LoadBitmap(IDB_WaterBig);
	spwan(EntityTypes::Villager, 3000, 3000);
}

void World::setScreenLocation(int x, int y) {
	sx = x;
	if (sx > (120 * 50 - SIZE_X)) {
		sx = 120 * 50 - SIZE_X;
	}
	sy = y;
	if (sy > (120 * 50 - SIZE_Y)) {
		sy = 120 * 50 - SIZE_Y;
	}
}

void World::setScreenLocation(CPoint point) {
	sx = point.x;
	if (sx > (120 * 50 - SIZE_X)) {
		sx = 120 * 50 - SIZE_X;
	}
	sy = point.y;
	if (sy > (120 * 50 - SIZE_Y)) {
		sy = 120 * 50 - SIZE_Y;
	}
}

void World::spwan(EntityTypes ET, int x, int y) {
	unit.push_back(entityFactory.SpawnEntity(ET, x, y));
	calculatePopulation();
}

void World::spwan(EntityTypes ET, CPoint p) {
	unit.push_back(entityFactory.SpawnEntity(ET, p));
	calculatePopulation();
}

void World::calculatePopulation() {
	int total = 0;
	for (unsigned int i = 0; i < unit.size(); i++) {
		if (typeid(*unit[i]) == typeid(Unit::Villager)) {
			total++;
		}
	}
	player.population = total;
}


vector<Unit::Entity*> World::listAllEntityInRange(CPoint p1, CPoint p2) {
	vector<Unit::Entity*> output;
	for (unsigned int i = 0; i < unit.size(); i++) {
		if ((unit[i]->point.x >= p1.x && unit[i]->point.x <= p2.x && unit[i]->point.y >= p1.y && unit[i]->point.y <= p2.y) || (unit[i]->point.x >= p2.x && unit[i]->point.x <= p1.x && unit[i]->point.y >= p2.y && unit[i]->point.y <= p1.y) ||
			(unit[i]->point.x >= p2.x && unit[i]->point.x <= p1.x && unit[i]->point.y >= p1.y && unit[i]->point.y <= p2.y) || (unit[i]->point.x >= p1.x && unit[i]->point.x <= p2.x && unit[i]->point.y >= p2.y && unit[i]->point.y <= p1.y)) {
			output.push_back(unit[i]);
			//TRACE("Entity: %d\n", i);
		}
	}
	return output;
}

void World::moveEntityToLocation(vector<Unit::Entity*> allEntity, CPoint p) {
	/*
	for (unsigned int i = 0; i < allEntity.size(); i++) {
		allEntity[i]->GetComponent<Unit::Navigator>()->FindPath(Screen2Global(p));
	}
	*/
}

void World::spawningEntity(int bitmap) {
	CMovingBitmap MB;
	MB.LoadBitmap(bitmap, RGB(255, 255, 255));
	spawningEntityBitmap = MB;
	switch (bitmap){
	case IDB_VILLAGER000:
		spawningEntityType = EntityTypes::Villager;
		break;
	default:
		break;
	}
	isSpawningEntity = true;
}

void World::spwanEnemy(EntityTypes ET, int x, int y) {
	EnemyUnit.push_back(entityFactory.SpawnEntity(ET, x, y));
}

void World::spwanEnemy(EntityTypes ET, CPoint p) {
	EnemyUnit.push_back(entityFactory.SpawnEntity(ET, p));
}

void World::LoadEnemyFromStringStream(int amount, stringstream& ss) {
	int size = EnemyUnit.size() ;
	//TRACE("Size: %d\n", amount);
	if (amount > size) {
		for (int i = 0; i < amount - size; i++) {
			spwanEnemy(EntityTypes::Villager, 0, 0);
		}
	}
	else if (amount < size) {
		
	}
	for (int i = 0; i < amount; i++) {
		dynamic_cast<Unit::Villager*>(EnemyUnit.at(i))->deSerialize(ss);
	}
}
World* World::instance;
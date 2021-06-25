#include "World.h"
#include "GUI/GUI.h"
#include "socket/NetWork.h"
#include "GUI/Frames/EntityDataFrame.h"
#include "mygame.h"
#include "audio.h"
World* World::getInstance()
{
	return &instance;
}



void World::initMap() {
	clearAllEntities();
	fstream file;      //宣告fstream物件
	file.open("..//Map//Map.txt", ios::in);
	if (!file)
		TRACE("File can't be opened\n");

	char* pBuf = new char[50000];
	CString strData;
	stringstream ss;
	file.read(pBuf, 50000);

	strData = pBuf;
	ss << strData;

	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			ss >> map[i][j];
			buildingMap[i][j] = 0;
			//TRACE("%d, %d :  %d\n", j, i, map[i][j]);
		}
	}
	UINT resaurceSize;
	ss >> resaurceSize;
	TRACE("Size: %d\n", resaurceSize);
	for (UINT i = 0; i < resaurceSize; i++) {
		int ET;
		ss >> ET;//Entity type
		int x, y;   //Entity Location
		ss >> x >> y;
		World::getInstance()->spawnResaurce(static_cast<EntityTypes>(ET), x, y);
	}

	delete[] pBuf;
	file.close();

}

void World::initMapFromNet(stringstream& ss) {
	clearAllEntities();

	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			ss >> map[i][j];
			buildingMap[i][j] = 0;
			//TRACE("%d, %d :  %d\n", j, i, map[i][j]);
		}
	}
	UINT resaurceSize;
	ss >> resaurceSize;
	TRACE("Size: %d\n", resaurceSize);
	for (UINT i = 0; i < resaurceSize; i++) {
		int ET;
		ss >> ET;//Entity type
		int x, y;   //Entity Location
		ss >> x >> y;
		World::getInstance()->spawnResaurce(static_cast<EntityTypes>(ET), x, y);
	}


}

World::World() {
	isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	sx = sy = 50 * 50; //螢幕座標

}

World::~World() {
	clearAllEntities();
	TRACE("~World()\n");
}

void World::clearAllEntities() {
	for (unsigned int i = 0; i < unit.size(); i++) {
		delete unit[i];
	}
	unit.clear();
	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		delete EnemyUnit[i];
	}
	EnemyUnit.clear();
	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		delete ResaurceUnit[i];
	}
	ResaurceUnit.clear();
}

int World::getLocationItem(int x, int y) {
	int GX = x / 50;
	int GY = y / 50;
	return map[GY][GX] || buildingMap[GY][GX];
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

	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		ResaurceUnit[i]->onMove();
	}

	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		EnemyUnit[i]->onMove();
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

	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		if (isOnScreen(ResaurceUnit[i]->point.x, ResaurceUnit[i]->point.y)) {
			ResaurceUnit[i]->onShow(GlobalX2ScreenX(ResaurceUnit[i]->point.x), GlobalY2ScreenY(ResaurceUnit[i]->point.y));
		}
	}
	if (isSpawningEntity) {
		//TRACE("Mouse monitor Location: (%d, %d)\n", mouseLocation.x, mouseLocation.y);
		spawningEntityBitmap.SetTopLeft(mouseLocation.x, mouseLocation.y);
		spawningEntityBitmap.ShowBitmap();
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

void World::spawn(EntityTypes ET, int x, int y) {
	Unit::Entity* en = entityFactory.SpawnEntity(ET, x, y);
	en->playerId = 0;						//0是自己1是敵人-1是資源
	unit.push_back(en);
	calculatePopulation();
	if (isInitingWorld)
		return;
	stringstream ss;
	ss << "spawn" << " ";
	ss << ET << " ";
	ss << x << " " << y;
	NetWork::getInstance()->SendData(ss);
}

void World::spawn(EntityTypes ET, CPoint p) {
	Unit::Entity* en = entityFactory.SpawnEntity(ET, p);
	en->playerId = 0;						//0是自己1是敵人-1是資源
	unit.push_back(en);
	calculatePopulation();
	if (isInitingWorld)
		return;
	stringstream ss;
	ss << "spawn" << " ";
	ss << ET << " ";
	ss << p.x << " " << p.y;
	NetWork::getInstance()->SendData(ss);
}

void World::spawnEnemy(EntityTypes ET, int x, int y) {
	Unit::Entity* en = entityFactory.SpawnEntity(ET, x, y);
	en->playerId = 1;						//0是自己1是敵人-1是資源
	EnemyUnit.push_back(en);
}

void World::spawnEnemy(EntityTypes ET, CPoint p) {
	Unit::Entity* en = entityFactory.SpawnEntity(ET, p);
	en->playerId = 1;						//0是自己1是敵人-1是資源
	EnemyUnit.push_back(en);
}

void World::spawnResaurce(EntityTypes ET, int x, int y) {
	int tileX = x / 50;
	int tileY = y / 50;
	if (buildingMap[tileY][tileX] == 1)
		return;
	Unit::Entity* en = entityFactory.SpawnEntity(ET, tileX * 50, tileY * 50);
	en->playerId = -1;						//0是自己1是敵人-1是資源
	ResaurceUnit.push_back(en);
}

void World::spawnResaurce(EntityTypes ET, CPoint p) {
	int tileX = p.x / 50;
	int tileY = p.y / 50;
	if (buildingMap[tileY][tileX] == 1)
		return;
	Unit::Entity* en = entityFactory.SpawnEntity(ET, tileX * 50, tileY * 50);
	en->playerId = -1;						//0是自己1是敵人-1是資源
	ResaurceUnit.push_back(en);				//0是自己1是敵人-1是資源
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

Unit::Entity* World::getNearestEntity(CPoint point) {
	Unit::Entity* output = NULL;
	for (unsigned int i = 0; i < unit.size(); i++) {
		if (unit[i]->HitBox.PtInRect(point)){
			output = unit[i];
			return output;
		}
	}

	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		if (EnemyUnit[i]->HitBox.PtInRect(point)) {
			output = EnemyUnit[i];
			return output;
		}
	}

	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		if (ResaurceUnit[i]->HitBox.PtInRect(point)) {
			output = ResaurceUnit[i];
			return output;
		}
	}
	return output;

}

void World::moveEntityToLocation(vector<Unit::Entity*> allEntity, CPoint p) {
	if (allEntity.size() < 1)
		return;
	if (allEntity[0]->playerId != 0)
		return;
	stringstream ss;// command = settarget <amount> <id id id ... id> x y
	ss << "settarget" << " ";
	ss << allEntity.size() << " ";
	for (unsigned int i = 0; i < allEntity.size(); i++)
	{
		ss << allEntity[i]->ID << " ";
		allEntity[i]->SetTarget(p, allEntity);
	}
	ss << p.x << " " << p.y;
	NetWork::getInstance()->SendData(ss);
	
}

void World::spawningEntity(int bitmap) {
	CMovingBitmap MB;
	MB.LoadBitmap(bitmap, RGB(255, 255, 255));
	spawningEntityBitmap = MB;
	switch (bitmap){
	case IDB_VILLAGER000:
		spawningEntityType = EntityTypes::Villager;
		isEditingMap = 0;
		break;
	case IDB_TOWNCENTER_ICON:
		spawningEntityType = EntityTypes::TownCenter;
		isEditingMap = 0;
		break;
	case IDB_GOLD:
		spawningEntityType = EntityTypes::GoldMine;
		isEditingMap = 0;
		break;
	case IDB_STONE:
		spawningEntityType = EntityTypes::Stone;
		isEditingMap = 0;
		break;
	case IDB_SHEEP:
		spawningEntityType = EntityTypes::Sheep;
		isEditingMap = 0;
		break;
	case IDB_TREE:
		spawningEntityType = EntityTypes::Tree;
		isEditingMap = 0;
		break;
	case IDB_GRASS:
		isEditingMap = 1;
		break;
	case IDB_WaterBig:
		isEditingMap = 2;
		break;
	case IDB_DESTROY_BUTTON:
		isEditingMap = 3;
		break;
	default:
		break;
	}
	isSpawningEntity = true;
}

void World::LoadEnemyFromStringStream(int amount, stringstream& ss) {
	int size = EnemyUnit.size();
	//TRACE("Size: %d\n", amount);
	if (size != amount)
		return;
	for (int i = 0; i < amount; i++) {
		string erase;
		int ET;
		ss >> erase >> ET;
		if (ET == static_cast<int>(EntityTypes::Villager)) {
			dynamic_cast<Unit::Villager*>(EnemyUnit.at(i))->deSerialize(ss);
		}
		else if (ET == static_cast<int>(EntityTypes::TownCenter)) {
			dynamic_cast<Unit::TownCenter*>(EnemyUnit.at(i))->deSerialize(ss);
		}
		else {	//略過出問題的資料
			TRACE("ERROR on update Enemy");
			TRACE("ET = %d, %s\n", ET, ss.str().c_str());
			ss >> erase;
			while (erase != "End") {
				ss >> erase;
			}
			break;
		}
	}
}

void World::LoadUnitFromStringStream(int amount, stringstream& ss) {
	int size = unit.size();
	TRACE("Size: %d %d\n", amount, size);
	if (size != amount)
		return;
	for (int i = 0; i < amount; i++) {
		string erase;
		int ET;
		ss >> erase;
		TRACE("erase: %s\n", erase.c_str());
		ss >> ET;
		TRACE("ER: %d\n", ET);
		if (ET == static_cast<int>(EntityTypes::Villager)) {
			dynamic_cast<Unit::Villager*>(unit.at(i))->deSerialize(ss);
		}
		else if (ET == static_cast<int>(EntityTypes::TownCenter)) {
			dynamic_cast<Unit::TownCenter*>(unit.at(i))->deSerialize(ss);
		}
		else {//略過出問題的資料
			TRACE("ERROR on update Unit");
			ss >> erase;
			TRACE("ET = %d, %s\n", ET, erase.c_str());
			ss >> erase;
			TRACE("erase: %s\n", erase.c_str());
			break;
		}
	}
}

void World::LoadResourceFromStringStream(int amount, stringstream& ss) {
	int size = ResaurceUnit.size();
	if (size != amount)
		return;
	//TRACE("Size: %d\n", amount);
	for (int i = 0; i < amount; i++) {
		string erase;
		int ET;
		ss >> erase >> ET;
		if (ET == static_cast<int>(EntityTypes::GoldMine)) {
			dynamic_cast<Unit::Mine*>(ResaurceUnit.at(i))->deSerialize(ss);
		}
		else if (ET == static_cast<int>(EntityTypes::Stone)) {
			dynamic_cast<Unit::Stone*>(ResaurceUnit.at(i))->deSerialize(ss);
		}
		else if (ET == static_cast<int>(EntityTypes::Sheep)) {
			dynamic_cast<Unit::Sheep*>(ResaurceUnit.at(i))->deSerialize(ss);
		}
		else if (ET == static_cast<int>(EntityTypes::Tree)) {
			dynamic_cast<Unit::Tree*>(ResaurceUnit.at(i))->deSerialize(ss);
		}
		else {	//略過出問題的資料
			TRACE("ERROR on update Resource");
			TRACE("ET = %d, %s\n", ET, ss.str().c_str());
			ss >> erase;
			while (erase != "End") {
				ss >> erase;
			}
			break;
		}
	}
}
void World::packUnit(vector<Unit::Entity*> entitys, int type) {
	stringstream cmd2;
	if(type == 1)
		cmd2 << "UpdateEntity1 ";
	else if(type == 2)
		cmd2 << "UpdateEntity2 ";
	else if (type ==3)
		cmd2 << "UpdateEntity3 ";
	cmd2 << entitys.size() << " ";
	//TRACE("%s\n", cmd2.str().c_str());
	for (unsigned int i = 0; i < entitys.size(); i++) {
		EntityTypes ET = entitys.at(i)->entityType;
		switch (ET) {
		case EntityTypes::Villager:
			dynamic_cast<Unit::Villager*>(entitys.at(i))->Serialize(cmd2);
			break;
		case EntityTypes::GoldMine:
			dynamic_cast<Unit::Mine*>(entitys.at(i))->Serialize(cmd2);
			break;
		case EntityTypes::Sheep:
			dynamic_cast<Unit::Sheep*>(entitys.at(i))->Serialize(cmd2);
			break;
		case EntityTypes::Stone:
			dynamic_cast<Unit::Stone*>(entitys.at(i))->Serialize(cmd2);
			break;
		case EntityTypes::Tree:
			dynamic_cast<Unit::Tree*>(entitys.at(i))->Serialize(cmd2);
			break;
		case EntityTypes::TownCenter:
			dynamic_cast<Unit::TownCenter*>(entitys.at(i))->Serialize(cmd2);
			break;
		}
	}
	NetWork::getInstance()->SendData(cmd2);
}

Unit::Entity* World::getEntityByID(unsigned int ID) {
	for (unsigned int i = 0; i < unit.size(); i++) {
		if (unit[i]->ID == ID) 
			return unit[i];
	}

	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		if (EnemyUnit[i]->ID == ID)
			return EnemyUnit[i];
	}

	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		if (ResaurceUnit[i]->ID == ID)
			return ResaurceUnit[i];
	}
	return NULL;
}

vector<Unit::Entity*> World::getEntityByID(vector<UINT> id) {
	vector<Unit::Entity*> output;
	for (unsigned int i = 0; i < unit.size(); i++) {
		for (unsigned int j = 0; j < id.size(); j++) {
			if (unit[i]->ID == id[j]) {
				output.push_back(unit[i]);
			}
		}
	}

	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		for (unsigned int j = 0; j < id.size(); j++) {
			if (EnemyUnit[i]->ID == id[j]) {
				output.push_back(EnemyUnit[i]);
			}
		}
	}

	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		for (unsigned int j = 0; j < id.size(); j++) {
			if (ResaurceUnit[i]->ID == id[j]) {
				output.push_back(ResaurceUnit[i]);
			}
		}
	}
	return output;
}

void World::killByID(UINT ID) {

	if (GUI::getInstance()->frames.size() > 2) {

		for (unsigned int i = 0; i < LE.size(); i++) {
			if (LE[i]->ID == ID) {
				LE.erase(LE.begin() + i);
			}
		}

		dynamic_cast<EntityDataFrame*>(GUI::getInstance()->frames.at(2))->loadEntitysBitmap(World::getInstance()->LE);
	}

	for (unsigned int i = 0; i < unit.size(); i++) {
		if (unit[i]->ID == ID) {
			if (this->isOnScreen(unit[i]->point.x, unit[i]->point.y) && dynamic_cast<Unit::Villager*>(unit[i])) {
				CAudio::Instance()->Play(AUDIO_VILLAGERDEATH, false);
			}
			delete unit[i];
			unit.erase(unit.begin() + i);
			calculatePopulation();
			stringstream command;
			command << "killEntity" << " ";
			command << ID;
			NetWork::getInstance()->SendData(command);
			calculatePopulation();
			return;
		}
	}

	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		if (EnemyUnit[i]->ID == ID) {
			if (this->isOnScreen(EnemyUnit[i]->point.x, EnemyUnit[i]->point.y) && dynamic_cast<Unit::Villager*>(EnemyUnit[i])) {
				CAudio::Instance()->Play(AUDIO_VILLAGERDEATH, false);
			}
			delete EnemyUnit[i];
			EnemyUnit.erase(EnemyUnit.begin() + i);
			if (NetWork::getInstance()->isConnectedToClient) {
				stringstream command;
				command << "killEntity" << " ";
				command << ID;
				NetWork::getInstance()->SendData(command);
				return;
			}
			else {
				int total = 0;
				for (unsigned int j = 0; j < EnemyUnit.size(); j++) {
					if (typeid(*EnemyUnit[j]) == typeid(Unit::Villager)) {
						total++;
					}
				}
				if (total == 0) {
					World::getInstance()->isWin = true;
					game_framework::CGame::Instance()->SetGameState(GAME_STATES::GAME_STATE_OVER);
				}
				return;
			}
		}
	}

	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		if (ResaurceUnit[i]->ID == ID) {
			delete ResaurceUnit[i];
			ResaurceUnit.erase(ResaurceUnit.begin() + i);
			stringstream command;
			command << "killEntity" << " ";
			command << ID;
			NetWork::getInstance()->SendData(command);
			return;
		}
	}



	TRACE("ID: %d Not Found\n", ID);
}

void World::initWorld() {
	for (unsigned int i = 0; i < unit.size(); i++) {
		delete unit[i];
	}
	unit.clear();
	for (unsigned int i = 0; i < EnemyUnit.size(); i++) {
		delete EnemyUnit[i];
	}
	EnemyUnit.clear();
	if (NetWork::getInstance()->isServer()) {//順序要一樣確保初始ID相同
		World::getInstance()->cheaterMode = true;
		setScreenLocation(1000, 2500);
		spawn(EntityTypes::Villager, 1500, 2800);
		spawn(EntityTypes::Villager, 1600, 2900);
		spawn(EntityTypes::Villager, 1500, 2950);
		spawn(EntityTypes::TownCenter, 1600, 3000);
		spawnEnemy(EntityTypes::Villager, 4000, 2800);
		spawnEnemy(EntityTypes::Villager, 4100, 2900);
		spawnEnemy(EntityTypes::Villager, 4000, 2950);
		spawnEnemy(EntityTypes::TownCenter, 4100, 3000);
		World::getInstance()->cheaterMode = false;
	}
	else {//順序要一樣確保初始ID相同
		World::getInstance()->cheaterMode = true;
		setScreenLocation(3500, 2500);
		spawnEnemy(EntityTypes::Villager, 1500, 2800);
		spawnEnemy(EntityTypes::Villager, 1600, 2900);
		spawnEnemy(EntityTypes::Villager, 1500, 2950);
		spawnEnemy(EntityTypes::TownCenter, 1600, 3000);
		spawn(EntityTypes::Villager, 4000, 2800);
		spawn(EntityTypes::Villager, 4100, 2900);
		spawn(EntityTypes::Villager, 4000, 2950);
		spawn(EntityTypes::TownCenter, 4100, 3000);
		World::getInstance()->cheaterMode = false;
	}
	isInitingWorld = false;
}

void World::setMap(CPoint p, int type) {
	int y = p.y / 50;
	int x = p.x / 50;
	map[y][x] = type;
}

void World::save() {
	fstream file;      //宣告fstream物件

	stringstream contain;
	file.open("..//Map//Map.txt", ios::out | ios::trunc);
	if (!file)
		TRACE("File can't be opened\n");
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			contain << map[i][j] << " ";
		}
	}
	contain << ResaurceUnit.size() << " ";

	for (unsigned int i = 0; i < ResaurceUnit.size(); i++) {
		contain << ResaurceUnit.at(i)->entityType << " " << ResaurceUnit.at(i)->point.x << " " << ResaurceUnit.at(i)->point.y << " ";
	}

	string str = contain.str();
	char* output = new char[str.length() + 1];
	strcpy(output, str.c_str());
	file.write(output, str.length() + 1);
	TRACE("Saving done\n");
	file.close();
	delete[] output;
}

UINT World::checkMap() {
	fstream file;      //宣告fstream物件
	file.open("..//Map//Map.txt", ios::in);
	if (!file)
		TRACE("File can't be opened\n");

	char* pBuf = new char[50000];
	CString strData;
	stringstream ss;
	file.read(pBuf, 50000);

	strData = pBuf;
	stringstream test;
	test << strData;
	UINT total = 0;
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			int temp = 0;
			test >> temp;
			total += temp;
			//TRACE("%d, %d :  %d\n", j, i, map[i][j]);
		}
	}
	UINT resaurceSize;
	test >> resaurceSize;
	for (UINT i = 0; i < resaurceSize; i++) {
		int ET;
		test >> ET;//Entity type
		int x, y;   //Entity Location
		test >> x >> y;
		total += ET + x + y;
	}
	delete [] pBuf;
	return total;
}

World World::instance;
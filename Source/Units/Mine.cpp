#include "Mine.h"


namespace Unit
{
	Mine::Mine() {

	}

	Mine::~Mine() {

	}

	void Mine::loadBitmap() {
		State es = State::Idle;
		Direction d = Direction::Down;

		animations[es][d].AddBitmap(IDB_GOLD, RGB(255, 255, 255));
	}













}
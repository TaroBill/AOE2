#pragma once
#include <vector>
#include "Frame.h"
#include <typeinfo>


class EntityDataFrame : public Frame
{
public:
	EntityDataFrame();
	~EntityDataFrame();
	void loadBitmap() override;
	void OnShow();
	void loadEntitysBitmap(vector<Unit::Entity*>);
	void clearEntitysBitmap();
	void onMove() override;
private:
	vector<CMovingBitmap> entitys;
	Unit::Entity* showDataEntity;
};

#pragma once
#include <vector>
#include "Frame.h"


class EntityDataFrame : public Frame
{
public:
	EntityDataFrame();
	~EntityDataFrame();
	void loadBitmap() override;
	void onClicked(CPoint) override;
private:
	vector<Button*> buttons;
};

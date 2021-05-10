#pragma once
#include "./StdAfx.h"

class ID
{
protected:
private:
	static ID _instance;
public:
	
	unsigned int IDCounter;
	static ID* getInstance();
	unsigned int GetID();
	void Reset();
	ID();
	~ID();
};
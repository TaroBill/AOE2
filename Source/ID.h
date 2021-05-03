#pragma once
#include "./StdAfx.h"

class ID
{
protected:
private:

public:
	static ID* _instance;
	unsigned int IDCounter;
	static ID* getInstance();
	unsigned int GetID();
	void Reset();
	ID();
	~ID();
};
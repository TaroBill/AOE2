#pragma once
#include <vector>

class ID
{
private:
	static ID* _instance;
	unsigned int IDCounter;

public:
	static ID* getInstance();
	unsigned int GetID();
	void Reset();
	ID();
};
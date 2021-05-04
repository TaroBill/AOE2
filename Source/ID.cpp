#pragma once
#include "./StdAfx.h"
#include "./ID.h"



ID* ID::getInstance() {
	if (_instance == nullptr)
	{
		_instance = new ID();
	}
	return _instance;
};
unsigned int ID::GetID() { return IDCounter++; };
void ID::Reset() { IDCounter = 0; };
ID::ID() { IDCounter = 0; };
ID::~ID() { delete this; };
ID* ID::_instance;
#pragma once
#include "StdAfx.h"
#include "ID.h"


ID ID::_instance;

ID* ID::getInstance() {
	return &_instance;
};
unsigned int ID::GetID() { return IDCounter++; };
void ID::Reset() { IDCounter = 0; };
ID::ID() { IDCounter = 0; };
ID::~ID() {};

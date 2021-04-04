#pragma once
static enum ResourceType
{
	None,Gold, Stone, Meat, Wood
};


class GameResource
{
public:

	int n;
	ResourceType type;
	GameResource() {};
	GameResource(ResourceType type,int n)
	{
		this->type = type;
		this->n = n;
	}
};
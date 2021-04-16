#pragma once
enum class ResourceType
{
	None,Gold, Stone, Meat, Wood
};


class GameResource
{
public:

	int amount;
	ResourceType type;
	void ResetType(ResourceType rt)
	{
		amount = 0;
		type = rt;
	}
	int GetResource()
	{
		if (amount == 0)
			return 0;
		return amount--;
	}
	int GetResource(int n)
	{
		int resource = 0;
		if (n > amount)
			for (int i = 0; i < n; i++)
				resource = GetResource();
		else
			resource = n;
		return resource;
	}
	GameResource()
	{
		this->type = ResourceType::None;
		this->amount = 0;
	};
	GameResource(ResourceType type, int n)
	{
		this->type = type;
		this->amount = n;
	}
};
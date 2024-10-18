#pragma once
#include "BaseItem.h"
#include <string>
class HealthPotion : public BaseItem
{
public:
	HealthPotion();
	~HealthPotion();
	void Use();
	int GetItemID() { return ItemID; };
	std::string GetItemName() { return ItemName; };
	bool GetIsStackable() { return bIsStackable; };
	int GetStackSize() { return stackSize; };
private:
	int healthAmount = 20; // Amount of health restored by the potion
	int stackSize = 5;     // Maximum number of potions in a stack
	int ItemID = 0;
	std::string ItemName = "Health Potion";
	bool bIsStackable = true;
};


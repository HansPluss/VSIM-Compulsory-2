#pragma once
#include "BaseItem.h"

// Forward declaration to avoid circular dependency
class Player;

class SpeedPotion : public BaseItem
{
public:
    SpeedPotion(Player& player);
    ~SpeedPotion();

    void Use();
    int GetItemID() { return ItemID; };
    std::string GetItemName() { return ItemName; };
    bool GetIsStackable() { return bIsStackable; };
    int GetStackSize() { return stackSize; };

private:
    int speedAmount = 10; // Amount of speed boost provided by the potion
    int stackSize = 5;    // Maximum number of potions in a stack
    int ItemID = 1;
    std::string ItemName = "Speed Potion";
    bool bIsStackable = true;
    Player& ref;
};

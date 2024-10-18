#include "SpeedPotion.h"
#include "Player.h" // Include Player here since we use it in the implementation
#include <iostream>

SpeedPotion::SpeedPotion(Player& player)
    : ref(player)
{
}

SpeedPotion::~SpeedPotion()
{
}

void SpeedPotion::Use()
{
    std::cout << "Using speed potion..." << std::endl;
    ref.SetSpeed(ref.GetSpeed() + speedAmount);
}

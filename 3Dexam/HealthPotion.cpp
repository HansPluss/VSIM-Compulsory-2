#include "HealthPotion.h"
#include <iostream>
HealthPotion::HealthPotion()
{
}

HealthPotion::~HealthPotion() 
{
}

void HealthPotion::Use()
{
	std::cout << "Using health potion..." << std::endl;
	// Restore health
//playerHealth += healthAmount;
//playerHealth = std::min(playerHealth, maxHealth);
}

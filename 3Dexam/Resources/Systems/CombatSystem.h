#pragma once
#include "../../Entity.h"

class EntityManager;
class CombatSystem {
public:
	CombatSystem();
	void Update(float deltaTime);
	void DealDamage(Entity& attacker, Entity& defender, const std::shared_ptr<EntityManager>& manager);
	
private:
	float damageCooldown;  // Time between damage applications
	float lastDamageTime;  // Tracks time since last damage
};
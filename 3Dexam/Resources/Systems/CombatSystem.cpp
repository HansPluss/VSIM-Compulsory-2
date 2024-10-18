#include "CombatSystem.h"
#include "../../Enemy.h"
#include "../../EntityManager.h"
CombatSystem::CombatSystem()
{
	damageCooldown = 0.5f;
	lastDamageTime = 0.0f;
}

void CombatSystem::Update(float deltaTime)
{
	lastDamageTime += deltaTime;
}


void CombatSystem::DealDamage(Entity& attacker, Entity& defender, const std::shared_ptr<EntityManager>& manager)
{
	auto* damageComponent = attacker.GetComponent<DamageComponent>();
	auto* healthComponent = defender.GetComponent<HealthComponent>();
	if (lastDamageTime >= damageCooldown) {

		healthComponent->health -= damageComponent->damage;
		std::cout << "Health: " << healthComponent->health << std::endl;
		lastDamageTime = 0.0f;
	}
	
	
}

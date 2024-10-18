#pragma once
#include "Entity.h"
#include "Component.h"
#include "PhysicsSystem.h"
class Projectile : public Entity {
public:
	Projectile() {
		AddComponent<PositionComponent>();
		AddComponent<RenderComponent>(glm::vec3(0.0f), glm::vec3(1.0f), "sphere");
		AddComponent<VelocityComponent>();
		AddComponent<AccelerationComponent>();
		AddComponent<DamageComponent>();
		lifetime = 5.0f;
		timer = 0.0f;
	}
	void MoveProjectile(Entity& basePosition, const std::shared_ptr<PhysicsSystem>& physicsSystem) {
		auto* position = basePosition.GetComponent<PositionComponent>();
		GetComponent<PositionComponent>()->position = position->position;

		physicsSystem->ApplyForce(*this, glm::vec3(1.0f));

	}
	void DespawnTimer(float deltatime) {
		timer += deltatime;
		if (timer >= lifetime)
			isMarkedForDeletion = true;
	}
private:
	float lifetime;
	float timer;

};
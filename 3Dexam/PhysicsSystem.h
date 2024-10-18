#pragma once

#include "RigidBody.h"
#include "Entity.h"
class PhysicsSystem {
public:
	RigidBody rigidBody;
	void Update(Entity& entity, float deltaTime) {
		if (entity.isMarkedForDeletion) return;
		auto* positionComponent = entity.GetComponent<PositionComponent>();
		auto* velocityComponent = entity.GetComponent<VelocityComponent>();
		auto* accelerationComponent = entity.GetComponent<AccelerationComponent>();

		if (positionComponent && velocityComponent && accelerationComponent) {

			rigidBody.Update(*positionComponent, *velocityComponent, *accelerationComponent, deltaTime);
		}
	}
	void UpdatePositions(PositionStorage& storage, AccelerationStorage& aStorage, VelocityStorage& vStorage, std::vector<Entity*>& entityList, float deltatime) {

		for (size_t i = 0; i < entityList.size(); ++i) {

			// Access the entity via pointer in the entityList
			if (entityList[i]->GetComponent<PositionComponent>() && entityList[i]->GetComponent<VelocityComponent>() && entityList[i]->GetComponent<AccelerationComponent>()) {
				// Update the PositionComponent with the new position
				rigidBody.DODUpdate(storage, aStorage, vStorage, entityList, deltatime);
			}
		}
	}
	void ApplyForce(Entity& entity, glm::vec3 force) {
		
		if (entity.isMarkedForDeletion) return;
		auto* accelerationComponent = entity.GetComponent<AccelerationComponent>();
		if (accelerationComponent) {
			
			rigidBody.ApplyForce(*accelerationComponent, force);
		}
	}
	glm::vec3 CalculateGravity(float inclineAngle, glm::vec3 slopeVector, glm::vec3 normal) {
		

		return rigidBody.CalculateGravity(inclineAngle,slopeVector,normal);
	}

};
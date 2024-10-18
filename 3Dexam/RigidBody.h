#pragma once
#include "glm/glm.hpp"
#include "Component.h"
#include "Entity.h"
class RigidBody
{
private:

	float gravity = -9.81f;
	float mass = 1.0f;
	glm::vec3 velocity; 
	glm::vec3 Acceleration;
	glm::vec3 position;
public: 

	glm::vec3 CalculateGravity(float inclineAngle, glm::vec3 slopeVector, glm::vec3 normal);
	void ApplyForce(AccelerationComponent& aComponent, glm::vec3 force);
	void Update(PositionComponent& position, VelocityComponent& velocity, AccelerationComponent& acceleration, float deltaTime);
	void DODUpdate(PositionStorage& storage,AccelerationStorage& aStorage, VelocityStorage& vStorage,std::vector<Entity*>& entityList, float deltatime);
	
};


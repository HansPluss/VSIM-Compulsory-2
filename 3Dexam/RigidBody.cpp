#include "RigidBody.h"
glm::vec3 RigidBody::CalculateGravity(float inclineAngle, glm::vec3 slopeVector, glm::vec3 normal)
{
    // Downward gravity force
    
    slopeVector = glm::normalize(slopeVector);
    
    
    glm::vec3 gravityForce(0.0f, gravity, 0.0f);

    // Calculating normal force (perpendicular to the slope)
    float normalForceMagnitude = glm::dot(gravityForce, normal); // Gravity along the normal
    glm::vec3 normalForce = normal * normalForceMagnitude;

    // Calculating gravitational force acting parallel to the slope (slope vector)
    glm::vec3 gravityParallel = gravityForce - normalForce; // Parallel force along the slope

    // Projecting this parallel gravity onto the slope's horizontal direction (slopeVector)
    glm::vec3 gravityAlongSlope = glm::dot(gravityParallel, slopeVector) * slopeVector;

    // Applying the force along the slope
    return gravityAlongSlope;
}

void RigidBody::ApplyForce(AccelerationComponent& aComponent, glm::vec3 force)
{
    aComponent.acceleration += force / 1.0f; // Mass to be added 
}

void RigidBody::Update(PositionComponent& pComponent, VelocityComponent& vComponent, AccelerationComponent& aComponent, float deltaTime)
{
    //updates the position of the entity
    vComponent.velocity += aComponent.acceleration * deltaTime;
    pComponent.position += vComponent.velocity * deltaTime;               
    aComponent.acceleration = glm::vec3(0.0f, gravity, 0.0f);
}

void RigidBody::DODUpdate(PositionStorage& storage, AccelerationStorage& aStorage, VelocityStorage& vStorage, std::vector<Entity*>& entityList, float deltaTime) {
    const float timeScale = 0.5f; // Scale down time to slow things down
    const float damping = 0.98f;  // Damping to slow down velocities
    const float maxVelocity = 10.0f;  // Cap the velocity for stability

    // Adjust deltaTime for time scale
    float timeStep = deltaTime * timeScale;

    for (auto* entity : entityList) {
        int entityID = entity->GetId();  // Assuming each entity has an ID

        // Ensure the entity has all the necessary components
        if (entity->GetComponent<PositionComponent>() && entity->GetComponent<VelocityComponent>() && entity->GetComponent<AccelerationComponent>()) {
            // Update velocity using acceleration
            glm::vec3& velocity = vStorage.GetVelocityByEntityID(entityID);
            glm::vec3& acceleration = aStorage.GetAccelerationByEntityID(entityID);

            velocity += acceleration * timeStep;

          

            // Update position using velocity
            glm::vec3& position = storage.GetPositionByEntityID(entityID);
            position += velocity * timeStep;

            // Apply gravity
            acceleration = glm::vec3(0.0f, gravity, 0.0f);

            // Apply friction (if on ground)
            

            // Update storage
            storage.GetPositionByEntityID(entityID) = position;
            aStorage.GetAccelerationByEntityID(entityID) = acceleration;
            vStorage.GetVelocityByEntityID(entityID) = velocity;

            // Update the entity's PositionComponent
            entity->GetComponent<PositionComponent>()->position = position;
        }
    }
}



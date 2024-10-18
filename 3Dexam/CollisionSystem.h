#pragma once
#include "Entity.h"
#include "Collision.h"
#include "PhysicsSystem.h"
#include "RenderingSystem.h"
class CollisionSystem {
public:
    void AABBCollision(Entity& entityA, std::vector<Entity> entities);

    void BarycentricCoordinates(Entity& ballEntity, Entity& planeEntity, const std::shared_ptr<PhysicsSystem>& physicsSystem);
    void DODBarycentric(PositionStorage& storage, AccelerationStorage& aStorage, VelocityStorage& vStorage, std::vector<Entity*>& entityList, Entity& planeEntity, const std::shared_ptr<PhysicsSystem>& physicsSystem);


    bool InvAABBCollision(Entity& entityA, Entity& entityB, float deltaTime);
    bool SphereCollision(Entity& entityA, Entity& entityB, float deltaTime);
};
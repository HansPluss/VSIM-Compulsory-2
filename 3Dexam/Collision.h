#pragma once
#include "vector"
class Draw; 
class Grid; 
class Entity;

class Collision

{
public:

	Collision();
	~Collision();
	//|-----------------------------------------------------------------------------|
	//|									Public Functions							|
	//|-----------------------------------------------------------------------------|
	void UpdateCollision(Grid* grid, float dt); 
	bool AABBCollision(Draw &objA, Draw &objB, float DeltaTime);
	bool InvAABBCollision(Draw& objA, Draw& objB, float DeltaTime);
	
	void calculateBarycentricCoordinates(Draw& ball, Draw& drawObject);
private:
	//|-----------------------------------------------------------------------------|
	//|									Private Functions							|
	//|-----------------------------------------------------------------------------|
	bool SphereCollison(Entity& objA, Entity& objB, float DeltaTime);
	void CollisionCalculations(Draw& objA, Draw& objB, float DeltaTime);
	void ObjectCollisionResponse(Entity& objA, Entity& objB);
	void CheckCollision(Entity* ball, std::vector<Entity*>& BallToCheck, int startingIndex, float dt);
	
};


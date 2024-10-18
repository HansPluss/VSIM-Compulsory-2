#include "Collision.h"
#include "Draw.h"
#include "glm/mat4x3.hpp"
#include <glm/glm.hpp>
#include "iostream"
#include <glm/gtc/type_ptr.hpp>
#include "Grid.h"
#include "Entity.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

void Collision::UpdateCollision(Grid* grid, float dt)
{
	for (int i = 0; i < grid->m_cells.size(); ++i)
	{
		int x = i % grid->m_numXCells;
		int y = i / grid->m_numXCells; 

		Cell& cell = grid->m_cells[i];

		for (int j = 0; j < cell.balls.size(); ++j)
		{
			Entity* object = cell.balls[j];
			CheckCollision(object, cell.balls, j + 1, dt);
			if (x > 0)
			{
				CheckCollision(object, grid->getCell(x - 1, y)->balls, 0, dt);
				if (y > 0)
				{
					CheckCollision(object, grid->getCell(x-1,y-1)->balls, 0, dt);
				}
				if (y < grid->m_numYCells - 1)
				{
					CheckCollision(object, grid->getCell(x - 1, y + 1)->balls, 0, dt);
				}
			}
			if (y > 0)
			{
				CheckCollision(object, grid->getCell(x, y - 1)->balls, 0, dt);
			}
		}
	}
}

bool Collision::SphereCollison(Entity& objA, Entity& objB, float DeltaTime)
{
	//float VelocityScale = 0.05f;
	glm::vec3 posA = objA.GetComponent<PositionComponent>()->position + objA.GetComponent<VelocityComponent>()->velocity * DeltaTime;
	glm::vec3 posB = objB.GetComponent<PositionComponent>()->position + objB.GetComponent<VelocityComponent>()->velocity * DeltaTime;
	float distance_centers = glm::length(posA - posB);

	if (distance_centers <= (objA.GetComponent<RenderComponent>()->size.x + objB.GetComponent<RenderComponent>()->size.x)) {
		float minimuntranslation = objA.GetComponent<RenderComponent>()->size.x + objB.GetComponent<RenderComponent>()->size.x - distance_centers;
		auto dirvec = glm::normalize(objA.GetComponent<PositionComponent>()->position - objB.GetComponent<PositionComponent>()->position);
		objA.GetComponent<PositionComponent>()->position = (objA.GetComponent<PositionComponent>()->position + dirvec * minimuntranslation);
		ObjectCollisionResponse(objA, objB);

		return true;
	}

	// No collision detected
	return false;
}

bool Collision::AABBCollision(Draw &objA, Draw &objB, float DeltaTime)
{
	if (abs(objA.GetPosition().x - objB.GetPosition().x) > (objA.GetSize().x + objB.GetSize().x))
	{
		return false;
	}
	if (abs(objA.GetPosition().y - objB.GetPosition().y) > (objA.GetSize().y + objB.GetSize().y))
	{
		return false;
	}
	if (abs(objA.GetPosition().z - objB.GetPosition().z) > (objA.GetSize().z + objB.GetSize().z))
	{
		return false;
	}
	std::cout << "collition" << std::endl;
	CollisionCalculations(objA, objB, DeltaTime);

	//AngularCollision(objB, objA);
	return true;
}

bool Collision::InvAABBCollision(Draw& objA, Draw& objB, float DeltaTime)
{
	glm::vec3 MainVelB = objB.GetVelocity();
	float speedBx = MainVelB.x;
	float speedBz = MainVelB.z;

	if (abs((objB.GetPosition().x + MainVelB.x * DeltaTime) - objA.GetPosition().x) > (objA.GetSize().x - objB.GetSize().x))
	{
		// Update velocities only along the X axis
		objB.SetVelocity(glm::vec3(speedBx*-1, 0, speedBz)); // X velocity changes, Z remains same
	}
	if (abs((objB.GetPosition().z + MainVelB.z * DeltaTime) - objA.GetPosition().z) > (objA.GetSize().z - objB.GetSize().z))
	{
		// Update velocities only along the Z axis
		objB.SetVelocity(glm::vec3(speedBx, 0, speedBz * -1)); // Z velocity changes, X remains same
	}
	objB.SetAngularVelocity(objB.GetVelocity());

	return false;
}

void Collision::CollisionCalculations(Draw &objA, Draw &objB, float DeltaTime)
{
	float massA = objA.GetMass();
	float massB = objB.GetMass();
	float speedAx = objA.GetVelocity().x;
	float speedAz = objA.GetVelocity().z;
	float speedBx = objB.GetVelocity().x;
	float speedBz = objB.GetVelocity().z;

	// Calculating relative velocity in both directions
	float relativeSpeedX = abs(speedAx - speedBx);
	float relativeSpeedZ = abs(speedAz - speedBz);

	glm::vec3 normalA = objA.GetNormal();
	glm::vec3 normalB = objB.GetNormal();
	
	glm::vec3 angularVelocityChangeA(0.0f);
	glm::vec3 angularVelocityChangeB(0.0f);

	// Determining primary axis of collision
	if (normalA.b != 0) // Primary collision is along the X axis
	{
		float newSpeedAx = ((massA - massB) * speedAx + 2 * massB * speedBx) / (massA + massB);
		float newSpeedBx = ((massB - massA) * speedBx + 2 * massA * speedAx) / (massA + massB);

		// Updating velocities only along the X axis
		objA.SetVelocity(glm::vec3(newSpeedAx, 0, speedAz)); // X velocity changes, Z remains same
		objB.SetVelocity(glm::vec3(newSpeedBx, 0, speedBz)); // X velocity changes, Z remains same

		angularVelocityChangeA.x = (speedAx - speedBx) / massA;
		angularVelocityChangeB.x = (speedBx - speedAx) / massB;
	}
	else // Primary collision is along the Z axis
	{
		float newSpeedAz = ((massA - massB) * speedAz + 2 * massB * speedBz) / (massA + massB);
		float newSpeedBz = ((massB - massA) * speedBz + 2 * massA * speedAz) / (massA + massB);

		// Updating velocities only along the Z axis
		objA.SetVelocity(glm::vec3(speedAx, 0, newSpeedAz)); // Z velocity changes, X remains same
		objB.SetVelocity(glm::vec3(speedBx, 0, newSpeedBz)); // Z velocity changes, X remains same

		angularVelocityChangeA.z = (speedAz - speedBz) / massA;
		angularVelocityChangeB.z = (speedBz - speedAz) / massB;
	}
	objA.SetAngularVelocity(objA.GetAngularVelocity() + angularVelocityChangeA * 0.01f);
	objB.SetAngularVelocity(objB.GetAngularVelocity() + angularVelocityChangeB * 0.01f);
}

void Collision::ObjectCollisionResponse(Entity& objA, Entity& objB)
{
	float massA = objA.GetComponent<PhysicsComponet>()->mass;
 //needs to add mass to the object
	float massB = objB.GetComponent<PhysicsComponet>()->mass;
	glm::vec3 posA = objA.GetComponent<PositionComponent>()->position;
	glm::vec3 posB = objB.GetComponent<PositionComponent>()->position;
	glm::vec3 velocityA = objA.GetComponent<VelocityComponent>()->velocity;
	glm::vec3 velocityB = objB.GetComponent<VelocityComponent>()->velocity;

	glm::vec3 normal = glm::normalize(posB - posA);					// Calculating the normal vector of the collision
	glm::vec3 relativeVelocity = velocityA - velocityB;				// Calculating the relative velocity
	float velocityAlongNormal = glm::dot(relativeVelocity, normal);	// Calculating the velocity component along the normal

	// Calculating the new velocities along the normal direction
	float restitution = 0.01f; // Coefficient of restitution (1 = perfectly elastic collision)
	float impulse = (-(1 + restitution) * velocityAlongNormal) / (1 / massA + 1 / massB);

	glm::vec3 impulseVector = impulse * normal;

	// Updating velocities along the normal
	glm::vec3 newVelocityA = velocityA + (impulseVector / massA);
	glm::vec3 newVelocityB = velocityB - (impulseVector / massB);

	// Setting new velocities
	objA.GetComponent<VelocityComponent>()->velocity = newVelocityA;
	objB.GetComponent<VelocityComponent>()->velocity = newVelocityB;

	// Setting angular velocity (optional, if needed)
	//objA.SetAngularVelocity(glm::cross(impulseVector, normal));
	//objB.SetAngularVelocity(glm::cross(-impulseVector, normal));
}

void Collision::CheckCollision(Entity* object, std::vector<Entity*>& objectToCheck, int startingIndex, float dt)
{
	for (int i = startingIndex; i < objectToCheck.size(); ++i)
	{
		SphereCollison(*object, *objectToCheck[i], dt);
	}
}



void Collision::calculateBarycentricCoordinates(Draw& object, Draw& drawObject)
{
	float u, v, w;
	glm::vec3 point = object.GetPosition();

	float groundThreshold = object.GetSize().y; // Margin before an object starts interracting with ground
	
	for (int i = 0; i < drawObject.GetVertices().size() -2; ++i) // Increment by 3 for triangle vertices
	{
		glm::vec3 v0 = glm::vec3((drawObject.GetVertices()[i].x * drawObject.GetSize().x) + drawObject.GetPosition().x,
			(drawObject.GetVertices()[i].y * drawObject.GetSize().y) + drawObject.GetPosition().y,
			(drawObject.GetVertices()[i].z * drawObject.GetSize().z) + drawObject.GetPosition().z);

		glm::vec3 v1 = glm::vec3((drawObject.GetVertices()[i + 1].x * drawObject.GetSize().x) + drawObject.GetPosition().x,
			(drawObject.GetVertices()[i + 1].y * drawObject.GetSize().y) + drawObject.GetPosition().y,
			(drawObject.GetVertices()[i + 1].z * drawObject.GetSize().z) + drawObject.GetPosition().z);

		glm::vec3 v2 = glm::vec3((drawObject.GetVertices()[i + 2].x * drawObject.GetSize().x) + drawObject.GetPosition().x,
			(drawObject.GetVertices()[i + 2].y * drawObject.GetSize().y) + drawObject.GetPosition().y,
			(drawObject.GetVertices()[i + 2].z * drawObject.GetSize().z) + drawObject.GetPosition().z);

		glm::vec3 v0v1 = v1 - v0;
		glm::vec3 v0v2 = v2 - v0;
		glm::vec3 v0p = point - v0;

		// Computing dot products
		float dot00 = glm::dot(v0v1, v0v1);
		float dot01 = glm::dot(v0v1, v0v2);
		float dot02 = glm::dot(v0v1, v0p);
		float dot11 = glm::dot(v0v2, v0v2);
		float dot12 = glm::dot(v0v2, v0p);

		// Computing barycentric coordinates
		float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
		v = (dot11 * dot02 - dot01 * dot12) * invDenom;
		w = (dot00 * dot12 - dot01 * dot02) * invDenom;
		u = 1 - w - v;
		float height = v0.y * u + v1.y * v + v2.y * w; // Interpolating height using barycentric coordinates

		// Only if the point is inside the triangle (u, v, w > 0)
		if (u >= 0 && v >= 0 && w >= 0) {
			if (object.GetPosition().y < height + groundThreshold) // Check if the object is sufficiently close to the ground
			{
				glm::vec3 currentVelocity = object.GetVelocity();

				// Stopping downward motion
				if (currentVelocity.y < 0)
				{
					currentVelocity.y = 0;  // Resetting downward velocity
				}

				// Counteracting force to gravity
				object.ApplyForce(glm::vec3(0, 9.81f, 0));
				object.SetVelocity(currentVelocity);

				// Additional ground proximity force in case of collision
				if (object.GetPosition().y < height + groundThreshold - 0.1)
				{
					object.ApplyForce(glm::vec3(0, 9.86f, 0)); // Applying small upward force
				}

				// Calculating the normal vector for the slope
				glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0)); // Normal of this triangle
				float inclineAngle = std::acos(normal.y);
				float slopeDirection = atan2(normal.z, normal.x);
				glm::vec3 Dirvec = object.GetVelocity();
				glm::vec3 slopeVector = glm::normalize(glm::vec3(normal.x, 0, normal.z)); // Horizontal direction of the slope

				// Determining if the object is moving uphill or downhill
				if (currentVelocity.y > 0) // Object is moving uphill
				{
					// Adjusting velocity based on slope incline
					float speedAdjustment = glm::dot(currentVelocity, slopeVector);
					currentVelocity.y -= speedAdjustment * sin(inclineAngle); // Reduce vertical velocity based on incline

					// Ensuring object doesn't go through floor
					if (object.GetPosition().y < height + groundThreshold)
					{
						object.SetPosition(glm::vec3(object.GetPosition().x, height + groundThreshold, object.GetPosition().z));
						currentVelocity.y = 0; // 0 vertical motion
					}
				}
				else if (currentVelocity.y < 0) // Object is moving downhill
				{
					// Adjusting velocity based on slope incline
					float speedAdjustment = glm::dot(currentVelocity, slopeVector);
					currentVelocity.y += speedAdjustment * sin(inclineAngle); // Increase vertical velocity based on incline

					// Ensuring object doesn't go through floor
					if (object.GetPosition().y < height + groundThreshold)
					{
						object.SetPosition(glm::vec3(object.GetPosition().x, height + groundThreshold, object.GetPosition().z));
						currentVelocity.y = 0; // 0 vertical motion
					}
				}

				object.SetVelocity(currentVelocity);

				// Calculating effect of gravity and slope on object
				object.CalculateGravity(inclineAngle, slopeVector, normal);
			}

			return;
		}
	}
}


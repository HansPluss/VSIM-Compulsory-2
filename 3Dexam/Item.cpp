#include "Item.h"
#include "Component.h"
#include <vector>

Item::Item() : ItemID(0)
{
    AddComponent<PositionComponent>(0.0f,10.0f,0.0f);
    AddComponent<RenderComponent>(glm::vec3(0.0f), glm::vec3(1.0f,0.5f,0.5f), "cube");
    AddComponent<VelocityComponent>();
    AddComponent<AccelerationComponent>();
    //AddComponent<CollisionComponent>();
	//playerref = &player;
    ItemID = rand() % 2;
}

Item::~Item()
{
}

void Item::Pickup(Player& player)
{
	// Adding a random item to the player's inventory
    std::cout << "item ID " << ItemID << std::endl;
    player.AddInventoryItem(ItemID);
}

void Item::UpdateTick(float deltaTime)
{
	if (playerref != nullptr)
	{
		//checkCollision(playerref);
	}
	else
	{
        std::cout << "Player reference is null" << std::endl;
	}
}

void Item::checkCollision(Player& player)
{
    glm::vec3 futurePosA = player.GetComponent<PositionComponent>()->GetPosition()
        + player.GetComponent<VelocityComponent>()->GetVelocity();
    
    // Calculating the distance between the centers of both objects
    float distanceCenters = glm::length(futurePosA - this->GetComponent<PositionComponent>()->GetPosition());

    // Checking if the distance is less than the sum of the radii
    if (distanceCenters <= (player.GetComponent<RenderComponent>()->size.x + this->GetComponent<RenderComponent>()->size.x))
    {
        Pickup(player); 
       
        isMarkedForDeletion = true;
    }
}

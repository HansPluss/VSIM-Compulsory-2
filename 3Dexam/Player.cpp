#include "Player.h"
#include <memory>
Player::Player()
{
	AddComponent<PositionComponent>(10.0f, 0.0f, 0.0f);
	AddComponent<VelocityComponent>();
	AddComponent<AccelerationComponent>();
	AddComponent<InputComponent>();
	AddComponent<RenderComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), "sphere");
	AddComponent<PhysicsComponet>();
	AddComponent<HealthComponent>(100);
	healthPotion = std::make_shared<HealthPotion>();
	speedPotion = std::make_shared<SpeedPotion>(*this);

	AddItemsToInventory();
}
void  Player::AddItemsToInventory() {

	m_inventory.AddItem(speedPotion, 2);  // Adding one SpeedPotion to the inventory
	m_inventory.AddItem(healthPotion, 2); // Adding one HealthPotion to the inventory
}

Player::~Player()
{
	// Destructor
}

std::vector<ItemData> Player::GetInventory()
{
	return m_inventory.listItems();
}

void Player::AddInventoryItem(int ID)
{
	switch (ID)
	{
	case 0:
	{
		m_inventory.AddItem(healthPotion, 1);
		break;
	}
	case 1:
	{
		m_inventory.AddItem(speedPotion, 1);
		break;
	}
	default:
		break;
	}
}

void Player::UseInventoryItem(int ID)
{
	m_inventory.UseItem(ID);
}

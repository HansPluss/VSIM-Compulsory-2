#pragma once
#include "Entity.h"
#include "Tick.h"
#include "Player.h"
class Item : public Entity, public Tick {
public:
	Item();
	~Item();
	void checkCollision(Player& player);

private:
	void Pickup(Player& player);
	int ItemID; // 0, 1, 2
	Entity* playerref;

    void UpdateTick(float deltaTime) override;
};
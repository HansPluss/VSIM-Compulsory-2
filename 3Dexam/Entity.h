#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include "Component.h"
#include "Grid.h"

class Entity {
public:
    //Entity ID, used for indexing
    int id;
    bool isMarkedForDeletion;
    Cell* ownerCell = nullptr;
    int cellvectorindex = -1;

    virtual ~Entity() = default; // Virtual destructor for polymorphism
    //Getter
    int GetId() {
        return id;
    }
    //Setter
    void SetId(int newId) {
        id = newId;
    }
    //default constructor
    Entity() {
        id = idCounter++;
        isMarkedForDeletion = false;
    }
    //used for updating collisions
    void updateGrid(Grid* grid)
    {
        Cell* newCell = grid->getCell(this->GetComponent<PositionComponent>()->position);
        if (newCell != this->ownerCell)
        {
            grid->RemoveBallFromCell(this, this->ownerCell);
            grid->AddBaLL(this, newCell);
            this->ownerCell = newCell; // Updating the ownerCell after moving
        }
    }
    //Add components to entity
    template<typename T, typename... Args>
    void AddComponent(Args&&... args) {
        components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }
    //Getter for components
    template<typename T>
    T* GetComponent() {
        auto it = components.find(typeid(T));
        return (it != components.end()) ? static_cast<T*>(it->second.get()) : nullptr;
    }

private:
    static int idCounter;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

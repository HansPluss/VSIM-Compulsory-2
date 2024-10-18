#pragma once
#include "Entity.h"
#include <memory>
#include "Component.h"
class EntityManager {
public:
    EntityManager() = default;

    //Creates entites and puts them in a vector
    Entity& CreateEntity() {
        entities.push_back(std::make_unique<Entity>());
 
        return *entities.back();
    }
    //Creates entities that inherit from another class like player, enemy etc
    template<typename T, typename... Args>
    T& CreateEntityDerivedFromClass(Args&&... args) {
        static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");
        entities.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *static_cast<T*>(entities.back().get());
    }
    //Deletes all entities that are marked
    void DeleteEntities(std::vector<Entity*>& entities) {
        for (auto it = entities.begin(); it != entities.end();) {
            if ((*it)->isMarkedForDeletion) {
                
                it = entities.erase(it);
            }
            else {
                ++it; 
            }
        }

    }
    //Extra function for marking entities
    void MarkForDeletion(Entity& entity) {
        entity.isMarkedForDeletion = true;

    }
    //Getter
    std::vector<std::unique_ptr<Entity>>& GetEntities() {
        return entities;
    }
   
private:
    std::vector<std::unique_ptr<Entity>> entities;

};
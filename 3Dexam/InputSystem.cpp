#pragma once
#include "InputSystem.h"
#include <glm/glm.hpp>
#include <iostream>
#include "Player.h"


void InputSystem::processInput(Entity& entity, GLFWwindow* window)
{
    InputComponent* input = entity.GetComponent<InputComponent>();
    VelocityComponent* velocity = entity.GetComponent<VelocityComponent>();

    if (input) {
        // Updating input states based on key presses
        input->updateInput(
            glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS,

            glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS
        );

        // Getting access to player from entity
        Player* player = dynamic_cast<Player*>(&entity);
        if (player) {
            // Opens inventory when tab is pressed

            if (input->bTab && !bUsingItem) {
                player->GetInventory();  // Calling the GetInventory() function
                bUsingItem = true;
            }
            else if ((input->bKey1 && !bUsingItem) || (inventoryItem == 0 && !bUsingItem && input->bKeyQ))
            {
                player->UseInventoryItem(0);
                bUsingItem = true;

            }
            else if ((input->bKey2 && !bUsingItem) || (inventoryItem == 1 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(1);
                bUsingItem = true;
            }
            else if ((input->bKey3 && !bUsingItem) || (inventoryItem == 2 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(2);
                bUsingItem = true;
            }
            else if ((input->bKey4 && !bUsingItem) || (inventoryItem == 3 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(3);
                bUsingItem = true;
            }
            else if ((input->bKey5 && !bUsingItem) || (inventoryItem == 4 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(4);
                bUsingItem = true;
            }
            else if ((input->bKey6 && !bUsingItem) || (inventoryItem == 5 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(5);
                bUsingItem = true;
            }
            else if ((input->bKey7 && !bUsingItem) || (inventoryItem == 6 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(6);
                bUsingItem = true;
            }
            else if ((input->bKey8 && !bUsingItem) || (inventoryItem == 7 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(7);
                bUsingItem = true;
            }
            else if ((input->bKey9 && !bUsingItem) || (inventoryItem == 8 && input->bKeyQ && !bUsingItem))
            {
                player->UseInventoryItem(8);
                bUsingItem = true;
            }
            if (bUsingItem)
            {
                // Spam Protection
                if (!input->bTab && !input->bKey1 && !input->bKey2 && !input->bKey3 && !input->bKey4 && !input->bKey5 && !input->bKey6 && !input->bKey7 && !input->bKey8 && !input->bKey9 && !input->bKeyQ)
                {
                    bUsingItem = false;
                }
            }

            // Maximum speed
            const float MAX_SPEED = 50.0f;

            // Updating velocity based on input
            if (velocity) {
                // Encoding movement direction into a single value
                int direction = 0;
                if (input->moveUp) direction |= 1;
                if (input->moveDown) direction |= 2;
                if (input->moveLeft) direction |= 4;
                if (input->moveRight) direction |= 8;

                // Switch case to handle movement direction
                switch (direction) {
                case 1: // Move up (W)
                    velocity->velocity.z = -player->GetSpeed();
                    break;
                case 2: // Move down (S)
                    velocity->velocity.z = player->GetSpeed();
                    break;
                case 4: // Move left (A)
                    velocity->velocity.x = -player->GetSpeed();
                    break;
                case 8: // Move right (D)
                    velocity->velocity.x = player->GetSpeed();
                    break;
                case 5: // Move up-left (W + A)
                    velocity->velocity.z = -player->GetSpeed();
                    velocity->velocity.x = -player->GetSpeed();
                    break;
                case 9: // Move up-right (W + D)
                    velocity->velocity.z = -player->GetSpeed();
                    velocity->velocity.x = player->GetSpeed();
                    break;
                case 6: // Move down-left (S + A)
                    velocity->velocity.z = player->GetSpeed();
                    velocity->velocity.x = -player->GetSpeed();
                    break;
                case 10: // Move down-right (S + D)
                    velocity->velocity.x = player->GetSpeed();
                    velocity->velocity.z = player->GetSpeed();
                    break;
                default:
                    velocity->velocity.x = 0.f;
                    velocity->velocity.z = 0.f;
                    break;
                }

                if (velocity->velocity.x > player->GetMaxSpeed())
                    velocity->velocity.x = player->GetMaxSpeed();
                if (velocity->velocity.x < -player->GetMaxSpeed())
                    velocity->velocity.x = -player->GetMaxSpeed();
                if (velocity->velocity.z > player->GetMaxSpeed())
                    velocity->velocity.z = player->GetMaxSpeed();
                if (velocity->velocity.z < -player->GetMaxSpeed())
                    velocity->velocity.z = -player->GetMaxSpeed();

            }
        }

    }
}

int InputSystem::SetMouseInput(int mouseValue)
{
    inventoryItem = mouseValue;
    return inventoryItem;
}

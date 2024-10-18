#pragma once
#include "Entity.h"
#include <GLFW/glfw3.h>

class Entity;
class GLFWwindow;

class InputSystem {
private:
	bool bUsingItem = false;
	int inventoryItem = 0;
public:
	void processInput(Entity& entity, GLFWwindow* window);
	int SetMouseInput(int mouseValue);
};
#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Player.h"

class ImGuiManager
{
public:
	ImGuiManager(GLFWwindow* window);
	void BasicText(const std::string& stringA, Player& player);
	void shutdown();
};


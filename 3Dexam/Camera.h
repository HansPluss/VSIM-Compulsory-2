#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "Resources/Shaders/shaderClass.h"

class Camera
{
public:
	// Main camera vectors
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 RotationAxis = glm::normalize(glm::cross(Orientation, Up));
	float angle = glm::radians(-45.0f);

	// Blocks very first camera input
	bool firstClick = false;

	// Window dimensions
	int width;
	int height;

	// Camera speeds
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Camera constructor
	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	glm::mat4 Matrix(float FOVdeg, float nearPlane, float farPlane, const std::shared_ptr<Shader>& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);
};
#endif

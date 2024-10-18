#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <array>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Vertex
{
	float x, y, z;
	float r, g, b;
	float u, v;
	float normalx, normaly, normalz;


};
class Construct
{
public:
	std::vector<Vertex> Cube(glm::vec3 Color);
	std::array<Vertex, 6> Plane(glm::vec3 Color, glm::vec3 PointPosition);
	std::vector<Vertex> Terrain(glm::vec3 Color, int terrainWidth, int terrainDepth, float terrainScale);
	std::vector<Vertex> Graph(float c, int iterations, int start);
};


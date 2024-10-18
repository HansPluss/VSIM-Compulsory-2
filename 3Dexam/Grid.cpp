#include "Grid.h"
#include "iostream"
#include "Entity.h"



Grid::Grid(int width, int height, int cellSize) : m_width(width), m_height(height), m_cellSize(cellSize)
{
	m_numXCells = ceil(static_cast<float>(m_width) / cellSize);
	m_numYCells = ceil(static_cast<float>(m_height) / cellSize);
	m_cells.resize(m_numYCells * m_numXCells);



}

Grid::~Grid()
{
}

void Grid::AddBaLL(Entity* ball)
{
	Cell* cell = getCell(ball->GetComponent<PositionComponent>()->position); 
	cell->balls.push_back(ball); 
	ball->ownerCell = cell;
	ball->cellvectorindex = cell->balls.size() - 1; 
}

void Grid::AddBaLL(Entity* ball, Cell* cell)
{
	cell->balls.push_back(ball);
	ball->ownerCell = cell;
	ball->cellvectorindex = cell->balls.size() - 1;
}

Cell* Grid::getCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= m_numXCells) x = m_numXCells;
	if (y < 0) y = 0;
	if (y >= m_numYCells) y = m_numYCells;

	return &m_cells[y * m_numXCells + x];
}

Cell* Grid::getCell(const glm::vec3& pos)
{
	if (pos.x < 0 || pos.x >= m_width || pos.z < 0 || pos.z >= m_height)
		return &m_cells[0];

	int cellX = pos.x / m_cellSize;
	int cellY = pos.z / m_cellSize;

	return getCell(cellX, cellY);
}



void Grid::RemoveBallFromCell(Entity* ball, Cell* cell) {
    if (cell) {
        auto& balls = cell->balls;
        balls.erase(std::remove(balls.begin(), balls.end(), ball), balls.end());
    }
}




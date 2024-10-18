#pragma once
#include <vector>
#include <glm/glm.hpp>

class Entity;

struct Cell {
    std::vector<Entity*> balls;
};

class Grid
{
    friend class Collision;
public:
    Grid(int width, int height, int cellSize);
    ~Grid();
    //|-----------------------------------------------------------------------------|
    //|                                Public Functions                             |
    //|-----------------------------------------------------------------------------|
    void AddBaLL(Entity* ball);
    void AddBaLL(Entity* ball, Cell* cell);
    void RemoveBallFromCell(Entity* ball, Cell* cell);
    //|-----------------------------------------------------------------------------|
    //|                                Getters                                      |
    //|-----------------------------------------------------------------------------|

    Cell* getCell(int x, int y);
    Cell* getCell(const glm::vec3& pos);

private:
    //|-----------------------------------------------------------------------------|
    //|                                Private variables                            |
    //|-----------------------------------------------------------------------------|
    std::vector<Cell> m_cells;
    int m_cellSize;
    int m_width;
    int m_height;
    int m_numXCells;
    int m_numYCells;
};

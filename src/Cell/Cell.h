#pragma once

#include <memory>
#include <vector>

#include <raylib.h>

enum CellType
{
    Empty,
    Start,
    End,
    Path,
    Visited,
    CurrentIndex,
    Wall
};

#include "Grid/Grid.h"

class Grid;

class Cell : public std::enable_shared_from_this<Cell>
{
public:
    Cell();
    ~Cell();

    void Render();
    void AddNeighbours(std::vector<std::vector<std::shared_ptr<Cell>>> &grid);
    void SetType(CellType type) { this->m_type = type; }
    void SetPosition(Vector2 position) { this->m_position = position; }
    void SetSize(Vector2 size) { this->m_size = size; }
    void SetPrevious(std::shared_ptr<Cell> previous) { this->m_previous = previous; }
    void SetIndex(Vector2 index) { this->m_index = index; }
    void HandleInput();
    std::shared_ptr<Cell> GetPrevious() { return this->m_previous; }
    std::vector<std::shared_ptr<Cell>> GetNeighbours() { return this->m_neighbours; }
    CellType GetType() { return this->m_type; }

    void SetF(float f) { this->f = f; }
    void SetG(float g) { this->g = g; }
    void SetH(float h) { this->h = h; }

    float GetF() { return this->f; }
    float GetG() { return this->g; }
    float GetH() { return this->h; }

    float Heuristic(std::shared_ptr<Cell> end)
    {
        return abs(this->m_position.x - end->m_position.x) + abs(this->m_position.y - end->m_position.y);
    }

private:
    std::shared_ptr<Cell>
        m_previous;
    std::vector<std::shared_ptr<Cell>> m_neighbours;

    Vector2 m_index = {0, 0};
    Vector2 m_position = {0, 0};
    Vector2 m_size = {0, 0};

    CellType m_type = CellType::Empty;

    Grid *m_grid = nullptr;

    float f = 0;
    float g = 0;
    float h = 0;
};
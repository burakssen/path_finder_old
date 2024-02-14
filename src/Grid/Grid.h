#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <thread>

#include <raylib.h>
#include <imgui.h>

#include "Cell/Cell.h"

class Cell;
class Algorithm;

class Grid
{
    Grid();

public:
    ~Grid();
    static Grid &GetInstance();

    void Init();
    void Run();
    void Update();
    void Render();
    void HandleInput();

    void SetPosition(Vector2 position);
    void SetSize(Vector2 size);
    void SetStart(std::shared_ptr<Cell> start);
    void SetEnd(std::shared_ptr<Cell> end);
    void SetCurrentCellType(CellType type) { this->m_currentCellType = type; }

    CellType GetCurrentCellType();
    std::shared_ptr<Cell> GetStart() { return this->m_start; }
    std::shared_ptr<Cell> GetEnd() { return this->m_end; }

    int GetRows() { return this->m_rows; }
    int GetColumns() { return this->m_columns; }
    void IncreaseCellSize();
    void DecreaseCellSize();

private:
    Vector2 m_position = {0, 0};
    Vector2 m_size = {0, 0};

    int m_rows = 0;
    int m_columns = 0;
    int m_cellSize = 0;
    std::vector<int> m_cellSizes = {10, 20, 25, 40, 50};
    int m_cellSizeIndex = 0;
    std::vector<std::vector<std::shared_ptr<Cell>>> m_grid;

    std::shared_ptr<Cell> m_start;
    std::shared_ptr<Cell> m_end;

    CellType m_currentCellType = CellType::Empty;

    std::shared_ptr<Algorithm> m_algorithm = nullptr;

    std::vector<std::shared_ptr<Cell>> m_openSet;
    std::vector<std::shared_ptr<Cell>> m_closedSet;

    std::vector<std::shared_ptr<Cell>> m_path;
    bool m_pathFound = false;
};
#include "Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
}

Grid &Grid::GetInstance()
{
    static Grid instance;
    return instance;
}

void Grid::Init()
{
    this->m_grid.clear();
    this->m_path.clear();
    this->m_openSet.clear();
    this->m_closedSet.clear();
    this->m_cellSize = this->m_cellSizes[this->m_cellSizeIndex];
    this->m_rows = this->m_size.x / this->m_cellSize;
    this->m_columns = this->m_size.y / this->m_cellSize;

    this->m_grid.resize(this->m_rows);

    for (int i = 0; i < this->m_rows; i++)
    {
        this->m_grid[i].resize(this->m_columns);
        for (int j = 0; j < this->m_columns; j++)
        {
            this->m_grid[i][j] = std::make_shared<Cell>();
            this->m_grid[i][j]->SetIndex({(float)i, (float)j});
            this->m_grid[i][j]->SetPosition({this->m_position.x + (i * this->m_cellSize), this->m_position.y + (j * this->m_cellSize)});
            this->m_grid[i][j]->SetSize({(float)this->m_cellSize, (float)this->m_cellSize});
            this->m_grid[i][j]->SetType(CellType::Empty);
        }
    }

    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            this->m_grid[i][j]->AddNeighbours(this->m_grid);
        }
    }
}

void Grid::Run()
{
    std::thread t(
        [this]()
        {
            while (this->m_openSet.size() > 0)
            {
                this->Update();
                WaitTime(0.01f);
                if (this->m_pathFound)
                {
                    break;
                }
            }
        });

    t.detach();
}

void Grid::Update()
{
    int winner = 0;
    for (int i = 0; i < this->m_openSet.size(); i++)
    {
        if (this->m_openSet[i]->GetF() < this->m_openSet[winner]->GetF())
        {
            winner = i;
        }

        std::shared_ptr<Cell> current = this->m_openSet[winner];
        if (current == this->m_end)
        {
            std::shared_ptr<Cell> temp = current;

            while (temp->GetPrevious() != nullptr)
            {
                this->m_path.push_back(temp->GetPrevious());
                temp = temp->GetPrevious();
                WaitTime(0.01f);
            }
            std::cout << "Done!" << std::endl;
            this->m_pathFound = true;
            return;
        }

        this->m_openSet.erase(this->m_openSet.begin() + winner);
        this->m_closedSet.push_back(current);

        std::vector<std::shared_ptr<Cell>> neighbors = current->GetNeighbours();

        for (auto neighbor : neighbors)
        {
            if (std::find(this->m_closedSet.begin(), this->m_closedSet.end(), neighbor) != this->m_closedSet.end())
            {
                continue;
            }

            // check if the neighbor is a wall
            if (neighbor->GetType() == CellType::Wall)
            {
                continue;
            }

            float tempG = current->GetG() + 1;

            if (std::find(this->m_openSet.begin(), this->m_openSet.end(), neighbor) == this->m_openSet.end())
            {
                this->m_openSet.push_back(neighbor);
            }
            else if (tempG >= neighbor->GetG())
            {
                continue;
            }

            neighbor->SetPrevious(current);
            neighbor->SetG(tempG);
            neighbor->SetH(neighbor->Heuristic(this->m_end));
            neighbor->SetF(neighbor->GetG() + neighbor->GetH());
        }

        for (auto cell : this->m_openSet)
        {
            cell->SetType(CellType::CurrentIndex);
        }

        for (auto cell : this->m_closedSet)
        {
            cell->SetType(CellType::Visited);
        }
    }
}

void Grid::Render()
{
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            this->m_grid[i][j]->Render();
        }
    }

    for (auto cell : this->m_path)
    {
        if (cell != this->m_start && cell != this->m_end)
        {
            cell->SetType(CellType::Path);
        }
        else
        {
            this->m_end->SetType(CellType::End);
            this->m_start->SetType(CellType::Start);
        }

        if (cell != this->m_start && cell != this->m_end)
        {
            cell->Render();
        }
    }

    DrawRectangleLines(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, WHITE);
}

void Grid::HandleInput()
{
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < this->m_columns; j++)
        {
            this->m_grid[i][j]->HandleInput();
        }
    }
}

void Grid::SetPosition(Vector2 position)
{
    this->m_position = position;
}

void Grid::SetSize(Vector2 size)
{
    this->m_size = size;
}

void Grid::SetStart(std::shared_ptr<Cell> start)
{
    if (this->m_start != nullptr && this->m_start != start)
    {
        this->m_openSet.clear();
        this->m_start->SetType(CellType::Empty);
    }

    this->m_start = start;
    this->m_openSet.push_back(start);
}

void Grid::SetEnd(std::shared_ptr<Cell> end)
{
    if (this->m_end != nullptr && this->m_end != end)
    {
        this->m_end->SetType(CellType::Empty);
    }

    this->m_end = end;
}

CellType Grid::GetCurrentCellType()
{
    return this->m_currentCellType;
}

void Grid::IncreaseCellSize()
{
    if (this->m_cellSizeIndex < this->m_cellSizes.size() - 1)
    {
        this->m_cellSizeIndex++;
        this->m_cellSize = this->m_cellSizes[this->m_cellSizeIndex];
        this->Init();
    }
}

void Grid::DecreaseCellSize()
{
    if (this->m_cellSizeIndex > 0)
    {
        this->m_cellSizeIndex--;
        this->m_cellSize = this->m_cellSizes[this->m_cellSizeIndex];
        this->Init();
    }
}

#include "Cell.h"

Cell::Cell()
{
    this->m_grid = &Grid::GetInstance();
}

Cell::~Cell()
{
}

void Cell::Render()
{
    switch (this->m_type)
    {
    case CellType::Empty:
        DrawRectangle(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, WHITE);
        break;
    case CellType::Start:
        DrawRectangle(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, GREEN);
        break;
    case CellType::End:
        DrawRectangle(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, RED);
        break;
    case CellType::Path:
        DrawRectangle(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, BLUE);
        break;
    case CellType::Visited:
        DrawRectangle(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, PURPLE);
        break;
    case CellType::CurrentIndex:
        DrawRectangle(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, ORANGE);
        break;
    default:
        break;
    }

    DrawRectangleLines(this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y, BLACK);
}

void Cell::AddNeighbours(std::vector<std::vector<std::shared_ptr<Cell>>> &grid)
{

    int i = this->m_index.x;
    int j = this->m_index.y;

    if (i < grid.size() - 1)
    {
        this->m_neighbours.push_back(grid[i + 1][j]);
    }

    if (i > 0)
    {
        this->m_neighbours.push_back(grid[i - 1][j]);
    }

    if (j < grid[0].size() - 1)
    {
        this->m_neighbours.push_back(grid[i][j + 1]);
    }

    if (j > 0)
    {
        this->m_neighbours.push_back(grid[i][j - 1]);
    }

    if (i > 0 && j > 0)
    {
        this->m_neighbours.push_back(grid[i - 1][j - 1]);
    }

    if (i < grid.size() - 1 && j < grid[0].size() - 1)
    {
        this->m_neighbours.push_back(grid[i + 1][j + 1]);
    }

    if (i > 0 && j < grid[0].size() - 1)
    {
        this->m_neighbours.push_back(grid[i - 1][j + 1]);
    }

    if (i < grid.size() - 1 && j > 0)
    {
        this->m_neighbours.push_back(grid[i + 1][j - 1]);
    }
}

void Cell::HandleInput()
{
    if (CheckCollisionRecs({this->m_position.x, this->m_position.y, this->m_size.x, this->m_size.y}, {GetMousePosition().x, GetMousePosition().y, 1, 1}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            this->m_type = this->m_grid->GetCurrentCellType();
            if (this->m_type == CellType::Start)
            {
                this->m_grid->SetStart(this->shared_from_this());
            }
            else if (this->m_type == CellType::End)
            {
                this->m_grid->SetEnd(this->shared_from_this());
            }
        }
    }
}

// Path: src/Cell/Cell.h
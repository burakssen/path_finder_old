#pragma once

#include <string>
#include <map>

#include <imgui.h>

#include "Grid/Grid.h"
#include "Cell/Cell.h"

class Cell;

class Topbar
{
    Topbar();

public:
    ~Topbar();
    static Topbar &GetInstance();

    void Init();

    void SetPosition(ImVec2 position);
    void SetSize(ImVec2 size);

    void Update();
    void Render();
    void HandleInput();

private:
    ImVec2 m_position = {0, 0};
    ImVec2 m_size = {0, 0};

    Grid *m_grid = nullptr;
};
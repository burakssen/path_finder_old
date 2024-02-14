#pragma once

#include <string>

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

#include "Grid/Grid.h"
#include "Topbar/Topbar.h"

class App
{
    App();

public:
    ~App();
    static App &GetInstance();

    void Run();

private:
    void Update();
    void Render();
    void HandleInput();

private:
    float m_width = 1024;
    float m_height = 768;

    std::string m_title = "Path Finding Visualiser";

    Topbar &m_topbar = Topbar::GetInstance();
    Grid &m_grid = Grid::GetInstance();
};
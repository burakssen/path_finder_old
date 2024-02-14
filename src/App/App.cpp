#include "App.h"

App::App()
{
    InitWindow(this->m_width, this->m_height, this->m_title.c_str());
    SetTargetFPS(60);
    rlImGuiSetup(true);

    this->m_topbar.SetPosition({12, 12});
    this->m_topbar.SetSize({this->m_width - 24, 144});
    this->m_topbar.Init();

    this->m_grid.SetPosition({12, 160});
    this->m_grid.SetSize({this->m_width - 24, this->m_height - 168});
    this->m_grid.Init();
}

App::~App()
{
    rlImGuiShutdown();
    CloseWindow();
}

App &App::GetInstance()
{
    static App instance;
    return instance;
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        this->HandleInput();
        this->Update();
        this->Render();
    }
}

void App::Update()
{
    this->m_topbar.Update();
}

void App::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    rlImGuiBegin();
    {
        this->m_topbar.Render();
    }
    rlImGuiEnd();

    this->m_grid.Render();
    EndDrawing();
}

void App::HandleInput()
{
    this->m_topbar.HandleInput();
    this->m_grid.HandleInput();
}

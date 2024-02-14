#include "Topbar.h"

Topbar::Topbar()
{
}

Topbar::~Topbar()
{
}

Topbar &Topbar::GetInstance()
{
    static Topbar instance;
    return instance;
}

void Topbar::Init()
{
    this->m_grid = &Grid::GetInstance();
}

void Topbar::SetPosition(ImVec2 position)
{
    this->m_position = position;
}

void Topbar::SetSize(ImVec2 size)
{
    this->m_size = size;
}

void Topbar::Update()
{
}

void Topbar::Render()
{
    ImGui::SetNextWindowPos(this->m_position);
    ImGui::SetNextWindowSize(this->m_size);
    ImGui::Begin("Topbar", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::Text("Cell Type");
        if (ImGui::Button("Empty"))
        {
            this->m_grid->SetCurrentCellType(CellType::Empty);
        }
        ImGui::SameLine();
        if (ImGui::Button("Start"))
        {
            this->m_grid->SetCurrentCellType(CellType::Start);
        }
        ImGui::SameLine();
        if (ImGui::Button("End"))
        {
            this->m_grid->SetCurrentCellType(CellType::End);
        }
        ImGui::SameLine();
        if (ImGui::Button("Wall"))
        {
            this->m_grid->SetCurrentCellType(CellType::Wall);
        }

        ImGui::SameLine();
        if (ImGui::Button("Run"))
        {
            this->m_grid->Run();
            std::cout << "Run" << std::endl;
        }

        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            this->m_grid->Init();
            std::cout << "Reset" << std::endl;
        }

        ImGui::SameLine();
        if (ImGui::Button("Increase Cell Size"))
        {
            this->m_grid->IncreaseCellSize();
        }

        ImGui::SameLine();
        if (ImGui::Button("Decrease Cell Size"))
        {
            this->m_grid->DecreaseCellSize();
        }

        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(255.0f, 255.0f, 255.0f, 255.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        switch (this->m_grid->GetCurrentCellType())
        {
        case CellType::Empty:
            ImGui::Text("Current Cell Type: Empty");
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(255.0f, 255.0f, 255.0f, 255.0f));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(255.0f, 255.0f, 255.0f, 255.0f));
            ImGui::Button("##empty", ImVec2(50, 50));
            ImGui::PopStyleColor(2);
            break;
        case CellType::Start:
            ImGui::Text("Current Cell Type: Start");
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 255.0f, 0.0f, 255.0f));

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 255.0f, 0.0f, 255.0f));
            ImGui::Button("##start", ImVec2(50, 50));
            ImGui::PopStyleColor(2);
            break;
        case CellType::End:
            ImGui::Text("Current Cell Type: End");
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(255.0f, 0.0f, 0.0f, 255.0f));

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(255.0f, 0.0f, 0.0f, 255.0f));
            ImGui::Button("##end", ImVec2(50, 50));
            ImGui::PopStyleColor(2);
            break;
        case CellType::Wall:
            ImGui::Text("Current Cell Type: Wall");
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 255.0f));

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 255.0f));
            ImGui::Button("##wall", ImVec2(50, 50));
            ImGui::PopStyleColor(2);
            break;
        default:
            break;
        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
    ImGui::End();
}

void Topbar::HandleInput()
{
}

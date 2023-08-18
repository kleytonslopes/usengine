/*********************************************************************
 *   File: EditorUI.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "UI/EditorUI.hpp"
#include "Runtime/Application.hpp"
#include "Presentation/Window.hpp"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include <backends/imgui_impl_sdl2.h>

//https://youtu.be/93bavRgVcwA?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT
DEFAULT_BODY(UEditorUI)

void UEditorUI::Construct()
{
	Super::Construct();

	//GetApplication()->OnDrawEvent.Add(this, &UEditorUI::Draw);
	GetWindow()->OnPollEventsEvent.Add(this, &UEditorUI::OnPollEventsEvent);
	GetWindow()->OnMouseButtonEvent.Add(this, &UEditorUI::OnMouseButtonEvent);
	GetWindow()->OnMouseWheelEvent.Add(this, &UEditorUI::OnMouseWheelEvent);
	GetWindow()->OnMouseMovementEvent.Add(this, &UEditorUI::OnMouseMovementEvent);
}

void UEditorUI::PostConstruct()
{
    Super::PostConstruct();
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.BackendFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.BackendFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.KeyMap[ImGuiKey_Tab] = SDL_KeyCode::SDLK_TAB;
    io.KeyMap[ImGuiKey_MouseLeft] = SDL_BUTTON_LEFT;
    io.KeyMap[ImGuiKey_MouseRight] = SDL_BUTTON_RIGHT;
    io.KeyMap[ImGuiKey_MouseMiddle] = SDL_BUTTON_MIDDLE;

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL2_InitForOpenGL(GetWindow()->GetSDLWIndow(), GetWindow()->GetSDLContext());
    ImGui_ImplOpenGL3_Init("#version 330");
}

void UEditorUI::Draw(float deltaTime)
{
    int width = GetWindow()->GetWidth();
    int height = GetWindow()->GetHeight();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(width, height);
    io.DeltaTime = deltaTime;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();


    static bool dockspaceOpen = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);

    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
            {
               
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
            {
                GetWindow()->SetShouldClose(true);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

	ImGui::Begin("Teste");
	ImGui::Text("testa");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    
    //uint32 textureId = 1;
    //ImGui::Image((void*)textureId, ImVec2{ 256.f, 256.f });

	ImGui::End();
	ImGui::End();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    OnDrawSceneEvent.Broadcast(deltaTime);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
}

void UEditorUI::Destroy()
{
    Super::Destroy();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void UEditorUI::OnMouseButtonEvent(uint32 keyCode, EKeyHandler keyHandler)
{
	ImGuiIO& io = ImGui::GetIO();
	

	switch (keyHandler)
	{
	case KEY_NONE:
		break;
	case KEY_PRESSED:
		io.MouseDown[keyCode - 1] = true;
		break;
	case KEY_RELEASED:
		io.MouseDown[keyCode - 1] = false;
		break;
	default:
		break;
	}
}

void UEditorUI::OnMouseWheelEvent(uint32 xOffset, uint32 yOffset)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += xOffset;
	io.MouseWheel += yOffset;
}

void UEditorUI::OnMouseMovementEvent(uint32 xPos, uint32 yPos, uint32 xPosRel, uint32 yPosRel)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(xPos, yPos);
}

void UEditorUI::OnPollEventsEvent(SDL_Event* sEvent)
{
    ImGui_ImplSDL2_ProcessEvent(sEvent);
}

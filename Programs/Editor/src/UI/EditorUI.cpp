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
#include "UI/imgui_impl_opengl3.h"


DEFAULT_BODY(UEditorUI)

void UEditorUI::Construct()
{
	Super::Construct();

	GetApplication()->OnDrawEvent.Add(this, &UEditorUI::Draw);
	GetWindow()->OnMouseButtonEvent.Add(this, &UEditorUI::OnMouseButtonEvent);
	GetWindow()->OnMouseWheelEvent.Add(this, &UEditorUI::OnMouseWheelEvent);
	GetWindow()->OnMouseMovementEvent.Add(this, &UEditorUI::OnMouseMovementEvent);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	io.KeyMap[ImGuiKey_Tab] = SDL_KeyCode::SDLK_TAB;
	io.KeyMap[ImGuiKey_MouseLeft] = SDL_BUTTON_LEFT;
	io.KeyMap[ImGuiKey_MouseRight] = SDL_BUTTON_RIGHT;
	io.KeyMap[ImGuiKey_MouseMiddle] = SDL_BUTTON_MIDDLE;

	ImGui_ImplOpenGL3_Init("#version 410");
}

void UEditorUI::Draw(float deltaTime)
{
	int width = GetWindow()->GetWidth();
	int height = GetWindow()->GetHeight();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(width, height);
	io.DeltaTime = deltaTime;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

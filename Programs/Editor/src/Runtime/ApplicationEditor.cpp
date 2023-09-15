/*********************************************************************
 *   File: ApplicationEditor.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Runtime/ApplicationEditor.hpp"
#include "Framework/EditorGameInstance.hpp"
#include "Physics/PhysicsSystemPhysX.hpp"
#include "UI/EditorUI.hpp"
#include "Presentation/Window.hpp"
#include "Camera/Camera.hpp"


DEFAULT_BODY(UApplicationEditor)

void UApplicationEditor::Construct()
{
	Super::Construct();

	FConstructorHelper::MakeClassOf<URendererOpenGL>(DefaultRenderer);
	FConstructorHelper::MakeClassOf<UEditorGameInstance>(DefaultGameInstance);
}

void UApplicationEditor::PostConstruct()
{
	Super::PostConstruct();

	GameInstance = FConstructorHelper::CreateObject<UEditorGameInstance>();

	UIEditor = FConstructorHelper::CreateObject<UEditorUI>();
	UIEditor->OnDrawSceneEvent.Add(this, &This::DrawScene);

	Window->OnMouseButtonEvent.Add(this, &This::OnMouseButtonEvent);
}

void UApplicationEditor::Initialize()
{
	Super::Initialize();

	UIEditor->Initialize();
}

void UApplicationEditor::Destroy()
{
	Super::Destroy();

	delete UIEditor; UIEditor = nullptr;
}

void UApplicationEditor::Draw(float deltaTime)
{
		PhysicsSystemPhysX->Update(deltaTime);
	Renderer->StartFrame();
		OnDrawEvent.Broadcast(deltaTime);
#if defined (APP_EDITOR_MODE)
	DrawScreenQuad();
#endif
	Renderer->EndFrame();
	UIEditor->Draw(deltaTime);
}

void UApplicationEditor::OnMouseButtonEvent(uint32 keyCode, EKeyHandler keyHandler)
{
	if (keyCode == 3)
	{
		switch (keyHandler)
		{
		case KEY_NONE:
			break;
		case KEY_PRESSED:
			Window->SetMouseLocked(true);
			break;
		case KEY_RELEASED:
			Window->SetMouseLocked(false);
			break;
		default:
			break;
		}
	}
}

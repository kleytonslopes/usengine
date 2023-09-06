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
#include "Physics/PhysicsSystem.hpp"
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
	Renderer->StartFrame();
		OnDrawEvent.Broadcast(deltaTime);
		//PhysicsSystem->Update(deltaTime);
		PhysicsSystemPhysX->Update(deltaTime);
#if defined (APP_EDITOR_MODE)
	DrawScreenQuad();
#endif
	Renderer->EndFrame();
	UIEditor->Draw(deltaTime);
	//Renderer->EndFrame();
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

//void UApplicationEditor::OnMouseMovementEvent(uint32 xPos, uint32 yPos, uint32 xPosRel, uint32 yPosRel)
//{
//	if (Scene)
//	{
//		ACamera* camera = Scene->GetCamera();
//		if (camera)
//		{
//			ULOG(ELogLevel::ELL_TRACE, FText::Format("x: %i, xr: %i , y: %i, yr: %i", xPos, xPosRel, yPos, yPosRel));
//			static float lastX = xPos;
//			static float lastY = yPos;
//			float sensitivity = 0.3f;
//
//			float xoffset = (xPos - lastX) * sensitivity;
//			float yoffset = (lastY - yPos) * sensitivity;
//
//			lastX = xPos;
//			lastY = yPos;
//			//camera->SetRotation(FVector{ xoffset , 0.0f, yoffset });
//			camera->SetYaw(xoffset);
//			camera->SetPitch(yoffset);
//			
//		}
//
//		//ACamera* camera = Scene->GetCamera();
//		//if (camera)
//		//{
//		//	ULOG(ELogLevel::ELL_TRACE, FText::Format("x: %i, xr: %i , y: %i, yr: %i", xPos, xPosRel, yPos, yPosRel));
//		//	static float lastX = xPos;
//		//	static float lastY = yPos;
//		//	float sensitivity = 0.3f;
//
//		//	float xoffset = (xPos - lastX) * sensitivity;
//		//	float yoffset = (lastY - yPos) * sensitivity;
//
//		//	lastX = xPos;
//		//	lastY = yPos;
//		//	camera->SetRotation(FVector{ -yoffset, 0.0f, xoffset });
//		//}
//	}
//}

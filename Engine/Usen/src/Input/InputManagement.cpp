/*********************************************************************
 *   File: InputManagement.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Input/InputManagement.hpp"
#include "Presentation/Window.hpp"
#include "Components/InputComponent.hpp"
#include "Runtime/Application.hpp"
#include "Configs/EngineConfig.hpp"
#include "Framework/Scene.hpp"
#include "Camera/Camera.hpp"

DEFAULT_BODY(UInputManagement)

void UInputManagement::Construct()
{
	Super::Construct();

	bCanUpdate = true;
}

void UInputManagement::PostConstruct()
{
	GetWindow()->OnKeyEvent.Add(this, &This::OnKeyEvent);
	GetWindow()->OnMouseMovementEvent.Add(this, &This::OnMouseMovementEvent);

	FEngineConfig engineConfig{};

	engineConfig.LoadConfig();
	TMap<uint32, FString> keysBinds = engineConfig.GetKeyBinds();

	for (const auto& it : keysBinds)
	{
		FKeyMap kb{};
		kb.ActionName = it.second;
		kb.KeyCode = it.first;

		RegisteredKeys[it.first] = kb;
	}

	Super::PostConstruct();
}

void UInputManagement::Update(float deltaTime)
{
	Super::Update(deltaTime);
	bool executed = false;
	for (auto& it : RegisteredKeys)
	{
		if (it.second.bIsPressed)
		{
			executed = InputComponent->ExecuteAxisAction(it.second.ActionName.c_str(), EKeyHandler::KEY_PRESSED);

			if (!executed)
				InputComponent->ExecuteVoidAction(it.second.ActionName.c_str(), EKeyHandler::KEY_PRESSED);
		}
	}
}

void UInputManagement::SetInputComponent(UInputComponent* inputComponent)
{
	if (InputComponent)
		InputComponent->Deactive();

	InputComponent = inputComponent;
	InputComponent->Active();
}

void UInputManagement::OnKeyEvent(uint32 keyCode, EKeyHandler keyHandler)
{
	if (!InputComponent)
		return;

	KeyMap::iterator it;

	it = RegisteredKeys.find(keyCode);
	
	if (it != RegisteredKeys.end())
	{
		it->second.bIsPressed = keyHandler == EKeyHandler::KEY_PRESSED ? true : false;
	}
}

void UInputManagement::OnMouseMovementEvent(uint32 xpos, uint32 ypos, uint32 xPosRel, uint32 yPosRel)
{
	UScene* scene = GetScene();
	if (scene)
	{
		UWindow* window = GetWindow();
		ACamera* camera = scene->GetCamera();
		if ((camera && window) && window->IsMouseLocked())
		{
		//	//float yaw = camera->GetYaw() + xPosRel;
		//	//ULOG(ELogLevel::ELL_TRACE, FText::Format("x: %i, xr: %i, y: %i, yr: %i", yaw, xPosRel, yPos, yPosRel));
		//	////ULOG(ELogLevel::ELL_TRACE, FText::Format("x: %i, xr: %i, y: %i, yr: %i", xPos, xPosRel, yPos, yPosRel));
		//	//static float lastX = yaw;
		//	//static float lastY = yPos;
		//	//float sensitivity = 0.3f;

		//	//float xoffset = (xPos - lastX) * sensitivity;
		//	//float yoffset = (lastY - yPos) * sensitivity;

		//	//lastX = xPos;
		//	//lastY = yPos;
		//	////camera->SetRotation(FVector{ xoffset , 0.0f, yoffset });
		//	
		//	/*
		////	static float lastX = camera->GetPitch();
		//	static float lastY = camera->GetYaw();
		//	float sensitivity = 0.01f;

		//	float xoffset = (camera->GetPitch() - lastX) * sensitivity;
		//	float yoffset = (lastY - camera->GetYaw()) * sensitivity;

		//	lastX = camera->GetPitch();
		//	lastY = camera->GetYaw();

		//	camera->SetRoll(0.f);
		//	camera->SetYaw(yoffset);
		//	camera->SetPitch(xoffset);
		//	*/

		//	float deltaTIme = GetApplication()->GetDeltaTime();
		//	float yaw = (camera->GetYaw() + xPosRel) * deltaTIme * 0.001f;
		//	float pitch = (camera->GetPitch() + yPosRel) * deltaTIme * 0.001f;

		//	if (pitch > 89.0f) pitch = 89.0f;
		//	if (pitch < -89.0f) pitch = -89.0f;

		//	camera->SetYaw(yaw);
		//	camera->SetPitch(pitch);



			//static float lastX = xPosRel;
			//static float lastY = yPosRel;
			//float sensitivity = 0.1f;

			//float xoffset = (xpos - lastX) * sensitivity;
			//float yoffset = (lastY - ypos) * sensitivity;

			//lastX = xpos;
			//lastY = ypos;

			/*camera.rotate(xoffset, yoffset, 0.0f);*/
			//float x = xPosRel * 0.001f;
			//float y = yPosRel * 0.001f;
			//camera->AddYaw(x);
			//camera->AddPitch(y);
			//camera->SetRoll(0.f);

			camera->AddMouseMovement(GetApplication()->GetDeltaTime(), xPosRel, yPosRel);
		}
	}
}

void UInputManagement::RegisterAction(uint32 keyCode, const FString& actionName)
{
	AxisActionMap::iterator it = AxisActions.find(actionName);

	if (it != AxisActions.end())
	{
		it->second.AddInput(keyCode, actionName);
		return;
	}
	
	FAction newAction{};
	newAction.AddInput(keyCode, actionName);
	AxisActions[actionName] = newAction;
}

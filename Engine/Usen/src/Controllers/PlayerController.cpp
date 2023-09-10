/*********************************************************************
 *   File: PlayerController.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Controllers/PlayerController.hpp"
#include "Input/InputManagement.hpp"
#include "Pawns/Pawn.hpp"
#include "Framework/Scene.hpp"
#include "Camera/Camera.hpp"
#include "Components/CameraComponent.hpp"

DEFAULT_BODY(UPlayerController)

void UPlayerController::Initialize()
{
	Super::Initialize();

	SetupInputComponent();
}

void UPlayerController::SetupInputComponent()
{
	UInputManagement* InputManagement = GetInputManagement();

	InputManagement->AddAxisAction("Exit", this, EKeyHandler::KEY_PRESSED, &This::ExitAction);
	InputManagement->AddAxisAction("MoveForward", this, EKeyHandler::KEY_PRESSED, &This::MoveForward);
	InputManagement->AddAxisAction("MoveBackward", this, EKeyHandler::KEY_PRESSED, &This::MoveBackward);
	InputManagement->AddAxisAction("MoveRight", this, EKeyHandler::KEY_PRESSED, &This::MoveRight);
	InputManagement->AddAxisAction("MoveLeft", this, EKeyHandler::KEY_PRESSED, &This::MoveLeft);
	InputManagement->AddVoidAction("ToggleMoveCharacter", this, EKeyHandler::KEY_PRESSED, &This::ToggleMoveCharacter);
	InputManagement->AddVoidAction("Jump", this, EKeyHandler::KEY_PRESSED, &This::StartJump);
}

void UPlayerController::ExitAction(float scale)
{

}

void UPlayerController::MoveForward(float scale)
{
	if (!Pawn)
		return;



	//if (!bMoveCharacter)
	//{
	//	UCameraComponent* camera = GetScene()->GetCamera()->GetCameraComponent();
	//	FVector Direction = camera->GetLocation();
	//	FVector Forward = camera->GetForwardVector();

	//	Direction += 2.f * scale * Forward;
	//	camera->AddMovementForward(Direction);
	//}
	//else
	//{
		Pawn->MoveForward(scale);
	//}
}

void UPlayerController::MoveBackward(float scale)
{
	if (!Pawn)
		return;

	//if (!bMoveCharacter)
	//{
	//	UCameraComponent* camera = GetScene()->GetCamera()->GetCameraComponent();
	//	FVector Direction = camera->GetLocation();
	//	FVector Forward = camera->GetForwardVector();

	//	Direction -= 2.f * scale * Forward;
	//	camera->AddMovementForward(Direction);
	//}
	//else
	//{
		Pawn->MoveForward(-scale);
	//}
}

void UPlayerController::MoveRight(float scale)
{
	if (!Pawn)
		return;

	//if (!bMoveCharacter)
	//{
	//	UCameraComponent* camera = GetScene()->GetCamera()->GetCameraComponent();
	//	FVector Direction = camera->GetLocation();
	//	FVector Forward = camera->GetForwardVector();
	//	FVector Up = camera->GetUpVector();

	//	Direction += glm::normalize(glm::cross(Forward, Up)) * 2.f * scale;///glm::normalize(glm::cross(Forward.ToGLM(), Up.ToGLM())) * 5.f * deltaTime;
	//	camera->AddMovementRight(Direction);
	//}
	//else
	//{
		Pawn->MoveRight(-scale);
	//}
}

void UPlayerController::MoveLeft(float scale)
{
	if (!Pawn)
		return;

	//if (!bMoveCharacter)
	//{
	//	UCameraComponent* camera = GetScene()->GetCamera()->GetCameraComponent();
	//	FVector Direction = camera->GetLocation();
	//	FVector Forward = camera->GetForwardVector();
	//	FVector Up = camera->GetUpVector();

	//	Direction -= glm::normalize(glm::cross(Forward, Up)) * 2.f * scale;///glm::normalize(glm::cross(Forward.ToGLM(), Up.ToGLM())) * 5.f * deltaTime;
	//	camera->AddMovementRight(Direction);
	//}
	//else
	//{
		Pawn->MoveRight(scale);
	//}
}

void UPlayerController::StartJump()
{
	if (!Pawn)
		return;

	Pawn->Jump();
}

void UPlayerController::ToggleMoveCharacter()
{
	bMoveCharacter = !bMoveCharacter;
}

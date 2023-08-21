/*********************************************************************
 *   File: Pawn.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_PAWN_HPP
#define	US_PAWN_HPP


#include "Actors/Actor.hpp"
#include "Pawn-generated.hpp"

class UCameraComponent;
class UInputComponent;
class UCapsuleComponent;
class UMovementComponent;

class APawn : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Update(float deltaTime) override;

	void SetupInputComponent();

	UCameraComponent* GetCameraComponent();
	UInputComponent* GetInputComponent();
	UCapsuleComponent* GetCapsuleComponent();
	UMovementComponent* GetMovementComponent();

	void MoveForward(float scale);
	void MoveRight(float scale);

private:
	UCameraComponent* CameraComponent = nullptr;
	UInputComponent* InputComponent = nullptr;
	UCapsuleComponent* CapsuleComponent = nullptr;
	UMovementComponent* MovementComponent = nullptr;
};

#endif // !US_PAWN_HPP
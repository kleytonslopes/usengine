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

class UInputComponent;
class UCapsuleComponent;

class APawn : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;

	void SetupInputComponent();

	UInputComponent* GetInputComponent();
	UCapsuleComponent* GetCapsuleComponent();

	void MoveForward(float scale);
	void MoveRight(float scale);
};

#endif // !US_PAWN_HPP
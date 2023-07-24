/*********************************************************************
 *   File: Pawn.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_PAWN_HPP
#define	US_PAWN_HPP


#include "Actors/Actor.hpp"
#include "Pawn-generated.hpp"

class UInputComponent;

class APawn : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	explicit APawn();
	virtual ~APawn();

	void Create() override;

	void SetupInputComponent();

	UInputComponent* GetInputComponent();
};

#endif // !US_PAWN_HPP
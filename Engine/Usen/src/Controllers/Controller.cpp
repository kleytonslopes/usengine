/*********************************************************************
 *   File: Controller.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Controllers/Controller.hpp"
#include "Input/InputManagement.hpp"
#include "Pawns/Pawn.hpp"

DEFAULT_BODY(UController)

void UController::Construct()
{
	Super::Construct();

	bCanUpdate = false;
}

void UController::SetPawn(APawn* pawn)
{
	this->Pawn = pawn;
	pawn->SetOwner(this);

	GetInputManagement()->SetInputComponent(Pawn->GetInputComponent());
}

APawn* UController::GetPawn()
{
	return Pawn;
}

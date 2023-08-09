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
#include "Pawns/Pawn.hpp"

DEFAULT_BODY(UController)

void UController::SetPawn(APawn* pawn)
{
	this->Pawn = pawn;
	pawn->SetOwner(this);
}

APawn* UController::GetPawn()
{
	return Pawn;
}

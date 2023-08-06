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

UController::UController()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UController::~UController()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UController::SetPawn(APawn* pawn)
{
	this->Pawn = pawn;
	pawn->SetOwner(this);
}

APawn* UController::GetPawn()
{
	return Pawn;
}

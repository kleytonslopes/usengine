/*********************************************************************
 *   File: Controller.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CONTROLLER_HPP
#define	US_CONTROLLER_HPP


#include "Actors/Entity.hpp"
#include "Controller-generated.hpp"

class APawn;

class UController : public AEntity
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;

	void SetPawn(APawn* pawn);

	APawn* GetPawn();

protected:
	APawn* Pawn = nullptr;

	friend class UInputManagement;
};

#endif // !US_CONTROLLER_HPP
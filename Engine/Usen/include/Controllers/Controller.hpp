/*********************************************************************
 *   File: Controller.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
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
	explicit UController();
	virtual ~UController();

	void SetPawn(APawn* pawn);

protected:
	APawn* Pawn = nullptr;
};

#endif // !US_CONTROLLER_HPP
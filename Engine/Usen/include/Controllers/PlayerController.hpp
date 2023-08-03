/*********************************************************************
 *   File: PlayerController.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_PLAYER_CONTROLLER_HPP
#define	US_PLAYER_CONTROLLER_HPP


#include "Controllers/Controller.hpp"
#include "PlayerController-generated.hpp"

class UPlayerController : public UController
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UPlayerController();
	virtual ~UPlayerController();
};

#endif // !US_PLAYER_CONTROLLER_HPP
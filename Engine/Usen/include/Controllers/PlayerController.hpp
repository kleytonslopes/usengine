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
	void Initialize() override;
	void Create() override;

	void SetupInputComponent();
	void ExitAction(float scale);
	void MoveForward(float scale);
	void MoveBackward(float scale);
	void MoveRight(float scale);
	void MoveLeft(float scale);

	friend class UInputManagement;
};
#endif // !US_PLAYER_CONTROLLER_HPP
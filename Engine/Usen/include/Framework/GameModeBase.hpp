/*********************************************************************
 *   File: GameModeBase.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_GAME_MODE_BASE_HPP
#define	US_GAME_MODE_BASE_HPP


#include "Base/Class.hpp"
#include "GameModeBase-generated.hpp"

class UController;
class APawn;

class UGameModeBase : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void Initialize() override;

	TClassOf<APawn> GetDefaultPlayerPawn();
	TClassOf<UController> GetDefaultController();

protected:
	UController* Controller = nullptr;
	APawn* PlayerPawn = nullptr;

private:
	TClassOf<UController> DefaultController;
	TClassOf<APawn> DefaultPlayerPawn;

	void SetController(UController* controller);
	void SetPlayerPawn(APawn* playerPawn);

	friend class BClass;
	friend class UScene;
};

#endif // !US_GAME_MODE_BASE_HPP
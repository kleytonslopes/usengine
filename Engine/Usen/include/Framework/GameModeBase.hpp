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

class UGameModeBase : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UGameModeBase();
	virtual ~UGameModeBase();

	void Create() override;
	void Initialize() override;

protected:
	USharedPtr<UController> Controller;

private:
	TClassOf<UController> DefaultController;
};

#endif // !US_GAME_MODE_BASE_HPP
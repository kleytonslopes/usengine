/*********************************************************************
 *   File: TestGameInstance.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_EDITOR_GAME_INSTANCE_HPP
#define	US_EDITOR_GAME_INSTANCE_HPP


#include "Framework/GameInstance.hpp"
#include "TestGameInstance-generated.hpp"

class UTestGameInstance : public UGameInstance
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
};

#endif // !US_EDITOR_GAME_INSTANCE_HPP
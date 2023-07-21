/*********************************************************************
 *   File: GameInstance.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_GAMEINSTANCE_HPP
#define	US_GAMEINSTANCE_HPP

#include "Core/Class.hpp"

class UScene;
class UApplication;

class UGameInstance : public UClass
{
	DEFAULT_BODY(UClass);
public:
	virtual ~UGameInstance();

	void Initialize() override;
	void OnInitialized() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;
};

#endif // !US_GAMEINSTANCE_HPP

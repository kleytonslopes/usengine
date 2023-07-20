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

#include "Core/WeakClass.hpp"

class UScene;

class UGameInstance : public UWeakClass
{
	using Super = UWeakClass;
public:
	UGameInstance();
	virtual ~UGameInstance();

	void Initialize() override;
	void OnInitialized() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	UScene* GetScene();
protected:
	USharedPtr<UScene> currentScene;
};

#endif // !US_GAMEINSTANCE_HPP

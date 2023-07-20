/*********************************************************************
 *   File: Scene.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SCENE_HPP
#define	US_SCENE_HPP

#include "Core/Class.hpp"

class Entity;
class URenderer;
class UApplication;

class UScene : public UClass
{
	using Super = UClass;
public:
	using UClass::UClass;
	virtual ~UScene();

	// Inherited via UWeakClass
	void Initialize() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

protected:
	TMap<uint32, Entity*> entities;
};

#endif // !US_SCENE_HPP

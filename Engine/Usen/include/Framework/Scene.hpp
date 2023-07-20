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

#include "Core/WeakClass.hpp"

class Entity;

class UScene : public UWeakClass
{
	using Super = UWeakClass;
public:
	UScene();
	virtual ~UScene();

	// Inherited via UWeakClass
	void Initialize() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

protected:
	TMap<uint32, Entity*> entities;
};

#endif // !US_SCENE_HPP

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

class UEntity;
class UCamera;
class URenderer;
class UApplication;

class UScene : public UClass
{
	DEFAULT_BODY(UClass);
public:
	virtual ~UScene();

	// Inherited via UWeakClass
	void Initialize() override;
	void OnInitialized() override;

	void Update(float deltaTime) override;
	void OnDestroy() override;

	template<typename T>
	T* CreateEntity();

	UCamera* GetCamera();

protected:
	UCamera* activeCamera = nullptr;

	TMap<FString, UEntity*> entities;

private:
	uint64 lastEntityId = 0;
};

#endif // !US_SCENE_HPP

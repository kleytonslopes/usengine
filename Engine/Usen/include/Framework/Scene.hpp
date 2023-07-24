/*********************************************************************
 *   File: Scene.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SCENE_HPP
#define	US_SCENE_HPP


#include "Base/Class.hpp"
#include "Scene-generated.hpp"

class AEntity;
class ACamera;
class APawn;

class UScene : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UScene();
	~UScene() final;
	void Destroy() final;

	void Initialize() override;
	void Update(float deltaTime) override;

private:
	UUniquePtr<ACamera> Camera;
	UUniquePtr<APawn> DefaultPawn;

	TMap<FString, AEntity*> entities;
};

#endif // !US_SCENE_HPP
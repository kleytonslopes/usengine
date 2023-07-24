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

struct FShaderParameters;

struct FSceneSettings
{
	FString Name = "Unnamed";
	TVector<FShaderParameters> ShadersParameters;
};

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
	FSceneSettings Settings{};

	UUniquePtr<ACamera> Camera;
	UUniquePtr<APawn> DefaultPawn;

	TMap<FString, AEntity*> entities;

	friend class FSceneSerializer;
};

#endif // !US_SCENE_HPP
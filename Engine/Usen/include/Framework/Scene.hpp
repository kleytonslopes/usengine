/*********************************************************************
 *   File: Scene.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
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

class FSceneSerializer;

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

	template<class T>
	T* CreateEntity();
private:
	FSceneSettings Settings{};

	UUniquePtr<ACamera> Camera;
	UUniquePtr<APawn> DefaultPawn;
	UUniquePtr<FSceneSerializer> Serializer;

	TMap<FString, AEntity*> entities;

	void SaveScene();
	bool LoadScene(const FString& sceneName);

	friend class FSceneSerializer;
};

#endif // !US_SCENE_HPP

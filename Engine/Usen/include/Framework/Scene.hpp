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
#include "Serializer/SceneSerializer.hpp"

class UEntity;
class UCamera;
class URenderer;
class UApplication;

struct FShaderParameters;

struct FSceneSettings
{
	FString Name = "Unnamed";
	TVector<FShaderParameters> ShadersParameters;
};

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

	void SaveScene();
	void LoadScene(const FString& scenePath);

	template<typename T>
	T* CreateEntity();

	UCamera* GetCamera();

protected:
	FSceneSettings sceneSettings{};
	UCamera* activeCamera = nullptr;

	TMap<FString, UEntity*> entities;

private:
	uint64 lastEntityId = 0;
	UUniquePtr<USceneSerializer> SceneSerializer;
};

#endif // !US_SCENE_HPP

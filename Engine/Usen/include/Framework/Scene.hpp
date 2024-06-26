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
class FSceneSerializer;
class UGameModeBase;

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
	void Destroy() final;

	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;
	void Update(float deltaTime) override;

	template<class T>
	T* CreateEntity();

	template<class T, class U>
	T* CreateEntity(U& entityClass);

	ACamera* GetCamera();

	UGameModeBase* GetGameMode();
private:
	TClassOf<UGameModeBase> GameModeClass;
	FSceneSettings Settings{};

	ACamera* Camera = nullptr;
	FSceneSerializer* Serializer = nullptr;
	UGameModeBase* GameMode = nullptr;

	TMap<FString, AEntity*> entities;

	void SaveScene();
	bool LoadScene(const FString& sceneName);

	void CreateDefaultCamera();
	void CreateDefaultPawn();
	void CreateDefaultController();

	friend class FSceneSerializer;
	friend class UApplication;
	friend class BClass;
};

#endif // !US_SCENE_HPP

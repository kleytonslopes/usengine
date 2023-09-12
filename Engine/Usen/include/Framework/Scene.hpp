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
class UStaticMesh;

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
	UStaticMesh* Floor = nullptr;
	APawn* Pawn = nullptr; // remove this
	void Destroy() final;

	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;
	void Update(float deltaTime) override;
	void DrawScene(float deltaTime);

	template<class T>
	T* CreateEntity();

	template<class T, class U>
	T* CreateEntity(U& entityClass);

	ACamera* GetCamera();
	ACamera* GetDebugCamera();

	UGameModeBase* GetGameMode();

	void SaveScene();
private:
	TClassOf<UGameModeBase> GameModeClass;
	FSceneSettings Settings{};

	ACamera* Camera = nullptr;
	ACamera* DebugCamera = nullptr;
	FSceneSerializer* Serializer = nullptr;
	UGameModeBase* GameMode = nullptr;

	TMap<FString, AEntity*> entities;

	
	bool LoadScene(const FString& sceneName);

	void CreateDefaultCamera();
	void CreateDefaultPawn();
	void CreateDefaultController();
	void CreateDebugCamera();

	friend class FSceneSerializer;
	friend class UApplication;
	friend class BClass;
};

#endif // !US_SCENE_HPP

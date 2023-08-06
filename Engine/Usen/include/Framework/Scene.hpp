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
	explicit UScene();
	~UScene() final;
	void Destroy() final;

	void Create() override;
	void Initialize() override;
	void Update(float deltaTime) override;

	template<class T>
	T* CreateEntity();

	ACamera* GetCamera();

	UGameModeBase* GetGameMode();
private:
	FSceneSettings Settings{};

	ACamera* Camera = nullptr;
	/*UUniquePtr<APawn> DefaultPawn;*/
	UUniquePtr<FSceneSerializer> Serializer;
	USharedPtr<UGameModeBase> GameMode;
	

	TMap<FString, AEntity*> entities;

	void SaveScene();
	bool LoadScene(const FString& sceneName);

	friend class FSceneSerializer;
	friend class UApplication;
	friend class BClass;
};

#endif // !US_SCENE_HPP

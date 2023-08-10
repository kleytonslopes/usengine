/*********************************************************************
 *   File: Application.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_APPLICATION_HPP
#define	US_APPLICATION_HPP


#include "Weaks/WeakClass.hpp"
#include "Base/Class.hpp"
#include "Framework/Scene.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"
#include "Renderer/Renderer.hpp"
#include "Environment/Environment.hpp"
#include "Application-generated.hpp"

class UWindow;
class UGameInstance;
class UScene;
class UController;
class UInputManagement;
class UPhysicsSystem;

DECLARE_FUNCTION_OneParam(FOnUpdateSignature, float, deltaTime)

class UApplication : public IWeakClass
{
	DEFAULT_BODY_GENERATED()

public:
	FOnUpdateSignature OnUpdateEvent;

	void Run();

	// Inherited via IWeakClass
	void PostConstruct() override;
	void Initialize() override;
	void Destroy() override;

	template<typename T>
	T* GetRenderer()
	{
		return static_cast<T*>(Renderer);
	}

	BRenderer* GetRenderer() { return Renderer; };
protected:
	TClassOf<UGameInstance> DefaultGameInstance;
	TClassOf<BRenderer> DefaultRenderer;

	TThread* ThreadTickEvent = nullptr;;

	//virtual void CreateWindow();
	//virtual void CreateGameInstance();
	//virtual void CreateRenderer();
	//virtual void CreateInputManagement();
	//virtual void CreateScene();
	//virtual void CreatePhysicsSystem();

private:
	UWindow* Window                   = nullptr;
	UGameInstance* GameInstance       = nullptr;
	BRenderer* Renderer               = nullptr;
	UScene* Scene                     = nullptr;
	UInputManagement* InputManagement = nullptr;
	UPhysicsSystem* PhysicsSystem     = nullptr;

	UController* Controller           = nullptr;

	void Loop();
	void CalculeDeltaTime(FTime& currentTime, float& deltaTime);

	friend class BClass;
};

#endif // !US_APPLICATION_HPP

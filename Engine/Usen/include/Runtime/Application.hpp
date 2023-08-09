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
	void Construct() override;
	void PostConstruct() override;
	void Create() override;
	void PostCreate() override;
	void Initialize() override;
	void Destroy() override;

	template<typename T>
	T* GetRenderer()
	{
		return static_cast<T*>(Renderer.Get());
	}

	BRenderer* GetRenderer() { return Renderer.Get(); };
protected:
	TClassOf<UGameInstance> DefaultGameInstance;
	TClassOf<BRenderer> DefaultRenderer;

	UUniquePtr<TThread> ThreadTickEvent = UUniquePtr<TThread>::Make();

	virtual void CreateWindow();
	virtual void CreateGameInstance();
	virtual void CreateRenderer();
	virtual void CreateInputManagement();
	virtual void CreateScene();
	virtual void CreatePhysicsSystem();

private:
	USharedPtr<UWindow> Window;
	USharedPtr<UGameInstance> GameInstance;
	USharedPtr<BRenderer> Renderer;
	USharedPtr<UScene> Scene;
	USharedPtr<UInputManagement> InputManagement;
	USharedPtr<UPhysicsSystem> PhysicsSystem;

	UController* Controller;

	void Loop();
	void CalculeDeltaTime(FTime& currentTime, float& deltaTime);

	friend class BClass;
};

#endif // !US_APPLICATION_HPP

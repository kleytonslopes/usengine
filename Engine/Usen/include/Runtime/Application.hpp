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
#include "Application-generated.hpp"

class UWindow;
class UGameInstance;
class UScene;
class UController;
class UInputManagement;

//#define CLASSOF(A) A

DECLARE_FUNCTION_OneParam(FOnUpdateSignature, float, deltaTime)

class UApplication : public IWeakClass
{
	DEFAULT_BODY_GENERATED()

public:
	FOnUpdateSignature OnUpdateEvent;

	explicit UApplication();
	virtual ~UApplication();
	
	void Run();

	// Inherited via IWeakClass
	void Create() override;
	void PostCreate() override;
	void Initialize() override;
	void PostInitialize() override;
	void Destroy() override;
	void PostDestroy() override;

	template<typename T>
	T* GetRenderer()
	{
		return static_cast<T*>(Renderer.Get());
	}

	BRenderer* GetRenderer() { return Renderer.Get(); };

protected:
	TClassOf<UGameInstance> DefaultGameInstance;
	TClassOf<BRenderer> DefaultRenderer;

	virtual void CreateWindow();
	virtual void CreateGameInstance();
	virtual void CreateRenderer();
	virtual void CreateInputManagement();
	virtual void CreateScene();
	virtual void CreateController();

private:
	USharedPtr<UWindow> Window;
	USharedPtr<UGameInstance> GameInstance;
	USharedPtr<BRenderer> Renderer;
	USharedPtr<UScene> Scene;
	USharedPtr<UInputManagement> InputManagement;

	UController* Controller;

	void Loop();
	void CalculeDeltaTime(FTime& currentTime, float& deltaTime);

	friend class BClass;
};

#endif // !US_APPLICATION_HPP

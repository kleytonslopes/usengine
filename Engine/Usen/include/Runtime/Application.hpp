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
#include "Framework/Scene.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"
#include "Renderer/Renderer.hpp"
#include "Application-generated.hpp"

class UWindow;
class UGameInstance;
class UScene;
class UController;
class UInputManagement;

class UApplication : public IWeakClass
{
	DEFAULT_BODY_GENERATED()

public:
	explicit UApplication();
	~UApplication() final;

	void Run();

	// Inherited via IWeakClass
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

	template<typename T>
	void RegistryClass();

private:
	UUniquePtr<UWindow> Window;
	UUniquePtr<UGameInstance> GameInstance;
	UUniquePtr<BRenderer> Renderer;
	UUniquePtr<UScene> Scene;
	UUniquePtr<UController> Controller;
	UUniquePtr<UInputManagement> InputManagement;

	void Loop();
	void CalculeDeltaTime(FTime& currentTime, float& deltaTime);

	friend class BClass;
};

#endif // !US_APPLICATION_HPP

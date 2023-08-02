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
#include <iostream>
#include "Application-generated.hpp"

class UWindow;
class UGameInstance;
class UScene;
class UController;
class UInputManagement;

#define EX(A,B) A##->B()
#define EXECI(A, B) EX(A,B)
#define EXEC(A, B) EXECI(A,B);

//#define AdIn(A, B, C) (A##,##B, C)
//#define AddIn(A, B, C) AdIn(A,##B,C)
//#define Add(A,...) AddIn(A, ##__VA_ARGS__##)



//#define Add(Object, Function) Add_Intern(Object, Function)
#define Add(Object, Function) Add_Intern(Object, Function, #Function)
#define Add2(Object, Function) Add_Inter2(Object, Function)



class BClass;
class UWIndow;

struct FFunction
{
	std::function<void()> Exec;
	void* Target = nullptr;

	template<class T>
	void SetTarget(T* target)
	{
		Target = target;
	}
};

class OAppOnUpdate
{
	typedef void Execute();
public:
	OAppOnUpdate(){}
	virtual ~OAppOnUpdate(){}

	template<class ClassType, typename ... Args>
	void Add_Inter2(ClassType* InClass, Args&& ... args)
	{
		function.Exec = std::bind(std::forward<Args>(args)..., InClass);
		function.SetTarget(InClass);
	}

	void Call()
	{
		function.Exec();
	}

	FFunction function;

	TVector<Execute*> obs;
};

class UApplication : public IWeakClass
{
	DEFAULT_BODY_GENERATED()

public:
	OAppOnUpdate OnUpdate;

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

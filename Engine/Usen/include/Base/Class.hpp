/*********************************************************************
 *   File: Class.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CLASS_HPP
#define	US_CLASS_HPP


#include "Weaks/WeakClass.hpp"
#include "Class-generated.hpp"

class UApplication;
class UWindow;
class UGameInstance;
class UScene;
class BRenderer;
class UController;
class UInputManagement;
class URendererOpenGL;
class UGameModeBase;
class UPhysicsSystem;

class BClass : public IWeakClass
{
	DEFAULT_BODY_GENERATED()
	
	void* operator new(size_t sz)
	{
		return new char[sz];
	}
public:
	BClass();
	virtual ~BClass();
	virtual void Update(float deltaTime) { /* override */ };

protected:
	UWindow* GetWindow();
	UGameInstance* GetGameInstance();
	UScene* GetScene();
	UController* GetController();
	UInputManagement* GetInputManagement();
	UApplication* GetApplication();
	BRenderer* GetRenderer();
	UGameModeBase* GetGameMode();
	UPhysicsSystem* GetPhysicsSystem();

	template<typename R>
	R* GetRenderer()
	{
		return static_cast<R*>(GetRenderer());
	}

private:
	UApplication* Application = nullptr;

	friend class UScene;
	friend class FConstructorHelper;
};

#endif // !US_CLASS_HPP


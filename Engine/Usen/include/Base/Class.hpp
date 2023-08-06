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

class BClass : public IWeakClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit BClass();
	~BClass() override;

	/// <summary>
	/// Call at Last Initialize overridden function
	/// </summary>
	void Initialize() override;
	void PostInitialize() override;
	void Create() override;
	void PostCreate() override;
	void Destroy() override;
	void PostDestroy() override { /* override */ };

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
	template<typename R>
	R* GetRenderer()
	{
		return static_cast<R*>(GetRenderer());
	}

private:
	UApplication* Application = nullptr;

	friend class UScene;
};

#endif // !US_CLASS_HPP


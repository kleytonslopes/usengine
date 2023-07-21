/*********************************************************************
 *   File: Application.hpp
 *  Brief:
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_APPLICATION_HPP
#define	US_APPLICATION_HPP

#include "Core/WeakClass.hpp"

class UWindow;
class UGameInstance;
class UScene;
class URenderer;

class UApplication : public UWeakClass
{
	DEFAULT_BODY(UWeakClass);
public:
	UApplication();

	virtual ~UApplication();

	void Run();

	UWindow* GetWindow();
	UGameInstance* GetGameInstance();
	URenderer* GetRenderer();
	UScene* GetScene();

	void Initialize() override;
	void OnInitialized() override;
	void Update(float deltaTime) override;

protected:
	UUniquePtr<UWindow> window;
	UUniquePtr<UGameInstance> gameInstance;
	UUniquePtr<URenderer> renderer;
	UUniquePtr<UScene> currentScene;

private:
	void Loop();
	void CalculeDeltaTime(FTime& currentTime, float& deltaTime);
};

#endif // !US_APPLICATION_HPP
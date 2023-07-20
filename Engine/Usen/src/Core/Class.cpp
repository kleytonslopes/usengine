/*********************************************************************
 *   File: Class.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Class.hpp"

#include "Presentation/Window.hpp"
#include "Runtime/Application.hpp"
#include "Framework/Scene.hpp"
#include "Renderer/Renderer.hpp"

UClass::UClass(UApplication* application) : application{ application }
{

}

UClass::~UClass()
{
}

UWindow* UClass::GetWindow()
{
    return application->GetWindow();
}

UApplication* UClass::GetApplication()
{
    return application;
}

URenderer* UClass::GetRenderer()
{
    return application->GetRenderer();
}

UScene* UClass::GetScene()
{
    return application->GetScene();
}

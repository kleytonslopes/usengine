/*********************************************************************
 *   File: Class.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CLASS_HPP
#define	US_CLASS_HPP

#include "Core/Core.hpp"
#include "Core/WeakClass.hpp"
#include "Class-generated.hpp"

class UWindow;
class UApplication;
class URenderer;
class UScene;

class UClass : public UWeakClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UClass(UApplication* application);
	virtual ~UClass();

	UWindow* GetWindow();
	UApplication* GetApplication();
	URenderer* GetRenderer();
	UScene* GetScene();

protected:
	UApplication* application = nullptr;
};

#endif // !US_CLASS_HPP
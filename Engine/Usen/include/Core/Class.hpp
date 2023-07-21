/*********************************************************************
 *   File: Class.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CLASS_HPP
#define	US_CLASS_HPP

#include "Core/WeakClass.hpp"

class UWindow;
class UApplication;
class URenderer;
class UScene;

class UClass : public UWeakClass
{
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
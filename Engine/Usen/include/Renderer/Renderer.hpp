/*********************************************************************
 *   File: Renderer.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once


#ifndef US_RENDERER_HPP
#define	US_RENDERER_HPP

#include "Core/Class.hpp"

class URenderer : public UClass
{
	using Super = UClass;
public:
	using UClass::UClass;
	virtual ~URenderer();

	void Initialize() override;
	void OnInitialized()  override;
	void Update(float deltaTime) override;
	void OnDestroy();

	void Draw();
};

#endif // !US_RENDERER_HPP

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
#include "Renderer/ShaderParameters.hpp"

class UShader;

class URenderer : public UClass
{
	DEFAULT_BODY(UClass);
public:
	virtual ~URenderer();

	void Initialize() override;
	void OnInitialized()  override;
	void Update(float deltaTime) override;
	void OnDestroy();

	void Draw();

	template<typename T>
	T* CreateShader(const FShaderParameters& parameters);

private:
	TMap<FString, UShader*> shaders;
};

#endif // !US_RENDERER_HPP

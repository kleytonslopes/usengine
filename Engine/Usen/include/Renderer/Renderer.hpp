/*********************************************************************
 *   File: Renderer.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_RENDERER_HPP
#define	US_RENDERER_HPP


#include "Base/Class.hpp"
#include "Renderer/ShaderParameters.hpp"
#include "Renderer-generated.hpp"

class BShader;
class AEntity;

class BRenderer : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit BRenderer();
	virtual ~BRenderer();

	void Draw(AEntity* entity, float deltaTime);

	template<typename T>
	T* CreateShader(const FShaderParameters& parameters);

protected:
	TMap<FString, BShader*> Shaders;
};

#endif // !US_RENDERER_HPP
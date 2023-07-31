/*********************************************************************
 *   File: RenderComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_RENDER_COMPONENT_HPP
#define	US_RENDER_COMPONENT_HPP


#include "Components/Component.hpp"
#include "RenderComponent-generated.hpp"

class BShader;

class URenderComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	explicit URenderComponent();
	virtual ~URenderComponent();

	void SetShader(BShader* shader);
protected:
	BShader* Shader = nullptr;
};

#endif // !US_RENDER_COMPONENT_HPP
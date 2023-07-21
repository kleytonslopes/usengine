/*********************************************************************
 *   File: RendererComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CAMERA_COMPONENT_HPP
#define	US_CAMERA_COMPONENT_HPP

#include "Components/Interface/IComponent.hpp"

class URendererComponent : public IComponent
{
	DEFAULT_BODY(IComponent);

public:
	URendererComponent() = default;

	void Initialize() override;
	
};

#endif // !US_CAMERA_COMPONENT_HPP
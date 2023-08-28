/*********************************************************************
 *   File: ArrowComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ARROW_COMPONENT_HPP
#define	US_ARROW_COMPONENT_HPP


#include "Components/Component.hpp"
#include "ArrowComponent-generated.hpp"

class UArrowComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:

private:
	FColor Color;
	FTransform Transform;
};

#endif // !US_ARROW_COMPONENT_HPP
/*********************************************************************
 *   File: UpdateComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_UPDATE_COMPONENT_HPP
#define	US_UPDATE_COMPONENT_HPP


#include "Components/Component.hpp"
#include "UpdateComponent-generated.hpp"

DECLARE_FUNCTION_OneParam(FOnUpdateCalledSignature, float, deltaTime)

class UUpdateComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	FOnUpdateCalledSignature OnUpdateCalledEvent;
};

#endif // !US_UPDATE_COMPONENT_HPP
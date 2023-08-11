/*********************************************************************
 *   File: CapsuleComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CAPSULE_COMPONENT_HPP
#define	US_CAPSULE_COMPONENT_HPP


#include "Components/CollisionComponent.hpp"
#include "CapsuleComponent-generated.hpp"

class UCapsuleComponent : public UCollisionComponent
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;

	void Initialize() override;

private:

};

#endif // !US_CAPSULE_COMPONENT_HPP
/*********************************************************************
 *   File: BoxCollisionComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_BOX_COLLISION_COMPONENT_HPP
#define	US_BOX_COLLISION_COMPONENT_HPP


#include "Components/CollisionComponent.hpp"
#include "BoxCollisionComponent-generated.hpp"


class UBoxCollisionComponent : public UCollisionComponent
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Destroy() override;
};

#endif // !US_BOX_COLLISION_COMPONENT_HPP
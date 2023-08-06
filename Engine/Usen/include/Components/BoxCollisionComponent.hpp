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
	explicit UBoxCollisionComponent();
	virtual ~UBoxCollisionComponent();

	void Create() override;
	void Destroy() override;

	void CalculeLocalInertia() override;
	btRigidBody* CreateRigidBody() override;
	FVector GetLocation() override;

private:
	FVector BoundBox{ 1.f, 1.f, 1.f };
	btBoxShape* Shape = nullptr;

	friend class UPhysicsSystem;
};

#endif // !US_BOX_COLLISION_COMPONENT_HPP
/*********************************************************************
 *   File: CollisionComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_COLLISION_COMPONENT_HPP
#define	US_COLLISION_COMPONENT_HPP


#include "Components/Component.hpp"
#include "CollisionComponent-generated.hpp"

class UCollisionComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UCollisionComponent();
	virtual ~UCollisionComponent();

	virtual void CalculeLocalInertia() { /* override */ };
	virtual btRigidBody* CreateRigidBody() { return nullptr; }
protected:
	bool bIsDynamic = false;
	float Mass = 100.f;
	btVector3 LocalInertia{ 0.f, 0.f, 0.f };
	btTransform StartTransform;

	btRigidBody* Body = nullptr;
private:

	friend class UPhysicsSystem;
};

#endif // !US_COLLISION_COMPONENT_HPP
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
	virtual void CalculeLocalInertia() { /* override */ };
	virtual btRigidBody* CreateRigidBody() { return nullptr; }
	
	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;

	void SetIsDynamic(const bool& isDynamic);

	bool IsDynamic() const { return bIsDynamic; }
	virtual FVector GetComponentLocation();
	virtual void SetOrigin(FVector& location);

protected:
	bool bIsDynamic = true;
	float Mass = 10.f;

	btVector3 LocalInertia{ 100.f, 0.f, 0.f };
	btTransform StartTransform;

	btRigidBody* Body = nullptr;

	// FVector GetLocationCalculated(const btVector3& btLocation);

private:
	float DefaultMass = 0.f;

	friend class UPhysicsSystem;
};

#endif // !US_COLLISION_COMPONENT_HPP
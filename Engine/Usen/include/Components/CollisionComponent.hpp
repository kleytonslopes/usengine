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
#include "Components/TransformComponent.hpp"
#include "CollisionComponent-generated.hpp"

class UCollisionComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	virtual void CalculeLocalInertia() { /* override */ };
	virtual btRigidBody* CreateRigidBody() { return nullptr; }
	virtual btCollisionObject* CreateCollisionObject() { return nullptr; }
	
	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;

	void SetIsDynamic(const bool& isDynamic);

	bool IsDynamic() const { return bIsDynamic; }
	virtual FVector GetComponentLocation();
	
	void SetLocation(FVector& location);
	void SetTransform(FTransform& transform);
	
	void SetCollisionGroup(ECollisionGroup collisionGroup);
	void SetCollisionMask(ECollisionMask collisionMask);

	ECollisionGroup GetCollisionGroup() const { return CollisionGroup; }
	ECollisionMask GetCollisionMask() const { return CollisionMask; }

protected:
	bool bIsDynamic = true;
	float Mass = 10.f;
	ECollisionGroup CollisionGroup = ECG_WorldStatic;
	ECollisionMask CollisionMask = ECM_WorldStatic;

	btVector3 LocalInertia{ 0.f, 0.f, 0.f };
	btTransform Transform;

	btRigidBody* Body = nullptr;

private:
	float DefaultMass = 100.f;

	friend class UPhysicsSystem;
};

#endif // !US_COLLISION_COMPONENT_HPP
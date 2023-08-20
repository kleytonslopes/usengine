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

DECLARE_FUNCTION_OneParam(FOnTransformUpdatedSignature, FTransform, newTransform);

class UCollisionComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	FOnTransformUpdatedSignature OnTransformUpdatedEvent;

	virtual void CalculeLocalInertia() { /* override */ };
	virtual void SetBoundBox(const FVector& boundBox) { /* override */ }
	virtual btRigidBody* CreateRigidBody() { return nullptr; }
	virtual btCollisionObject* CreateCollisionObject() { return nullptr; }
	
	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;
	void Update(float deltaTime) override;

	void SetIsDynamic(const bool& isDynamic);
	void SetCanCollider(const bool& canCollider);

	bool IsDynamic() const { return bIsDynamic; }
	bool CanCollider() const { return bCanCollider; }
	virtual FVector GetComponentLocation();
	virtual FVector GetComponentRotation();
	
	void SetLocation(FVector location);
	void SetTransform(FTransform& transform);
	
	
	void SetCollisionGroup(ECollisionGroup collisionGroup);
	void SetCollisionMask(ECollisionMask collisionMask);

	ECollisionGroup GetCollisionGroup() const { return CollisionGroup; }
	ECollisionMask GetCollisionMask() const { return CollisionMask; }

protected:
	bool bIsDynamic = true;
	bool bCanCollider = true;

	float Mass = 10.f;
	ECollisionGroup CollisionGroup = ECG_WorldStatic;
	ECollisionMask CollisionMask = ECM_WorldStatic;
	ECollisionObject CollisionObjectType = ECO_Static;

	btVector3 LocalInertia{ 0.f, 0.f, 0.f };
	btTransform Transform;

	btRigidBody* Body = nullptr;

	void UpdateParentTransform();

private:
	float DefaultMass = 100.f;

	friend class UPhysicsSystem;
};

#endif // !US_COLLISION_COMPONENT_HPP
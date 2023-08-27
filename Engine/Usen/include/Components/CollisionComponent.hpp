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
#include "Physics/PhysicsShapeInitialize.hpp"
#include "CollisionComponent-generated.hpp"

DECLARE_FUNCTION_OneParam(FOnTransformUpdatedSignature, FTransform, newTransform);

enum class EBodyType : uint8
{
	EBT_Static  = 0,
	EBT_Dynamic = 1
};

class UCollisionComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	FOnTransformUpdatedSignature OnTransformUpdatedEvent;

	virtual void CalculeLocalInertia() { /* override */ };
	
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
	
	void SetBoundBox(const FVector& boundBox);
	void SetLocation(FVector location);
	void SetTransform(FTransform& transform);
	void SetBodyType(EBodyType bodyType);
	void SetPhysicsShapeInitialize(const FPhysicsShapeInitialize& physicsShapeInitialize);
	
	FVector GetBoundBox();
	void SetCollisionGroup(ECollisionGroup collisionGroup);
	void SetCollisionMask(ECollisionMask collisionMask);

	ECollisionGroup GetCollisionGroup() const { return CollisionGroup; }
	ECollisionMask GetCollisionMask() const { return CollisionMask; }

protected:
	bool bIsDynamic = true;
	bool bCanCollider = true;

	float Mass = 10.f;

	EBodyType BodyType = EBodyType::EBT_Static;
	FPhysicsShapeInitialize PhysicsShapeInitialize{};

	ECollisionGroup CollisionGroup = ECG_WorldStatic;
	ECollisionMask CollisionMask = ECM_WorldStatic;
	ECollisionObject CollisionObjectType = ECO_Static;

	FVector BoundBox{ 1.f, 1.f, 1.f };
	FVector Inertia{ 0.f, 0.f, 0.f };
	FVector Position{ 0.f, 0.f, 0.f };

	/* Bullet */
	btVector3 LocalInertia{ 0.f, 0.f, 0.f };
	btTransform Transform;
	btRigidBody* Body = nullptr;
	btCollisionObject* CollisionObject = nullptr;
	/* Bullet */

	/* PhysX */
	physx::PxRigidStatic* BodyStatic = nullptr;
	physx::PxRigidDynamic* BodyDynamic = nullptr;
	//physx::PxShape* ShapeX = nullptr;
	/* PhysX */

	void UpdateParentTransform();

private:
	float DefaultMass = 100.f;

	friend class UPhysicsSystem;
};

#endif // !US_COLLISION_COMPONENT_HPP
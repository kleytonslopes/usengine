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
#include "Components/MovementComponent.hpp"
#include "CapsuleComponent-generated.hpp"

class UCapsuleComponent : public UCollisionComponent
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;
	void Destroy() override;
	void Update(float deltaTime) override;
	void CalculeLocalInertia() override;
	void AddForwardMovement(float scaleMovement);
	void AddRightMovement(float scaleMovement);
	void AddMovement(float scaleMovement, float speed, EAxis axis);
	virtual FVector GetWorldPosition() override;

	btRigidBody* CreateRigidBody() override;

protected:
	btCapsuleShape* CreateCapsuleShape();

private:

	btCapsuleShape* Shape = nullptr;
	float Radius = 1.f;
	float Height = 1.f;


	physx::PxController* CapsuleController = NULL;
	
	friend class UPhysicsSystem;
};

#endif // !US_CAPSULE_COMPONENT_HPP
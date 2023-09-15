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
	void AddMovement(float scaleMovement, float speed, FVector axis);
	void HandleJump(const FVector& startLocation, const FVector& targetLocation);
	void StopJump();
	void CalculeJump(FVector& nextLocation, bool& reached);
	virtual FVector GetWorldPosition() override;

	bool IsJumping() const { return bIsJumping; }
	bool IsInAir() const { return bIsInAir; }
	bool CanHandleJump() const;

private:
	float Radius = 1.f;
	float Height = 1.f;

	//float JumpHeight = 3.f;
	bool bIsJumping = false;
	bool bIsInAir = false;
	struct {
		FVector startPoint;
		FVector endPoint;
	} JumpEventParameters;

	physx::PxController* CapsuleController = NULL;
	
	friend class UPhysicsSystem;
};

#endif // !US_CAPSULE_COMPONENT_HPP
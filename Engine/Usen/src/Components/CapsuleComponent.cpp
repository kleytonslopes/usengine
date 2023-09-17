/*********************************************************************
 *   File: CapsuleComponent.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Components/CapsuleComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Physics/PhysicsSystemPhysX.hpp"
#include "Mesh/Mesh.hpp"
#include "Runtime/Application.hpp"

DEFAULT_BODY(UCapsuleComponent)

void UCapsuleComponent::Construct()
{
	Super::Construct();

	BodyType = EBodyType::EBT_Dynamic;
	bIsDynamic = true;
	bCanUpdate = true;
	Mass = 70.f;
}

void UCapsuleComponent::PostConstruct()
{
	Super::PostConstruct();

	physx::PxCapsuleControllerDesc desc;
	desc.height = 1.f;
	desc.scaleCoeff = 1.f;
	desc.volumeGrowth = 1.9f;
	desc.nonWalkableMode = physx::PxControllerNonWalkableMode::ePREVENT_CLIMBING;
	desc.radius = 0.5f;
	desc.contactOffset = 0.05f;
	desc.stepOffset = 0.01f;
	desc.material = GetPhysicsSystemPhysX()->Material;

	CapsuleController = GetPhysicsSystemPhysX()->ControllerManager->createController(desc);

}

void UCapsuleComponent::Initialize()
{
	Super::Initialize();
}

void UCapsuleComponent::Destroy()
{
	Super::Destroy();
}

void UCapsuleComponent::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Parent)
	{
		FVector rvec = Parent->GetRotation();

		rvec.y += deltaTime * 2.f;

		Parent->SetRotation(rvec);
	}

	//if (bIsJumping)
	//{
	//	physx::PxControllerFilters filters;
	//	FVector location = CollisionComponent->Getw();
	//	CapsuleController->move(physx::PxVec3{0.f, JumpHeight, 0.f}, 0.f, GetApplication()->GetDeltaTime(), filters);
	//}
}

void UCapsuleComponent::CalculeLocalInertia()
{

}

void UCapsuleComponent::AddForwardMovement(float scaleMovement)
{
	if (CapsuleController)
	{
		physx::PxControllerFilters filters;

		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
		{
			FVector location = aParent->GetLocation();

			physx::PxVec3 disp = physx::PxVec3(scaleMovement, 0.f, 0.f);
			physx::PxF32 dispMin = .001f;
			CapsuleController->move(disp, dispMin, scaleMovement, filters);
		}
	}
}

void UCapsuleComponent::AddRightMovement(float scaleMovement)
{

	AActor* aParent = Cast<AActor*>(Parent);
	if (aParent)
	{
		physx::PxControllerFilters filters;
		FVector location = aParent->GetLocation();

		physx::PxVec3 disp = physx::PxVec3(0.f, 0.f, scaleMovement);
		physx::PxF32 dispMin = 0.001f;
		CapsuleController->move(disp, dispMin, scaleMovement, filters);

	}
}

void UCapsuleComponent::AddMovement(float scaleMovement, float speed, EAxis axis)
{
	AActor* aParent = Cast<AActor*>(Parent);
	if (aParent)
	{
		physx::PxControllerFilters filters;
		FVector location = aParent->GetLocation();

		physx::PxVec3 disp;
		switch (axis)
		{
		case EAxis::X:
			//disp = physx::PxVec3(0.f, 0.f, scaleMovement * speed);
			disp = physx::PxVec3(scaleMovement * speed, 0.f, 0.f);
			break;
		case EAxis::Y:
			disp = physx::PxVec3(0.f, scaleMovement * speed, 0.f);
			//disp = physx::PxVec3(0.f, scaleMovement * speed, 0.f);
			break;
		case EAxis::Z:
			disp = physx::PxVec3(0.f, 0.f, scaleMovement * speed);
			//disp = physx::PxVec3(scaleMovement * speed, 0.f, 0.f);
			break;
		}

		physx::PxF32 dispMin = 0.001f;
		CapsuleController->move(disp, dispMin, scaleMovement, filters);
	}
}

void UCapsuleComponent::AddMovement(float scaleMovement, float speed, FVector axis)
{
	AActor* aParent = Cast<AActor*>(Parent);
	if (aParent)
	{
		physx::PxControllerFilters filters;
		FVector location = aParent->GetLocation();

		physx::PxVec3 disp;

		disp = physx::PxVec3(axis.x * speed * scaleMovement, axis.y * speed * scaleMovement, axis.z * speed * -scaleMovement);

		physx::PxF32 dispMin = 0.001f;
		CapsuleController->move(disp, dispMin, scaleMovement, filters);
	}
}

void UCapsuleComponent::AddMovement(FVector direction)
{
	AActor* aParent = Cast<AActor*>(Parent);
	if (aParent)
	{
		physx::PxControllerFilters filters;
		FVector location = aParent->GetLocation();

		physx::PxVec3 disp;

		disp = physx::PxVec3(direction.x, direction.y, direction.z);

		physx::PxF32 dispMin = 0.001f;
		CapsuleController->move(disp, dispMin, 1.f, filters);
	}
}

void UCapsuleComponent::HandleJump(const FVector& startLocation, const FVector& targetLocation)
{
	//physx::PxControllerState controlState;
	//CapsuleController->getState(controlState);
	bIsJumping = true;
	bIsInAir = true;
	JumpEventParameters.startPoint = startLocation;
	JumpEventParameters.endPoint = targetLocation;
}

void UCapsuleComponent::StopJump()
{
	bIsJumping = false;

	JumpEventParameters.startPoint = FVector{ 0 };
	JumpEventParameters.endPoint = FVector{ 0 };
}

void UCapsuleComponent::CalculeJump(FVector& nextLocation, bool& reached)
{
	if (nextLocation.y >= JumpEventParameters.endPoint.z)
	{
		reached = true;
		nextLocation.y = JumpEventParameters.endPoint.z;
	}
	else
		reached = false;
}

FVector UCapsuleComponent::GetWorldPosition()
{
	if (CapsuleController)
	{

		physx::PxExtendedVec3 newLocation = CapsuleController->getPosition();
		return FVector(newLocation.x, newLocation.y, newLocation.z);
	}
	return FVector(0.f, 0.f, 0.f);
}

bool UCapsuleComponent::CanHandleJump() const
{
	return !bIsJumping;// && !bIsInAir;
}

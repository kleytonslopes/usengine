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
#include "Physics/PhysicsSystem.hpp"
#include "Physics/PhysicsSystemPhysX.hpp"
#include "Mesh/Mesh.hpp"

DEFAULT_BODY(UCapsuleComponent)

void UCapsuleComponent::Construct()
{
	Super::Construct();

	BodyType = EBodyType::EBT_Dynamic;
	CollisionObjectType = ECO_Character;
	bIsDynamic = true;
	bCanUpdate = true;

	//if (Parent)
	//{
	//	AMesh* meshParent = Cast<AMesh*>(Parent);
	//	if (meshParent)
	//	{
	//		Shape = CreateCapsuleShape();// new btBoxShape(btVector3{ boundBox.x, boundBox.y, boundBox.z });
	//	}
	//	else
	//		Shape = CreateCapsuleShape();// new btBoxShape(btVector3{ 1, 1, 1 });
	//}
	//else
	//	Shape = CreateCapsuleShape();//new btBoxShape(btVector3{ 1, 1, 1 });
}

void UCapsuleComponent::PostConstruct()
{
	Super::PostConstruct();

	//GetPhysicsSystem()->RegisterComponent(this);

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

	//if (CapsuleController)
	//{
	//	physx::PxControllerFilters filters;
	//	physx::PxVec3 disp = physx::PxVec3(0.f, deltaTime * -10.f, 0.f);//physx::PxVec3(location.x, location.y, location.z);
	//	physx::PxF32 dispMin = 0.001f;
	//	CapsuleController->move(disp, dispMin, deltaTime, filters);
	//}

	if (Body)
	{
		//Body->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
		//btTransform transform = Body->getWorldTransform();
		//btQuaternion quat = transform.getRotation();
		//quat.setZ(90.f);
		//quat.setY(90.f);


		//transform.setRotation(quat);
		//Body->setWorldTransform(transform);
	}
}

void UCapsuleComponent::CalculeLocalInertia()
{
	/*if(Shape)
		Shape->calculateLocalInertia(Mass, LocalInertia);*/
}

void UCapsuleComponent::AddForwardMovement(float scaleMovement)
{
	if (CapsuleController)
	{
		/*
		\param[in] disp	Displacement vector
		\param[in] minDist The minimum travelled distance to consider. If travelled distance is smaller, the character doesn't move.
	This is used to stop the recursive motion algorithm when remaining distance to travel is small.
		\param[in] elapsedTime Time elapsed since last call
		\param[in] filters User-defined filters for this move
		\param[in] obstacles Potential additional obstacles the CCT should collide with.
		\return Collision flags, collection of ::PxControllerCollisionFlags
		virtual		PxControllerCollisionFlags	move(const PxVec3 & disp, PxF32 minDist, PxF32 elapsedTime, const PxControllerFilters & filters, const PxObstacleContext * obstacles = NULL) = 0;

		*/

		physx::PxControllerFilters filters;

		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
		{
			FVector location = aParent->GetLocation();

			physx::PxVec3 disp = physx::PxVec3(scaleMovement, 0.f, 0.f);//physx::PxVec3(location.x, location.y, location.z);
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

		physx::PxVec3 disp = physx::PxVec3(0.f, 0.f, scaleMovement);//physx::PxVec3(location.x, location.y, location.z);
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
			disp = physx::PxVec3(scaleMovement * speed, 0.f, 0.f);
			break;
		case EAxis::Y:
			disp = physx::PxVec3(0.f, scaleMovement * speed, 0.f);
			break;
		case EAxis::Z:
			disp = physx::PxVec3(0.f, 0.f, scaleMovement * speed);
			break;
		}

		physx::PxF32 dispMin = 0.001f;
		CapsuleController->move(disp, dispMin, scaleMovement, filters);
	}
}

FVector UCapsuleComponent::GetWorldPosition()
{
	physx::PxExtendedVec3 newLocation = CapsuleController->getPosition();
	return FVector(newLocation.x, newLocation.z, newLocation.y);
}

btRigidBody* UCapsuleComponent::CreateRigidBody()
{
	if (!bCanCollider)
		return nullptr;

	//btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	//btRigidBody::btRigidBodyConstructionInfo rbInfo(Mass, motionState, Shape, LocalInertia);
	//
	//Body = new btRigidBody(rbInfo);
	//Body->setCollisionFlags(Body->getCollisionFlags() | CollisionObjectType);// btCollisionObject::CF_KINEMATIC_OBJECT);
	//Body->setActivationState(DISABLE_DEACTIVATION);
	//Body->setAngularFactor(btVector3(0.0f, 0.0f, 0.0f));

	//btTransform transform;
	//Body->getMotionState()->getWorldTransform(transform);
	//transform.setRotation(btQuaternion(0, -90, 0));
	//Body->setWorldTransform(transform);
	return nullptr;
}

btCapsuleShape* UCapsuleComponent::CreateCapsuleShape()
{
	if (!bCanCollider)
		return nullptr;

	//Shape = new btCapsuleShape(Radius, Height);
	return nullptr;
}

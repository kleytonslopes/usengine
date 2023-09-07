/*********************************************************************
 *   File: CollisionComponent.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Components/CollisionComponent.hpp"
#include "Actors/Actor.hpp"
#include "Physics/PhysicsSystemPhysX.hpp"

DEFAULT_BODY(UCollisionComponent)

void UCollisionComponent::Construct()
{
	Super::Construct();

	bCanUpdate = true;
	DefaultMass = Mass;
}

void UCollisionComponent::PostConstruct()
{
	Super::PostConstruct();

	if (!bIsDynamic)
		Mass = 0.f;

	AFTransform trasnform = GetParentTransform();

	Transform.setIdentity();
	SetTransform(trasnform);

	switch (BodyType)
	{
	case EBodyType::EBT_Static:
		//ShapeX = GetPhysicsSystemPhysX()->CreateShape(BodyDynamic, physicsShapeInitialize);
		BodyStatic = GetPhysicsSystemPhysX()->CreateRigidStatic(PhysicsShapeInitialize, trasnform);
		break;
	case EBodyType::EBT_Dynamic:
		BodyDynamic = GetPhysicsSystemPhysX()->CreateRigidDynamic(PhysicsShapeInitialize, trasnform);
		break;
	default:
		break;
	}
}

void UCollisionComponent::Initialize()
{
	Super::Initialize();

	//if (Parent)
	//{
	//	AActor* pActor = Cast<AActor*>(Parent);
	//	if (pActor && Body)
	//	{
	//		FTransform transform = pActor->GetTransform();
	//		btTransform transf;
	//		transf.setOrigin(btVector3(transform.Location.x, transform.Location.y, transform.Location.z));
	//		transf.setRotation(btQuaternion(transform.Rotation.x, transform.Rotation.y, transform.Rotation.z));
	//	}
	//}
}

void UCollisionComponent::Update(float deltaTime)
{
	Super::Update(deltaTime);

	//UpdateParentTransform();
}

void UCollisionComponent::SetBoundBox(const FVector& boundBox)
{
	BoundBox.x = boundBox.x;
	BoundBox.y = boundBox.y;
	BoundBox.z = boundBox.z;
}

void UCollisionComponent::SetIsDynamic(const bool& isDynamic)
{
	if (isDynamic)
	{
		bIsDynamic = true;
		Mass = DefaultMass;
	}
	else
	{
		bIsDynamic = false;
		Mass = 0.f;
	}
}

void UCollisionComponent::SetCanCollider(const bool& canCollider)
{
	bCanCollider = canCollider;
}

FVector UCollisionComponent::GetComponentLocation()
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	AActor* parentActor = Cast<AActor*>(Parent);/*GetParent<AActor>();*/
	if (parentActor)
	{
		const FVector location = parentActor->GetLocation();

		x = location.x;
		y = location.y;
		z = location.z;
	}

	return FVector{ x, y, z };
}

FVector UCollisionComponent::GetComponentRotation()
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	AActor* parentActor = GetParent<AActor>();
	if (parentActor)
	{
		const FVector rotation = parentActor->GetRotation();

		x = rotation.x;
		y = rotation.y;
		z = rotation.z;
	}

	return FVector{ x, y, z };
}

FVector UCollisionComponent::GetWorldPosition()
{
	if (BodyStatic || BodyDynamic)
	{
		physx::PxTransform transform;
		switch (BodyType)
		{
		case EBodyType::EBT_Static:
			transform = BodyStatic->getGlobalPose();
			break;
		case EBodyType::EBT_Dynamic:
			transform = BodyDynamic->getGlobalPose();
			break;
		}

		return FVector(transform.p.x, transform.p.y, transform.p.z);
	}
	else
		return FVector(0.f, 0.f, 0.f);
}

void UCollisionComponent::SetLocation(FVector location)
{
	switch (BodyType)
	{
	case EBodyType::EBT_Static:
	{
		if (BodyStatic)
		{
			physx::PxTransform transform(physx::PxVec3(location.x, location.y, location.z));
			BodyStatic->setGlobalPose(transform);
		}
		break;
	}
	case EBodyType::EBT_Dynamic:
	{
		if (BodyDynamic)
		{
			physx::PxTransform transform(physx::PxVec3(location.x, location.y, location.z));
			BodyDynamic->setGlobalPose(transform);
		}
		break;
	}
	}
}

void UCollisionComponent::SetRotation(FVector vector)
{
	switch (BodyType)
	{
	case EBodyType::EBT_Static:
	{
		if (BodyStatic)
		{
			physx::PxTransform currentTransform = BodyStatic->getGlobalPose();
			physx::PxVec3 currentPosition = currentTransform.p;
			physx::PxTransform newTransform(currentPosition);

			physx::PxQuat rotationQuaternion(physx::PxPi / 2.0f, physx::PxVec3(vector.x, vector.y, vector.z));
			newTransform.q = rotationQuaternion;
			//physx::PxTransform transform(physx::PxVec3(location.x, location.y, location.z));
			BodyStatic->setGlobalPose(newTransform);
		}
		break;
	}
	case EBodyType::EBT_Dynamic:
	{
		if (BodyDynamic)
		{
			physx::PxTransform currentTransform = BodyDynamic->getGlobalPose();
			physx::PxVec3 currentPosition = currentTransform.p;
			physx::PxTransform newTransform(currentPosition);

			physx::PxQuat rotationQuaternion(physx::PxPi / 2.0f, physx::PxVec3(vector.x, vector.y, vector.z));
			newTransform.q = rotationQuaternion;
			//physx::PxTransform transform(physx::PxVec3(location.x, location.y, location.z));
			BodyDynamic->setGlobalPose(newTransform);

			//physx::PxTransform transform(physx::PxVec3(location.x, location.y, location.z));
			//BodyDynamic->setGlobalPose(transform);
		}
		break;
	}
	}
}

//void UCollisionComponent::SetUpVector(FVector vector)
//{
//}

void UCollisionComponent::SetTransform(AFTransform& transform)
{

}

void UCollisionComponent::SetBodyType(EBodyType bodyType)
{
	BodyType = bodyType;
}

void UCollisionComponent::SetPhysicsShapeInitialize(const FPhysicsShapeInitialize& physicsShapeInitialize)
{
	PhysicsShapeInitialize = physicsShapeInitialize;
}

FVector UCollisionComponent::GetBoundBox()
{
	return BoundBox;
}

void UCollisionComponent::SetCollisionGroup(ECollisionGroup collisionGroup)
{
	CollisionGroup = collisionGroup;
}

void UCollisionComponent::SetCollisionMask(ECollisionMask collisionMask)
{
	CollisionMask = collisionMask;
}

void UCollisionComponent::UpdateParentTransform()
{
	AActor* aParent = Cast<AActor*>(Parent);
	if (aParent)
	{
		aParent->SetLocation(GetComponentLocation());
		aParent->SetRotation(GetComponentRotation());
	}
}

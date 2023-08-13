/*********************************************************************
 *   File: BoxCollisionComponent.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Components/BoxCollisionComponent.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Mesh/Mesh.hpp"

DEFAULT_BODY(UBoxCollisionComponent);

void UBoxCollisionComponent::Construct()
{
	Super::Construct();

	if (Parent)
	{
		AMesh* meshParent = Cast<AMesh*>(Parent);
		if (meshParent)
		{
			const FVector boundBox = meshParent->GetBoundBox();
			Shape = CreateBoxShape(boundBox);// new btBoxShape(btVector3{ boundBox.x, boundBox.y, boundBox.z });
		}
		else
			Shape = CreateBoxShape(FVector{1.f, 1.f, 1.f});// new btBoxShape(btVector3{ 1, 1, 1 });
	}
	else
		Shape = CreateBoxShape(FVector{1.f, 1.f, 1.f});//new btBoxShape(btVector3{ 1, 1, 1 });


	/*GetPhysicsSystem()->RegisterComponent(this);*/
}

void UBoxCollisionComponent::PostConstruct()
{
	Super::PostConstruct();

	GetPhysicsSystem()->RegisterComponent(this);
}

void UBoxCollisionComponent::Destroy()
{
	Super::Destroy();
}

void UBoxCollisionComponent::CalculeLocalInertia()
{
	Shape->calculateLocalInertia(Mass, LocalInertia);
}

btRigidBody* UBoxCollisionComponent::CreateRigidBody()
{
	btDefaultMotionState* myMotionState = new btDefaultMotionState(StartTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(Mass, myMotionState, Shape, LocalInertia);
	Body = new btRigidBody(rbInfo);
	return Body;
}

btBoxShape* UBoxCollisionComponent::CreateBoxShape(const FVector& boxBound)
{
	btBoxShape* box = new btBoxShape(btVector3(btScalar(boxBound.x), btScalar(boxBound.y), btScalar(boxBound.z)));

	return box;
}

// FVector UBoxCollisionComponent::GetComponentLocation()
// {
// 	btVector3 scalLocation = Shape->getLocalScaling();

// 	return GetLocationCalculated(scalLocation);
// }
//
//void UBoxCollisionComponent::SetOrigin(FVector& location)
//{
//	Super::SetOrigin(location);
//
//	btVector3 scalLocation;
//	scalLocation.setX(location.x);
//	scalLocation.setY(location.y);
//	scalLocation.setZ(location.z);
//
//	Shape->setLocalScaling(scalLocation);
//}

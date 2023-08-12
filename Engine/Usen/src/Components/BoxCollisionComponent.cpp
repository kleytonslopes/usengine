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

DEFAULT_BODY(UBoxCollisionComponent);

void UBoxCollisionComponent::Construct()
{
	Super::Construct();
	Shape = new btBoxShape(btVector3{ BoundBox.x, BoundBox.y, BoundBox.z });

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

FVector UBoxCollisionComponent::GetComponentLocation()
{
	btVector3 scalLocation = Shape->getLocalScaling();

	return GetLocationCalculated(scalLocation);
}
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

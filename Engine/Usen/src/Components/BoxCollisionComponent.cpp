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

UBoxCollisionComponent::UBoxCollisionComponent()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UBoxCollisionComponent::~UBoxCollisionComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));

}

void UBoxCollisionComponent::Create()
{
	Shape = new btBoxShape(btVector3{ BoundBox.x, BoundBox.y, BoundBox.z });
}

void UBoxCollisionComponent::Destroy()
{
	Super::Destroy();

	delete Body;
	delete Shape;
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

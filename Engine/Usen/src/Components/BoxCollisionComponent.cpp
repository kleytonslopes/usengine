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
#include "Physics/PhysicsSystemPhysX.hpp"
#include "Mesh/Mesh.hpp"

DEFAULT_BODY(UBoxCollisionComponent);

void UBoxCollisionComponent::Construct()
{
	Super::Construct();
}

void UBoxCollisionComponent::PostConstruct()
{
	PhysicsShapeInitialize.InitializeBox(BoundBox.x, BoundBox.y, BoundBox.z);
	PhysicsShapeInitialize.Mass = Mass;

	Super::PostConstruct();

	//GetPhysicsSystem()->RegisterComponent(this);
	/*ShapeX = GetPhysicsSystemPhysX()->CreateShape(BodyDynamic, physicsShapeInitialize);*/
}

void UBoxCollisionComponent::Destroy()
{
	Super::Destroy();
}
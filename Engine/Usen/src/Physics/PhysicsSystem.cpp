/*********************************************************************
 *   File: PhysicsSystem.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Runtime/Application.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/BoxCollisionComponent.hpp"

UPhysicsSystem::UPhysicsSystem()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UPhysicsSystem::~UPhysicsSystem()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));

	delete DiscreteDynamicsWorld;
	delete ConstraintSolver;
	delete BroadphaseInterface;
	delete CollisionDispatcher;
	delete DefaultCollisionConfiguration;
}

void UPhysicsSystem::Create()
{
	GetApplication()->OnUpdateEvent.Add(this, &This::Update);
	
	CreateEmptyDynamicsWorld();

	Super::Create();
}

void UPhysicsSystem::Update(float deltaTime)
{
	if (DiscreteDynamicsWorld)
	{
		DiscreteDynamicsWorld->stepSimulation(deltaTime);
	}
}

void UPhysicsSystem::RegisterComponent(UBoxCollisionComponent* collisionComponent)
{
	if (!collisionComponent)
		return;

	if (collisionComponent->bIsDynamic)
		collisionComponent->CalculeLocalInertia();

	CollisionShapes.push_back(collisionComponent->Shape);
	btRigidBody* rigidBody = collisionComponent->CreateRigidBody();

	DiscreteDynamicsWorld->addRigidBody(rigidBody);
}

void UPhysicsSystem::CreateEmptyDynamicsWorld()
{
	DefaultCollisionConfiguration = new btDefaultCollisionConfiguration();
	CollisionDispatcher = new btCollisionDispatcher(DefaultCollisionConfiguration);
	BroadphaseInterface = new btDbvtBroadphase();

	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	ConstraintSolver = sol;

	DiscreteDynamicsWorld = new btDiscreteDynamicsWorld(CollisionDispatcher, BroadphaseInterface, ConstraintSolver, DefaultCollisionConfiguration);

	DiscreteDynamicsWorld->setGravity(gravity);
}

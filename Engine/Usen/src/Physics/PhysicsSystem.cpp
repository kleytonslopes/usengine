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
#include "Physics/PhysicsDebug.hpp"
#include "Runtime/Application.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/BoxCollisionComponent.hpp"


DEFAULT_BODY(UPhysicsSystem)

void UPhysicsSystem::Construct()
{
	Super::Construct();
	PhysicsDebug = new UPhysicsDebug();
	PhysicsDebug->Application = GetApplication();
	bCanUpdate = false;
}

void UPhysicsSystem::PostConstruct()
{
	CreateEmptyDynamicsWorld();

	btBoxShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.0), btScalar(0.1)));
	btVector3 localInertia(0, 0, 0);
	CollisionShapes.push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, -0.1));

	groundShape->calculateLocalInertia(0.f, localInertia);
	
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo cInfo(0.f, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(cInfo);
	//body->setUserIndex(-1);
	DiscreteDynamicsWorld->addRigidBody(body);
	
	Super::PostConstruct();
}

void UPhysicsSystem::Update(float deltaTime)
{
	if (DiscreteDynamicsWorld)
	{
		DiscreteDynamicsWorld->stepSimulation(deltaTime);
		DiscreteDynamicsWorld->debugDrawWorld();
	}
}

void UPhysicsSystem::Destroy()
{
	delete PhysicsDebug;

	if (TypedConstraint)
	{
		RigidBody->forceActivationState(SavedState);
		RigidBody->activate();
		DiscreteDynamicsWorld->removeConstraint(TypedConstraint);
		delete TypedConstraint;
		TypedConstraint = 0;
		RigidBody = 0;
	}

	if (CollisionDispatcher)
	{
		int i;
		for (i = DiscreteDynamicsWorld->getNumConstraints() - 1; i >= 0; i--)
		{
			DiscreteDynamicsWorld->removeConstraint(DiscreteDynamicsWorld->getConstraint(i));
		}
		for (i = DiscreteDynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = DiscreteDynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			DiscreteDynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}

	}

	for (int j = 0; j < CollisionShapes.size(); j++)
	{
		btCollisionShape* shape = CollisionShapes[j];
		delete shape;
	}
	CollisionShapes.clear();

	delete DiscreteDynamicsWorld;
	DiscreteDynamicsWorld = 0;

	delete ConstraintSolver;
	ConstraintSolver = 0;

	delete BroadphaseInterface;
	BroadphaseInterface = 0;

	delete CollisionDispatcher;
	CollisionDispatcher = 0;

	delete DefaultCollisionConfiguration;
	DefaultCollisionConfiguration = 0;
}

void UPhysicsSystem::RegisterComponent(UBoxCollisionComponent* collisionComponent)
{
	if (!collisionComponent)
		return;

	CollisionShapes.push_back(collisionComponent->Shape);

	if (collisionComponent->bIsDynamic)
		collisionComponent->CalculeLocalInertia();

	/*CollisionShapes.push_back(collisionComponent->Shape);*/
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
	DiscreteDynamicsWorld->setDebugDrawer(PhysicsDebug);
	DiscreteDynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	DiscreteDynamicsWorld->setGravity(gravity);
}

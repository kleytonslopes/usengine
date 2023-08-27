/*********************************************************************
 *   File: PhysicsSystemPhysX.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Physics/PhysicsSystemPhysX.hpp"

DEFAULT_BODY(UPhysicsSystemPhysX)

void UPhysicsSystemPhysX::Construct()
{
	Super::Construct();

	bCanUpdate = true;

	Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, DefaultAllocatorCallback, DefaultErrorCallback);
	if (!Foundation)
		FException::RuntimeError("PxFoundation creation Failed!");

	Pvd = PxCreatePvd(*Foundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	Pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
	TolerancesScale.length = 100;
	TolerancesScale.speed = 981;

	Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *Foundation, TolerancesScale, true, Pvd);
	physx::PxSceneDesc sceneDesc(Physics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.f, -10.f, 0.f);
	Dispatcher = physx::PxDefaultCpuDispatcherCreate(2);// 2 Thread
	sceneDesc.cpuDispatcher = Dispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	Scene = Physics->createScene(sceneDesc);

	physx::PxPvdSceneClient* pvdClient = Scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	// Create Simulation
	Material = Physics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 99), *Material);
	Scene->addActor(*groundPlane);

	float halfExtent = 0.5f;
	physx::PxU32 size = 30;
	physx::PxTransform t(physx::PxVec3(0));
	/** 
	physx::PxShape* shape = Physics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *Material);
	for (physx::PxU32 i = 0; i < size; i++)
	{
		for (physx::PxU32 j = 0; j < size; j++)
		{
			physx::PxTransform local(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2), 0) * halfExtent);
			physx::PxRigidDynamic* body = Physics->createRigidDynamic(t.transform(local));
			body->attachShape(*shape);
			physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			Scene->addActor(*body);
		}
	}
	shape->release();
	*/

	physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	physx::PxTransform local(physx::PxVec3(physx::PxReal(2) - physx::PxReal(size), physx::PxReal(2), 2) * halfExtent);
	physx::PxRigidDynamic* body = Physics->createRigidDynamic(t.transform(local));
	physx::PxShape* aCapsuleShape = physx::PxRigidActorExt::createExclusiveShape(*body,	physx::PxCapsuleGeometry(physx::PxReal(2), physx::PxReal(4)), *Material);
	aCapsuleShape->setLocalPose(relativePose);
	Scene->addActor(*body);

	aCapsuleShape->release();

}

void UPhysicsSystemPhysX::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Scene->simulate(deltaTime);
	Scene->fetchResults(true);
}

void UPhysicsSystemPhysX::Destroy()
{
	Super::Destroy();

	//Pvd->release();
	//Material->release();
	//Scene->release();
	//Dispatcher->release();
	Physics->release();
	Foundation->release();
}

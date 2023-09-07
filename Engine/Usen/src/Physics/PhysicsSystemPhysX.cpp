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
	//sceneDesc.gravity = physx::PxVec3(0.f, -10.f, 0.f);
	//sceneDesc.gravity = physx::PxVec3(0.f, -10.f, 0.f);
	Dispatcher = physx::PxDefaultCpuDispatcherCreate(2);// 2 Thread
	sceneDesc.cpuDispatcher = Dispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	Scene = Physics->createScene(sceneDesc);
	Scene->setGravity(physx::PxVec3(0.f, GravityScale, 0.f ));

	physx::PxPvdSceneClient* pvdClient = Scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	// Create Simulation
	Material = Physics->createMaterial(0.0f, 0.0f, 0.0f);
	
	//{ //center Sphere

	//	physx::PxTransform centerTransform(physx::PxVec3(0));
	//	physx::PxShape* shapeSphere = Physics->createShape(physx::PxSphereGeometry(1.0f), *Material);
	//	physx::PxRigidStatic* center = physx::PxCreateStatic(*Physics, centerTransform, *shapeSphere);
	//	Scene->addActor(*center);
	//}

	//{ // Up Sphere
	//	physx::PxTransform upLocation(physx::PxVec3(0, 10, 0));
	//	physx::PxShape* shapeSphere = Physics->createShape(physx::PxSphereGeometry(1.0f), *Material);
	//	physx::PxRigidStatic* center = physx::PxCreateStatic(*Physics, upLocation, *shapeSphere);
	//	Scene->addActor(*center);
	//}

	//{ // Fwd Sphere
	//	physx::PxTransform upLocation(physx::PxVec3(0, 0, -5));
	//	physx::PxShape* shapeSphere = Physics->createShape(physx::PxSphereGeometry(1.0f), *Material);
	//	physx::PxRigidStatic* center = physx::PxCreateStatic(*Physics, upLocation, *shapeSphere);
	//	Scene->addActor(*center);
	//}




	//float halfExtent = 1.5f;
	//physx::PxU32 size = 50;
	//physx::PxTransform t(physx::PxVec3(0));

	//physx::PxShape* shape = Physics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *Material);
	//for (physx::PxU32 i = 0; i < size; i++)
	//{
	//	for (physx::PxU32 j = 0; j < size; j++)
	//	{
	//		physx::PxTransform local(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2), 0) * halfExtent);
	//		physx::PxRigidDynamic* body = Physics->createRigidDynamic(t.transform(local));
	//		body->attachShape(*shape);
	//		physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
	//		Scene->addActor(*body);
	//	}
	//}
	//shape->release();


	//physx::PxTransform t(physx::PxVec3(0));
	//physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	//physx::PxTransform local(physx::PxVec3(physx::PxReal(0), physx::PxReal(10), physx::PxReal(0)));
	//physx::PxRigidDynamic* body = Physics->createRigidDynamic(t.transform(local));
	//physx::PxShape* aCapsuleShape = physx::PxRigidActorExt::createExclusiveShape(*body, physx::PxCapsuleGeometry(physx::PxReal(2), physx::PxReal(2)), *Material);
	//aCapsuleShape->setLocalPose(relativePose);
	//Scene->addActor(*body);

	//aCapsuleShape->release();

	/*Controller*/
	ControllerManager = PxCreateControllerManager(*Scene);
	physx::PxCapsuleControllerDesc desc;
	desc.height = 2.f;
	desc.scaleCoeff = 1.f;
	desc.volumeGrowth = 1.9f;
	desc.nonWalkableMode = physx::PxControllerNonWalkableMode::ePREVENT_CLIMBING;
	desc.radius = 2.f;
	desc.contactOffset = 0.05f;
	desc.stepOffset = 0.01f;
	desc.material = Material;


	//Controller = ControllerManager->createController(desc);
}

void UPhysicsSystemPhysX::PostConstruct()
{
	Super::PostConstruct();

	//Controller = ControllerManager->getController(0);
}


void UPhysicsSystemPhysX::Destroy()
{
	Super::Destroy();

	///Pvd->release();
	///Material->release();
	///Scene->release();
	///Dispatcher->release();

	ControllerManager->release();
	Scene->release();
	Physics->release();

	Foundation->release();
}

void UPhysicsSystemPhysX::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Scene->simulate(deltaTime);
	Scene->fetchResults(true);
}

physx::PxRigidDynamic* UPhysicsSystemPhysX::CreateRigidDynamic(const FPhysicsShapeInitialize& physicsShapeInitialize, AFTransform transform)
{
	physx::PxTransform local(physx::PxVec3(physx::PxReal(transform.GetLocation().x), physx::PxReal(transform.GetLocation().y), transform.GetLocation().z));
	physx::PxTransform zeroTransform(physx::PxVec3(0));
	return Physics->createRigidDynamic(zeroTransform.transform(local));
}

physx::PxRigidStatic* UPhysicsSystemPhysX::CreateRigidStatic(const FPhysicsShapeInitialize& physicsShapeInitialize, AFTransform transform)
{
	physx::PxShape* shape = CreateShapeStatic(physicsShapeInitialize);

	physx::PxTransform local(physx::PxVec3(physx::PxReal(transform.GetLocation().x), physx::PxReal(transform.GetLocation().y), transform.GetLocation().z));
	physx::PxTransform zeroTransform(physx::PxVec3(0));
	physx::PxRigidStatic* body = physx::PxCreateStatic(*Physics, zeroTransform.transform(local), *shape);
	Scene->addActor(*body);

	return body;
}

physx::PxShape* UPhysicsSystemPhysX::CreateShape(physx::PxRigidDynamic* body, FPhysicsShapeInitialize physicsShapeInitialize)
{
	switch (physicsShapeInitialize.Shape)
	{
	case EShapeForm::ESF_Box:
		return CreateShapeBox(body, physicsShapeInitialize);
	default:
		return nullptr;
	}
}

physx::PxShape* UPhysicsSystemPhysX::CreateShapeStatic(FPhysicsShapeInitialize physicsShapeInitialize)
{
	switch (physicsShapeInitialize.Shape)
	{
	case EShapeForm::ESF_Box:
		return CreateShapeBox(physicsShapeInitialize);
	default:
		return nullptr;
	}
}


physx::PxShape* UPhysicsSystemPhysX::CreateShapeBox(physx::PxRigidDynamic* body, FPhysicsShapeInitialize physicsShapeInitialize)
{
	physx::PxShape* shape = Physics->createShape(physx::PxBoxGeometry(physx::PxReal(physicsShapeInitialize.HalfHeightY), physx::PxReal(physicsShapeInitialize.HalfHeightZ), physx::PxReal(physicsShapeInitialize.HalfHeightX)), *Material);

	body->attachShape(*shape);
	if (physicsShapeInitialize.Mass <= 0.f)
		physicsShapeInitialize.Mass = 1.f;
	physx::PxRigidBodyExt::updateMassAndInertia(*body, physx::PxReal(physicsShapeInitialize.Mass));
	Scene->addActor(*body);

	shape->release();
	return shape;
}

physx::PxShape* UPhysicsSystemPhysX::CreateShapeBox(FPhysicsShapeInitialize physicsShapeInitialize)
{
	return Physics->createShape(physx::PxBoxGeometry(physx::PxReal(physicsShapeInitialize.HalfHeightY), physx::PxReal(physicsShapeInitialize.HalfHeightZ), physx::PxReal(physicsShapeInitialize.HalfHeightX)), *Material);
}

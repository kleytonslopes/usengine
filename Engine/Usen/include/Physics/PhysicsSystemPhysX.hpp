/*********************************************************************
 *   File: PhysicsSystemPhysX.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_PHYSICS_SYSTEM_PHYS_X_HPP
#define	US_PHYSICS_SYSTEM_PHYS_X_HPP


#include "Base/Class.hpp"
#include "Physics/PhysicsShapeInitialize.hpp"
#include "PhysicsSystemPhysX-generated.hpp"

class UPhysicsSystemPhysX : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	physx::PxDefaultAllocator DefaultAllocatorCallback;
	physx::PxDefaultErrorCallback DefaultErrorCallback;
	physx::PxTolerancesScale TolerancesScale;

	physx::PxFoundation* Foundation = NULL;
	physx::PxPhysics* Physics = NULL;
	physx::PxDefaultCpuDispatcher* Dispatcher = NULL;
	physx::PxScene* Scene = NULL;
	physx::PxMaterial* Material = NULL;
	physx::PxPvd* Pvd = NULL;
	physx::PxControllerManager* ControllerManager = NULL;
	

	void Construct() override;
	void PostConstruct() override;
	void Update(float deltaTime) override;

	physx::PxRigidDynamic* CreateRigidDynamic(const FPhysicsShapeInitialize& physicsShapeInitialize, FTransform transform);
	physx::PxRigidStatic* CreateRigidStatic(const FPhysicsShapeInitialize& physicsShapeInitialize, FTransform transform);

	void Destroy() override;

private:
	physx::PxShape* CreateShape(physx::PxRigidDynamic* body, FPhysicsShapeInitialize physicsShapeInitialize);
	physx::PxShape* CreateShapeStatic(FPhysicsShapeInitialize physicsShapeInitialize);

	physx::PxShape* CreateShapeBox(physx::PxRigidDynamic* body, FPhysicsShapeInitialize physicsShapeInitialize);
	physx::PxShape* CreateShapeBox(FPhysicsShapeInitialize physicsShapeInitialize);
};

#endif // !US_PHYSICS_SYSTEM_PHYS_X_HPP
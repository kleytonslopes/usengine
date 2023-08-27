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

	void Construct() override;
	void Update(float deltaTime) override;

	void Destroy() override;
};

#endif // !US_PHYSICS_SYSTEM_PHYS_X_HPP
/*********************************************************************
 *   File: PhysicsSystem.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_PHYSICS_SYSTEM_HPP
#define	US_PHYSICS_SYSTEM_HPP


#include "Base/Class.hpp"
#include "PhysicsSystem-generated.hpp"

class UBoxCollisionComponent;
class UPhysicsDebug;

class UPhysicsSystem : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Update(float deltaTime) override;
	void Destroy() override;
	void RegisterComponent(UBoxCollisionComponent* collisionComponent);

private:
	btDefaultCollisionConfiguration* DefaultCollisionConfiguration{ 0 };
	btCollisionDispatcher* CollisionDispatcher{ 0 };
	btBroadphaseInterface* BroadphaseInterface{ 0 };
	btConstraintSolver* ConstraintSolver{ 0 };
	btDiscreteDynamicsWorld* DiscreteDynamicsWorld{ 0 };
	btAlignedObjectArray<btCollisionShape*> CollisionShapes;
	UPhysicsDebug* PhysicsDebug = nullptr;

	btTypedConstraint* TypedConstraint{ 0 };
	btRigidBody* RigidBody{ 0 };

	int SavedState;

	btVector3 gravity{ 0.f, 0.f, -2.f };

	void CreateEmptyDynamicsWorld();
};

#endif // !US_PHYSICS_SYSTEM_HPP
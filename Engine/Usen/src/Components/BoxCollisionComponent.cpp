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
#include "Physics/PhysicsSystemPhysX.hpp"
#include "Mesh/Mesh.hpp"

DEFAULT_BODY(UBoxCollisionComponent);

void UBoxCollisionComponent::Construct()
{
	Super::Construct();

	if (Parent)
	{
		AMesh* meshParent = Cast<AMesh*>(Parent);
		if (meshParent)
		{
			const FVector boundBox = meshParent->GetBoundBox();
			Shape = CreateBoxShape(boundBox);
		}
		else
			Shape = CreateBoxShape(FVector{ 1.f, 1.f, 1.f });
	}
	else
		Shape = CreateBoxShape(FVector{ 1.f, 1.f, 1.f });
}

void UBoxCollisionComponent::PostConstruct()
{
	PhysicsShapeInitialize.InitializeBox(BoundBox.x, BoundBox.y, BoundBox.z);
	PhysicsShapeInitialize.Mass = Mass;

	Super::PostConstruct();

	GetPhysicsSystem()->RegisterComponent(this);
	/*ShapeX = GetPhysicsSystemPhysX()->CreateShape(BodyDynamic, physicsShapeInitialize);*/
}

void UBoxCollisionComponent::Destroy()
{
	Super::Destroy();
}

void UBoxCollisionComponent::CalculeLocalInertia()
{
	if (Shape)
		Shape->calculateLocalInertia(Mass, LocalInertia);
}

//void UBoxCollisionComponent::SetBoundBox(const FVector& boundBox)
//{
//	if (Shape)
//	{
//		Shape->setImplicitShapeDimensions(btVector3{ boundBox.x, boundBox.y, boundBox.z});
//	}
//}

btRigidBody* UBoxCollisionComponent::CreateRigidBody()
{
	if (!bCanCollider)
		return nullptr;

	btDefaultMotionState* myMotionState = new btDefaultMotionState(Transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(Mass, myMotionState, Shape, LocalInertia);
	Body = new btRigidBody(rbInfo);

	if (IsDynamic())
		Body->setCollisionFlags(Body->getCollisionFlags() | btCollisionObject::CF_DYNAMIC_OBJECT);
	else
		Body->setCollisionFlags(Body->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);

	return Body;
}

btCollisionObject* UBoxCollisionComponent::CreateCollisionObject()
{
	if (!bCanCollider)
		return nullptr;

	CollisionObject = new btCollisionObject();

	CollisionObject->setWorldTransform(Transform);
	CollisionObject->setCollisionShape(Shape);

	if (IsDynamic())
		CollisionObject->setCollisionFlags(CollisionObject->getCollisionFlags() | btCollisionObject::CF_CHARACTER_OBJECT);
	else
		CollisionObject->setCollisionFlags(CollisionObject->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);

	return CollisionObject;
}

btBoxShape* UBoxCollisionComponent::CreateBoxShape(const FVector& boxBound)
{
	if (!bCanCollider)
		return nullptr;

	btBoxShape* box = new btBoxShape(btVector3(btScalar(boxBound.x), btScalar(boxBound.y), btScalar(boxBound.z)));

	return box;
}

// FVector UBoxCollisionComponent::GetComponentLocation()
// {
// 	btVector3 scalLocation = Shape->getLocalScaling();

// 	return GetLocationCalculated(scalLocation);
// }
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

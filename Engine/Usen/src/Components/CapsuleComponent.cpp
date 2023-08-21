/*********************************************************************
 *   File: CapsuleComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Components/CapsuleComponent.hpp"
#include "Mesh/Mesh.hpp"

DEFAULT_BODY(UCapsuleComponent)

void UCapsuleComponent::Construct()
{
	Super::Construct();

	CollisionObjectType = ECO_Character;
	bIsDynamic = true;
	bCanUpdate = true;
	if (Parent)
	{
		AMesh* meshParent = Cast<AMesh*>(Parent);
		if (meshParent)
		{
			Shape = CreateCapsuleShape();// new btBoxShape(btVector3{ boundBox.x, boundBox.y, boundBox.z });
		}
		else
			Shape = CreateCapsuleShape();// new btBoxShape(btVector3{ 1, 1, 1 });
	}
	else
		Shape = CreateCapsuleShape();//new btBoxShape(btVector3{ 1, 1, 1 });
}

void UCapsuleComponent::PostConstruct()
{
	Super::PostConstruct();

	GetPhysicsSystem()->RegisterComponent(this);
}

void UCapsuleComponent::Initialize()
{
	Super::Initialize();
}

void UCapsuleComponent::Destroy()
{
	Super::Destroy();
}

void UCapsuleComponent::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Body)
	{
		//Body->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
		//btTransform transform = Body->getWorldTransform();
		//btQuaternion quat = transform.getRotation();
		//quat.setZ(90.f);
		//quat.setY(90.f);


		//transform.setRotation(quat);
		//Body->setWorldTransform(transform);
	}
}

void UCapsuleComponent::CalculeLocalInertia()
{
	if(Shape)
		Shape->calculateLocalInertia(Mass, LocalInertia);
}

btRigidBody* UCapsuleComponent::CreateRigidBody()
{
	if (!bCanCollider)
		return nullptr;

	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo rbInfo(Mass, motionState, Shape, LocalInertia);
	
	Body = new btRigidBody(rbInfo);
	Body->setCollisionFlags(Body->getCollisionFlags() | CollisionObjectType);// btCollisionObject::CF_KINEMATIC_OBJECT);
	Body->setActivationState(DISABLE_DEACTIVATION);
	Body->setAngularFactor(btVector3(0.0f, 0.0f, 0.0f));

	btTransform transform;
	Body->getMotionState()->getWorldTransform(transform);
	transform.setRotation(btQuaternion(0, -90, 0));
	Body->setWorldTransform(transform);
	return Body;
}

btCapsuleShape* UCapsuleComponent::CreateCapsuleShape()
{
	if (!bCanCollider)
		return nullptr;

	Shape = new btCapsuleShape(Radius, Height);
	return Shape;
}

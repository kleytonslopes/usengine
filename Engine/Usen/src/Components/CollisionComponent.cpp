/*********************************************************************
 *   File: CollisionComponent.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Components/CollisionComponent.hpp"
#include "Actors/Actor.hpp"

DEFAULT_BODY(UCollisionComponent)

void UCollisionComponent::Construct()
{
	Super::Construct();

	bCanUpdate = true;
	DefaultMass = Mass;
}

void UCollisionComponent::PostConstruct()
{
	Super::PostConstruct();

	if (!bIsDynamic)
		Mass = 0.f;

	FTransform trasnform = GetParentTransform();

	Transform.setIdentity();
	SetTransform(trasnform);
}

void UCollisionComponent::Initialize()
{
	Super::Initialize();

	if (Parent)
	{
		AActor* pActor = Cast<AActor*>(Parent);
		if (pActor && Body)
		{
			FTransform transform = pActor->GetTransform();
			btTransform transf;
			transf.setOrigin(btVector3(transform.Location.x, transform.Location.y, transform.Location.z));
			transf.setRotation(btQuaternion(transform.Rotation.x, transform.Rotation.y, transform.Rotation.z));
		}
	}
}

void UCollisionComponent::Update(float deltaTime)
{
	Super::Update(deltaTime);

	UpdateParentTransform();
}

void UCollisionComponent::SetIsDynamic(const bool& isDynamic)
{
	if (isDynamic)
	{
		bIsDynamic = true;
		Mass = DefaultMass;
	}
	else
	{
		bIsDynamic = false;
		Mass = 0.f;
	}
}

void UCollisionComponent::SetCanCollider(const bool& canCollider)
{
	bCanCollider = canCollider;
}

FVector UCollisionComponent::GetComponentLocation()
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	if (Body && bIsDynamic)
	{
		btTransform transform;

		Body->getMotionState()->getWorldTransform(transform);

		x = float(Transform.getOrigin().getX());
		y = float(Transform.getOrigin().getY());
		z = float(Transform.getOrigin().getZ());
	}
	else
	{
		AActor* parentActor = GetParent<AActor>();
		if (parentActor)
		{
			const FVector location = parentActor->GetLocation();

			x = location.x;
			y = location.y;
			z = location.z;
		}
	}

	return FVector{ x, y, z };
}

FVector UCollisionComponent::GetComponentRotation()
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	if (Body && bIsDynamic)
	{
		btTransform transform;

		Body->getMotionState()->getWorldTransform(transform);

		x = float(transform.getRotation().getX());
		y = float(transform.getRotation().getY());
		z = float(transform.getRotation().getZ());
	}
	else
	{
		AActor* parentActor = GetParent<AActor>();
		if (parentActor)
		{
			const FVector rotation = parentActor->GetRotation();

			x = rotation.x;
			y = rotation.y;
			z = rotation.z;
		}
	}

	return FVector{ x, -y, z };
}

void UCollisionComponent::SetLocation(FVector& location)
{
	if (Body)
	{
		Body->getMotionState()->getWorldTransform(Transform);

		Transform.setOrigin(btVector3(location.x, location.y, location.z));

		Body->setWorldTransform(Transform);
	}
	else
	{
		Transform.setOrigin(btVector3(location.x, location.y, location.z));
	}
	/*
	
	FTransform newTransform{};

	newTransform.Location.x = location.x;
	newTransform.Location.y = location.y;
	newTransform.Location.z = location.z;

	newTransform.Rotation.x = Transform.getRotation().getX();
	newTransform.Rotation.y = Transform.getRotation().getY();
	newTransform.Rotation.z = Transform.getRotation().getZ();

	OnTransformUpdatedEvent.Broadcast(newTransform);*/
}

void UCollisionComponent::SetTransform(FTransform& transform)
{
	/*if (Body)
	{
		Body->getMotionState()->getWorldTransform(Transform);

		Transform.setOrigin(btVector3(transform.Location.x, transform.Location.y, transform.Location.z));
		Transform.setRotation(btQuaternion(transform.Rotation.x, transform.Rotation.y, transform.Rotation.z));

		Body->setWorldTransform(Transform);
	}
	else
	{
		Transform.setOrigin(btVector3(transform.Location.x, transform.Location.y, transform.Location.z));
		Transform.setRotation(btQuaternion(transform.Rotation.x, transform.Rotation.y, transform.Rotation.z));
	}*/
}

void UCollisionComponent::SetCollisionGroup(ECollisionGroup collisionGroup)
{
	CollisionGroup = collisionGroup;
}

void UCollisionComponent::SetCollisionMask(ECollisionMask collisionMask)
{
	CollisionMask = collisionMask;
}

void UCollisionComponent::UpdateParentTransform()
{
	AActor* aParent = Cast<AActor*>(Parent);
	if (aParent)
	{
		aParent->SetLocation(GetComponentLocation());
		aParent->SetRotation(GetComponentRotation());
	}
}

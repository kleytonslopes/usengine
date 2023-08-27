/*********************************************************************
 *   File: BoxCollisionComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_BOX_COLLISION_COMPONENT_HPP
#define	US_BOX_COLLISION_COMPONENT_HPP


#include "Components/CollisionComponent.hpp"
#include "BoxCollisionComponent-generated.hpp"


class UBoxCollisionComponent : public UCollisionComponent
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Destroy() override;

	void CalculeLocalInertia() override;
	//void SetBoundBox(const FVector& boundBox) override;
	btRigidBody* CreateRigidBody() override;
	btCollisionObject* CreateCollisionObject() override;
	
	//FVector GetComponentLocation() override;

	//void SetOrigin(FVector& location) override;

protected:
	btBoxShape* CreateBoxShape(const FVector& boxShape);

private:
	btBoxShape* Shape = nullptr;

	friend class UPhysicsSystem;
};

#endif // !US_BOX_COLLISION_COMPONENT_HPP
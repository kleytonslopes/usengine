/*********************************************************************
 *   File: StaticMesh.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Mesh/StaticMesh.hpp"
#include "Components/CollisionComponent.hpp"

DEFAULT_BODY(UStaticMesh)

void UStaticMesh::Construct()
{
	SetBoundBox(FVector{ 2.f, 2.f, 2.f });//parametrize

	Super::Construct();

	CollisionComponent->SetIsDynamic(false);
	
	
}

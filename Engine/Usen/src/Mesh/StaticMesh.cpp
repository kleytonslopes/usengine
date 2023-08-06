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

UStaticMesh::UStaticMesh()
{
}

UStaticMesh::~UStaticMesh()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UStaticMesh::Create()
{
	Super::Create();

	CollisionComponent->SetIsDynamic(false);
}

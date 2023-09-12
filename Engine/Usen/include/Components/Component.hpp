/*********************************************************************
 *   File: Component.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_COMPONENT_HPP
#define	US_COMPONENT_HPP


#include "Actors/Entity.hpp"
#include "Component-generated.hpp"

struct AFTransform;
class AActor;

class AComponent : public AEntity
{
	DEFAULT_BODY_GENERATED()
public:
	void SetParent(AActor* parent);

	FVector GetParentLocation();
	AFTransform GetParentTransform();

	FVector GetLocation();
	FVector GetUpVector();
	FVector GetForwardVector();
	FVector GetRightVector();

protected:
	AActor* Parent = nullptr;
	AFTransform TrasnformComponent;


	void BeginComponentSection(SeriFile& otherOut, const FString& identity);

	friend class AActor;

};

#endif // !US_COMPONENT_HPP
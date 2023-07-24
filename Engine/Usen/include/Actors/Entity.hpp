/*********************************************************************
 *   File: Entity.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ENTITY_HPP
#define	US_ENTITY_HPP


#include "Base/Class.hpp"
#include "Entity-generated.hpp"

class AEntity : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit AEntity();
	virtual ~AEntity();

	virtual void Create() { /* override */ };

	void SetOwner(AEntity* owner);

protected:
	AEntity* Owner = nullptr;

private:
	FString Id;
	void Draw(float deltaTime);

	friend class BRenderer;
};

#endif // !US_ENTITY_HPP
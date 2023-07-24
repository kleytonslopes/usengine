/*********************************************************************
 *   File: Component.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_COMPONENT_HPP
#define	US_COMPONENT_HPP


#include "Actors/Entity.hpp"
#include "Component-generated.hpp"

class AComponent : public AEntity
{
	DEFAULT_BODY_GENERATED()
public:
	explicit AComponent();
	virtual ~AComponent();

	void Create() override;
	void SetParent(AEntity* parent);

protected:
	AEntity* Parent = nullptr;

};

#endif // !US_COMPONENT_HPP
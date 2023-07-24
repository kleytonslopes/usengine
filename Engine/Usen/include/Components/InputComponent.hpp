/*********************************************************************
 *   File: InputComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_INPUT_COMPONENT_HPP
#define	US_INPUT_COMPONENT_HPP


#include "Components/Component.hpp"
#include "InputComponent-generated.hpp"

class UInputComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UInputComponent();
	virtual ~UInputComponent();

	bool IsActive() const { return true; }
private:
	bool bIsActive = false;

	void Active();
	void Deactive();

	friend class UInputManagement;
};

#endif // !US_INPUT_COMPONENT_HPP
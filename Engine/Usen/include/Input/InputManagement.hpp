/*********************************************************************
 *   File: InputManagement.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_INPUT_MANAGEMENT_HPP
#define	US_INPUT_MANAGEMENT_HPP


#include "Actors/Entity.hpp"
#include "InputManagement-generated.hpp"

class UInputComponent;

class UInputManagement : public AEntity
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UInputManagement();
	virtual ~UInputManagement();

	void SetInputComponent(UInputComponent* inputComponent);
protected:
	UInputComponent* InputComponent = nullptr;
};

#endif // !US_INPUT_MANAGEMENT_HPP
/*********************************************************************
 *   File: ApplicationEditor.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_APPLICATION_EDITOR_HPP
#define	US_APPLICATION_EDITOR_HPP


#include "Runtime/Application.hpp"
#include "ApplicationEditor-generated.hpp"

class UApplicationEditor : public UApplication
{
	DEFAULT_BODY_GENERATED()
public:

	void Construct() override;

};

#endif // !US_APPLICATION_EDITOR_HPP
/*********************************************************************
 *   File: Exception.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_EXCEPTION_HPP
#define	US_EXCEPTION_HPP

#include "Core/MinimalCore.hpp"

class FException
{
	
public:
	explicit FException();
	virtual ~FException();

	static void RuntimeError(const FString& message);
	static void InvalidArgument(const FString& message);
};

#endif // !US_EXCEPTION_HPP
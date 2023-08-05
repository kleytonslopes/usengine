/*********************************************************************
 *   File: Exception.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Exception.hpp"

FException::FException()
{
}

FException::~FException()
{
}

void FException::RuntimeError(const FString& message)
{
	FLogger::Fatal(message.c_str());
	throw std::runtime_error(message);
}

void FException::InvalidArgument(const FString& message)
{
	FLogger::Fatal(message.c_str());
	throw std::invalid_argument(message);
}

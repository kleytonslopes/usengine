/*********************************************************************
 *   File: Guid.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Guid.hpp"

#include "uuid_v4.h"

FString FGuid::NewGuid()
{
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
	UUIDv4::UUID uuid = uuidGenerator.getUUID();

	FString id = uuid.str();

	return id;
}

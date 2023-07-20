/*********************************************************************
 *   File: Guid.h
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_GUID_HPP
#define	US_GUID_HPP

#include "Core/String.hpp"

class FGuid
{
public:
	static FString NewGuid();
};

#endif // !US_GUID_HPP
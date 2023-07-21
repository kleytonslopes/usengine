/*********************************************************************
 *   File: File.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_FILE_HPP
#define	US_FILE_HPP

#include "Core/String.hpp"

struct FFile
{
	static FString Read(UCharPtr filePath);
};

#endif // !US_FILE_HPP

/*********************************************************************
 *   File: File.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_FILE_HPP
#define	US_FILE_HPP

#include "Core/MinimalCore.hpp"

class FFile
{
	
public:
	explicit FFile();
	virtual ~FFile();

	static FString Read(UCharPtr filePath);
};

#endif // !US_FILE_HPP
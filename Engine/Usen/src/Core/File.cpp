/*********************************************************************
 *   File: File.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/File.hpp"
#include <fstream>

FString FFile::Read(UCharPtr filePath)
{
	FString fileContent;
	if (std::ifstream fileStream{filePath, std::ios::in})
	{
		fileContent.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
	}
	return fileContent;
}

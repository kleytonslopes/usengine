/*********************************************************************
 *   File: Texture.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_TEXTURE_HPP
#define	US_TEXTURE_HPP


#include "Base/Class.hpp"
#include "Texture-generated.hpp"

class UTexture : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UTexture();
	virtual ~UTexture();

	UCharPtr GetPath() const { return Path.c_str(); };

protected:
	FString Path;
	FString Type;
};

#endif // !US_TEXTURE_HPP
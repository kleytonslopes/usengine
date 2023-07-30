/*********************************************************************
 *   File: Vertex.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_VERTEX_HPP
#define	US_VERTEX_HPP

#include "Core/MinimalCore.hpp"

class FVertex
{
public:
	FVector Position{};
	FVector Color{};
	FVector2 UV{};
	FVector Normals{};
	FVector Tangent{};
	FVector Bitangent{};
};

#endif // !US_VERTEX_HPP
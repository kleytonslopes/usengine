/*********************************************************************
 *   File: SerializerOperators.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SERIALIZER_OPERATORS_HPP
#define	US_SERIALIZER_OPERATORS_HPP

#include "Core/MinimalCore.hpp"

inline YAML::Emitter& operator<<(YAML::Emitter& out, const FVector& vector)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
	return out;
}

#endif // !US_SERIALIZER_OPERATORS_HPP
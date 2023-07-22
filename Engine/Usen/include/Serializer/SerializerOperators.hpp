/*********************************************************************
 *   File: SerializerOperators.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SERIALIZER_OPERATORS_HPP
#define	US_SERIALIZER_OPERATORS_HPP

#include "Core/Core.hpp"

//YAML::Emitter& operator<<(YAML::Emitter& out, const TVector<FShaderParameters>& vector)
//{
//	out << YAML::Flow;
//	out << YAML::BeginSeq;
//
//	for (const FShaderParameters& val : vector)
//	{
//		out << val.Name;
//	}
//
//	out << YAML::EndSeq;
//
//	return out;
//}


inline YAML::Emitter& operator<<(YAML::Emitter& out, const FVector& vector)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
	return out;
}

#endif // !US_SERIALIZER_OPERATORS_HPP

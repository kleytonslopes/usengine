/*********************************************************************
 *   File: SerializerTypes.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_SERIALIZER_TYPES_HPP
#define	US_SERIALIZER_TYPES_HPP

#include "Core/MinimalCore.hpp"
#include <yaml-cpp/yaml.h>

namespace us::seri::type
{
	struct FSerializerTypes
	{
		using FST_Emitter = YAML::Emitter;
		using FST_Node = YAML::Node;
	};
}

using SeriFile = us::seri::type::FSerializerTypes::FST_Emitter;
using SeriNode = us::seri::type::FSerializerTypes::FST_Node;

//enum SeriEnum
//{
//	YAML::Key           = YAML::Key,
//	YAML::Value         = YAML::Value,
//	YAML::BeginMap = YAML::BeginMap,
//	YAML::EndMap   = YAML::EndMap,
//	YAML::BeginSeq   = YAML::BeginSeq,
//	YAML::EndSeq     = YAML::EndSeq,
//	YAML::Flow          = YAML::Flow,
//};

#endif // !US_SERIALIZER_TYPES_HPP
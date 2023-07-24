/*********************************************************************
 *   File: SerializerTypes.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
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

enum SeriEnum
{
	SERI_KEY           = YAML::Key,
	SERI_VALUE         = YAML::Value,
	SERI_SECTION_BEGIN = YAML::BeginMap,
	SERI_SECTION_END   = YAML::EndMap,
	SERI_ARRAY_BEGIN   = YAML::BeginSeq,
	SERI_ARRAY_END     = YAML::EndSeq,
	SERI_LINE          = YAML::Flow,
};

#endif // !US_SERIALIZER_TYPES_HPP
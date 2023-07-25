/*********************************************************************
 *   File: SerializeConverters.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SERIALIZE_CONVERTERS_HPP
#define	US_SERIALIZE_CONVERTERS_HPP

#include "Core/MinimalCore.hpp"
#include "Renderer/ShaderParameters.hpp"

namespace YAML
{
	template<>
	struct convert<FVector>
	{
		static Node encode(const FVector& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);

			return node;
		}
		static bool decode(const Node& node, FVector& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();

			return true;
		}
	};

	template<>
	struct convert<FShaderParameters>
	{
		static Node encode(const FShaderParameters& rhs)
		{
			Node node;
			node.push_back(rhs.Name);

			return node;
		}

		static bool decode(const Node& node, FShaderParameters& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.Name = node[0].as<FString>();

			return true;
		}
	};

	template<>
	struct convert<TVector<FShaderParameters>>
	{
		static Node encode(const TVector<FShaderParameters>& rhs)
		{
			Node node;

			return node;
		}

		static bool decode(const Node& node, TVector<FShaderParameters>& rhs)
		{
			if (!node.IsSequence())
				return false;

			for (size_t i = 0; i < node.size(); i++)
			{
				FShaderParameters fsp{};
				fsp.Name = node[i].as<FString>();
				rhs.push_back(fsp);
			}

			return true;
		}
	};
}

#endif // !US_SERIALIZE_CONVERTERS_HPP
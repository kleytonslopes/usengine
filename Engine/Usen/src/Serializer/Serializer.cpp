/*********************************************************************
 *   File: Serializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializer/Serializer.hpp"
#include "Renderer/ShaderParameters.hpp"

/** Converters */
//namespace YAML
//{
//	template<>
//	struct convert<FShaderParameters>
//	{
//		static Node encode(const FShaderParameters& rhs)
//		{
//			Node node;
//			node.push_back(rhs.Name);
//
//			return node;
//		}
//
//		static bool decode(const Node& node, FShaderParameters& rhs)
//		{
//			if (!node.IsSequence() || node.size() != 3)
//				return false;
//
//			rhs.Name = node[0].as<FString>();
//
//			return true;
//		}
//	};
//
//
//}

/** ************************************************************************** */
/** ************************************************************************** */
/** ************************************************************************** */

void USerializer::Save()
{
	std::ofstream fout(filePath);
	fout << out.c_str();
}

YAML::Node USerializer::Load(const FString& filePath)
{
	std::ifstream stream(filePath);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	return YAML::Load(strStream.str());
}

void USerializer::SetFilePath(const FString& fineName)
{
	filePath = fineName;
}

void USerializer::BeginMap()
{
	out << YAML::BeginMap;
}
void USerializer::BeginMap(const FString& key)
{
	out << YAML::BeginMap;
	out << YAML::Key << key;
}
void USerializer::BeginMap(const FString& key, const FString& value)
{
	out << YAML::BeginMap;
	out << YAML::Key << key << YAML::Value << value;
}

void USerializer::BeginMap(YAML::Emitter& otherOut)
{
	otherOut << YAML::BeginMap;
}
void USerializer::BeginMap(YAML::Emitter& otherOut, const FString& key)
{
	otherOut << YAML::BeginMap;
	otherOut << YAML::Key << key;
}
void USerializer::BeginMap(YAML::Emitter& otherOut, const FString& key, const FString& value)
{
	otherOut << YAML::BeginMap;
	otherOut << YAML::Key << key << YAML::Value << value;
}

void USerializer::EndMap()
{
	out << YAML::EndMap;
}

void USerializer::EndMap(YAML::Emitter& otherOut)
{
	otherOut << YAML::EndMap;
}

void USerializer::BeginSequence()
{
	out << YAML::BeginSeq;
}
void USerializer::BeginSequence(const FString& key)
{
	out << YAML::Key << key;
	out << YAML::BeginSeq;
}
void USerializer::EndSequence()
{
	out << YAML::EndSeq;
}

void USerializer::BeginSequence(YAML::Emitter& otherOut)
{
	otherOut << YAML::BeginSeq;
}
void USerializer::BeginSequence(YAML::Emitter& otherOut, const FString& key)
{
	otherOut << YAML::Key << key;
	otherOut << YAML::BeginSeq;
}
void USerializer::EndSequence(YAML::Emitter& otherOut)
{
	otherOut << YAML::EndSeq;
}

void USerializer::Key(const FString& key)
{
	out << YAML::Key << key;
}
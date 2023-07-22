/*********************************************************************
 *   File: Serializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SERIALIZER_HPP
#define	US_SERIALIZER_HPP

#include "Core/Core.hpp"
#include "Serializer/SerializerOperators.hpp"
#include "Serializer/SerializeConverters.hpp"

struct FShaderParameters;

class USerializer
{

public:
	USerializer() = default;
	virtual ~USerializer() = default;

	virtual void Serialize() = 0;
	virtual void Serialize(YAML::Emitter& otherOut) = 0;
	virtual bool Deserialize(const FString& scenePath) = 0;

	void SetFilePath(const FString& fineName);

	void BeginMap();
	void BeginMap(const FString& key);
	void BeginMap(const FString& key, const FString& value);

	void BeginMap(YAML::Emitter& otherOut);
	void BeginMap(YAML::Emitter& otherOut, const FString& key);
	void BeginMap(YAML::Emitter& otherOut, const FString& key, const FString& value);

	void EndMap();
	void EndMap(YAML::Emitter& otherOut);

	void BeginSequence();
	void BeginSequence(const FString& key);
	void EndSequence();

	void BeginSequence(YAML::Emitter& otherOut);
	void BeginSequence(YAML::Emitter& otherOut, const FString& key);
	void EndSequence(YAML::Emitter& otherOut);

	void Key(const FString& key);
	template<typename T>
	inline void Key(const FString& key, T& value)
	{
		out << YAML::Key << key << YAML::Value << value;
	}
	
	template<typename T>
	inline void Key(YAML::Emitter& otherOut, const T& key)
	{
		otherOut << YAML::Key << key;
	}
	template<typename T>
	inline void Key(YAML::Emitter& otherOut, const FString& key, T& value)
	{
		otherOut << YAML::Key << key << YAML::Value << value;
	}

	template<typename T>
	inline T Read(const YAML::Node& node, FString key)
	{
		return node[key].as<T>();
	}

protected:
	YAML::Emitter out;
	FString filePath;

	virtual void Save();
	YAML::Node Load(const FString& filePath);
};

#endif // !US_SERIALIZER_HPP


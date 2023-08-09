/*********************************************************************
 *   File: Serializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SERIALIZER_HPP
#define	US_SERIALIZER_HPP

#include "Core/MinimalCore.hpp"
#include "Serializers/SerializerTypes.hpp"
#include "Serializers/SerializerOperators.hpp"
#include "Serializers/SerializeConverters.hpp"
#include "Serializer-generated.hpp"

class BSerializer
{
	DEFAULT_BODY_GENERATED()
public:
	explicit BSerializer();
	virtual ~BSerializer();

	void SetFilePath(const FString& fineName);

	void BeginSection();
	void BeginSection(const FString& key);
	void BeginSection(const FString& key, const FString& value);

	void BeginSection(SeriFile& otherOut);
	void BeginSection(SeriFile& otherOut, const FString& key);
	void BeginSection(SeriFile& otherOut, const FString& key, const FString& value);

	void EndSection();
	void EndSection(SeriFile& otherOut);

	void BeginArray();
	void BeginArray(const FString& key);
	void EndArray();

	void BeginArray(SeriFile& otherOut);
	void BeginArray(SeriFile& otherOut, const FString& key);
	void EndSequence(SeriFile& otherOut);

	void Key(const FString& key);
	template<typename T>
	inline void Key(const FString& key, T& value)
	{
		out << YAML::Key << key << YAML::Value << value;
	}

	template<typename T>
	inline void Key(SeriFile& otherOut, const T& key)
	{
		otherOut << YAML::Key << key;
	}

	template<typename T>
	inline void Key(SeriFile& otherOut, const FString& key, T& value)
	{
		otherOut << YAML::Key << key << YAML::Value << value;
	}

	template<typename T>
	inline T Read(const SeriNode& node, const FString& key)
	{
		return node[key].as<T>();
	}

protected:
	SeriFile out;
	FString seriFilePath;

	virtual void Save();
	SeriNode Load(const FString& filePath);

	virtual void Serialize() { /* override */ };
	virtual void Serialize(SeriFile& otherOut) { /* override */ };
	virtual bool Deserialize(const FString& scenePath) { return false; /* override */ };
};

#endif // !US_SERIALIZER_HPP
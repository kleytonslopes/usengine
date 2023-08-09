/*********************************************************************
 *   File: Serializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializers/Serializer.hpp"

BSerializer::BSerializer()
	: out{ CreateSeriFile() }
{
	Identity = "BSerializer";
}

BSerializer::~BSerializer()
{
	delete outPtr;
}

void BSerializer::Save()
{
	std::ofstream fout(seriFilePath);
	fout << out.c_str();
}

SeriFile& BSerializer::CreateSeriFile()
{
	if(!outPtr)
		outPtr = new SeriFile();

	return *outPtr;
}

SeriNode BSerializer::Load(const FString& filePath)
{
	std::ifstream stream(filePath);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	return YAML::Load(strStream.str());
}

void BSerializer::SetFilePath(const FString& fineName)
{
	seriFilePath = fineName;
}

void BSerializer::BeginSection()
{
	out << YAML::BeginMap;
}
void BSerializer::BeginSection(const FString& key)
{
	out << YAML::BeginMap;
	out << YAML::Key << key;
}
void BSerializer::BeginSection(const FString& key, const FString& value)
{
	out << YAML::BeginMap;
	out << YAML::Key << key << YAML::Value << value;
}

void BSerializer::BeginSection(SeriFile& otherOut)
{
	otherOut << YAML::BeginMap;
}
void BSerializer::BeginSection(SeriFile& otherOut, const FString& key)
{
	otherOut << YAML::BeginMap;
	otherOut << YAML::Key << key;
}
void BSerializer::BeginSection(SeriFile& otherOut, const FString& key, const FString& value)
{
	otherOut << YAML::BeginMap;
	otherOut << YAML::Key << key << YAML::Value << value;
}

void BSerializer::EndSection()
{
	out << YAML::EndMap;
}

void BSerializer::EndSection(SeriFile& otherOut)
{
	otherOut << YAML::EndMap;
}

void BSerializer::BeginArray()
{
	out << YAML::BeginSeq;
}
void BSerializer::BeginArray(const FString& key)
{
	out << YAML::Key << key;
	out << YAML::BeginSeq;
}
void BSerializer::EndArray()
{
	out << YAML::EndSeq;
}

void BSerializer::BeginArray(SeriFile& otherOut)
{
	otherOut << YAML::BeginSeq;
}
void BSerializer::BeginArray(SeriFile& otherOut, const FString& key)
{
	otherOut << YAML::Key << key;
	otherOut << YAML::BeginSeq;
}
void BSerializer::EndSequence(SeriFile& otherOut)
{
	otherOut << YAML::EndSeq;
}

void BSerializer::Key(const FString& key)
{
	out << YAML::Key << key;
}
/*********************************************************************
 *   File: Serializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializers/Serializer.hpp"

BSerializer::BSerializer()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

BSerializer::~BSerializer()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void BSerializer::Save()
{
	std::ofstream fout(filePath);
	fout << out.c_str();
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
	filePath = fineName;
}

void BSerializer::BeginSection()
{
	out << SERI_SECTION_BEGIN;
}
void BSerializer::BeginSection(const FString& key)
{
	out << SERI_SECTION_BEGIN;
	out << SERI_KEY << key;
}
void BSerializer::BeginSection(const FString& key, const FString& value)
{
	out << SERI_SECTION_BEGIN;
	out << SERI_KEY << key << YAML::Value << value;
}

void BSerializer::BeginSection(SeriFile& otherOut)
{
	otherOut << SERI_SECTION_BEGIN;
}
void BSerializer::BeginSection(SeriFile& otherOut, const FString& key)
{
	otherOut << SERI_SECTION_BEGIN;
	otherOut << SERI_KEY << key;
}
void BSerializer::BeginSection(SeriFile& otherOut, const FString& key, const FString& value)
{
	otherOut << SERI_SECTION_BEGIN;
	otherOut << SERI_KEY << key << YAML::Value << value;
}

void BSerializer::EndSection()
{
	out << SERI_SECTION_END;
}

void BSerializer::EndSection(SeriFile& otherOut)
{
	otherOut << SERI_SECTION_END;
}

void BSerializer::BeginArray()
{
	out << SERI_ARRAY_BEGIN;
}
void BSerializer::BeginArray(const FString& key)
{
	out << SERI_KEY << key;
	out << SERI_ARRAY_BEGIN;
}
void BSerializer::EndArray()
{
	out << SERI_ARRAY_END;
}

void BSerializer::BeginArray(SeriFile& otherOut)
{
	otherOut << SERI_ARRAY_BEGIN;
}
void BSerializer::BeginArray(SeriFile& otherOut, const FString& key)
{
	otherOut << SERI_KEY << key;
	otherOut << SERI_ARRAY_BEGIN;
}
void BSerializer::EndSequence(SeriFile& otherOut)
{
	otherOut << SERI_ARRAY_END;
}

void BSerializer::Key(const FString& key)
{
	out << SERI_KEY << key;
}
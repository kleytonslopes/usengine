/*********************************************************************
 *   File: EngineConfig.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Configs/EngineConfig.hpp"

FEngineConfig::FEngineConfig()
{
}

FEngineConfig::~FEngineConfig()
{
}

void FEngineConfig::LoadConfig()
{
	mINI::INIFile initFile{FText::Format(Content::ConfigsPath, FileName.c_str())};
	mINI::INIStructure ini;
	initFile.read(ini);

	for (auto const& it : ini)
	{
		auto const& section = it.first;
		auto const& collection = it.second;

		for (auto const& pit : collection )
		{
			auto const& key = pit.first;
			auto const& value = pit.second;

			ParamList[std::make_pair(section, key)] = value;
			if (section == "AxisActionBinds")
			{
				KeysParamList[stoi(value)] = key;
			}
		}
	}
	
}

void FEngineConfig::RegisterActionKey(uint32 keyCode, const FString& actionName)
{
	mINI::INIFile initFile{FText::Format(Content::ConfigsPath, FileName.c_str())};
	mINI::INIStructure ini;
	initFile.read(ini);

	ini["AxisActionBinds"][actionName.c_str()] = std::to_string(keyCode);

	initFile.write(ini, true);
}

TMap<uint32, FString>& FEngineConfig::GetKeyBinds()
{
	return KeysParamList;

}

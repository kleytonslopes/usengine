/*********************************************************************
 *   File: EngineConfig.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_ENGINE_CONFIG_HPP
#define	US_ENGINE_CONFIG_HPP

#include "Core/MinimalCore.hpp"
#define MINI_CASE_SENSITIVE
#include "mini/ini.h"
#include "EngineConfig-generated.hpp"

struct FConfigParam
{
	FString Section;
	FString Parameter;
	FString Value;
};
struct FConfigKey
{
	FString Section;
	FString Parameter;
};
struct FKeyBind
{
	FString ActionName;
	uint32 KeyCode;
};

class FEngineConfig
{
	using ParamsMap = TMap<TPair<FString, FString>, FString>;
	using KeyBindMap = TMap<uint32, FString>;

	DEFAULT_BODY_GENERATED()
public:
	explicit FEngineConfig();
	virtual ~FEngineConfig();

	void LoadConfig();
	void RegisterActionKey(uint32 keyCode, const FString& actionName);
	
	KeyBindMap& GetKeyBinds();
private:
	FString FileName{ "EngineConfig" };
	
	ParamsMap ParamList;
	KeyBindMap KeysParamList;
};

#endif // !US_ENGINE_CONFIG_HPP
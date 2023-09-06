/*********************************************************************
 *   File: Core.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CORE_HPP
#define	US_CORE_HPP

#include <yaml-cpp/yaml.h>

#include "Core/String.hpp"
#include "Core/Logger.hpp"

# define M_PI 3.14159265358979323846

inline void ULOG(ELogLevel level, const FString& message)
{
	switch (level)
	{
	case ELogLevel::ELL_FATAL:
		FLogger::Fatal(message);
		break;
	case ELogLevel::ELL_ERROR:
		FLogger::Error(message);
		break;
	case ELogLevel::ELL_WARNING:
		FLogger::Warning(message);
		break;
	case ELogLevel::ELL_INFORMATION:
		FLogger::Information(message);
		break;
	case ELogLevel::ELL_DEBUG:
		FLogger::Debug(message);
		break;
	case ELogLevel::ELL_TRACE:
		FLogger::Trace(message);
		break;
	case ELogLevel::ELL_SUCCESS:
		FLogger::Success(message);
		break;
	default:
		FLogger::Log(message);
		break;
	}
}

inline void ULOG_Trace(const FString& message)
{
	ULOG(ELogLevel::ELL_TRACE, message);
}
inline void ULOG_Warning(const FString& message)
{
	ULOG(ELogLevel::ELL_WARNING, message);
}
inline void ULOG_Error(const FString& message)
{
	ULOG(ELogLevel::ELL_ERROR, message);
}

namespace ShaderDefault
{
	const FString DEFAULT{ "default" };
	const FString SKYBOX{ "skybox" };
}

namespace Content
{
	const UCharPtr ModelFilePath{ "../../Content/Models/%s" };
	const UCharPtr ModelPath{ "../../Content/Models/%s" };
	const UCharPtr SceneFilePath{ "../../Content/Scene/%s.usscn" };
	const UCharPtr ConfigsPath{ "../../Content/Configs/%s.ini" };
	const UCharPtr FontPath{ "../../Content/Fonts/%s/%s.ttf" };
}

namespace TextureSlot
{
	const FString DIFFUSE{ "texture_diffuse" };
	const FString SPECULAR{ "texture_specular" };
	const FString NORMAL{ "texture_normal" };
	const FString HEIGHT{ "texture_height" };
}

#endif // !US_CORE_HPP
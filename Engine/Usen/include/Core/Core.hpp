/*********************************************************************
 *   File: Core.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CORE_HPP
#define	US_CORE_HPP

#define UASSERT(COND, MSG) assert(COND && MSG)

#include "Core/CommonTypes.hpp"
#include "Core/SharedPtr.hpp"
#include "Core/String.hpp"
#include "Core/Clock.hpp"
#include "Core/Logger.hpp"
#include "Core/Formatter.hpp"
#include "Core/Map.hpp"

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
	default:
		FLogger::Log(message);
		break;
	}
}

#endif // !US_CORE_HPP

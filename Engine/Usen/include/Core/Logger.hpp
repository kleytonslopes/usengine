/*********************************************************************
 *   File: Logger.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_LOGGER_HPP
#define	US_LOGGER_HPP

#include "Core/String.hpp"

enum class ELogLevel
{
	ELL_FATAL,
	ELL_ERROR,
	ELL_WARNING,
	ELL_INFORMATION,
	ELL_DEBUG,
	ELL_TRACE,
	ELL_LOG,
	ELL_SUCCESS
};

struct FLogger
{
	static void Fatal(const FString& text);
	static void Error(const FString& text);
	static void Warning(const FString& text);
	static void Information(const FString& text);
	static void Debug(const FString& text);
	static void Trace(const FString& text);
	static void Log(const FString& text);
	static void Success(const FString& text);
};

#endif // !US_LOGGER_HPP
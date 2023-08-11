/*********************************************************************
 *   File: Logger.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Logger.hpp"

void FLogger::Fatal(const FString& text)
{
	std::cout << "\033[41;1;37m>> : " << text << "\033[0m" << std::endl;
}

void FLogger::Error(const FString& text)
{
	std::cout << "\033[5;31m>> : " << text << "\033[0m" << std::endl;
}

void FLogger::Warning(const FString& text)
{
#ifdef LOG_WARNING
	std::cout << "\033[5;33m>> : " << text << "\033[0m" << std::endl;
#endif
}

void FLogger::Information(const FString& text)
{
#ifdef LOG_INFORMATION
	std::cout << "\033[5;36m>> : " << text << "\033[0m" << std::endl;
#endif
}

void FLogger::Debug(const FString& text)
{
#ifdef LOG_DEBUG
	std::cout << "\033[1;33m>> : " << text << "\033[0m" << std::endl;
#endif
}

void FLogger::Trace(const FString& text)
{
#ifdef LOG_TRACE
	std::cout << "\033[5;37m>> : " << text << "\033[0m" << std::endl;
#endif
}

void FLogger::Log(const FString& text)
{
#ifdef LOG_DEFAULT
	std::cout << "\033[1;37m>> : " << text << "\033[0m" << std::endl;
#endif
}

void FLogger::Success(const FString& text)
{
	std::cout << "\033[1;32m>> : " << text << "\033[0m" << std::endl;
}

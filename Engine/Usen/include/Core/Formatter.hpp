/*********************************************************************
 *   File: Formatter.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_FORMATTER_HPP
#define	US_FORMATTER_HPP

#include "Core/String.hpp"

namespace suformat
{
	template<typename ... Args>
	FString str_format(const FString& format, Args ... args)
	{
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1);
	}

#define TEXT(X, ...)                      \
	{                                         \
		suformat::str_format(X, ##__VA_ARGS__).c_str() \
	}
}

struct FText
{
	template<typename ... Args>
	static FString Format(const FString& format, Args ... args)
	{
		return TEXT(format, args ...);
	}

	static FString Replace(const FString& text, const FString& repl, const FString& remov)
	{
		return std::regex_replace(text, std::regex(repl), remov);
	}

	static FString Concat(FString& left, const FString& right)
	{
		return left.append(right);
	}
};

#endif // !US_FORMATTER_HPP
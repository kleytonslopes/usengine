/*********************************************************************
 *   File: String.hpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_STRING_HPP
#define	US_STRING_HPP

#include <string>
#include <regex>

using FString = std::string;
using UCharPtr = const char*;

//struct FString
//{
//	FString() = default;
//	FString(const FString& fs) = default;
//
//	FString(std::string value) : str{ value } {};
//	FString(const std::string& value) : str{ value } {};
//
//	FString& operator=(const FString& value) = default;
//
//	//FString& operator=(const std::string& value)
//	//{
//	//	this->str = value;
//	//	return *this;
//	//}
//	
//	operator std::string& () { return str; }
//	operator const std::string& () { return str; }
//
//private:
//	std::string str;
//};

//namespace std {
//
//	constexpr string& operator=(const FString& fs)
//{
//		return "fs";
//}
//}

#endif // !US_STRING_HPP


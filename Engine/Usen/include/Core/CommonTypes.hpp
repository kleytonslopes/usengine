/*********************************************************************
 *   File: CommonTypes.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_COMMON_TYPES_HPP
#define	US_COMMON_TYPES_HPP

#include <list>
#include <vector>
#include <memory>
#include <tuple>
#include <chrono>
#include <map>
#include <thread>

namespace us::types
{
	struct FCommonTypes
	{
		using UUtint8  = unsigned char;
		using UUtint16 = unsigned short int;
		using UUtint32 = unsigned int;
		using UUtint64 = unsigned long long;

		using StInt8  = signed char;
		using StInt16 = signed short int;
		using StInt32 = signed int;
		using StInt64 = signed long long;

		using Clock = std::chrono::high_resolution_clock;
		using Time = std::chrono::high_resolution_clock::time_point;
		using Seconds = std::chrono::seconds;

		using SThread = std::thread;
	};
}

/** @brief Integer unsigned range 0 to 255 */
using uint8 = us::types::FCommonTypes::UUtint8;
/* @brief Integer unsigned range 0 to 65535 */
using uint16 = us::types::FCommonTypes::UUtint16;
/* @brief Integer unsigned range 0 to 4294967295 */
using uint32 = us::types::FCommonTypes::UUtint32;
/* @brief Integer unsigned range 0 to 18446744073709551615 */
using uint64 = us::types::FCommonTypes::UUtint64;

/* @brief Integer signed range -128 to 127 */
using int8 = us::types::FCommonTypes::StInt8;
/* @brief Integer signed range -32768 to 32767 */
using int16 = us::types::FCommonTypes::StInt16;
/* @brief Integer signed range -2147483648 to 2147483647 */
using int32 = us::types::FCommonTypes::StInt32;
/* @brief Integer signed range -9223372036854775808 to 9223372036854775807 */
using int64 = us::types::FCommonTypes::StInt64;

template<class T>
using TVector = std::vector<T>;

template<class T, uint64 s>
using TArray = std::array<T, s>;

template<typename T>
using TList = std::list<T>;

template<typename K, typename T>
using TMap = std::map<K, T>;

template<typename R, typename L>
using TPair = std::pair<R, L>;

using TThread = us::types::FCommonTypes::SThread;

#endif // !US_COMMON_TYPES_HPP
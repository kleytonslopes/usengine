/*********************************************************************
 *   File: KyrnnessArch.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef KNC_ARCH_HPP
#define	KNC_ARCH_HPP

#if defined(KNC_SHARED)
	#define KN_API __declspec(dllexport)
#else
	#define KN_API
#endif

#define INLINE_STATIC inline static

#endif // !KNC_ARCH_HPP

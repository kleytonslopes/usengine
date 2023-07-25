/*********************************************************************
 *   File: Macros.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MACROS_HPP
#define	US_MACROS_HPP

#include "Core/Core.hpp"

#define DEFAULT_BODY_GENERATED_FILTER_IN(A,B,C) A##B##C
#define DEFAULT_BODY_GENERATED_FILTER(A,B,C) DEFAULT_BODY_GENERATED_FILTER_IN(A,B,C)
#define DEFAULT_BODY_GENERATED(...) DEFAULT_BODY_GENERATED_FILTER(CURRENT_CLASS_IDENTITY_FILE,_,def);

#define UASSERT(COND, MSG) \
ULOG(ELogLevel::ELL_FATAL, MSG); \
assert(COND && MSG)

#endif // !US_MACROS_HPP
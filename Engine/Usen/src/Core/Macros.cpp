/*********************************************************************
 *   File: Macros.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Macros.hpp"

#define UASSERT(COND, MSG) \
ULOG(ELogLevel::ELL_FATAL, MSG); \
assert(COND && MSG)
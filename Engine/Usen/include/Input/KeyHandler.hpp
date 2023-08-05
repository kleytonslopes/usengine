/*********************************************************************
 *   File: KeyHandler.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_KEY_HANDLER_HPP
#define	US_KEY_HANDLER_HPP

#include "Core/MinimalCore.hpp"

enum EKeyHandler : uint8
{
	KEY_NONE     = 0,
	KEY_PRESSED  = 1,
	KEY_RELEASED = 2,
};

#endif // !US_KEY_HANDLER_HPP
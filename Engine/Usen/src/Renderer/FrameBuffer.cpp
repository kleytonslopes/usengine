/*********************************************************************
 *   File: FrameBuffer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/FrameBuffer.hpp"

DEFAULT_BODY(UFrameBuffer)

void UFrameBuffer::SetFrameBufferSettings(const FFrameBufferSettings& frameBufferSettings)
{
	Settings = frameBufferSettings;
}

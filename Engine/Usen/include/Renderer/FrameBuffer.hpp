/*********************************************************************
 *   File: FrameBuffer.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_FRAME_BUFFER_HPP
#define	US_FRAME_BUFFER_HPP


#include "Base/Class.hpp"
#include "FrameBuffer-generated.hpp"

struct FFrameBufferSettings
{
	uint32 Width;
	uint32 Height;
	uint32 Samples = 1;

	bool bSwapChainTarget = false;
};

class UFrameBuffer : public BClass
{
	DEFAULT_BODY_GENERATED()
public:

	virtual FFrameBufferSettings& GetFrameBufferSettings() const { return FFrameBufferSettings{}; }
	virtual uint32 GetColorAttachment() const { return 0; }
	void SetFrameBufferSettings(const FFrameBufferSettings& frameBufferSettings);

	virtual void Bind() {/* override*/ }
	virtual void Unbind() {/* override*/ }
	virtual void DrawScreenQuad() { /* override */ }

protected:
	FFrameBufferSettings Settings;
};

#endif // !US_FRAME_BUFFER_HPP
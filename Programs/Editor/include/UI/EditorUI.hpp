/*********************************************************************
 *   File: EditorUI.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_EDITOR_UI_HPP
#define	US_EDITOR_UI_HPP


#include "Base/Class.hpp"
#include "Input/KeyHandler.hpp"
#include "EditorUI-generated.hpp"

class UEditorUI : public BClass
{
	DEFAULT_BODY_GENERATED()
public:

	void Construct() override;
	void Draw(float deltaTime);

	void OnMouseButtonEvent(uint32 keyCode, EKeyHandler keyHandler);
	void OnMouseWheelEvent(uint32 xOffset, uint32 yOffset);
	void OnMouseMovementEvent(uint32 xPos, uint32 yPos, uint32 xPosRel, uint32 yPosRel);
};

#endif // !US_EDITOR_UI_HPP
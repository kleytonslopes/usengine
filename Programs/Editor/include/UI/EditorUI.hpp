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
#include "SDL.h"
#include "EditorUI-generated.hpp"

DECLARE_FUNCTION_OneParam(FOnDrawSceneSignature, float, deltaTime);

class UEditorUI : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	FOnDrawSceneSignature OnDrawSceneEvent;

	void Construct() override;
	void PostConstruct() override;
	void Draw(float deltaTime);
	void Destroy() override;

	void OnMouseButtonEvent(uint32 keyCode, EKeyHandler keyHandler);
	void OnMouseWheelEvent(uint32 xOffset, uint32 yOffset);
	void OnMouseMovementEvent(uint32 xPos, uint32 yPos, uint32 xPosRel, uint32 yPosRel);
	void OnPollEventsEvent(SDL_Event* sEvent);

private:
	FVector2 viewportSize;
};

#endif // !US_EDITOR_UI_HPP
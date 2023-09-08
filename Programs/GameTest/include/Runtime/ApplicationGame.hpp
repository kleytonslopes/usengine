/*********************************************************************
 *   File: ApplicationGame.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_APPLICATION_EDITOR_HPP
#define	US_APPLICATION_EDITOR_HPP


#include "Runtime/Application.hpp"
#include "Input/KeyHandler.hpp"
#include "ApplicationGame-generated.hpp"

class UEditorUI;

class UApplicationGame : public UApplication
{
	DEFAULT_BODY_GENERATED()
public:

	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;
	void Destroy() override;
	void Draw(float deltaTime) override;
	void OnMouseButtonEvent(uint32 keyCode, EKeyHandler keyHandler);
protected:
	UEditorUI* UIEditor;
};

#endif // !US_APPLICATION_EDITOR_HPP
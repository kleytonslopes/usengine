/*********************************************************************
 *   File: InputComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_INPUT_COMPONENT_HPP
#define	US_INPUT_COMPONENT_HPP


#include "Components/Component.hpp"
#include "Input/KeyHandler.hpp"
#include "InputComponent-generated.hpp"

DECLARE_FUNCTION_OneParam(FOnActionHandleSignature, float, scale);
struct InputAction
{
	void* Target = nullptr;
	FString Action;
	FOnActionHandleSignature Execute;
};

class UInputComponent : public AComponent
{
	using ActionMap = TMap<FString, InputAction>;
	DEFAULT_BODY_GENERATED()
public:
	bool IsActive() const { return true; }

	template<class TObject, class Fx>
	void AddAction(const FString& action, TObject* target, EKeyHandler keyHandle, Fx&& function)
	{
		InputAction inputAction{};
		FString localAction = action;
		switch (keyHandle)
		{
		case KEY_RELEASED:
			localAction = action + "_Released";
			break;
		default:
			localAction = action + "_Pressed";
			break;
		}
		
		inputAction.Action = localAction;
		inputAction.Target = target;
		inputAction.Execute.Add(target, function);
		Actions[localAction] = inputAction;
	}
	
	void ExecuteAction(const FString& action, EKeyHandler keyHandler);
private:
	bool bIsActive = false;
	ActionMap Actions;

	void Active();
	void Deactive();

	friend class UInputManagement;
};

#endif // !US_INPUT_COMPONENT_HPP
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
DECLARE_FUNCTION(FOnVoidActionHandleSignature);

struct InputAxisAction
{
	void* Target = nullptr;
	FString Action;
	FOnActionHandleSignature Execute;
};

struct InputVoidAction
{
	void* Target = nullptr;
	FString Action;
	FOnVoidActionHandleSignature Execute;
};

class UInputComponent : public AComponent
{
	using AxisActionMap = TMap<FString, InputAxisAction>;
	using VoidActionMap = TMap<FString, InputVoidAction>;
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;

	bool IsActive() const { return true; }

	template<class TObject, class Fx>
	void AddAxisAction(const FString& action, TObject* target, EKeyHandler keyHandle, Fx&& function)
	{
		InputAxisAction inputAxisAction{};
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
		
		inputAxisAction.Action = localAction;
		inputAxisAction.Target = target;
		inputAxisAction.Execute.Add(target, function);
		AxisActions[localAction] = inputAxisAction;
	}
	bool ExecuteAxisAction(const FString& action, EKeyHandler keyHandler);

	template<class TObject, class Fx>
	void AddVoidAction(const FString& action, TObject* target, EKeyHandler keyHandle, Fx&& function)
	{
		InputVoidAction inputVoidAction{};
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

		inputVoidAction.Action = localAction;
		inputVoidAction.Target = target;
		inputVoidAction.Execute.Add(target, function);
		VoidActions[localAction] = inputVoidAction;
	}
	bool ExecuteVoidAction(const FString& action, EKeyHandler keyHandler);
private:
	bool bIsActive = false;
	AxisActionMap AxisActions;
	VoidActionMap VoidActions;

	void Active();
	void Deactive();

	friend class UInputManagement;
};

#endif // !US_INPUT_COMPONENT_HPP
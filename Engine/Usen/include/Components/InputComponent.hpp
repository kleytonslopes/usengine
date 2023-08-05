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
#include "InputComponent-generated.hpp"

DECLARE_FUNCTION_OneParam(FOnActionHandleSignature, float, scale);
struct InputAction
{
	void* Target = nullptr;
	FString Action;
	FOnActionHandleSignature onActionHandleSignature;
};

class UInputComponent : public AComponent
{
	using ActionMap = TMap<FString, InputAction>;
	DEFAULT_BODY_GENERATED()
public:
	explicit UInputComponent();
	virtual ~UInputComponent();

	bool IsActive() const { return true; }

	template<class TObject, class Fx>
	void AddAction(const FString& action, TObject* target, Fx&& function)
	{
		InputAction inputAction{};
		inputAction.Target = target;
		inputAction.onActionHandleSignature.Add(target, function);
		Actions[action] = inputAction;
	}
private:
	bool bIsActive = false;
	ActionMap Actions;

	void Active();
	void Deactive();

	friend class UInputManagement;
};

#endif // !US_INPUT_COMPONENT_HPP
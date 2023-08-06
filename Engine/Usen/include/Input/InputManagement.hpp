/*********************************************************************
 *   File: InputManagement.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_INPUT_MANAGEMENT_HPP
#define	US_INPUT_MANAGEMENT_HPP


#include "Actors/Entity.hpp"
#include "Components/InputComponent.hpp"
#include "Input/KeyHandler.hpp"
#include "InputManagement-generated.hpp"

class UInputComponent;

struct FKeyMap
{
	uint32 KeyCode;
	FString ActionName;
	bool bIsPressed = false;
};
struct FAction
{
	FString Name;
	TVector<FKeyMap> Inputs;
	void AddInput(uint32 keyCode, FString actionName)
	{
		Inputs.push_back(FKeyMap{ keyCode, actionName });
	}
};

class UInputManagement : public AEntity
{
	using ActionMap = TMap<FString, FAction>;
	using KeyMap = TMap<uint32, FKeyMap>;

	DEFAULT_BODY_GENERATED()
public:
	explicit UInputManagement();
	virtual ~UInputManagement();

	void Create() override;
	void Update(float deltaTime) override;
	void SetInputComponent(UInputComponent* inputComponent);
	void OnKeyEvent(uint32 keyCode, EKeyHandler keyHandler);

	template<class TObject, class Fx>
	void AddAction(const FString& action, TObject* target, EKeyHandler keyHandler, Fx&& function)
	{
		if (!InputComponent)
			FException::RuntimeError("Input component not Initialized!");

		InputComponent->AddAction(action, target, keyHandler, function);
	}

	void RegisterAction(uint32 keyCode, const FString& actionName);

protected:
	UInputComponent* InputComponent = nullptr;
	ActionMap Actions;
	KeyMap RegisteredKeys;

};

#endif // !US_INPUT_MANAGEMENT_HPP

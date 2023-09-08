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
	using AxisActionMap = TMap<FString, FAction>;
	using KeyMap = TMap<uint32, FKeyMap>;

	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Update(float deltaTime) override;
	void SetInputComponent(UInputComponent* inputComponent);
	void OnKeyEvent(uint32 keyCode, EKeyHandler keyHandler);
	void OnMouseMovementEvent(uint32 xPos, uint32 yPos, uint32 xPosRel, uint32 yPosRel);

	template<class TObject, class Fx>
	void AddAxisAction(const FString& action, TObject* target, EKeyHandler keyHandler, Fx&& function)
	{
		if (!InputComponent)
			FException::RuntimeError("Input component not Initialized!");

		InputComponent->AddAxisAction(action, target, keyHandler, function);
	}

	template<class TObject, class Fx>
	void AddVoidAction(const FString& action, TObject* target, EKeyHandler keyHandler, Fx&& function)
	{
		if (!InputComponent)
			FException::RuntimeError("Input component not Initialized!");

		InputComponent->AddVoidAction(action, target, keyHandler, function);
	}

	void RegisterAction(uint32 keyCode, const FString& actionName);

protected:
	UInputComponent* InputComponent = nullptr;
	AxisActionMap AxisActions;
	KeyMap RegisteredKeys;

};

#endif // !US_INPUT_MANAGEMENT_HPP

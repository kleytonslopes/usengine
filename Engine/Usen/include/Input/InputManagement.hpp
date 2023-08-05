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
#include "InputManagement-generated.hpp"

class UInputComponent;

struct FInputAction
{
	uint32 KeyCode;
	float Scale = 1.f;
};
struct FAction
{
	FString Name;
	TVector<FInputAction> Inputs;
	void AddInput(uint32 keyCode, float scale)
	{
		Inputs.push_back(FInputAction{ keyCode, scale });
	}
};

class UInputManagement : public AEntity
{
	using ActionMap = TMap<FString, FAction>;
	DEFAULT_BODY_GENERATED()
public:
	explicit UInputManagement();
	virtual ~UInputManagement();

	void SetInputComponent(UInputComponent* inputComponent);

	template<class TObject, class Fx>
	void AddAction(const FString& action, TObject* target, Fx&& function)
	{
		if (!InputComponent)
			FException::RuntimeError("Input component not Initialized!");

		InputComponent->AddAction(action, target, function);
	}
	
	void RegisterAction(const FString& actionName, uint32 keyCode, float scale);

protected:
	UInputComponent* InputComponent = nullptr;
	ActionMap Actions;

};

#endif // !US_INPUT_MANAGEMENT_HPP

//template<class TObject, class Fx>
//inline void UInputManagement::AddAction(const FString& action, TObject* target, Fx&& function)
//{
//
//}
